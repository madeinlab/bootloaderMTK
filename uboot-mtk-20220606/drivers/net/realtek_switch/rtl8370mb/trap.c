/*
 * Copyright (C) 2013 Realtek Semiconductor Corp.
 * All Rights Reserved.
 *
 * This program is the proprietary software of Realtek Semiconductor
 * Corporation and/or its licensors, and only be used, duplicated,
 * modified or distributed under the authorized license from Realtek.
 *
 * ANY USE OF THE SOFTWARE OTHER THAN AS AUTHORIZED UNDER
 * THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.
 *
 * $Revision$
 * $Date$
 *
 * Purpose : RTK switch high-level API for RTL8367/RTL8367C
 * Feature : Here is a list of all functions and variables in Trap module.
 *
 */

#include <rtk_switch.h>
#include <rtk_error.h>
#include <trap.h>
#include <string.h>

#include <dal/dal_mgmt.h>


/* Function Name:
 *      rtk_trap_unknownUnicastPktAction_set
 * Description:
 *      Set unknown unicast packet action configuration.
 * Input:
 *      port            - ingress port ID for unknown unicast packet
 *      ucast_action    - Unknown unicast action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT               - Invalid input parameters.
 * Note:
 *      This API can set unknown unicast packet action configuration.
 *      The unknown unicast action is as following:
 *          - UCAST_ACTION_FORWARD_PMASK
 *          - UCAST_ACTION_DROP
 *          - UCAST_ACTION_TRAP2CPU
 *          - UCAST_ACTION_FLOODING
 */
rtk_api_ret_t rtk_trap_unknownUnicastPktAction_set(rtk_port_t port, rtk_trap_ucast_action_t ucast_action)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_unknownUnicastPktAction_set)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_unknownUnicastPktAction_set(port, ucast_action);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_unknownUnicastPktAction_get
 * Description:
 *      Get unknown unicast packet action configuration.
 * Input:
 *      port            - ingress port ID for unknown unicast packet
 * Output:
 *      pUcast_action   - Unknown unicast action.
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT               - Invalid input parameters.
 *      RT_ERR_NULL_POINTER        - Null pointer
 * Note:
 *      This API can get unknown unicast packet action configuration.
 *      The unknown unicast action is as following:
 *          - UCAST_ACTION_FORWARD_PMASK
 *          - UCAST_ACTION_DROP
 *          - UCAST_ACTION_TRAP2CPU
 *          - UCAST_ACTION_FLOODING
 */
rtk_api_ret_t rtk_trap_unknownUnicastPktAction_get(rtk_port_t port, rtk_trap_ucast_action_t *pUcast_action)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_unknownUnicastPktAction_get)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_unknownUnicastPktAction_get(port, pUcast_action);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_unknownMacPktAction_set
 * Description:
 *      Set unknown source MAC packet action configuration.
 * Input:
 *      ucast_action    - Unknown source MAC action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT               - Invalid input parameters.
 * Note:
 *      This API can set unknown unicast packet action configuration.
 *      The unknown unicast action is as following:
 *          - UCAST_ACTION_FORWARD_PMASK
 *          - UCAST_ACTION_DROP
 *          - UCAST_ACTION_TRAP2CPU
 */
rtk_api_ret_t rtk_trap_unknownMacPktAction_set(rtk_trap_ucast_action_t ucast_action)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_unknownMacPktAction_set)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_unknownMacPktAction_set(ucast_action);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_unknownMacPktAction_get
 * Description:
 *      Get unknown source MAC packet action configuration.
 * Input:
 *      None.
 * Output:
 *      pUcast_action   - Unknown source MAC action.
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NULL_POINTER        - Null Pointer.
 *      RT_ERR_INPUT               - Invalid input parameters.
 * Note:
 *
 */
rtk_api_ret_t rtk_trap_unknownMacPktAction_get(rtk_trap_ucast_action_t *pUcast_action)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_unknownMacPktAction_get)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_unknownMacPktAction_get(pUcast_action);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_unmatchMacPktAction_set
 * Description:
 *      Set unmatch source MAC packet action configuration.
 * Input:
 *      ucast_action    - Unmatch source MAC action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT               - Invalid input parameters.
 * Note:
 *      This API can set unknown unicast packet action configuration.
 *      The unknown unicast action is as following:
 *          - UCAST_ACTION_FORWARD_PMASK
 *          - UCAST_ACTION_DROP
 *          - UCAST_ACTION_TRAP2CPU
 */
rtk_api_ret_t rtk_trap_unmatchMacPktAction_set(rtk_trap_ucast_action_t ucast_action)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_unmatchMacPktAction_set)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_unmatchMacPktAction_set(ucast_action);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_unmatchMacPktAction_get
 * Description:
 *      Get unmatch source MAC packet action configuration.
 * Input:
 *      None.
 * Output:
 *      pUcast_action   - Unmatch source MAC action.
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT               - Invalid input parameters.
 * Note:
 *      This API can set unknown unicast packet action configuration.
 *      The unknown unicast action is as following:
 *          - UCAST_ACTION_FORWARD_PMASK
 *          - UCAST_ACTION_DROP
 *          - UCAST_ACTION_TRAP2CPU
 */
rtk_api_ret_t rtk_trap_unmatchMacPktAction_get(rtk_trap_ucast_action_t *pUcast_action)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_unmatchMacPktAction_get)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_unmatchMacPktAction_get(pUcast_action);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_unmatchMacMoving_set
 * Description:
 *      Set unmatch source MAC packet moving state.
 * Input:
 *      port        - Port ID.
 *      enable      - ENABLED: allow SA moving, DISABLE: don't allow SA moving.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT               - Invalid input parameters.
 * Note:
 */
rtk_api_ret_t rtk_trap_unmatchMacMoving_set(rtk_port_t port, rtk_enable_t enable)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_unmatchMacMoving_set)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_unmatchMacMoving_set(port, enable);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_unmatchMacMoving_get
 * Description:
 *      Set unmatch source MAC packet moving state.
 * Input:
 *      port        - Port ID.
 * Output:
 *      pEnable     - ENABLED: allow SA moving, DISABLE: don't allow SA moving.
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT               - Invalid input parameters.
 * Note:
 */
rtk_api_ret_t rtk_trap_unmatchMacMoving_get(rtk_port_t port, rtk_enable_t *pEnable)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_unmatchMacMoving_get)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_unmatchMacMoving_get(port, pEnable);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_unknownMcastPktAction_set
 * Description:
 *      Set behavior of unknown multicast
 * Input:
 *      port            - Port id.
 *      type            - unknown multicast packet type.
 *      mcast_action    - unknown multicast action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_PORT_ID         - Invalid port number.
 *      RT_ERR_NOT_ALLOWED     - Invalid action.
 *      RT_ERR_INPUT         - Invalid input parameters.
 * Note:
 *      When receives an unknown multicast packet, switch may trap, drop or flood this packet
 *      (1) The unknown multicast packet type is as following:
 *          - MCAST_L2
 *          - MCAST_IPV4
 *          - MCAST_IPV6
 *      (2) The unknown multicast action is as following:
 *          - MCAST_ACTION_FORWARD
 *          - MCAST_ACTION_DROP
 *          - MCAST_ACTION_TRAP2CPU
 */
rtk_api_ret_t rtk_trap_unknownMcastPktAction_set(rtk_port_t port, rtk_mcast_type_t type, rtk_trap_mcast_action_t mcast_action)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_unknownMcastPktAction_set)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_unknownMcastPktAction_set(port, type, mcast_action);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_unknownMcastPktAction_get
 * Description:
 *      Get behavior of unknown multicast
 * Input:
 *      type - unknown multicast packet type.
 * Output:
 *      pMcast_action - unknown multicast action.
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_PORT_ID             - Invalid port number.
 *      RT_ERR_NOT_ALLOWED         - Invalid operation.
 *      RT_ERR_INPUT             - Invalid input parameters.
 * Note:
 *      When receives an unknown multicast packet, switch may trap, drop or flood this packet
 *      (1) The unknown multicast packet type is as following:
 *          - MCAST_L2
 *          - MCAST_IPV4
 *          - MCAST_IPV6
 *      (2) The unknown multicast action is as following:
 *          - MCAST_ACTION_FORWARD
 *          - MCAST_ACTION_DROP
 *          - MCAST_ACTION_TRAP2CPU
 */
rtk_api_ret_t rtk_trap_unknownMcastPktAction_get(rtk_port_t port, rtk_mcast_type_t type, rtk_trap_mcast_action_t *pMcast_action)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_unknownMcastPktAction_get)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_unknownMcastPktAction_get(port, type, pMcast_action);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_lldpEnable_set
 * Description:
 *      Set LLDP enable.
 * Input:
 *      enabled - LLDP enable, 0: follow RMA, 1: use LLDP action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT             - Invalid input parameters.
 * Note:
 *      - DMAC                                                 Assignment
 *      - 01:80:c2:00:00:0e ethertype = 0x88CC    LLDP
 *      - 01:80:c2:00:00:03 ethertype = 0x88CC
 *      - 01:80:c2:00:00:00 ethertype = 0x88CC

 */
rtk_api_ret_t rtk_trap_lldpEnable_set(rtk_enable_t enabled)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_lldpEnable_set)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_lldpEnable_set(enabled);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_lldpEnable_get
 * Description:
 *      Get LLDP status.
 * Input:
 *      None
 * Output:
 *      pEnabled - LLDP enable, 0: follow RMA, 1: use LLDP action.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT         - Invalid input parameters.
 * Note:
 *      LLDP is as following definition.
 *      - DMAC                                                 Assignment
 *      - 01:80:c2:00:00:0e ethertype = 0x88CC    LLDP
 *      - 01:80:c2:00:00:03 ethertype = 0x88CC
 *      - 01:80:c2:00:00:00 ethertype = 0x88CC
 */
rtk_api_ret_t rtk_trap_lldpEnable_get(rtk_enable_t *pEnabled)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_lldpEnable_get)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_lldpEnable_get(pEnabled);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_reasonTrapToCpuPriority_set
 * Description:
 *      Set priority value of a packet that trapped to CPU port according to specific reason.
 * Input:
 *      type     - reason that trap to CPU port.
 *      priority - internal priority that is going to be set for specific trap reason.
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NOT_INIT - The module is not initial
 *      RT_ERR_INPUT    - Invalid input parameter
 * Note:
 *      Currently the trap reason that supported are listed as follows:
 *      - TRAP_REASON_RMA
 *      - TRAP_REASON_OAM
 *      - TRAP_REASON_1XUNAUTH
 *      - TRAP_REASON_VLANSTACK
 *      - TRAP_REASON_UNKNOWNMC
 *      - TRAP_REASON_IGMPMLD
 */
rtk_api_ret_t rtk_trap_reasonTrapToCpuPriority_set(rtk_trap_reason_type_t type, rtk_pri_t priority)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_reasonTrapToCpuPriority_set)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_reasonTrapToCpuPriority_set(type, priority);
    RTK_API_UNLOCK();

    return retVal;
}


/* Function Name:
 *      rtk_trap_reasonTrapToCpuPriority_get
 * Description:
 *      Get priority value of a packet that trapped to CPU port according to specific reason.
 * Input:
 *      type      - reason that trap to CPU port.
 * Output:
 *      pPriority - configured internal priority for such reason.
 * Return:
 *      RT_ERR_OK
 *      RT_ERR_FAILED
 *      RT_ERR_NOT_INIT     - The module is not initial
 *      RT_ERR_INPUT        - Invalid input parameter
 *      RT_ERR_NULL_POINTER - NULL pointer
 * Note:
 *      Currently the trap reason that supported are listed as follows:
 *      - TRAP_REASON_RMA
 *      - TRAP_REASON_OAM
 *      - TRAP_REASON_1XUNAUTH
 *      - TRAP_REASON_VLANSTACK
 *      - TRAP_REASON_UNKNOWNMC
 *      - TRAP_REASON_IGMPMLD
 */
rtk_api_ret_t rtk_trap_reasonTrapToCpuPriority_get(rtk_trap_reason_type_t type, rtk_pri_t *pPriority)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_reasonTrapToCpuPriority_get)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_reasonTrapToCpuPriority_get(type, pPriority);
    RTK_API_UNLOCK();

    return retVal;
}



/* Function Name:
 *      rtk_trap_rmaAction_set
 * Description:
 *      Set Reserved multicast address action configuration.
 * Input:
 *      type    - rma type.
 *      rma_action - RMA action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *
 *      There are 48 types of Reserved Multicast Address frame for application usage.
 *      (1)They are as following definition.
 *      - TRAP_BRG_GROUP,
 *      - TRAP_FD_PAUSE,
 *      - TRAP_SP_MCAST,
 *      - TRAP_1X_PAE,
 *      - TRAP_UNDEF_BRG_04,
 *      - TRAP_UNDEF_BRG_05,
 *      - TRAP_UNDEF_BRG_06,
 *      - TRAP_UNDEF_BRG_07,
 *      - TRAP_PROVIDER_BRIDGE_GROUP_ADDRESS,
 *      - TRAP_UNDEF_BRG_09,
 *      - TRAP_UNDEF_BRG_0A,
 *      - TRAP_UNDEF_BRG_0B,
 *      - TRAP_UNDEF_BRG_0C,
 *      - TRAP_PROVIDER_BRIDGE_GVRP_ADDRESS,
 *      - TRAP_8021AB,
 *      - TRAP_UNDEF_BRG_0F,
 *      - TRAP_BRG_MNGEMENT,
 *      - TRAP_UNDEFINED_11,
 *      - TRAP_UNDEFINED_12,
 *      - TRAP_UNDEFINED_13,
 *      - TRAP_UNDEFINED_14,
 *      - TRAP_UNDEFINED_15,
 *      - TRAP_UNDEFINED_16,
 *      - TRAP_UNDEFINED_17,
 *      - TRAP_UNDEFINED_18,
 *      - TRAP_UNDEFINED_19,
 *      - TRAP_UNDEFINED_1A,
 *      - TRAP_UNDEFINED_1B,
 *      - TRAP_UNDEFINED_1C,
 *      - TRAP_UNDEFINED_1D,
 *      - TRAP_UNDEFINED_1E,
 *      - TRAP_UNDEFINED_1F,
 *      - TRAP_GMRP,
 *      - TRAP_GVRP,
 *      - TRAP_UNDEF_GARP_22,
 *      - TRAP_UNDEF_GARP_23,
 *      - TRAP_UNDEF_GARP_24,
 *      - TRAP_UNDEF_GARP_25,
 *      - TRAP_UNDEF_GARP_26,
 *      - TRAP_UNDEF_GARP_27,
 *      - TRAP_UNDEF_GARP_28,
 *      - TRAP_UNDEF_GARP_29,
 *      - TRAP_UNDEF_GARP_2A,
 *      - TRAP_UNDEF_GARP_2B,
 *      - TRAP_UNDEF_GARP_2C,
 *      - TRAP_UNDEF_GARP_2D,
 *      - TRAP_UNDEF_GARP_2E,
 *      - TRAP_UNDEF_GARP_2F,
 *      - TRAP_CDP.
 *      - TRAP_CSSTP.
 *      - TRAP_LLDP.
 *      (2) The RMA action is as following:
 *      - RMA_ACTION_FORWARD
 *      - RMA_ACTION_TRAP2CPU
 *      - RMA_ACTION_DROP
 *      - RMA_ACTION_FORWARD_EXCLUDE_CPU
 */
rtk_api_ret_t rtk_trap_rmaAction_set(rtk_trap_type_t type, rtk_trap_rma_action_t rma_action)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_rmaAction_set)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_rmaAction_set(type, rma_action);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_rmaAction_get
 * Description:
 *      Get Reserved multicast address action configuration.
 * Input:
 *      type - rma type.
 * Output:
 *      pRma_action - RMA action.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      There are 48 types of Reserved Multicast Address frame for application usage.
 *      (1)They are as following definition.
 *      - TRAP_BRG_GROUP,
 *      - TRAP_FD_PAUSE,
 *      - TRAP_SP_MCAST,
 *      - TRAP_1X_PAE,
 *      - TRAP_UNDEF_BRG_04,
 *      - TRAP_UNDEF_BRG_05,
 *      - TRAP_UNDEF_BRG_06,
 *      - TRAP_UNDEF_BRG_07,
 *      - TRAP_PROVIDER_BRIDGE_GROUP_ADDRESS,
 *      - TRAP_UNDEF_BRG_09,
 *      - TRAP_UNDEF_BRG_0A,
 *      - TRAP_UNDEF_BRG_0B,
 *      - TRAP_UNDEF_BRG_0C,
 *      - TRAP_PROVIDER_BRIDGE_GVRP_ADDRESS,
 *      - TRAP_8021AB,
 *      - TRAP_UNDEF_BRG_0F,
 *      - TRAP_BRG_MNGEMENT,
 *      - TRAP_UNDEFINED_11,
 *      - TRAP_UNDEFINED_12,
 *      - TRAP_UNDEFINED_13,
 *      - TRAP_UNDEFINED_14,
 *      - TRAP_UNDEFINED_15,
 *      - TRAP_UNDEFINED_16,
 *      - TRAP_UNDEFINED_17,
 *      - TRAP_UNDEFINED_18,
 *      - TRAP_UNDEFINED_19,
 *      - TRAP_UNDEFINED_1A,
 *      - TRAP_UNDEFINED_1B,
 *      - TRAP_UNDEFINED_1C,
 *      - TRAP_UNDEFINED_1D,
 *      - TRAP_UNDEFINED_1E,
 *      - TRAP_UNDEFINED_1F,
 *      - TRAP_GMRP,
 *      - TRAP_GVRP,
 *      - TRAP_UNDEF_GARP_22,
 *      - TRAP_UNDEF_GARP_23,
 *      - TRAP_UNDEF_GARP_24,
 *      - TRAP_UNDEF_GARP_25,
 *      - TRAP_UNDEF_GARP_26,
 *      - TRAP_UNDEF_GARP_27,
 *      - TRAP_UNDEF_GARP_28,
 *      - TRAP_UNDEF_GARP_29,
 *      - TRAP_UNDEF_GARP_2A,
 *      - TRAP_UNDEF_GARP_2B,
 *      - TRAP_UNDEF_GARP_2C,
 *      - TRAP_UNDEF_GARP_2D,
 *      - TRAP_UNDEF_GARP_2E,
 *      - TRAP_UNDEF_GARP_2F,
 *      - TRAP_CDP.
 *      - TRAP_CSSTP.
 *      - TRAP_LLDP.
 *      (2) The RMA action is as following:
 *      - RMA_ACTION_FORWARD
 *      - RMA_ACTION_TRAP2CPU
 *      - RMA_ACTION_DROP
 *      - RMA_ACTION_FORWARD_EXCLUDE_CPU
 */
rtk_api_ret_t rtk_trap_rmaAction_get(rtk_trap_type_t type, rtk_trap_rma_action_t *pRma_action)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_rmaAction_get)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_rmaAction_get(type, pRma_action);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_rmaKeepFormat_set
 * Description:
 *      Set Reserved multicast address keep format configuration.
 * Input:
 *      type    - rma type.
 *      enable - enable keep format.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_ENABLE       - Invalid IFG parameter
 * Note:
 *
 *      There are 48 types of Reserved Multicast Address frame for application usage.
 *      They are as following definition.
 *      - TRAP_BRG_GROUP,
 *      - TRAP_FD_PAUSE,
 *      - TRAP_SP_MCAST,
 *      - TRAP_1X_PAE,
 *      - TRAP_UNDEF_BRG_04,
 *      - TRAP_UNDEF_BRG_05,
 *      - TRAP_UNDEF_BRG_06,
 *      - TRAP_UNDEF_BRG_07,
 *      - TRAP_PROVIDER_BRIDGE_GROUP_ADDRESS,
 *      - TRAP_UNDEF_BRG_09,
 *      - TRAP_UNDEF_BRG_0A,
 *      - TRAP_UNDEF_BRG_0B,
 *      - TRAP_UNDEF_BRG_0C,
 *      - TRAP_PROVIDER_BRIDGE_GVRP_ADDRESS,
 *      - TRAP_8021AB,
 *      - TRAP_UNDEF_BRG_0F,
 *      - TRAP_BRG_MNGEMENT,
 *      - TRAP_UNDEFINED_11,
 *      - TRAP_UNDEFINED_12,
 *      - TRAP_UNDEFINED_13,
 *      - TRAP_UNDEFINED_14,
 *      - TRAP_UNDEFINED_15,
 *      - TRAP_UNDEFINED_16,
 *      - TRAP_UNDEFINED_17,
 *      - TRAP_UNDEFINED_18,
 *      - TRAP_UNDEFINED_19,
 *      - TRAP_UNDEFINED_1A,
 *      - TRAP_UNDEFINED_1B,
 *      - TRAP_UNDEFINED_1C,
 *      - TRAP_UNDEFINED_1D,
 *      - TRAP_UNDEFINED_1E,
 *      - TRAP_UNDEFINED_1F,
 *      - TRAP_GMRP,
 *      - TRAP_GVRP,
 *      - TRAP_UNDEF_GARP_22,
 *      - TRAP_UNDEF_GARP_23,
 *      - TRAP_UNDEF_GARP_24,
 *      - TRAP_UNDEF_GARP_25,
 *      - TRAP_UNDEF_GARP_26,
 *      - TRAP_UNDEF_GARP_27,
 *      - TRAP_UNDEF_GARP_28,
 *      - TRAP_UNDEF_GARP_29,
 *      - TRAP_UNDEF_GARP_2A,
 *      - TRAP_UNDEF_GARP_2B,
 *      - TRAP_UNDEF_GARP_2C,
 *      - TRAP_UNDEF_GARP_2D,
 *      - TRAP_UNDEF_GARP_2E,
 *      - TRAP_UNDEF_GARP_2F,
 *      - TRAP_CDP.
 *      - TRAP_CSSTP.
 *      - TRAP_LLDP.
 */
rtk_api_ret_t rtk_trap_rmaKeepFormat_set(rtk_trap_type_t type, rtk_enable_t enable)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_rmaKeepFormat_set)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_rmaKeepFormat_set(type, enable);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_rmaKeepFormat_get
 * Description:
 *      Get Reserved multicast address action configuration.
 * Input:
 *      type - rma type.
 * Output:
 *      pEnable - keep format status.
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      There are 48 types of Reserved Multicast Address frame for application usage.
 *      They are as following definition.
 *      - TRAP_BRG_GROUP,
 *      - TRAP_FD_PAUSE,
 *      - TRAP_SP_MCAST,
 *      - TRAP_1X_PAE,
 *      - TRAP_UNDEF_BRG_04,
 *      - TRAP_UNDEF_BRG_05,
 *      - TRAP_UNDEF_BRG_06,
 *      - TRAP_UNDEF_BRG_07,
 *      - TRAP_PROVIDER_BRIDGE_GROUP_ADDRESS,
 *      - TRAP_UNDEF_BRG_09,
 *      - TRAP_UNDEF_BRG_0A,
 *      - TRAP_UNDEF_BRG_0B,
 *      - TRAP_UNDEF_BRG_0C,
 *      - TRAP_PROVIDER_BRIDGE_GVRP_ADDRESS,
 *      - TRAP_8021AB,
 *      - TRAP_UNDEF_BRG_0F,
 *      - TRAP_BRG_MNGEMENT,
 *      - TRAP_UNDEFINED_11,
 *      - TRAP_UNDEFINED_12,
 *      - TRAP_UNDEFINED_13,
 *      - TRAP_UNDEFINED_14,
 *      - TRAP_UNDEFINED_15,
 *      - TRAP_UNDEFINED_16,
 *      - TRAP_UNDEFINED_17,
 *      - TRAP_UNDEFINED_18,
 *      - TRAP_UNDEFINED_19,
 *      - TRAP_UNDEFINED_1A,
 *      - TRAP_UNDEFINED_1B,
 *      - TRAP_UNDEFINED_1C,
 *      - TRAP_UNDEFINED_1D,
 *      - TRAP_UNDEFINED_1E,
 *      - TRAP_UNDEFINED_1F,
 *      - TRAP_GMRP,
 *      - TRAP_GVRP,
 *      - TRAP_UNDEF_GARP_22,
 *      - TRAP_UNDEF_GARP_23,
 *      - TRAP_UNDEF_GARP_24,
 *      - TRAP_UNDEF_GARP_25,
 *      - TRAP_UNDEF_GARP_26,
 *      - TRAP_UNDEF_GARP_27,
 *      - TRAP_UNDEF_GARP_28,
 *      - TRAP_UNDEF_GARP_29,
 *      - TRAP_UNDEF_GARP_2A,
 *      - TRAP_UNDEF_GARP_2B,
 *      - TRAP_UNDEF_GARP_2C,
 *      - TRAP_UNDEF_GARP_2D,
 *      - TRAP_UNDEF_GARP_2E,
 *      - TRAP_UNDEF_GARP_2F,
 *      - TRAP_CDP.
 *      - TRAP_CSSTP.
 *      - TRAP_LLDP.
 */
rtk_api_ret_t rtk_trap_rmaKeepFormat_get(rtk_trap_type_t type, rtk_enable_t *pEnable)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_rmaKeepFormat_get)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_rmaKeepFormat_get(type, pEnable);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_portUnknownMacPktAction_set
 * Description:
 *      Set unknown source MAC packet action configuration.
 * Input:
 *      port            - Port ID.
 *      ucast_action    - Unknown source MAC action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT               - Invalid input parameters.
 * Note:
 *      This API can set unknown unicast packet action configuration.
 *      The unknown unicast action is as following:
 *          - UCAST_ACTION_FORWARD_PMASK
 *          - UCAST_ACTION_DROP
 *          - UCAST_ACTION_TRAP2CPU
 */
rtk_api_ret_t rtk_trap_portUnknownMacPktAction_set(rtk_port_t port, rtk_trap_ucast_action_t ucast_action)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_portUnknownMacPktAction_set)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_portUnknownMacPktAction_set(port, ucast_action);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_portUnknownMacPktAction_get
 * Description:
 *      Get unknown source MAC packet action configuration.
 * Input:
 *      port            - Port ID.
 * Output:
 *      pUcast_action   - Unknown source MAC action.
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NULL_POINTER        - Null Pointer.
 *      RT_ERR_INPUT               - Invalid input parameters.
 * Note:
 *
 */
rtk_api_ret_t rtk_trap_portUnknownMacPktAction_get(rtk_port_t port, rtk_trap_ucast_action_t *pUcast_action)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_portUnknownMacPktAction_get)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_portUnknownMacPktAction_get(port, pUcast_action);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_portUnmatchMacPktAction_set
 * Description:
 *      Set unmatch source MAC packet action configuration.
 * Input:
 *      port            - Port ID
 *      ucast_action    - Unmatch source MAC action.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT               - Invalid input parameters.
 * Note:
 *      This API can set unknown unicast packet action configuration.
 *      The unknown unicast action is as following:
 *          - UCAST_ACTION_FORWARD_PMASK
 *          - UCAST_ACTION_DROP
 *          - UCAST_ACTION_TRAP2CPU
 */
rtk_api_ret_t rtk_trap_portUnmatchMacPktAction_set(rtk_port_t port, rtk_trap_ucast_action_t ucast_action)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_portUnmatchMacPktAction_set)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_portUnmatchMacPktAction_set(port, ucast_action);
    RTK_API_UNLOCK();

    return retVal;
}

/* Function Name:
 *      rtk_trap_portUnmatchMacPktAction_get
 * Description:
 *      Get unmatch source MAC packet action configuration.
 * Input:
 *      port            - Port ID
 * Output:
 *      pUcast_action   - Unmatch source MAC action.
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_FAILED              - Failed
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_NOT_ALLOWED         - Invalid action.
 *      RT_ERR_INPUT               - Invalid input parameters.
 * Note:
 *      This API can set unknown unicast packet action configuration.
 *      The unknown unicast action is as following:
 *          - UCAST_ACTION_FORWARD_PMASK
 *          - UCAST_ACTION_DROP
 *          - UCAST_ACTION_TRAP2CPU
 */
rtk_api_ret_t rtk_trap_portUnmatchMacPktAction_get(rtk_port_t port, rtk_trap_ucast_action_t *pUcast_action)
{
    rtk_api_ret_t retVal;

    if (NULL == RT_MAPPER->trap_portUnmatchMacPktAction_get)
        return RT_ERR_DRIVER_NOT_FOUND;

    RTK_API_LOCK();
    retVal = RT_MAPPER->trap_portUnmatchMacPktAction_get(port, pUcast_action);
    RTK_API_UNLOCK();

    return retVal;
}


