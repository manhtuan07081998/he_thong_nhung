#include <16F877A.h>
#device ADC=10
#use delay(crystal=12MHz)

#define DS_PIN    PIN_B0
#define SHCP_PIN  PIN_B1
#define STCP_PIN  PIN_B2

unsigned char Data_LED[] = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};

void Init_74hc595(int data);
void OUTPUT_74HC595();
void LED_sang_dan_trai_qua_phai(int16 toc_do);
void LED_tat_dan_phai_qua_trai(int16 toc_do);
void main()
{
   while(TRUE)
   {
      LED_sang_dan_trai_qua_phai(200);
      LED_tat_dan_phai_qua_trai(200);
   }
}

void Init_74hc595(int data) 
{
   int i;
   output_low(SHCP_PIN);
   for(i=0;i<=7;i++)
   {
      if((data & 0x80)==0)
         output_low(DS_PIN);
      else
         output_high(DS_PIN);
         data=data<<1;
         output_high(SHCP_PIN);
         output_low(SHCP_PIN);
   }
}
void OUTPUT_74HC595()
{
   output_low(STCP_PIN);
   delay_us(5);
   output_high(STCP_PIN);
   output_low(STCP_PIN);
}

void LED_sang_dan_trai_qua_phai(int16 toc_do)
{

   for(int i = 0; i < 16 ; i++)
      {
         if(i < 8)
         {
            Init_74hc595(0);
            Init_74hc595(Data_LED[i]);
            OUTPUT_74HC595();
            delay_ms(toc_do);
         }
         else
         {
            Init_74hc595(Data_LED[i - 8]);
            Init_74hc595(0xFF);
            OUTPUT_74HC595();
            delay_ms(toc_do);
         }
      }
}
void LED_tat_dan_phai_qua_trai(int16 toc_do)
{
   for(int i = 15; i > 0 ; i--)
      {
         if(i > 7)
         {
            Init_74hc595(Data_LED[i - 8]);
            Init_74hc595(0xFF);
            OUTPUT_74HC595();
            delay_ms(toc_do);
         }
         else
         {
            Init_74hc595(0);
            Init_74hc595(Data_LED[i]);
            OUTPUT_74HC595();
            delay_ms(toc_do);
         }
      }
}

