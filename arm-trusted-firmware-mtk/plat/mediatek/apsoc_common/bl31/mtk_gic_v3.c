// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright (c) 2021, MediaTek Inc. All rights reserved.
 */

#include <assert.h>
#include <lib/mmio.h>
#include <common/bl_common.h>
#include <common/debug.h>
#include <drivers/arm/gicv3.h>
#include <bl31/interrupt_mgmt.h>
#include "../drivers/arm/gic/v3/gicv3_private.h"
#include <plat_private.h>
#include <plat/common/platform.h>
#include <platform_def.h>
#include <stdint.h>
#include <stdio.h>
#include "mtk_gic_v3.h"

static uintptr_t rdistif_base_addrs[PLATFORM_CORE_COUNT];
static uint32_t rdist_has_saved[PLATFORM_CORE_COUNT];

/* we save and restore the GICv3 context on system suspend */
static gicv3_dist_ctx_t dist_ctx;

static unsigned int mt_mpidr_to_core_pos(u_register_t mpidr)
{
	return plat_core_pos_by_mpidr(mpidr);
}

gicv3_driver_data_t mt_gicv3_data = {
	.gicd_base = PLAT_ARM_GICD_BASE,
	.gicr_base = PLAT_ARM_GICR_BASE,
	.rdistif_num = PLATFORM_CORE_COUNT,
	.rdistif_base_addrs = rdistif_base_addrs,
	.mpidr_to_core_pos = mt_mpidr_to_core_pos,
};

struct gic_chip_data {
	unsigned int saved_group;
	unsigned int saved_enable;
	unsigned int saved_conf0;
	unsigned int saved_conf1;
	unsigned int saved_grpmod;
};

static struct gic_chip_data gic_data;

void mt_gic_rdistif_init(void)
{
	unsigned int proc_num;
	uintptr_t gicr_base;

	proc_num = plat_my_core_pos();
	gicr_base = gicv3_driver_data->rdistif_base_addrs[proc_num];

	/* set all SGI/PPI as non-secure GROUP1 by default */
	mmio_write_32(gicr_base + GICR_IGROUPR0, ~0U);
	mmio_write_32(gicr_base + GICR_IGRPMODR0, 0x0);
}

void mt_gic_cpuif_enable(void)
{
	gicv3_cpuif_enable(plat_my_core_pos());
}

void mt_gic_cpuif_disable(void)
{
	gicv3_cpuif_disable(plat_my_core_pos());
}

void mt_gic_distif_save(void)
{
	gicv3_distif_save(&dist_ctx);
}

void mt_gic_distif_restore(void)
{
	gicv3_distif_init_restore(&dist_ctx);
}

void mt_gic_rdistif_save(void)
{
	unsigned int proc_num;
	uintptr_t gicr_base;

	proc_num = plat_my_core_pos();
	gicr_base = gicv3_driver_data->rdistif_base_addrs[proc_num];

	gic_data.saved_group = mmio_read_32(gicr_base + GICR_IGROUPR0);
	gic_data.saved_enable = mmio_read_32(gicr_base + GICR_ISENABLER0);
	gic_data.saved_conf0 = mmio_read_32(gicr_base + GICR_ICFGR0);
	gic_data.saved_conf1 = mmio_read_32(gicr_base + GICR_ICFGR1);
	gic_data.saved_grpmod = mmio_read_32(gicr_base + GICR_IGRPMODR0);

	rdist_has_saved[proc_num] = 1;
}

void mt_gic_rdistif_restore(void)
{
	unsigned int proc_num;
	uintptr_t gicr_base;

	proc_num = plat_my_core_pos();
	if (rdist_has_saved[proc_num] == 1) {
		gicr_base = gicv3_driver_data->rdistif_base_addrs[proc_num];
		mmio_write_32(gicr_base + GICR_IGROUPR0, gic_data.saved_group);
		mmio_write_32(gicr_base + GICR_ISENABLER0,
			      gic_data.saved_enable);
		mmio_write_32(gicr_base + GICR_ICFGR0, gic_data.saved_conf0);
		mmio_write_32(gicr_base + GICR_ICFGR1, gic_data.saved_conf1);
		mmio_write_32(gicr_base + GICR_IGRPMODR0,
			      gic_data.saved_grpmod);
	}
}

static void mt_gic_sync_high_polarity(void)
{
#ifdef INT_POL_CTL0
	unsigned int reg_idx, value;

	for (reg_idx = 0; reg_idx < NR_INT_POL_CTL; reg_idx++) {
		value = mmio_read_32(INT_POL_CTL0 + (reg_idx * 4));
		value |= 0xFFFFFFFF;
		mmio_write_32((INT_POL_CTL0 + (reg_idx * 4)), value);
	}
#endif
}

static void mt_gic_clear_sec_pol_ctl_en(void)
{
#ifdef SEC_POL_CTL_EN0
	unsigned int i;

	for (i = 0; i < NR_INT_POL_CTL; i++)
		mmio_write_32((SEC_POL_CTL_EN0 + (i * 4)), 0);
#endif
}

void plat_mt_gic_init(void)
{
	uintptr_t gicr_base = PLAT_ARM_GICR_BASE + 0x10000;
	uint32_t i;

	for (i = 0; i < PLATFORM_CORE_COUNT; i++)
		rdistif_base_addrs[i] = gicr_base + 0x20000 * i;

	gicv3_driver_init(&mt_gicv3_data);
	gicv3_distif_init();
	mt_gic_cpuif_enable();
	mt_gic_rdistif_init();
	mt_gic_clear_sec_pol_ctl_en();
	mt_gic_sync_high_polarity();
}
