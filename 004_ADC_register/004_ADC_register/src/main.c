
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint8_t adc_value;

void RCC_Config()
{
	RCC->CR |= 0x00030000;  //HSEON and HSEONRDY ENABLE
	while(!(RCC->CR & 0x00020000));  //HSEON Ready Flag Wait
	RCC->CR |= 0x00080000;  // CSS ENABLE
	RCC->PLLCFGR |= 0x00400000;  // PLL e HSE se�tik
	RCC->PLLCFGR |= 0x00000004;  // PLL M = 4
	RCC->PLLCFGR |= 0x0005A000;  // PLL N = 168
	RCC->PLLCFGR |= 0x00000000;  // PLL P = 2
	RCC->CFGR |= 0x00000000;  //AHB Prescaler = 1
	RCC->CFGR |= 0x00080000;  //APB2 Prescaler = 2
	RCC->CFGR |= 0x00001400;  //APB1 Prescaler = 4
	RCC->CIR |= 0x00080000;  //HSERDY Flag clear
	RCC->CIR |= 0x00800000;  //CSS Flag clear
}
void GPIO_Config()
{
	RCC->AHB1ENR |= 0x00000001; // GPIO Clock ENABLE
	GPIOA->MODER |= 0x00000003; // Pin 0 Analog Mode
	GPIOA->OSPEEDR |= 0x00000003; // Pin 0 100 MHz
}

void ADC_Config()
{
	RCC->APB2ENR |= 0x00000100; // ADC1 Clock ENABLE
	ADC1->CR1 |= 0x02000000; // Resolution 8 bit
	ADC1->CR2 |= 0x00000001; // ADC ENABLE
	ADC1->SMPR2 |= 0x00000003; // 56 Cycles
	ADC->CCR |= 0x00010000; // Div 4
}

uint8_t Read_ADC()
{
	uint8_t value;

	ADC1->CR2 |= 0x40000000; // ADC yaz�l�msal olarak ba�lat�ld�.

	while(!(ADC1->SR & 0x00000002)); // EOC flagi nin kalkma durumu kontrol edildi.

	value = ADC1->DR;

	return value;
}


int main(void)
{
	RCC_Config();
	GPIO_Config();
	ADC_Config();


  while (1)
  {
	  adc_value = Read_ADC();

  }
}


/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}