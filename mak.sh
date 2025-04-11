#!/bin/bash

cd uboot-mtk-20220606
make V=1 CROSS_COMPILE=/usr/bin/aarch64-linux-gnu- mt7981_spim_nand_rfb_with_rtl8370mb_defconfig
make V=1 CROSS_COMPILE=/usr/bin/aarch64-linux-gnu-

cd ../arm-trusted-firmware-mtk/
make -f ./Makefile PLAT="mt7981" CROSS_COMPILE="/usr/bin/aarch64-linux-gnu-" BOOT_DEVICE="spim-nand" NMBM=1 NAND_TYPE="spim:2k+64" DRAM_USE_DDR4=0 DDR3_FREQ_2133=1 BOARD_BGA=1 LOG_LEVEL=20 BL33="../uboot-mtk-20220606/u-boot.bin" all fip


cp build/mt7981/release/bl2.img ../.
cp build/mt7981/release/fip.bin ../.

