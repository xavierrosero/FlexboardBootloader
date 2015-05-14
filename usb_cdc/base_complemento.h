#include <18f2550.h>

//external oscillator 20Mhz
//#fuses hspll,nowdt,noprotect,nolvp,nodebug,usbdiv,pll3,cpudiv1,vregen

  #fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN

  ////slow speed
  //#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV3,VREGEN
  //#use delay(clock=24000000)
  //#define USB_USE_FULL_SPEED  FALSE

#use delay(clock = 48000000)
#use rs232(baud = 115200, parity = n, xmit = pin_c6 ,rcv = pin_c7, bits = 8)
#use standard_io(a)
#include <string.h>
#include ".\archivos\usb_cdc.h"
#include <stdlib.h>
#define tamanio_buffer 40
//#define usb_con_sense_pin_pin_b2
#byte porta = 0xf80    //portx
#byte portb = 0xf81
#byte portc = 0xf82
#byte lata = 0xf89     //latx 
#byte latb = 0xf8a
#byte latc = 0xf8b
#byte trisa = 0xf92    //trisx
#byte trisb = 0xf93
#byte trisc = 0xf94
//#bit led_sys = portb.5
#bit stateDspic = portb.2

#define stop false
#define running true

char data_rx_uart;
char data_rx_usb;
int1 send_via_usb = 0;
unsigned char counterReset = 0;
unsigned char rstKeyword[5]={'*','C','x','R','c'};
unsigned int16 i=0;

#int_rda //interrupción
void interrupt()
{ 
   if(kbhit())
   {
      data_rx_uart = getc();//read buffer and store data_rx
      if(send_via_usb == true)
      {   
         printf(usb_cdc_putc,"%c",data_rx_uart);
      }
   }
}

void manage_conection(void)
{
   int8 attached;
   int8 enumerated;
   int8 new_cdc;

   attached = usb_attached();
   enumerated = usb_enumerated();
   new_cdc = usb_cdc_connected();

   if(usb_cdc_carrier.dte_present)
   {
      //led_sys = true;//turn on led 2 if device is enumerated by the host
      send_via_usb = true;
   }
   else
   {
      //led_sys = false;      
      send_via_usb = false;
   }
}
