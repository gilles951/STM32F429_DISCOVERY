/*
 * compact_lib.h
 *
 *  Created on: 11-nov.-2015
 *      Author: michiel
 */

#ifndef COMPACT_LIB_STM32F4_H_
#define COMPACT_LIB_STM32F4_H_
#include "compact_lib_stm32f4.cpp"
#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"

#define LED_GREEN					GPIO_Pin_13
#define LED_RED					    GPIO_Pin_14

#define on					        Bit_SET
#define off					        Bit_RESET



void GPIO_write_led(int led , BitAction toestand);




#endif /* COMPACT_LIB_STM32F4_H_ */
