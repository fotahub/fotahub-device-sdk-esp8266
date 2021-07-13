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
#include "MultiPartitionAWSIoTThingShadowDataPlane.h"

#include "FotaHub.h"
#include "DemoProductInfo.h"
#include "BinHexConverter.h"
#include <stdlib.h>
#include <string.h>

static char updateVersion[MAX_DEMO_FIRMWARE_UPDATE_VERSION_LENGTH + 1] = { 0 };

static uint8_t *MultiPartitionAWSIoTThingShadowDataPlane_updateVerificationData[UPDATE_PARTITION_COUNT] = { 0 };

void ICACHE_FLASH_ATTR fotahub_onProvideFirmwareUpdateVerificationInfo(FirmwareUpdateInfo_t const *pUpdateInfo, FOTAUpdateVerificationAlgorithm_t *pVerificationAlgorithm, uint8_t const  **ppVerificationData)
{
  *pVerificationAlgorithm = DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM;
  if (pUpdateInfo->partitionIdx >= 0 && pUpdateInfo->partitionIdx < UPDATE_PARTITION_COUNT) 
  {
    *ppVerificationData = MultiPartitionAWSIoTThingShadowDataPlane_updateVerificationData[((size_t)(pUpdateInfo->partitionIdx))];
  }
  else
  {
    *ppVerificationData = NULL;
  }
}

void ICACHE_FLASH_ATTR MultiPartitionAWSIoTThingShadowIOHandlerImpl_init(void *___id)
{
  MultiPartitionAWSIoTThingShadowIOHandlerImpl__cdata_t *___cid = ((MultiPartitionAWSIoTThingShadowIOHandlerImpl__cdata_t *) ___id);
  ___cid->firmwareUpdateVersionInfo__srdata.updateVersion = updateVersion;
  
  size_t updateVerificationDataSize = getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM);
  for ( int16_t __i = 0 ; __i < UPDATE_PARTITION_COUNT; __i++ )
  {
    MultiPartitionAWSIoTThingShadowDataPlane_updateVerificationData[__i] = ((uint8_t *)(os_malloc(updateVerificationDataSize)));
    os_memset(MultiPartitionAWSIoTThingShadowDataPlane_updateVerificationData[__i], 0, updateVerificationDataSize);
  }
}

bool ICACHE_FLASH_ATTR MultiPartitionAWSIoTThingShadowIOHandlerImpl_jsonDocumentIOHandler_writeOutput(struct jsontree_context *pTreeCtx, struct jsontree_msg *pMsg, void *pUserData, void *___id)
{
  char const *path = jsontree_path_name(pTreeCtx);
  if (os_strncmp(path, ((char *)(AWS_IOT_THING_SHADOW_JSON_ATTRIBUTE_UPDATE_CURRENT_VERSION)), os_strlen(((char *)(AWS_IOT_THING_SHADOW_JSON_ATTRIBUTE_UPDATE_CURRENT_VERSION)))) == 0) 
  {
    jsontree_write_string(pMsg, ((char *)(DEMO_PRODUCT_FIRMWARE_VERSION)), ((int32_t)(os_strlen(((char *)(DEMO_PRODUCT_FIRMWARE_VERSION))))));
  }
  /* 
   * Return false to say that we don't need to output any other siblings (object attributes or array items) than we actually did at this time
   */
  return false;
}

void ICACHE_FLASH_ATTR MultiPartitionAWSIoTThingShadowIOHandlerImpl_jsonDocumentIOHandler_readInput(struct jsontree_context *pTreeCtx, struct jsonparse_state *pParser, void *pUserData, void *___id)
{
  char const *path = jsontree_path_name(pTreeCtx);
  if (os_strncmp(path, ((char *)(AWS_IOT_THING_SHADOW_JSON_ATTRIBUTE_UPDATE_NEW_VERSION)), os_strlen(((char *)(AWS_IOT_THING_SHADOW_JSON_ATTRIBUTE_UPDATE_NEW_VERSION)))) == 0) 
  {
    jsonparse_copy_value_as_string(pParser, updateVersion, ((int32_t)(sizeof(updateVersion))));
  }
  else if (os_strncmp(path, ((char *)(AWS_IOT_THING_SHADOW_JSON_ATTRIBUTE_UPDATE_VERIFICATION_DATA)), os_strlen(((char *)(AWS_IOT_THING_SHADOW_JSON_ATTRIBUTE_UPDATE_VERIFICATION_DATA)))) == 0) {
    char const *value = jsonparse_get_value(pParser);
    size_t valueLength = ((size_t)(jsonparse_get_len(pParser)));
    size_t updateVerificationDataSize = getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM);
    for ( int16_t __i = 0 ; __i < UPDATE_PARTITION_COUNT; __i++ )
    {
      convertHexString8ToBinData(((char *)(value + __i * (valueLength >> 1))), valueLength >> 1, MultiPartitionAWSIoTThingShadowDataPlane_updateVerificationData[__i], updateVerificationDataSize);
    }
  }
}
