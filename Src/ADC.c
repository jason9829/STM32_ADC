#include "ADC.h"
#include "common.h"
#include "RCC.h"

void adcEnableClock(adcRegs *adc){
	RESET_ADC_CLK_GATING();
	UNRESET_ADC_CLK_GATING();

	if(adc == adc1)
		ENABLE_ADC1_CLK_GATING();
	else if(adc == adc2)
		ENABLE_ADC2_CLK_GATING();
	else if(adc == adc3)
		ENABLE_ADC3_CLK_GATING();

}

/**
 * @desc Configure the sampling sequence of regular ADC channels
 * @param adc is the pointer to the registers
 * @param channel is an array of channels (the first element is the first in
 * sequence and the channel number must be in between 0..18)
 * @param numOfChan is the number of channels in the array (the number must be
 * between 1..16)
 */

void adcSetChannelSamplingSequence(adcRegs *adc, int channels[], int numOfChan){

	if(numOfChan == 0)
		return;

	IoRegister *seqRegPtr = &((adc)->SQR3);
	(adc)->SQR1 |= (numOfChan <<20);
	int shift = 0;
	for(int i = 1; i <=numOfChan; i++){
		if(i == 13){
			shift = 0;
			seqRegPtr -= 2;
		}
		if(i == 7){
			shift = 0;
			seqRegPtr -= 1;
		}
		*seqRegPtr |= (channels[i-1] << (shift * 5));
		shift++;
	}
}

/**
 * @desc Configure the sampling time (in cycles) of a ADC channel
 * @param adc is the pointer to the registers
 * @param channel is the channel to configure (the channel number must be 0..18)
 * @param cycles is the sampling time in number of cycles:
 * ADC_3_CYCLES
 * ADC_15_CYCLES
 * ADC_28_CYCLES
 * ADC_56_CYCLES
 * ADC_84_CYCLES
 * ADC_112_CYCLES
 * ADC_144_CYCLES
 * ADC_480_CYCLES
 */

void adcChannelSamplingTime(adcRegs *adc, int channel, int cycles){

	IoRegister *sampleRegPtr = &((adc)->SMPR2);
	int shift;
	shift = channel;
	if(channel > 9){
		sampleRegPtr--;
		shift -=10;
	}
	*sampleRegPtr |= (cycles << (shift * 3));

}

// Combined the configuration of CR1 and CR2
void configureADC(adcRegs *adc, long long mode){
	(adc)->CR1 = (uint32_t)(mode & 0xffffffff);
	(adc)->CR2 = (uint32_t)((mode>>32) & 0xffffffff);
}
