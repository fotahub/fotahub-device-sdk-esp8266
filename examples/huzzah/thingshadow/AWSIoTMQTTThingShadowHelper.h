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
#ifndef AWSIOTMQTTTHINGSHADOWHELPER_H
#define AWSIOTMQTTTHINGSHADOWHELPER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <c_types.h>
#include <osapi.h>
#include "AWSIoTDefinitions.h"
#include "MQTTDefinitions.h"

#ifdef __cplusplus
extern "C" {
#endif

void ICACHE_FLASH_ATTR buildAWSIoTThingShadowTopicName(char *topicName, char const *thingName, AWSIoTThingShadowAction_t action, AWSIoTThingShadowSubTopicKind_t subTopicKind);

AWSIoTThingShadowAction_t ICACHE_FLASH_ATTR getAWSIoTThingShadowActionfromTopicName(char *topicName, size_t topicNameLen);

AWSIoTThingShadowSubTopicKind_t ICACHE_FLASH_ATTR getAWSIoTThingShadowSubTopicfromTopicName(char *topicName, size_t topicNameLen);

AWSIoTThingShadowAckStatus_t ICACHE_FLASH_ATTR subTopicToAWSIoTThingShadowAckStatus(AWSIoTThingShadowSubTopicKind_t subTopic);

AWSIoTError_t ICACHE_FLASH_ATTR mqttToAWSIoTError(MQTTError_t mqttError);

char *ICACHE_FLASH_ATTR awsIoTThingShadowActionToString(AWSIoTThingShadowAction_t action);

char *ICACHE_FLASH_ATTR awsIoTThingShadowAckStatusToString(AWSIoTThingShadowAckStatus_t status);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
