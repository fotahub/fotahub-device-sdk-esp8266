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
#ifndef ESPCONNHELPER_H
#define ESPCONNHELPER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <c_types.h>
#include "SocketDefinitions.h"
#include <osapi.h>
#include <espconn.h>

#ifdef __cplusplus
extern "C" {
#endif

struct espconn *ICACHE_FLASH_ATTR createESPConn(enum espconn_type connectionType, uint32_t ipAddr, uint16_t port, size_t reverseDataSize);

void ICACHE_FLASH_ATTR setESPConnRemoteIP(struct espconn *espconn, uint32_t ipAddr);

void ICACHE_FLASH_ATTR disposeESPConn(struct espconn *pConn);

SocketError_t ICACHE_FLASH_ATTR espConnToSocketError(int8_t errorCode);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
