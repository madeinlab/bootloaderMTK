/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Configuration for MediaTek MT7981 SoC
 *
 * Copyright (C) 2021 MediaTek Inc.
 * Author: Sam Shih <sam.shih@mediatek.com>
 */

#ifndef __MT7981_H
#define __MT7981_H

#include <linux/sizes.h>

#define CONFIG_SYS_MAXARGS		32
#define CONFIG_SYS_BOOTM_LEN		SZ_64M
#define CONFIG_SYS_CBSIZE		SZ_1K
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE +	\
					sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_NONCACHED_MEMORY	SZ_1M
#define CONFIG_SYS_MMC_ENV_DEV 0

/* Uboot definition */
#define CONFIG_SYS_UBOOT_BASE                   CONFIG_SYS_TEXT_BASE

/* SPL -> Uboot */
#define CONFIG_SYS_UBOOT_START		CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_TEXT_BASE + SZ_2M - \
					 GENERATED_GBL_DATA_SIZE)

/* Flash */
#define CONFIG_SYS_NAND_MAX_CHIPS	1

/* DRAM */
#define CONFIG_SYS_SDRAM_BASE		0x40000000

/* Ethernet */
#define CONFIG_IPADDR			10.10.10.2
#define CONFIG_SERVERIP			10.10.10.3
#define CONFIG_NETMASK			255.255.255.0

/* Default Environment */
#define	CONFIG_SERIAL_NO_DEFAULT		"DW250412345"	/* DW + YY + MM + 12345 */
#define	CONFIG_ETHADDR_DEFAULT			"1C:56:8E:11:22:33"
#define	CONFIG_ETHADDR1_DEFAULT			"1C:56:8E:11:22:34"

#endif
