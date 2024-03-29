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
#ifndef AWSIOTTHINGSHADOWDOCUMENTDEFINITION_H
#define AWSIOTTHINGSHADOWDOCUMENTDEFINITION_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <c_types.h>
#include <osapi.h>
#include "JSON.h"
#include "JSONProcessorImpl.h"
#include "AWSIoTDefinitions.h"
#include "FOTAUpdateDefinitions.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t ICACHE_FLASH_ATTR updateStatusEncoderFunc(uint32_t value, char *msg, size_t msgLength);

uint32_t ICACHE_FLASH_ATTR updateStatusDecoderFunc(char const *msg, size_t msgLength);

extern ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_JSON_ATTRIBUTE_UPDATE_CURRENT_VERSION[];

extern ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_JSON_ATTRIBUTE_UPDATE_NEW_VERSION[];

extern ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_JSON_ATTRIBUTE_UPDATE_VERIFICATION_DATA[];

extern ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_JSON_ATTRIBUTE_UPDATE_STATUS[];

extern ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_JSON_ATTRIBUTE_VALUE_UPDATE_STATUS_FAILED[];

extern ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_JSON_ATTRIBUTE_VALUE_UPDATE_STATUS_SUCCEEDED[];

extern ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_JSON_ATTRIBUTE_VALUE_UPDATE_STATUS_NONE[];

extern struct jsontree_callback updateCurrentVersion;

extern struct jsontree_callback updateNewVersion;

extern struct jsontree_callback AWSIoTThingShadowDocumentDefinition_updateVerificationData;

extern struct jsontree_enum updateStatus;

extern struct jsontree_object requestStateDoc;

extern struct jsontree_pair requestStateDocPairs[];

extern struct jsontree_object stateObj;

extern struct jsontree_pair statePairs[];

extern struct jsontree_object nullObj;

extern struct jsontree_object attributeUpdateStateObj;

extern struct jsontree_pair attributeUpdateStatePairs[];

/* 
 * Handles every json with 'state' field in it. 
 * This contains /desired, /reported, and /delta
 */
extern struct jsontree_object deltaStateDoc;

extern struct jsontree_pair deltaStateDocPairs[];

extern struct jsontree_object attributeUpdateTriggerObj;

extern struct jsontree_pair attributeUpdateTriggerPairs[];

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
