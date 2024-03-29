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
#ifndef JSONPROCESSORIMPL_H
#define JSONPROCESSORIMPL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <c_types.h>
#include <osapi.h>
#include "JSON.h"
#include "JSONTreeExtensions.h"
#include <jsonparse.h>

#ifdef __cplusplus
extern "C" {
#endif

struct JSONProcessorCtx {
  bool busy;
};
typedef struct JSONProcessorCtx JSONProcessorCtx_t;

struct JSONParseCtx {
  bool busy;
  struct jsontree_context treeCtx;
  struct jsonparse_state parseState;
  IJSONDocumentIOHandler__idata_t *documentIOHandler;
  void *pUserData;
};
typedef struct JSONParseCtx JSONParseCtx_t;

struct JSONSerializeCtx {
  bool busy;
  struct jsontree_context treeCtx;
  struct jsontree_msg msgState;
  IJSONDocumentIOHandler__idata_t *documentIOHandler;
  void *pUserData;
};
typedef struct JSONSerializeCtx JSONSerializeCtx_t;

struct JSONProcessorImpl__cdata {
  /* 
   * fields
   */
  JSONParseCtx_t parseCtx__field;
  /* 
   * fields
   */
  JSONSerializeCtx_t serializeCtx__field;
};
typedef struct JSONProcessorImpl__cdata JSONProcessorImpl__cdata_t;

void ICACHE_FLASH_ATTR delegatingJSONTreeInputHandler(struct jsontree_context *pTreeCtx, struct jsonparse_state *pParseState);

int32_t ICACHE_FLASH_ATTR delegatingJSONTreeOutputHandler(struct jsontree_context *pTreeCtx, struct jsontree_msg *pMsg);

void ICACHE_FLASH_ATTR JSONProcessorImpl_init(void *___id);

JSONParseCtx_t *ICACHE_FLASH_ATTR JSONProcessorImpl_newJSONParseCtx(void *___id);

JSONSerializeCtx_t *ICACHE_FLASH_ATTR JSONProcessorImpl_newJSONSerializeCtx(char *msg, size_t msgSize, void *___id);

void ICACHE_FLASH_ATTR JSONProcessorImpl_deleteJSONProcessorCtx(JSONProcessorCtx_t *pProcessorCtx, void *___id);

bool ICACHE_FLASH_ATTR JSONProcessorImpl_jsonParser_parse(struct jsontree_value *pDocumentModel, IJSONDocumentIOHandler__idata_t *documentIOHandler, void *pUserData, char *msg, size_t msgLength, void *___id);

void ICACHE_FLASH_ATTR JSONProcessorImpl_jsonParser_resetFlags(struct jsontree_value *pDocumentModel, void *___id);

bool ICACHE_FLASH_ATTR JSONProcessorImpl_jsonSerializer_serialize(struct jsontree_value *pDocumentModel, JSONObjectSerializationMode_t mode, IJSONDocumentIOHandler__idata_t *documentIOHandler, void *pUserData, char *msg, size_t msgSize, void *___id);

void const* ICACHE_FLASH_ATTR JSONProcessorImpl_jsonSerializer_beginDocument(struct jsontree_value *pDocumentModel, IJSONDocumentIOHandler__idata_t *documentIOHandler, void *pUserData, char *msg, size_t msgSize, void *___id);

bool ICACHE_FLASH_ATTR JSONProcessorImpl_jsonSerializer_beginObject(void const* hDocument, char const *path, void *___id);

bool ICACHE_FLASH_ATTR JSONProcessorImpl_jsonSerializer_addValue(void const* hDocument, char const *path, JSONObjectSerializationMode_t mode, void *___id);

bool ICACHE_FLASH_ATTR JSONProcessorImpl_jsonSerializer_endObject(void const* hDocument, void *___id);

bool ICACHE_FLASH_ATTR JSONProcessorImpl_jsonSerializer_endDocument(void const* hDocument, void *___id);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
