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
#ifndef AWSIOTDEFINITIONS_H
#define AWSIOTDEFINITIONS_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <c_types.h>
#include "Datagram.h"
#include "AWSCredentialsDefinitions.h"
#include "IoTDefinitions.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AWS_IOT_THING_SHADOW_TOPIC_UPDATE_LENGTH 30

#define AWS_IOT_THING_SHADOW_TOPIC_GET_LENGTH 27

#define AWS_IOT_THING_SHADOW_SUBTOPIC_ACCEPTED_LENGTH 9

#define AWS_IOT_THING_SHADOW_SUBTOPIC_REJECTED_LENGTH 9

#define AWS_IOT_THING_SHADOW_SUBTOPIC_DELTA_LENGTH 6

#define MAX_AWS_IOT_THING_SHADOW_TOPIC_NAME_LENGTH (IOT_MAX_DEVICE_NAME_LENGTH + AWS_IOT_THING_SHADOW_TOPIC_UPDATE_LENGTH + AWS_IOT_THING_SHADOW_SUBTOPIC_ACCEPTED_LENGTH)

#define MAX_AWS_IOT_THING_SHADOW_HANDLER_COUNT 1

#define AWS_IOT_THING_SHADOW_SUBTOPICS_COUNT 5

ICACHE_RODATA_ATTR
extern char const AWS_HEADER_SECURITY_TOKEN[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_SERVICE[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_WEBSOCKET_PROTOCOL_NAME[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_WEBSOCKET_PATH[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_JSON_STATE[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_JSON_REPORTED[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_JSON_DESIRED[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_JSON_DELTA[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_JSON_CLIENT_TOKEN[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_JSON_METADATA[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_JSON_VERSION[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_JSON_TIMESTAMP[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_JSON_REPORTED_PATH[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_JSON_DESIRED_PATH[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_TOPIC_UPDATE[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_TOPIC_UPDATE_PATTERN[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_TOPIC_GET[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_TOPIC_GET_PATTERN[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_SUBTOPIC_NONE[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_SUBTOPIC_ACCEPTED[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_SUBTOPIC_REJECTED[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_SUBTOPIC_DELTA[];

ICACHE_RODATA_ATTR
extern char const AWS_IOT_THING_SHADOW_REST_PATH_PATTERN[];

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
