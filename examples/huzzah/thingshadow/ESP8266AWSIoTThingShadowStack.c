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
#include "ESP8266AWSIoTThingShadowStack.h"

#include "ESP8266AWSIoTThingShadowConfiguration.h"
#include "user_config.h"

void ICACHE_FLASH_ATTR ESP8266AWSIoTThingShadowStack___setup(void *___id)
{
  ESP8266AWSIoTThingShadowStack__cdata_t *___cid = ((ESP8266AWSIoTThingShadowStack__cdata_t *) ___id);
  
  ___cid->thingShadowGateInst__field->connectionParameters__field = &awsIoTConnParams;
  ___cid->mqttClientInst__field->maxSubscribeMessageLength__field = DEFAULT_SUBSCRIBE_MESSAGE_LENGTH;
  ___cid->espConnClientInst__field->sessionBufferSize__field = TCP_CLIENT_SESSION_BUFFER_SIZE;
  
  
  AWSIoTThingShadowGateImpl_init(___cid->thingShadowGateInst__field);
  JSONProcessorImpl_init(___cid->jsonProcessorInst__field);
}
