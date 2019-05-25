#include <msp430x14x.h>
#include "lcd.h"
#include "portyLcd.h"
#include "uart.h"
#include "portyUart.h" 
#include <time.h>
#include "buzzer.h"



int game(int score, int maxScore)
{ 
  char heartLevel1[] = {0x00, 0x0A, 0x1F, 0x1F, 0x1F, 0x0E, 0x04, 0x00};
  char heartLevel2[] = {0x00, 0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00};
  char heartLevel3[] = {0x00, 0x00, 0x00, 0x0A, 0x1F, 0x0E, 0x04, 0x00};
  char hurdleLevel1[] = {0x00, 0x0E, 0x1F, 0x1F, 0x1F, 0x0E, 0x00, 0x00};
  char hurdleLevel2[] = {0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00};
  char hurdleLevel3[] = {0x00, 0x04, 0x0E, 0x1F, 0x0E, 0x04, 0x00, 0x00}; 
  char startGame[5]="START";
  char endGame[12]="GAME OVER :(";

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
        SEND_CHAR(startGame[i]);
      }
  delay(18);
  clearDisplay(); 
          
  int life=3;
  score=0;
  int level=1;
       
  srand(time(NULL));
  int exit=0;
  
  SEND_CMD(0x40);
  for(int i=0; i<8 ; i++)
    SEND_CHAR(heartLevel1[i]);
   for(int i=0; i<8 ; i++)
    SEND_CHAR(heartLevel2[i]);
   for(int i=0; i<8 ; i++)
    SEND_CHAR(heartLevel3[i]);
   for(int i=0; i<8 ; i++)
    SEND_CHAR(hurdleLevel1[i]);
  for(int i=0; i<8 ; i++)
    SEND_CHAR(hurdleLevel2[i]);
  for(int i=0; i<8 ; i++)
    SEND_CHAR(hurdleLevel3[i]);
  
  while(exit==0)
  {
    if(level==1){
      P1OUT |= BIT5;
    }
    if(level==2){
      P1OUT |= BIT6;
    }
    if(level==3){
      P2OUT &= ~BIT1;
    }

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
          SEND_CHAR(5);
        }
     }  
  }

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
	beep(440, 50);
	delay(20);

  }
  else if((obstacle[15][0]==1 && whereHeart==1) || (obstacle[15][1]==1 && whereHeart==0))
  {
    if(level==1){
      score=score+5;
      if(score==50)
        level++;
    }
    if(level==2){
      P1OUT |= BIT6;
      score+=10;
      if(score==150)
        level++;
    }
    if(level==3){
      P2OUT |= BIT1;
      score+=20;
    }
  }
  
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
      SEND_CHAR(endGame[i]);
    }
    SEND_CMD(DD_RAM_ADDR2+0);
    printDecDigit(score/1000);
    printDecDigit((score%1000-score%100)/100);
    printDecDigit((score%100-score%10)/10);
    printDecDigit(score%10);
      
    delay(36);
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
	return maxScore;
}