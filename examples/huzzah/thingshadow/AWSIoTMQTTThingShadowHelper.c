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
#include "AWSIoTMQTTThingShadowHelper.h"

#include "StringHelper.h"
#include <stdio.h>
#include <string.h>

void ICACHE_FLASH_ATTR buildAWSIoTThingShadowTopicName(char *topicName, char const *thingName, IoTAction_t action, IoTSubTopicKind_t subTopicKind)
{
  size_t length = os_strlen(thingName) - 3;
  
  if (action == IOT_ACTION_REPORT) 
  {
    length += AWS_IOT_THING_SHADOW_TOPIC_UPDATE_LENGTH;
    switch (subTopicKind)
    {
      case IOT_SUBTOPIC_KIND_ACCEPTED:
      {
        length += AWS_IOT_THING_SHADOW_SUBTOPIC_ACCEPTED_LENGTH;
        os_snprintf(topicName, length, ((char *)(AWS_IOT_THING_SHADOW_TOPIC_UPDATE_PATTERN)), thingName, ((char *)(AWS_IOT_THING_SHADOW_SUBTOPIC_ACCEPTED)));
        break;
      }
      case IOT_SUBTOPIC_KIND_REJECTED:
      {
        length += AWS_IOT_THING_SHADOW_SUBTOPIC_REJECTED_LENGTH;
        os_snprintf(topicName, length, ((char *)(AWS_IOT_THING_SHADOW_TOPIC_UPDATE_PATTERN)), thingName, ((char *)(AWS_IOT_THING_SHADOW_SUBTOPIC_REJECTED)));
        break;
      }
      case IOT_SUBTOPIC_KIND_DELTA:
      {
        length += AWS_IOT_THING_SHADOW_SUBTOPIC_DELTA_LENGTH;
        os_snprintf(topicName, length, ((char *)(AWS_IOT_THING_SHADOW_TOPIC_UPDATE_PATTERN)), thingName, ((char *)(AWS_IOT_THING_SHADOW_SUBTOPIC_DELTA)));
        break;
      }
      default: {
        os_snprintf(topicName, length, ((char *)(AWS_IOT_THING_SHADOW_TOPIC_UPDATE_PATTERN)), thingName, ((char *)(AWS_IOT_THING_SHADOW_SUBTOPIC_NONE)));
        break;
      }
    }
  }
  else if (action == IOT_ACTION_GET) {
    length += AWS_IOT_THING_SHADOW_TOPIC_GET_LENGTH;
    switch (subTopicKind)
    {
      case IOT_SUBTOPIC_KIND_ACCEPTED:
      {
        length += AWS_IOT_THING_SHADOW_SUBTOPIC_ACCEPTED_LENGTH;
        os_snprintf(topicName, length, ((char *)(AWS_IOT_THING_SHADOW_TOPIC_GET_PATTERN)), thingName, ((char *)(AWS_IOT_THING_SHADOW_SUBTOPIC_ACCEPTED)));
        break;
      }
      case IOT_SUBTOPIC_KIND_REJECTED:
      {
        length += AWS_IOT_THING_SHADOW_SUBTOPIC_ACCEPTED_LENGTH;
        os_snprintf(topicName, length, ((char *)(AWS_IOT_THING_SHADOW_TOPIC_GET_PATTERN)), thingName, ((char *)(AWS_IOT_THING_SHADOW_SUBTOPIC_REJECTED)));
        break;
      }
      default: {
        os_snprintf(topicName, length, ((char *)(AWS_IOT_THING_SHADOW_TOPIC_GET_PATTERN)), thingName, ((char *)(AWS_IOT_THING_SHADOW_SUBTOPIC_NONE)));
        break;
      }
    }
  }
  
  topicName[length] = '\0';
}

IoTAction_t ICACHE_FLASH_ATTR getAWSIoTThingShadowActionfromTopicName(char *topicName, size_t topicNameLen)
{
  if ((topicName == NULL) || (topicNameLen == 0)) 
  {
    return IOT_ACTION_INTERNAL;
  }
  
  if (StringHelper_strnstr(topicName, topicNameLen, ((char *)(AWS_IOT_THING_SHADOW_TOPIC_UPDATE))) != NULL) 
  {
    return IOT_ACTION_REPORT;
  }
  if (StringHelper_strnstr(topicName, topicNameLen, ((char *)(AWS_IOT_THING_SHADOW_TOPIC_GET))) != NULL) 
  {
    return IOT_ACTION_GET;
  }
  
  return IOT_ACTION_INTERNAL;
}

IoTSubTopicKind_t ICACHE_FLASH_ATTR getAWSIoTThingShadowSubTopicfromTopicName(char *topicName, size_t topicNameLen)
{
  if ((topicName == NULL) || (topicNameLen == 0)) 
  {
    return IOT_SUBTOPIC_KIND_NONE;
  }
  
  if (StringHelper_strnstr(topicName, topicNameLen, ((char *)(AWS_IOT_THING_SHADOW_SUBTOPIC_ACCEPTED))) != NULL) 
  {
    return IOT_SUBTOPIC_KIND_ACCEPTED;
  }
  if (StringHelper_strnstr(topicName, topicNameLen, ((char *)(AWS_IOT_THING_SHADOW_SUBTOPIC_REJECTED))) != NULL) 
  {
    return IOT_SUBTOPIC_KIND_REJECTED;
  }
  if (StringHelper_strnstr(topicName, topicNameLen, ((char *)(AWS_IOT_THING_SHADOW_SUBTOPIC_DELTA))) != NULL) 
  {
    return IOT_SUBTOPIC_KIND_DELTA;
  }
  return IOT_SUBTOPIC_KIND_NONE;
}

IoTResponseStatus_t ICACHE_FLASH_ATTR subTopicToAWSIoTThingShadowAckStatus(IoTSubTopicKind_t subTopic)
{
  switch (subTopic)
  {
    case IOT_SUBTOPIC_KIND_ACCEPTED:
    {
      return IOT_RESPONSE_STATUS_ACCEPTED;
    }
    case IOT_SUBTOPIC_KIND_REJECTED:
    {
      return IOT_RESPONSE_STATUS_REJECTED;
    }
    default: {
      return IOT_RESPONSE_STATUS_NONE;
    }
  }
}

char *ICACHE_FLASH_ATTR awsIoTThingShadowActionToString(IoTAction_t action)
{
  switch (action)
  {
    case IOT_ACTION_GET:
    {
      return "ThingShadow Get";
    }
    case IOT_ACTION_REPORT:
    {
      return "ThingShadow Update";
    }
    case IOT_ACTION_DELETE:
    {
      return "ThingShadow Delete";
    }
    case IOT_ACTION_INTERNAL:
    {
      return "ThingShadow None";
    }
    default: {
      return "Unknown";
    }
  }
}

char *ICACHE_FLASH_ATTR awsIoTThingShadowAckStatusToString(IoTResponseStatus_t status)
{
  switch (status)
  {
    case IOT_RESPONSE_STATUS_TIMEOUT:
    {
      return "Timeout";
    }
    case IOT_RESPONSE_STATUS_REJECTED:
    {
      return "Rejected";
    }
    case IOT_RESPONSE_STATUS_ACCEPTED:
    {
      return "Accepted";
    }
    case IOT_RESPONSE_STATUS_NONE:
    {
      return "None";
    }
    default: {
      return "Unknown";
    }
  }
}
