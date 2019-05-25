#include <msp430x14x.h>
#include "lcd.h"
#include "portyLcd.h"
#include "uart.h"
#include "portyUart.h" 
#include <string.h>
#include <time.h>
#include <stdlib.h>


char heart1[] = {0x00,  0x0A,  0x1F,  0x1F,  0x1F,  0x0E,  0x04,  0x00};
char heart2[] ={0x00,0x00,0x0A,0x1F,0x1F,0x0E,0x04,0x00
};
char heart3[] ={  0x00,  0x00,  0x00,  0x0A,  0x1F,  0x0E,  0x04,  0x00};
char life[] = {0x0A,  0x1F,  0x0E,  0x04,  0x00,  0x00,  0x00,  0x00};
char hurdle1[] = { 0x00,  0x0E,  0x1F,  0x1F,  0x1F,  0x0E,  0x00,  0x00};
char  hurdle2[] = {  0x00,  0x1F,  0x1F,  0x1F,  0x1F,  0x1F,  0x00,  0x00};
char hurdle3[] = {  0x00,  0x04,  0x0E,  0x1F,  0x0E,  0x04,  0x00,  0x00};  
char name[10];
int z=0;
 int maxScore;
 int score;
   char Bufor[10];
  int low=0;
  int high=0;
  int namehelp=0;

int main( void )
{

  WDTCTL = WDTPW + WDTHOLD;
  InitPortsLcd();
  InitLCD();
  clearDisplay();
  initPortyUart();
  initUart(1200);
  _EINT();
  P4DIR &= ~BIT4;
  P4DIR &= ~BIT5;
  P4DIR &= ~BIT6;
  P4DIR &= ~BIT7;   
  
  char menu1[7]="B1-PLAY";
  char menu2[9]="B2-SCORE";
  char menu3[15]=" B3-HOW TO PLAY";

  char desc1[10]="BUTTON1-UP";
  char desc2[12]="BUTTON2-DOWN";
  char desc3[10]="BUTTON3-:)";
  char desc4[12]="BUTTON4-EXIT";
  char desc5[7]="3 LIFES";
  char desc6[8]="3 LEVELS";
  char desc7[12]="GOOD LUCK :)";
  char desc8[1]=" ";
  char desc9[11]="N.OLSZEWSKA";
  char desc10[8]="J.KLIMEK";
  char desc11[11]="D.KRAJEWSKI";

  int i;
  while(1)
  {
    clearDisplay();
    while(1)
    {
      SEND_CMD(DD_RAM_ADDR+0);
      for(i=0;i<7;i++)
      {
        SEND_CHAR(menu1[i]);
      }
      SEND_CMD(DD_RAM_ADDR+8);
      for(i=0;i<9;i++)
      {
        SEND_CHAR(menu2[i]);
      }
      SEND_CMD(DD_RAM_ADDR2+0);
      for(i=0;i<15;i++)
      {
        SEND_CHAR(menu3[i]);
      }
      
      
      if((P4IN & 0x10)==0)
      {
       //gra
        namehelp=0;
        game();
        if(score==maxScore){
    while(namehelp!=10){
       while(high != low){
         putc(Bufor[low]);
         low= (++low)%10;
         namehelp++;
          }
        }
        }
        
      clearDisplay();
    
      }
      
      if((P4IN & 0x20)==0)
      {
      //wyniki
        max();




      }
        
      if((P4IN & 0x40)==0)
        {
//O GRZE, AUTORZY
//czy da sie wszystko w jedna funkcje wstawiæ???
//desc();
          clearDisplay();
          SEND_CMD(DD_RAM_ADDR+0);
          for(i=0;i<10;i++){
             SEND_CHAR(desc1[i]);
          }
          SEND_CMD(DD_RAM_ADDR2+0);
          for(i=0;i<12;i++){
            SEND_CHAR(desc2[i]);
          }
delay(25);
delay(25);

          clearDisplay();
          SEND_CMD(DD_RAM_ADDR+0);
          for(i=0;i<10;i++){
            SEND_CHAR(desc3[i]);
          }
          SEND_CMD(DD_RAM_ADDR2+0);
          for(i=0;i<12;i++){
            SEND_CHAR(desc4[i]);
          }
delay(25);	
delay(25);
        clearDisplay();
        SEND_CMD(DD_RAM_ADDR+0);
        for(i=0;i<7;i++)
        {
          SEND_CHAR(desc5[i]);
        }
        SEND_CMD(DD_RAM_ADDR2+0);
        for(i=0;i<8;i++)
        {
          SEND_CHAR(desc6[i]);
        }
delay(25);
delay(25);
        clearDisplay();

        SEND_CMD(DD_RAM_ADDR+0);
        for(i=0;i<12;i++)
        {
          SEND_CHAR(desc7[i]);
        }
        SEND_CMD(DD_RAM_ADDR2+0);
        for(i=0;i<1;i++)
        {
          SEND_CHAR(desc8[i]);
        }
delay(25);
delay(25);
        clearDisplay();

        SEND_CMD(DD_RAM_ADDR+0);
        for(i=0;i<11;i++)
        {
          SEND_CHAR(desc9[i]);
        }
        SEND_CMD(DD_RAM_ADDR2+0);
        for(i=0;i<8;i++)
        {
          SEND_CHAR(desc10[i]);
        }
delay(25);
delay(25);
          clearDisplay();
          SEND_CMD(DD_RAM_ADDR+0);
          for(i=0;i<11;i++){
             SEND_CHAR(desc11[i]);
          }
          SEND_CMD(DD_RAM_ADDR2+0);
          for(i=0;i<1;i++){
            SEND_CHAR(desc8[i]);
          }
delay(25);
delay(25);

          clearDisplay();     
        } 
    }
  }
}
  



int max()
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
//maksScore
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
//maxTime
//printDecDigit(maxTime);
delay(30);
delay(30);
  clearDisplay();
}

int delay(int value)
{
  for(int i=0;i<value;i++)
  {
      Delayx100us(250);
  }
}



int game(int life, int level)
{ 
  char game1[5]="START";
  char game2[12]="GAME OVER :(";
  int obstacle[16][2];
  for(int i=0;i<2;i++){
    for(int j=0;j<16;j++){
      obstacle[j][i]=0;
    }
  }
  int whereHeart=0;
  
  clearDisplay(); 
  SEND_CMD(DD_RAM_ADDR+0);
      for(int i=0;i<5;i++)
      {
        SEND_CHAR(game1[i]);
      }
delay(18);
          clearDisplay(); 

          
        life=3;
        score=0;
        level=1;
       
       srand(time(NULL));
  int exit=0;
  
  SEND_CMD(0x40);
  for(int i=0; i<8 ; i++)
    SEND_CHAR(heart1[i]);
   for(int i=0; i<8 ; i++)
    SEND_CHAR(heart2[i]);
   for(int i=0; i<8 ; i++)
    SEND_CHAR(heart3[i]);
   for(int i=0; i<8 ; i++)
    SEND_CHAR(hurdle1[i]);
  for(int i=0; i<8 ; i++)
    SEND_CHAR(hurdle2[i]);
  for(int i=0; i<8 ; i++)
    SEND_CHAR(hurdle3[i]);
  
  while(exit==0)
{
  /* z=rand()%9999999+1;
      if(z%2==1)
      {
        obstacle[15][1]=1;
        
      }
      else obstacle[15][1]=1;
      z++;*/
  
  int random= rand()%2;
  if(random==0 && obstacle[1][0]!=1 && obstacle[1][1]!=1 && obstacle[2][0]!=1 && obstacle[2][1]!=1)
    obstacle[0][0]=1;
  if(random==1 && obstacle[1][0]!=1 && obstacle[1][1]!=1 && obstacle[2][0]!=1 && obstacle[2][1]!=1)
    obstacle[0][1]=1;
  
  for(int i=15;i>0;i--){
  obstacle[i][0]=obstacle[i-1][0];
  obstacle[i][1]=obstacle[i-1][1];
  obstacle[i-1][0]=0;
  obstacle[i-1][1]=0;
  }
    
       
   
if((P4IN & 0x10)==0){
  whereHeart=0;
  
     }
if((P4IN & 0x20)==0){
whereHeart=1;
  
    }
 
 if((P4IN & 0x80)==0)
 {
   exit=1;
 }
clearDisplay();
 if(whereHeart==0){

   if(life==3)
   {
  SEND_CMD(DD_RAM_ADDR);
  SEND_CHAR(0);
   }
   if(life==2)
   {
  SEND_CMD(DD_RAM_ADDR);
  SEND_CHAR(1);
   }
   if(life==1)
   {
  SEND_CMD(DD_RAM_ADDR);
  SEND_CHAR(2);
   }
 }
 if(whereHeart==1){

     if(life==3)
   {
  SEND_CMD(DD_RAM_ADDR2);
  SEND_CHAR(0);
   }
   if(life==2)
   {
  SEND_CMD(DD_RAM_ADDR2);
  SEND_CHAR(1);
   }
   if(life==1)
   {
  SEND_CMD(DD_RAM_ADDR2);
  SEND_CHAR(2);
   }
 }
  for(int i=0;i<16;i++){
if(obstacle[15-i][0]==1){
if(!(i==0 && whereHeart==0)){
  SEND_CMD(DD_RAM_ADDR+(i));
  if(level==1)
  SEND_CHAR(3);
  if(level==2)
    SEND_CHAR(4);
  if(level==3)
    SEND_CHAR(5);}
}
}

 //for(int g=0; g<100;g++)
  //     for(int r=0; r<100;r++);
for(int j=0;j<16;j++){
if(obstacle[15-j][1]==1){
if(!(j==0 && whereHeart==1)){
  SEND_CMD(DD_RAM_ADDR2+(j));
  if(level==1)
  SEND_CHAR(3);
  if(level==2)
    SEND_CHAR(4);
  if(level==3)
    SEND_CHAR(5);

} 
  }
}
 if(level==1){
delay(12);
 }
    if(level==2){
delay(9);
    }
 if(level==3){
delay(5);
 }
if((obstacle[15][0]==1 && whereHeart==0) || (obstacle[15][1]==1 && whereHeart==1)){
life--;  
}
else if((obstacle[15][0]==1 && whereHeart==1) || (obstacle[15][1]==1 && whereHeart==0))
{if(level==1){
score=score+5;
if(score==50)
level++;
}
if(level==2){
score+=10;
if(score==150)
level++;
}
if(level==3){
score+=20;
//if(score>=150)
//miganie

}}
  
if(life==0){
exit=1;
}

}

if(score>maxScore){
maxScore=score;
}


         clearDisplay();
   SEND_CMD(DD_RAM_ADDR+0);
      for(int i=0;i<12;i++)
      {
        SEND_CHAR(game2[i]);
      }
	  SEND_CMD(DD_RAM_ADDR2+0);
       printDecDigit(score/1000);
printDecDigit((score%1000-score%100)/100);
printDecDigit((score%100-score%10)/10);
printDecDigit(score%10);
      
delay(18);
delay(18);
          clearDisplay();
          SEND_CMD(DD_RAM_ADDR);
  SEND_CHAR('E');
  SEND_CHAR('N');
  SEND_CHAR('T');
  SEND_CHAR('E');
  SEND_CHAR('R');
  SEND_CHAR(' ');
  SEND_CHAR('N');
  SEND_CHAR('A');
  SEND_CHAR('M');
  SEND_CHAR('E');
  SEND_CHAR('(');
  SEND_CHAR('1');
  SEND_CHAR('0');
  SEND_CHAR(')');
  SEND_CHAR(':');
  SEND_CMD(DD_RAM_ADDR2);
  }


#pragma vector=UART0RX_VECTOR
__interrupt void usart0_rx (void){
Bufor[high]=RXBUF0;
if(Bufor[high]!=NULL){
name[namehelp]=Bufor[high];
}
high=(++high)%10;
}
