/*
 *  user_interface_missing.h
 *
 *  Function prototypes, data types, etc. that are missing in Espressif SDK headers.
 *
 *  Created on: 26 mai 2016
 *      Author: steph
 */

#ifndef INCLUDE_USER_INTERFACE_MISSING_H_
#define INCLUDE_USER_INTERFACE_MISSING_H_

void system_overclock(void);
bool system_restoreclock(void);

uint8 system_get_data_of_array_8(const uint8* rodata, uint32 mask);
uint16 system_get_data_of_array_16(const uint16* rodata, uint32 mask);
void system_get_string_from_flash(const char* rostring, char* string, size_t string_size);

#endif /* INCLUDE_USER_INTERFACE_MISSING_H_ */
