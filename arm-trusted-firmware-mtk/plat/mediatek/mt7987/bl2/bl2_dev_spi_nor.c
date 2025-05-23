// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright (c) 2024, MediaTek Inc. All rights reserved.
 */

#include <stddef.h>
#include <stdint.h>
#include <boot_spi.h>

#define FIP_BASE			0x250000
#define FIP_SIZE			0x80000

#define MTK_QSPI_SRC_CLK		CB_MPLL_D2

uint32_t mtk_plat_get_qspi_src_clk(void)
{
	/* config GPIO pinmux to spi mode */
	mtk_spi_gpio_init(SPIM2);

	/* select 208M clk */
	mtk_spi_source_clock_select(MTK_QSPI_SRC_CLK);

	return MTK_QSPI_SRC_CLK;
}

void mtk_plat_fip_location(size_t *fip_off, size_t *fip_size)
{
	*fip_off = FIP_BASE;
	*fip_size = FIP_SIZE;
}
