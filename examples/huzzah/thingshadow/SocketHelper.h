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
#ifndef SOCKETHELPER_H
#define SOCKETHELPER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <c_types.h>
#include <osapi.h>
#include "SocketDefinitions.h"

#ifdef __cplusplus
extern "C" {
#endif

char *ICACHE_FLASH_ATTR getCertsDir(char *certsDir, size_t maxCertsDirLength);

uint8_t ICACHE_FLASH_ATTR convertMaxFragmentLengthToMFLCode(TLSMaxFragmentLength_t maxFragmentLength);

void ICACHE_FLASH_ATTR ipv4ToStr(uint32_t ipAddr, char *ipAddrStr, size_t ipAddrStrSize);

uint32_t ICACHE_FLASH_ATTR strToIPv4(char *ipAddrStr, size_t ipAddrStrLength);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif