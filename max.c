#include <msp430x14x.h>
#include "lcd.h"
#include "portyLcd.h"
#include "uart.h"
#include "portyUart.h" 

int max(int maxScore, char * name)
{
  clearDisplay();
  SEND_CMD(DD_RAM_ADDR);
  SEND_CHAR('M');
  SEND_CHAR('A');
  SEND_CHAR('X');
  SEND_CHAR(' ');
  SEND_CHAR('S');
  SEND_CHAR('C');
  SEND_CHAR('O');
  SEND_CHAR('R');
  SEND_CHAR('E');
  SEND_CHAR(':');

  printDecDigit(maxScore/1000);
  printDecDigit((maxScore%1000-maxScore%100)/100);
  printDecDigit((maxScore%100-maxScore%10)/10);
  printDecDigit(maxScore%10);
  SEND_CMD(DD_RAM_ADDR2);
  SEND_CHAR('N');
  SEND_CHAR('A');
  SEND_CHAR('M');
  SEND_CHAR('E');
  SEND_CHAR(':');
  for(int i=0;i<10;i++){
   SEND_CHAR(name[i]);
   }
  delay(30);
  delay(30);
  clearDisplay();
}