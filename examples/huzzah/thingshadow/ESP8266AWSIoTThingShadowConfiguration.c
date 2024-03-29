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
#include "ESP8266AWSIoTThingShadowConfiguration.h"

#include "user_config.h"

SecureConnectionParameters_t secureSocketParams = 
{
  .maxFragmentLength = TLS_MAX_FRAGMENT_LENGTH_DISABLED, 
  .maxDataRate = TLS_MAX_DATA_RATE_NONE, 
  .readTimeout = 2000, 
  .authenticateServer = true, 
  .rootCACertsAddress = 0xF8u, 
  .clientCertAddress = 0xF9u
};

HostNameEndpointAddress_t hostNameEndPoint = 
{
  .type = ENDPOINT_ADDRESS_TYPE_HOST_NAME, 
  .hostName = "<Your AWS IoT device data endpoint>"
};

SocketConnectionParameters_t socketParams = 
{
  .type = SOCKET_CONNECTION_TYPE_TCP, 
  .pAddr = ((EndpointAddress_t *)(&hostNameEndPoint)), 
  .port = 8883, 
  .pSecureConnectionParams = &secureSocketParams
};

MQTTConnectionParameters_t mqttParams = 
{
  .clientID = NULL, 
  .userName = NULL, 
  .password = NULL, 
  .isCleanSession = true, 
  .keepAliveInterval = MQTT_MAX_KEEP_ALIVE_VALUE, 
  .keepAliveIntervalScale = ((float)(MQTT_KEEP_ALIVE_VALUE_SCALE)), 
  .keepAliveTimeoutInterval = MQTT_MAX_KEEP_ALIVE_TIMEOUT_VALUE, 
  .pSocketConnectionParams = &socketParams
};

IoTConnectionParameters_t awsIoTConnParams = 
{
  .deviceName = "FotaHubExampleThing", 
  .qos = IOT_QOS_0, 
  .timeout = 12, 
  .pDownstreamConnParams = &mqttParams
};
