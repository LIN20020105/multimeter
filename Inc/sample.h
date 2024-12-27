#pragma once
#include "main.h"
#define ADC_BUFFER_SIZE 100
#define IO_NB_NETMODE (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == 0 ? 0 : 1)
#define IO_NB_LINK (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == 0 ? 0 : 1)

void sample_adc(void);
void determine_phase_order (uint16_t *o1, uint16_t *o2, uint16_t *o3);
