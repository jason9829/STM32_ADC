#ifndef __ADC_H__
#define __ADC_H__

#include <stdint.h>
#include "common.h"

typedef struct adcRegs adcRegs;
struct adcRegs{
	IoRegister SR;		// 0x00
	IoRegister CR1;		// 0x04
	IoRegister CR2;		// 0x08
	IoRegister SMPR1;	// 0x0c
	IoRegister SMPR2;	// 0x10
	IoRegister JOFR1;	// 0x14
	IoRegister JOFR2;	// 0x18
	IoRegister JOFR3;	// 0x1c
	IoRegister JOFR4;	// 0x20
	IoRegister HTR;		// 0x24
	IoRegister LTR;		// 0x28
	IoRegister SQR1;	// 0x2c
	IoRegister SQR2;	// 0x30
	IoRegister SQR3;	// 0x34
	IoRegister JSQR;	// 0x3c
	IoRegister JDR1;	// 0x38
	IoRegister JDR2;	// 0x40
	IoRegister JDR3;	// 0x44
	IoRegister JDR4;	// 0x48
	IoRegister DR;		// 0x4c
};

typedef struct c_adcRegs c_adcRegs;
struct c_adcRegs{
	IoRegister CSR;		// 0x00
	IoRegister CCR;		// 0x04
	IoRegister CDR;		// 0x08
};

#define adc1		(adcRegs*)(0x40012000)
#define adc2		(adcRegs*)(0x40012100)
#define adc3		(adcRegs*)(0x40012200)
#define c_adc		(c_adcRegs*)(0x40012300)


/**************ADC status register (ADC_SR)*********************/
#define ADC_AWD		1 << 0	// Analog watchdog flag
#define ADC_EOC		1 << 1	// Regular channel end of conversion
#define ADC_JEOC	1 << 2	// Injected channel end of conversion
#define ADC_JSTRT	1 << 3	// Injected channel start flag
#define ADC_STRT	1 << 4	// Regular channel start flag
#define ADC_OVR		1 << 5	// Overrun flag

/**************ADC control register 1 (ADC_CR1)******************/
#define ADC_AWDCH_0		(0ULL)	// ADC analog input Channel 0
#define ADC_AWDCH_1		(1ULL)	// ADC analog input Channel 1
#define ADC_AWDCH_2		(2ULL)	// ADC analog input Channel 2
#define ADC_AWDCH_3		(3ULL)	// ADC analog input Channel 3
#define ADC_AWDCH_4		(4ULL)	// ADC analog input Channel 4
#define ADC_AWDCH_5		(5ULL)	// ADC analog input Channel 5
#define ADC_AWDCH_6		(6ULL)	// ADC analog input Channel 6
#define ADC_AWDCH_7		(7ULL)	// ADC analog input Channel 7
#define ADC_AWDCH_8		(8ULL)	// ADC analog input Channel 8
#define ADC_AWDCH_9		(9ULL)	// ADC analog input Channel 9
#define ADC_AWDCH_10	(10ULL)	// ADC analog input Channel 10
#define ADC_AWDCH_11	(11ULL)	// ADC analog input Channel 11
#define ADC_AWDCH_12	(12ULL)	// ADC analog input Channel 12
#define ADC_AWDCH_13	(13ULL)	// ADC analog input Channel 13
#define ADC_AWDCH_14	(14ULL)	// ADC analog input Channel 14
#define ADC_AWDCH_15	(15ULL)	// ADC analog input Channel 15
#define ADC_AWDCH_16	(16ULL)	// ADC analog input Channel 16
#define ADC_AWDCH_17	(17ULL)	// ADC analog input Channel 17
#define ADC_AWDCH_18	(18ULL)	// ADC analog input Channel 18

#define ADC_EOCIE		(1ULL << 5)		// Enable end of conversion (EOC) interrupt
#define ADC_AWDIE		(1ULL << 6) 	// Enable Analog watchdog interrupt enable
#define ADC_JEOCIE		(1ULL << 7)		// Enable interrupt for injected channels
#define ADC_SCAN_EN		(1ULL << 8) 	// Enable scan mode
#define ADC_AWDSGL_EN	(1ULL << 9)		// Enable watchdog on single channel, default is all channels
#define ADC_JAUTO_EN	(1ULL << 10)    // Enable automatic injected group conversion
#define ADC_DISCEN		(1ULL << 11)    // Enable discontinuous mode on regular channels
#define ADC_JDISCEN		(1ULL << 12)    // Enable discontinuous mode on injected channels

#define ADC_DISCNUM_1		(0ULL << 13)	// Discontinuous mode channel count, 1 channel
#define ADC_DISCNUM_2		(1ULL << 13)	// Discontinuous mode channel count, 2 channels
#define ADC_DISCNUM_3		(2ULL << 13)	// Discontinuous mode channel count, 3 channels
#define ADC_DISCNUM_4		(3ULL << 13)	// Discontinuous mode channel count, 4 channels
#define ADC_DISCNUM_5		(4ULL << 13)	// Discontinuous mode channel count, 5 channels
#define ADC_DISCNUM_6		(5ULL << 13)	// Discontinuous mode channel count, 6 channels
#define ADC_DISCNUM_7		(6ULL << 13)	// Discontinuous mode channel count, 7 channels
#define ADC_DISCNUM_8		(7ULL << 13)	// Discontinuous mode channel count, 8 channels

#define ADC_JAWDEN			(1ULL << 22) // Enable Analog watchdog on injected channels
#define ADC_AWDEN			(1ULL << 23) // Enable Analog watchdog on regular channels

#define ADC_RES_12			(0ULL << 24) // Resolution 12-bit (15ADCCLK cycles)
#define ADC_RES_10			(1ULL << 24) // Resolution 10-bit (10ADCCLK cycles)
#define ADC_RES_8			(2ULL << 24) // Resolution 8-bit (8ADCCLK cycles)
#define ADC_RES_6			(3ULL << 24) // Resolution 6-bit (9ADCCLK cycles)

#define ADC_OVRIE			(1ULL << 26)	// Enable overrun interrupt


/**************ADC control register 2 (ADC_CR2)******************/
#define ADC_ADON			(1ULL << 32)   	 // Enable ADC
#define ADC_CONT			(1ULL << 33)	 // Continuous conversion mode, default is single conversion
#define ADC_DMA				(1ULL << 40)	 // Enable DMA, for single ADC mode
#define ADC_DDS				(1ULL << 41)	 // Disable DMA selection, DMA requests issue as long as
									 	 	 // data are converted and DMA is enable for single ADC mode
#define ADC_EOCS				(1ULL << 42)	 // End of conversion selection (overrun detection when DMA enabled)
#define ADC_LEFT_ALIGN			(1ULL << 43)	 // Data left alignment, default right alignment
#define ADC_RIGHT_ALIGN			(0ULL << 43)	 // Data left alignment, default right alignment

#define ADC_JEXTSEL_TIM1_CC4	(0ULL << 48)	// Timer 1 CC4 event
#define ADC_JEXTSEL_TIM1_TRGO	(1ULL << 48)	// Timer 1 TRGO event
#define ADC_JEXTSEL_TIM2_CC1	(2ULL << 48)	// Timer 2 CC1 event
#define ADC_JEXTSEL_TIM2_TRGO	(3ULL << 48)	// Timer 2 TRGO event
#define ADC_JEXTSEL_TIM3_CC2	(4ULL << 48)	// Timer 3 CC2 event
#define ADC_JEXTSEL_TIM3_CC4	(5ULL << 48)	// Timer 3 CC4 event
#define ADC_JEXTSEL_TIM4_CC1	(6ULL << 48)	// Timer 4 CC1 event
#define ADC_JEXTSEL_TIM4_CC2	(7ULL << 48)	// Timer 4 CC2 event
#define ADC_JEXTSEL_TIM4_CC3	(8ULL << 48)	// Timer 4 CC3 event
#define ADC_JEXTSEL_TIM4_TRGO	(9ULL << 48)	// Timer 4 TRGO event
#define ADC_JEXTSEL_TIM5_CC4	(10ULL << 48)	// Timer 5 CC4 event
#define ADC_JEXTSEL_TIM5_TRGO	(11ULL << 48)	// Timer 5 TRGO event
#define ADC_JEXTSEL_TIM8_CC2	(12ULL << 48)	// Timer 8 CC2 event
#define ADC_JEXTSEL_TIM8_CC3	(13ULL << 48)	// Timer 8 CC3 event
#define ADC_JEXTSEL_TIM8_CC4	(14ULL << 48)	// Timer 8 CC4 event
#define ADC_JEXTSEL_EXTI_LINE15		(15ULL << 48)	//  EXTI line15

#define ADC_JEXTEN_DIS				(0ULL << 52)		// External trigger enable for injection channels,
													// Trigger detection disable
#define ADC_JEXTEN_RISE_EDGE		(1ULL << 52)		// Trigger detection on rising edge
#define ADC_JEXTEN_FALL_EDGE		(2ULL << 52)		// Trigger detection on falling edge
#define ADC_JEXTEN_RISE_FALL		(3ULL << 52)		// Trigger detection on both rising and falling edge

#define ADC_JSWSTART				(1ULL << 54)		// Starts conversion of injected channels

#define ADC_EXTSEL_TIM1_CC1			(0ULL << 56)		// Timer 1 CC1 event
#define ADC_EXTSEL_TIM1_CC2			(1ULL << 56)		// Timer 1 CC2 event
#define ADC_EXTSEL_TIM1_CC3			(2ULL << 56)		// Timer 1 CC3 event
#define ADC_EXTSEL_TIM2_CC2			(3ULL << 56)		// Timer 2 CC2 event
#define ADC_EXTSEL_TIM2_CC3			(4ULL << 56)		// Timer 2 CC3 event
#define ADC_EXTSEL_TIM2_CC4			(5ULL << 56)		// Timer 2 CC4 event
#define ADC_EXTSEL_TIM2_TRGO		(6ULL << 56)		// Timer 2 TRGO event
#define ADC_EXTSEL_TIM3_CC1			(7ULL << 56)		// Timer 3 CC1 event
#define ADC_EXTSEL_TIM3_TRGO		(8ULL << 56)		// Timer 3 TRGO event
#define ADC_EXTSEL_TIM4_CC4			(9ULL << 56)		// Timer 4 CC4 event
#define ADC_EXTSEL_TIM5_CC1			(10ULL << 56)		// Timer 5 CC1 event
#define ADC_EXTSEL_TIM5_CC2			(11ULL << 56)		// Timer 5 CC2 event
#define ADC_EXTSEL_TIM5_CC3			(12ULL << 56) 		// Timer 5 CC3 event
#define ADC_EXTSEL_TIM8_CC1			(13ULL << 56)		// Timer 8 CC1 event
#define ADC_EXTSEL_TIM8_TRGO		(14ULL << 56)		// Timer 8 TRGO event
#define ADC_EXTSEL_EXTI_LINE11		(15ULL << 56)		// EXTI line11

												// External trigger enable for regular channels,
#define ADC_EXTEN_DIS				(0ULL << 60)		// Trigger detection disabled
#define ADC_EXTEN_RISE_EDGE			(1ULL << 60)		// Trigger detection on the rising edge
#define ADC_EXTEN_FALL_EDGE			(2ULL << 60)		// Trigger detection on the falling edge
#define ADC_EXTEN_RISE_FALL			(3ULL << 60)		// Trigger detection on both the rising and falling edges

#define ADC_SWSTART					(1ULL << 62)		// Starts conversion of regular channels

/*************************Channels*************************/
#define ADC_CH_0		0	// ADC Channel 0
#define ADC_CH_1		1	// ADC Channel 1
#define ADC_CH_2		2	// ADC Channel 2
#define ADC_CH_3		3	// ADC Channel 3
#define ADC_CH_4		4	// ADC Channel 4
#define ADC_CH_5		5	// ADC Channel 5
#define ADC_CH_6		6	// ADC Channel 6
#define ADC_CH_7		7	// ADC Channel 7
#define ADC_CH_8		8	// ADC Channel 8
#define ADC_CH_9		9	// ADC Channel 9
#define ADC_CH_10		10	// ADC Channel 10
#define ADC_CH_11		11	// ADC Channel 11
#define ADC_CH_12		12	// ADC Channel 12
#define ADC_CH_13		13	// ADC Channel 13
#define ADC_CH_14		14	// ADC Channel 14
#define ADC_CH_15		15	// ADC Channel 15
#define ADC_CH_16		16	// ADC Channel 16
#define ADC_CH_17		17	// ADC Channel 17
#define ADC_CH_18		18	// ADC Channel 18


/*********************ADC Sampling Timing******************/
#define ADC_SAMP_3_CYCLES	0	// Sampling time is 3 cycles
#define ADC_SAMP_15_CYCLES	1	// Sampling time is 15 cycles
#define ADC_SAMP_28_CYCLES	2	// Sampling time is 28 cycles
#define ADC_SAMP_56_CYCLES	3	// Sampling time is 56 cycles
#define ADC_SAMP_84_CYCLES	4	// Sampling time is 84 cycles
#define ADC_SAMP_112_CYCLES	5	// Sampling time is 112 cycles
#define ADC_SAMP_144_CYCLES	6	// Sampling time is 144 cycles
#define ADC_SAMP_480_CYCLES	7	// Sampling time is 480 cycles




/********************Common ADC*****************************/
// ADC common status register (ADC_CSR)
#define C_ADC_AWD1		1			// Analog watchdog flag of ADC1
#define C_ADC_EOC1		(1 << 1)	// End of conversion of ADC1
#define C_ADC_JEOC1		(1 << 2)	// Injected channel end of conversion of ADC1
#define C_ADC_JSTRT1	(1 << 3)	// Injected channel Start flag of ADC1
#define C_ADC_STRT1		(1 << 4)	// Regular channel Start flag of ADC1
#define C_ADC_OVR1		(1 << 5)	// Overrun flag of ADC1

#define C_ADC_AWD2		(1 << 8)	// Analog watchdog flag of ADC2
#define C_ADC_EOC2		(1 << 9)	// End of conversion of ADC2
#define C_ADC_JEOC2		(1 << 10)	// Injected channel end of conversion of ADC2
#define C_ADC_JSTRT2	(1 << 11)	// Injected channel Start flag of ADC2
#define C_ADC_STRT2		(1 << 12)	// Regular channel Start flag of ADC2
#define C_ADC_OVR2		(1 << 13)	// Overrun flag of ADC2

#define C_ADC_AWD3		(1 << 16)	// Analog watchdog flag of ADC3
#define C_ADC_EOC3		(1 << 17)	// End of conversion of ADC3
#define C_ADC_JEOC3		(1 << 18)	// Injected channel end of conversion of ADC3
#define C_ADC_JSTRT3	(1 << 19)	// Injected channel Start flag of ADC3
#define C_ADC_STRT3		(1 << 20)	// Regular channel Start flag of ADC3
#define C_ADC_OVR3		(1 << 21)	// Overrun flag of ADC3

//	ADC common control register (ADC_CCR)
// Multi ADC mode selection
#define C_ADC_INDEPENDENT		0 	// All ADCs are independent
// ADC1 & ADC2
#define C_ADC12_CRSNISM_		1	// Combined regular simultaneous + injected simultaneous mode
#define C_ADC12_CRSNATM			2	// Combined regular simultaneous + alternate trigger mode
#define C_ADC12_ISM				5	// Injected simultaneous mode only
#define C_ADC12_RSM				6	// Regular simultaneous mode only
#define C_ADC12_INTERLEAVED		7	// Interleaved mode only
#define C_ADC12_ALTM			9	// Alternate trigger mode only
// ADC1 & ADC2 & ADC3
#define C_ADC123_CRSNISM		17	// Refer above
#define C_ADC123_CRSNATM		18	// Combined regular simultaneous + alternate trigger mode
#define C_ADC123_ISM			21	// Injected simultaneous mode only
#define C_ADC123_RSM			22	// Regular simultaneous mode only
#define C_ADC123_INTERLEAVED	23	// Interleaved mode only
#define C_ADC123_ALTM			25	// Alternate trigger mode only

#define C_ADC_VBATE				(1 << 22)	// VBAT enable
#define C_ADC_TSVREFE			(1 << 23)	// Temperature sensor and VREFINT enable

#define C_ADC_ADCPRE2			(0 << 16)	// PCLK2 divided by 2
#define C_ADC_ADCPRE4			(1 << 16)	// PCLK2 divided by 4
#define C_ADC_ADCPRE6			(2 << 16)	// PCLK2 divided by 6
#define C_ADC_ADCPRE8			(3 << 16)	// PCLK2 divided by 8

#define adcClearAllFlags(adc)	adcClearFlag(adc, ADC_AWD | ADC_EOC | ADC_JEOC | \
								ADC_JSTRT | ADC_STRT | ADC_OVR)
#define adcClearFlag(adc, whichFlag)	((adc)->SR &= ~(whichFlag))
#define adcGetStatus(adc, whichFlag)	((adc)->SR & whichFlag)

#define adcIsRegularConversionEnded(adc)		adcGetStatus(adc, ADC_EOC)
#define adcIsInjectedConversionEnded(adc)		adcGetStatus(adc, ADC_JEOC)

/*
#define adcStartConversion(adc)		\
		do{							\
			adcClearAllFlags(adc);	\
			(adc)->CR2 |= (uint32_t)((ADC_SWSTART >>32) & 0xffffffff);\
		}while(0)
*/
#define adcStartConversion(adc)		\
		do{							\
			(adc)->CR2 |= (1 << 30);\
		}while(0)

void adcEnableClock(adcRegs *adc);
void adcSetChannelSamplingSequence(adcRegs *adc, int channels[], int numOfChan);
void adcChannelSamplingTime(adcRegs *adc, int channel, int cycles);
void configureADC(adcRegs *adc, long long mode);
void configureCommonADC(uint32_t mode);
uint16_t adcReadValue(adcRegs *adc);
float calculateTemperature(uint8_t resolution, float Vdd, int valReaded);


#endif // __ADC_H__
