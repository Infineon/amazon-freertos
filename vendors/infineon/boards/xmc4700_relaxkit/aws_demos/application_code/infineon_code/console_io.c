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

#include <stdio.h>

#include "console_io.h"

#include "xmc_uart.h"
#include "xmc_gpio.h"

#define CONSOLE_IO_UART_BAUDRATE 115200
#define CONSOLE_IO_UART_CH XMC_UART0_CH0
#define CONSOLE_IO_UART_TX_PIN P1_5
#define CONSOLE_IO_UART_TX_PIN_AF P1_5_AF_U0C0_DOUT0
#define CONSOLE_IO_UART_RX_PIN P1_4
#define CONSOLE_IO_UART_INPUT USIC0_C0_DX0_P1_4

static const XMC_UART_CH_CONFIG_t uart_config =
{
  .baudrate = CONSOLE_IO_UART_BAUDRATE,
  .data_bits = 8,
  .stop_bits = 1,
};

int _write(int fd, const void *buf, size_t count)
{
  (void)fd;

  for (int i = 0; i < count; ++i)
  {
    XMC_UART_CH_Transmit(CONSOLE_IO_UART_CH, *(const uint8_t *)buf);
    buf++;
  }
  return count;
}

int _read(int fd, void *buf, size_t count)
{
  int char_cnt = 0;
  (void)fd;

  while ((XMC_UART_CH_GetStatusFlag(CONSOLE_IO_UART_CH) & (XMC_UART_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION |
                                                         XMC_UART_CH_STATUS_FLAG_RECEIVE_INDICATION)) == 0);

  char_cnt++;
  *(uint8_t *)buf = XMC_UART_CH_GetReceivedData(CONSOLE_IO_UART_CH);

  XMC_UART_CH_ClearStatusFlag(CONSOLE_IO_UART_CH, XMC_UART_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION |
                                                XMC_UART_CH_STATUS_FLAG_RECEIVE_INDICATION);

  return char_cnt;
}

void _putchar(char c)
{
  XMC_UART_CH_Transmit(CONSOLE_IO_UART_CH, c);
}

void CONSOLE_IO_Init(void)
{
  XMC_UART_CH_Init(CONSOLE_IO_UART_CH, &uart_config);

  XMC_GPIO_SetMode(CONSOLE_IO_UART_RX_PIN, XMC_GPIO_MODE_INPUT_PULL_UP);
  XMC_UART_CH_SetInputSource(CONSOLE_IO_UART_CH, XMC_UART_CH_INPUT_RXD, CONSOLE_IO_UART_INPUT);

  XMC_UART_CH_Start(CONSOLE_IO_UART_CH);

  XMC_GPIO_SetMode(CONSOLE_IO_UART_TX_PIN, XMC_GPIO_MODE_OUTPUT_PUSH_PULL | CONSOLE_IO_UART_TX_PIN_AF);
}
