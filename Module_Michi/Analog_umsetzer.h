/*
 * Analog_umsetzer.h
 *
 * Created: 08.07.2014 18:59:54
 *  Author: Michael
 */ 


#ifndef ANALOG_UMSETZER_H_
#define ANALOG_UMSETZER_H_

void ADC_init();	
uint16_t ADC_Read( uint8_t channel );
uint16_t ADC_Read_Avg( uint8_t channel, uint8_t nsamples );
uint16_t prozent(uint16_t input);
int adc_to_bargraph(uint16_t input);

#endif /* ANALOG_UMSETZER_H_ */