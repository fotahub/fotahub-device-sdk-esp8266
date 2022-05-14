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
#include "MQTTPacketExtensions.h"

#include <MQTTPacket.h>

void ICACHE_FLASH_ATTR getMQTTPacketLengths(Datagram_t *pDatagram, MQTTPacketLengths_t *mqttPacketLengths)
{
  uint8_t multiplier = 1;
  
  do {
    mqttPacketLengths->payloadLength += (pDatagram->pVisiblePayload[mqttPacketLengths->headerLength] & 0x7Fu) * multiplier;
    multiplier *= 128;
    mqttPacketLengths->headerLength++;
  }
  while ((pDatagram->pVisiblePayload[mqttPacketLengths->headerLength - 1] & 128) != 0);
}
