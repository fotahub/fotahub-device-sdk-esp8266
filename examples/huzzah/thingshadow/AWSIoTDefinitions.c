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
#include "AWSIoTDefinitions.h"

ICACHE_RODATA_ATTR char const AWS_HEADER_SECURITY_TOKEN[] = "X-Amz-Security-Token";

ICACHE_RODATA_ATTR char const AWS_IOT_SERVICE[] = "iotdata";

ICACHE_RODATA_ATTR char const AWS_IOT_WEBSOCKET_PROTOCOL_NAME[] = "mqtt";

ICACHE_RODATA_ATTR char const AWS_IOT_WEBSOCKET_PATH[] = "/mqtt";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_JSON_STATE[] = "state";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_JSON_REPORTED[] = "reported";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_JSON_DESIRED[] = "desired";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_JSON_DELTA[] = "delta";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_JSON_CLIENT_TOKEN[] = "clientToken";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_JSON_METADATA[] = "metadata";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_JSON_VERSION[] = "version";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_JSON_TIMESTAMP[] = "timestamp";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_JSON_REPORTED_PATH[] = "/state/reported";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_JSON_DESIRED_PATH[] = "/state/desired";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_TOPIC_UPDATE[] = "update";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_TOPIC_UPDATE_PATTERN[] = "$aws/things/%s/shadow/update%s";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_TOPIC_GET[] = "get";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_TOPIC_GET_PATTERN[] = "$aws/things/%s/shadow/get%s";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_SUBTOPIC_NONE[] = "";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_SUBTOPIC_ACCEPTED[] = "/accepted";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_SUBTOPIC_REJECTED[] = "/rejected";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_SUBTOPIC_DELTA[] = "/delta";

ICACHE_RODATA_ATTR char const AWS_IOT_THING_SHADOW_REST_PATH_PATTERN[] = "/things/%s/shadow";
