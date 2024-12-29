#include "sample.h"

#include "adc.h"
#include "main.h"

#include "gpio.h"
#include "usart.h"
#include "math.h"
#include "tim.h"
#include <stdlib.h>
#include "string.h"
//uint16_t adc_data_1[ADC_BUFFER_SIZE];
//uint16_t adc_data_2[ADC_BUFFER_SIZE];
//uint16_t adc_data_3[ADC_BUFFER_SIZE];
//uint16_t adc_data_4[ADC_BUFFER_SIZE];
//uint32_t adc1_idx = 0;
//uint32_t adc2_idx = 0;
//uint32_t adc3_idx = 0;
//uint32_t adc4_idx = 0;
uint32_t ADC_zcount[3];
uint32_t ADC_ztime[3];
double ADC_SUM[3];
double RMS[3];
uint32_t adc_index = 0;
uint32_t send_flag = 0;

/**
 * @brief
 *
 * @param push_to_pkg
 * push_to_pkg: 0: not push to package, 1: push to package
 */
void sample_adc(void) {


  for (int i = 0; i < 4; i++) {
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK) {
      ADC_Buffer[i] = HAL_ADC_GetValue(&hadc1);
    }
  }
	for (int i = 0; i < 3; i++) {
		if (ADC_Buffer[i] <ADC_Buffer[3]) {
			ADC_zcount[i]++;
		}		
		else if (ADC_Buffer[i] >= ADC_Buffer[3] && ADC_zcount[i] > 4) {
			ADC_ztime[i] = HAL_GetTick();
			ADC_zcount[i] = 0;
		}
		ADC_SUM[i] += (ADC_Buffer[i] - ADC_Buffer[3]) * (ADC_Buffer[i] - ADC_Buffer[3]);
	}
//  adc_data_1[adc1_idx] = ADC_Buffer[0];
//  adc_data_2[adc2_idx] = ADC_Buffer[1];
//  adc_data_3[adc3_idx] = ADC_Buffer[2];
//  adc_data_4[adc4_idx] = ADC_Buffer[3];

//  adc1_idx = (adc1_idx + 1) % ADC_BUFFER_SIZE;
//  adc2_idx = (adc2_idx + 1) % ADC_BUFFER_SIZE;
//  adc3_idx = (adc3_idx + 1) % ADC_BUFFER_SIZE;
//  adc4_idx = (adc4_idx + 1) % ADC_BUFFER_SIZE;

}
//1ms adc
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if (htim->Instance == TIM2){
			sample_adc();
			if (0 == (adc_index % ADC_BUFFER_SIZE)) {
			for(int i =0; i<3; i++){
				RMS[i] = sqrt(ADC_SUM[i] /ADC_BUFFER_SIZE ); 
				ADC_SUM[i] = 0;
			}
		}
			adc_index ++;
			if (adc_index == (100 * ADC_BUFFER_SIZE + 1) ) {
			adc_index  = 0;
			send_flag = 1;
			}
	}
}
void determine_phase_order (uint16_t *o1, uint16_t *o2, uint16_t *o3) {
	int BA = (ADC_ztime[1] - ADC_ztime[2]) * (360 / 20); //note: 50hz signal <==> 20ms 
	int CA = (ADC_ztime[0] - ADC_ztime[2]) * (360 / 20);
	BA = BA % 360;
	CA = CA % 360;
	if (BA < 0) BA += 360;
	if (CA < 0) CA += 360;
	*o1 = 0;
	*o2 = CA <= BA ? 2: 1;
	*o3 = (*o2) == 1? 2: 1;
}

