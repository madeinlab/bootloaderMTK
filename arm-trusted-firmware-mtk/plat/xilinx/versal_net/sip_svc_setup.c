/*
 * Copyright (c) 2018-2019, Arm Limited and Contributors. All rights reserved.
 * Copyright (c) 2018-2022, Xilinx, Inc. All rights reserved.
 * Copyright (c) 2022-2024, Advanced Micro Devices, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* Top level SMC handler for SiP calls. Dispatch PM calls to PM SMC handler. */

#include <errno.h>
#include <inttypes.h>

#include <common/debug.h>
#include <common/runtime_svc.h>
#include <tools_share/uuid.h>

#include "ipi_mailbox_svc.h"
#include "plat_private.h"
#include "pm_svc_main.h"

/* SMC function IDs for SiP Service queries */
#define VERSAL_NET_SIP_SVC_UID		(0x8200ff01U)
#define VERSAL_NET_SIP_SVC_VERSION	(0x8200ff03U)

/* SiP Service Calls version numbers */
#define SIP_SVC_VERSION_MAJOR		(0U)
#define SIP_SVC_VERSION_MINOR		(2U)

/* These macros are used to identify PM calls from the SMC function ID */
#define SIP_FID_MASK	GENMASK(23, 16)
#define XLNX_FID_MASK	GENMASK(23, 12)
#define PM_FID_VALUE	0u
#define IPI_FID_VALUE	0x1000u
#define is_pm_fid(_fid) (((_fid) & XLNX_FID_MASK) == PM_FID_VALUE)
#define is_ipi_fid(_fid) (((_fid) & XLNX_FID_MASK) == IPI_FID_VALUE)

/* SiP Service UUID */
DEFINE_SVC_UUID2(versal_net_sip_uuid,
		0x80d4c25au, 0xebaf, 0x11eb, 0x94, 0x68,
		0x0b, 0x4e, 0x3b, 0x8f, 0xc3, 0x60);

/**
 * sip_svc_setup() - Setup SiP Service
 *
 * Return: 0 on success, negative error code on failure.
 *
 */
static int32_t sip_svc_setup(void)
{
	return sip_svc_setup_init();
}

/*
 * sip_svc_smc_handler() - Top-level SiP Service SMC handler
 *
 * Handler for all SiP SMC calls. Handles standard SIP requests
 * and calls PM SMC handler if the call is for a PM-API function.
 */
static uintptr_t sip_svc_smc_handler(uint32_t smc_fid,
			     u_register_t x1,
			     u_register_t x2,
			     u_register_t x3,
			     u_register_t x4,
			     void *cookie,
			     void *handle,
			     u_register_t flags)
{
	VERBOSE("SMCID: 0x%08x, x1: 0x%016" PRIx64 ", x2: 0x%016" PRIx64 ", x3: 0x%016" PRIx64 ", x4: 0x%016" PRIx64 "\n",
		smc_fid, x1, x2, x3, x4);

	if ((smc_fid & SIP_FID_MASK) != 0U) {
		WARN("SMC out of SiP assinged range: 0x%x\n", smc_fid);
		SMC_RET1(handle, SMC_UNK);
	}

	/* Let PM SMC handler deal with PM-related requests */
	if (is_pm_fid(smc_fid)) {
		return smc_handler(smc_fid, x1, x2, x3, x4, cookie, handle,
				flags);
	}

	/* Let IPI SMC handler deal with IPI-related requests if platform */
	if (is_ipi_fid(smc_fid)) {
		return ipi_smc_handler(smc_fid, x1, x2, x3, x4, cookie, handle, flags);
	}

	/* Let PM SMC handler deal with PM-related requests */
	switch (smc_fid) {
	case VERSAL_NET_SIP_SVC_UID:
		SMC_UUID_RET(handle, versal_net_sip_uuid);

	case VERSAL_NET_SIP_SVC_VERSION:
		SMC_RET2(handle, SIP_SVC_VERSION_MAJOR, SIP_SVC_VERSION_MINOR);

	default:
		WARN("Unimplemented SiP Service Call: 0x%x\n", smc_fid);
		SMC_RET1(handle, SMC_UNK);
	}
}

/* Register PM Service Calls as runtime service */
DECLARE_RT_SVC(
		sip_svc,
		OEN_SIP_START,
		OEN_SIP_END,
		SMC_TYPE_FAST,
		sip_svc_setup,
		sip_svc_smc_handler);
