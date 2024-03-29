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
#ifndef DEMOFOTAUPDATEWORKFLOW_H
#define DEMOFOTAUPDATEWORKFLOW_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <c_types.h>
#include <osapi.h>
#include "FotaHub.h"

#ifdef __cplusplus
extern "C" {
#endif

void ICACHE_FLASH_ATTR fotaUpdateWorkflow_init(void);

void ICACHE_FLASH_ATTR fotaUpdateWorkflow_onConnectionStatusChanged(ConnectionStatus_t status);

void ICACHE_FLASH_ATTR fotaUpdateWorkflow_onFirmwareUpdateStatusChanged(FOTAUpdateStatus_t status);

void ICACHE_FLASH_ATTR fotaUpdateWorkflow_onFirmwareUpdateVersionChanged(char *updateVersion);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
