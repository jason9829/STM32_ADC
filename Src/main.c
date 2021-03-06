
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */
#include "ADC.h"
#include "GPIO.h"
#include "USART.h"
#include "RCC.h"

#include <stdio.h>
#include <math.h>
#include <stdarg.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
#define MAX_BUFFER_SIZE	512
char uartPrintBuffer[MAX_BUFFER_SIZE];

void uartPrintf(char *message, ...){
	va_list args;
	int length, i;

	va_start(args, message);
	length = vsnprintf(uartPrintBuffer, 0, message, args);

	if(length > MAX_BUFFER_SIZE - 1){
		length = MAX_BUFFER_SIZE - 1;
	}

	vsnprintf(uartPrintBuffer, length +1, message, args);

	for(i = 0; i < length; i++){
		while(!(usartIsTxRegEmpty(uart5)));
		(uart5)->DR = uartPrintBuffer[i];
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	int volatile valueReadCH5, valueReadCH13, valueReadCH18;
	int volatile ch5;
	float temperature;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  int channelSeq[] = {ADC_CH_18, ADC_CH_13, ADC_CH_5};
  adcEnableClock(adc1);
  adcSetChannelSamplingSequence(adc1, channelSeq, sizeof(channelSeq)/4);
   // CH18
   adcChannelSamplingTime(adc1, ADC_CH_18, ADC_SAMP_112_CYCLES);
   // PC3
   adcChannelSamplingTime(adc1, ADC_CH_13, ADC_SAMP_480_CYCLES);
   // PA5
   adcChannelSamplingTime(adc1, ADC_CH_5, ADC_SAMP_480_CYCLES);



  configureADC(adc1, ADC_RES_10  |	ADC_SCAN_EN |	\
		  	  	  	 ADC_ADON | ADC_EOCS);
  configureCommonADC(C_ADC_TSVREFE | C_ADC_ADCPRE4);

  RESET_UART5_CLK_GATING();
  UNRESET_UART5_CLK_GATING();
  ENABLE_UART5_CLK_GATING();
  ENABLE_GPIOA_CLK_GATING();
  ENABLE_GPIOC_CLK_GATING();

  // UART5_TX
  GPIOConfigurePin(gpioC, GPIOPin12, GPIO_ALT_FUNC|GPIO_VERY_HI_SPEED);
  GPIOConfigureAltFunc(gpioC, GPIOPin12, AF8);

  usartConfigure(uart5, USART_OVERSAMPLING_16 | USART_WORD_LENGTH_9BITS |	\
		  	  	  	  	USART_ENABLE | USART_STOP_BIT_1 | USART_PC_ENABLE | \
						USART_PARITY_ODD \
						| USART_TE_ENABLE  ,115200, 45000000);

  // GPIO config for PA5 (2 V), ADC channel 5
  GPIOConfigurePin(gpioA, GPIOPin5, GPIO_ANALOG);

  // GPIO config for PC3 (1 V), ADC channel 13
  GPIOConfigurePin(gpioC, GPIOPin3, GPIO_ANALOG);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
	  do{
		  do{

			  adcClearAllFlags(adc1);
			  adcStartConversion(adc1);
			  while(!(adcIsRegularConversionEnded(adc1))){
			  if(adcGetStatus(adc1, ADC_OVR)){
				  goto overrunOccured;
			  	  }
			  }
			  //adcClearFlag(adc1, ADC_OVR);
			  valueReadCH18 = adcReadValue(adc1);


			  //adcStartConversion(adc1);
			  while(!(adcIsRegularConversionEnded(adc1))){
				  if(adcGetStatus(adc1, ADC_OVR)){
					  goto overrunOccured;
				  }
			  }
			  //adcClearFlag(adc1, ADC_OVR);
			  valueReadCH13 = adcReadValue(adc1);


			  //adcStartConversion(adc1);
			  while(!(adcIsRegularConversionEnded(adc1))){
				  if(adcGetStatus(adc1, ADC_OVR)){
					  goto overrunOccured;
				  }
			  }
			  //adcClearFlag(adc1, ADC_OVR);
			  valueReadCH5 = adcReadValue(adc1);

			  temperature = calculateTemperature(10, 2.93, valueReadCH18);

			  uartPrintf("(ch18)%4d | (ch13)%4d | (ch5)%4d  |  (ch18) %.4fV | (ch13) %.4fV | (ch5) %.4fV | Temperature : %.4fC\n", \
					  valueReadCH18, valueReadCH13, valueReadCH5, valueReadCH18* (2.93 / 1023), valueReadCH13* (2.93 / 1023), valueReadCH5* (2.93 / 1023) ,temperature);
			  //uartPrintf("(ch18) %.4fV | (ch13) %.4fV | (ch5) %.4fV | Temperature : %.4fC\n ", \
			 					  valueReadCH18* (2.93 / 1023), valueReadCH13* (2.93 / 1023), valueReadCH5* (2.93 / 1023),temperature);
			  HAL_Delay(500);
		  }while(1);
		  overrunOccured:
		  adcClearAllFlags(adc1);

	  }while(1);

  }

}
/* USER CODE END WHILE */

/* USER CODE BEGIN 3 */
/* USER CODE END 3 */
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 90;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Activate the Over-Drive mode 
    */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
