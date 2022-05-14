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
#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <c_types.h>
#include <osapi.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t ICACHE_FLASH_ATTR strnlen(char const *str, size_t maxLen);

char *ICACHE_FLASH_ATTR StringHelper_strnstr(char *s1, size_t s1Len, char const *s2);

char *ICACHE_FLASH_ATTR strnchr(char *s, size_t len, int32_t charDelimitor);

size_t ICACHE_FLASH_ATTR strnspn(char const *s1, size_t s1Len, char const *s2);

size_t ICACHE_FLASH_ATTR strcnspn(char const *s1, size_t s1Len, char const *s2);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
