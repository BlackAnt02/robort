#ifndef _BSP_GPIO_H
#define _BSP_GPIO_H

#include "stm32f10x.h"
#include <assert.h>
typedef enum
{
	U_GPIO_A = 0,
	U_GPIO_B,
	U_GPIO_C,
	U_GPIO_D,
	U_GPIO_E,
	U_GPIO_F,
	U_GPIO_G,
}GPIO_IDX_TAG;

typedef enum
{
	U_PIN_0 = 0,
	U_PIN_1,
	U_PIN_2,
	U_PIN_3,
	U_PIN_4,
	U_PIN_5,
	U_PIN_6,
	U_PIN_7,
	U_PIN_8,
	U_PIN_9,
	U_PIN_10,
	U_PIN_11,
	U_PIN_12,
	U_PIN_13,
	U_PIN_14,
	U_PIN_15,
}GPIO_PIN_TAG;


typedef enum
{
	U_PP = 0,
}GPIO_MODE_TAG;

void STM32_GPIO_SetPin( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, u8 val);
void STM32_GPIO_ConfgPin(uint8_t gpio, uint8_t pin, uint8_t mode);


#endif
