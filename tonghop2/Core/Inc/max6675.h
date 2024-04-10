/*
 * max6675.h
 *
 *  Created on: Apr 9, 2023
 *      Author: Alcides Ramos
 */

#ifndef LIBRERIAS_MAX6675_H_
#define LIBRERIAS_MAX6675_H_

#include "main.h"

#define CK_MAX_GPIO_Port	GPIOA
#define CK_MAX_Pin 				GPIO_PIN_4

#define DAT_MAX_GPIO_Port	GPIOA
#define DAT_MAX_Pin				GPIO_PIN_3


#define CS_MAX_GPIO_Port	GPIOA
#define CS_MAX_Pin			GPIO_PIN_5



void MAX6675_init();
uint8_t MAX6675_pulso();
float MAX6675_lee();

#endif /* LIBRERIAS_MAX6675_H_ */
