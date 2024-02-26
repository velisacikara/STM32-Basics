
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/*
 * SYSTick basit, sadece s�re ama�l� kullan�lan bir timer'd�r.
 * Bu �al��mada da SYSTcik timer'� kullan�larak ledler toggle yap�lm��t�r.
 * Delay fonksiyonu src i�indeki stm32f4xx_it.c dosyas�nda SysTick_Handler() ad�nda bir fonksiyondur.
 * Bu fonksiyon main.c'de de yaz�labilece�i gibi ilgili yerde haz�r olarak kullan�labilir.
 * �lgili yerde yaz�lacak ise count ifadesi o dosyaya da ta��nmal�d�r.
 * Bunun i�in extern ifadesi kullan�l�r, count de�i�keni ilgili dosyaya ta��n�r.
 * */


GPIO_InitTypeDef GPIO_InitStruct;

uint16_t count;

void Delay_ms(uint32_t time)
{
	count = time;

	while(count); // count de�i�keni 0 olana kadar bekler. E�er bu sat�r olmasayd� anl�k olarak s�rekli toggle yapard�.
}

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 |  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

	GPIO_Init(GPIOD, & GPIO_InitStruct);
}
int main(void)
{
	GPIO_Config();
	SysTick_Config(SystemCoreClock / 1000);
	/*
	 * SystemCoreClock / 1000		her 1 ms'de interrupta gider.
	 * SystemCoreClock / 100000		her 10 us'de interrupta gider.
	 * SystemCoreClock / 1000000	her 1 us'de interrupta gider.
	 * */

  while (1)
  {
	  GPIO_ToggleBits(GPIOD, GPIO_Pin_12 |  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	  Delay_ms(1000);


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