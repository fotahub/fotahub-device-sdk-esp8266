/*
 *  Copyright (C) 2022 FotaHub Inc. All rights reserved.
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
#ifndef USER_CONFIG_H
#define USER_CONFIG_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <c_types.h>
#include "FOTAUpdateDefinitions.h"
#include <driver/uart.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UART_UNIT (UART0)

#define UART_BAUDRATE BIT_RATE_57600

#define BLINK_PERIOD 1000

extern FOTAUpdateClientConfig_t ESP8266_FOTA_UPDATE_CLIENT_CONFIG;

extern ICACHE_RODATA_ATTR char const WIFI_STATION_SSID[];

extern ICACHE_RODATA_ATTR char const WIFI_STATION_PASSWORD[];

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
