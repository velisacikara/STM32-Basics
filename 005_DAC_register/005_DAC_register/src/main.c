
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


// Led DAC1 ile kullan�ld��� i�in PA4 pinine ba�land�.
int i;


void Delay(uint32_t time)
{
	while(time--);
}

void RCC_Config()
{
	RCC->CR |= 0x00010000;  //HSEON ENABLE
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

void DAC1_Config()
{
	RCC->AHB1ENR |= 0x00000001; // GPIOA portunun bulundu�u hat aktif edildi.
	RCC->APB1ENR |= 0x20000000; // DAC portnun bulundu�u hat aktif edildi.

	DAC->CR |= 0x00000001; // DAC Channel 1 enable
	DAC->SWTRIGR |= 0x00000000; // DAC Channel 1 software disable
	DAC->DHR12R1 |= 0x00000000; // DAC Channel 1 12 bit right-aligned data. Ba�lang��ta 0 yapmam�z�n nedeni s�f�rdan ba�lamas� i�in. FFF yazsayd�k 4095'ten ba�layacakt�.


}

int main(void)
{
	RCC_Config();
	DAC1_Config();


  while (1)
  {
	  for(; i < 4096 ; i++)
	  {
		  DAC->DHR12R1 = i; // Data bu registere yaz�l�r.
		  Delay(33600);
	  }
	  i = 0;

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