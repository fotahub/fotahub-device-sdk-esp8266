/*
 *  Copyright (C) 2020-2021 FotaHub Inc. All rights reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of the FotaHub(R) Device SDK program (https://fotahub.com)
 */
#ifndef UARTDRV_H
#define UARTDRV_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <c_types.h>
#include <driver/uart.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UART_TXFIFO_DATA_LEN(status) ((((uint32_t)(status)) >> UART_TXFIFO_CNT_S) & UART_TXFIFO_CNT)

#define UART_RXFIFO_DATA_LEN(status) ((((uint32_t)(status)) >> UART_RXFIFO_CNT_S) & UART_RXFIFO_CNT)

#define UART_RXFIFO_DATA(fifo) ((((uint32_t)(fifo)) >> UART_RXFIFO_RD_BYTE_S) & UART_RXFIFO_RD_BYTE)

void ICACHE_FLASH_ATTR one_uart_init(uint8_t unit, UartBautRate baudrate);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
