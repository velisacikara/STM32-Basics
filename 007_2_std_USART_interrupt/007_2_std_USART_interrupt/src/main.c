
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <stdio.h>


char rx_buff[50];
int i = 0;

GPIO_InitTypeDef GPIO_InitStruct;
USART_InitTypeDef USART_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

void NVIC_Config()
{
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;

	NVIC_Init(&NVIC_InitStruct);
}

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); // PA2 Tx Pini oldu.
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); // PA3 Rx Pini oldu.

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; // Tx Pin 2 - Rx Pin 3

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void USART_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // Alýcý ve Vericinin duruma göre birbirlerini uyarmasýna yarar.
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No; // Güvenlik amacýyla (bitlerin doðru alýnýp alýnmadýðýnýn kontrolü için) vardýr.
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART2, &USART_InitStruct);
	USART_Cmd(USART2, ENABLE);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // Bir mesaj alýndýðýnda interrupt aktif olur.
}

void USART_Puts(USART_TypeDef* USARTx, volatile char *s) // Mesajý göndermek için kullanýlan fonksiyon
{
	while(*s)
	{
		/*
		 * Veri geldiði zaman SR register'ý 1 olur.
		 * bu while döngüsü sayesinde veri gelene kadar bekler,
		 * veri geldiði zaman iþlem devam eder.*/
		while(!(USARTx->SR = 0x00000040));

		USART_SendData(USART2, *s);
		*s++;
	}
}

/*
 * Bu interrupt fonksiyonu ile veri geldiðinde flag kalktý.
 * Gelen veri rx_buffer deðiþkenine atandý.
 * Sonrasýnda Send fonksiyonu ile gönderildi.
 */
void USART2_IRQHandler()
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE)) // Flag'in kalkma durumu kontrol edildi
	{
		char rx_buffer = USART_ReceiveData(USART2);
		USART_SendData(USART2, rx_buffer);

		if(rx_buffer != '\n' && i < 50) // Enter'a basýlmadýðý sürece, yani rx_buffer boþ deðilse
		{
			rx_buff[i] = rx_buffer;
			i++;
		}
		else // artýk eleman gelmediði durumda
		{
			rx_buff[i] = rx_buffer; // son gelen elemaný (enter karakteri alt satýra geeçmek için) almak için.
			i = 0;
			USART_Puts(USART2, rx_buff);
			/*
			 * Dizideki elemanlar sonraki gelecek
			 * elemanlarý aynýý verinin üzerine
			 * yazmamasý için temizlenir.
			 */
			for(int j = 0; j < 50; j++)
			{
				rx_buff[j] = '\0';
			}
		}
	}
}

int main(void)
{
	GPIO_Config();
	USART_Config();
	NVIC_Config();

  while (1)
  {

  }
}

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
