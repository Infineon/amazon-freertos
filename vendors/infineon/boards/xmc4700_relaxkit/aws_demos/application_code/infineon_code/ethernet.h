/*
 * Copyright (C) 2018 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

#ifndef ETHERNET_H
#define ETHERNET_H

#include "xmc_eth_mac.h"
#include "xmc_eth_phy.h"

#define ETH_PHY_ADDR 0

#define RXD1     P2_3
#define RXD0     P2_2
#define RXER     P2_4
#define CLK_RMII P15_8
#define CRS_DV   P15_9

#define TX_EN    P2_5
#define TXD1     P2_9
#define TXD0     P2_8

#define MDIO     P2_0
#define MDC      P2_7

#define ETH_IRQ_PRIO 62

extern XMC_ETH_MAC_t eth_mac;

#ifdef __cplusplus
extern "C" {
#endif

int32_t ETEHRNET_Init(void);

#ifdef __cplusplus
}
#endif

#endif
