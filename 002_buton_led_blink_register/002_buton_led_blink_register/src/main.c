
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint8_t count;

void GPIO_Config()
{

	RCC->AHB1ENR |= 1<<3;

	RCC->AHB1ENR |= 1<<0;


	GPIOD->MODER = 0x55000000;
	GPIOD->OTYPER = 0x00000000;
	GPIOD->OSPEEDR = 0xFF000000;
	GPIOD->PUPDR = 0x00000000;



}


int main(void)
{


	GPIO_Config();


  while (1)
  {

	  if(GPIOA->IDR & 0x00000001)
	  {
		  while(GPIOA->IDR & 0x00000001);
		  count++;

		  if(count %2 ==1)
		  {
			  GPIOD->ODR = 0x0000F000;
		  }

		  else
		  {
			  GPIOD->ODR = 0x00000000;
		  }
	  }


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