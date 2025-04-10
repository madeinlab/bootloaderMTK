// SPDX-License-Identifier: GPL-2.0+

#include <common.h>
#include <command.h>
#include <dm.h>
#include <hexdump.h>
#include <mapmem.h>


extern int rtk_port_status(void);
extern int rtk_vlan_status(void);
extern int rtk_l2_status(void);
extern int rtk_stat_status(void);
static int do_rtk_port(struct udevice *dev, int argc, char * const argv[])
{
	printf("do_rtk_port\n");
	rtk_port_status();
	return CMD_RET_SUCCESS;
}

static int do_rtk_vlan(struct udevice *dev, int argc, char * const argv[])
{
	printf("do_rtk_vlan\n");
	rtk_vlan_status();
	return CMD_RET_SUCCESS;
}

static int do_rtk_l2(struct udevice *dev, int argc, char * const argv[])
{
	printf("do_rtk_l2\n");
	rtk_l2_status();
	return CMD_RET_SUCCESS;
}

static int do_rtk_stat(struct udevice *dev, int argc, char * const argv[])
{
	printf("do_rtk_stat\n");
	rtk_stat_status();
	return CMD_RET_SUCCESS;
}

int do_rtk(struct cmd_tbl *cmdtp, int flag, int argc, char * const argv[])
{
	int i;
	struct udevice *dev = NULL;

	printf("argc %d\n", argc);
	for (i = 0; i < argc; i++) {
		printf(" %s ", argv[i]);
	}
	printf("\n\n");

	if (!strcmp(argv[1], "port"))
		return do_rtk_port(dev, argc - 1, argv + 1);

	if (!strcmp(argv[1], "vlan"))
		return do_rtk_vlan(dev, argc - 1, argv + 1);

	if (!strcmp(argv[1], "l2"))
		return do_rtk_l2(dev, argc - 1, argv + 1);

	if (!strcmp(argv[1], "stat"))
		return do_rtk_stat(dev, argc - 1, argv + 1);

	return CMD_RET_USAGE;
}

U_BOOT_CMD(
	rtk,	5,	0,	do_rtk,
	"RealTek Switch subsystem",
	"port - Display Port status\n"
	"rtk vlan - Display VLAN members\n"
	"rtk l2   - Display L2 addresses\n"
	"rtk stat - Display L2 addresses\n"
);
