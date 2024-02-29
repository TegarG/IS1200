/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;

volatile int* trisE = (volatile int*) 0xbf886100; //Pointer till trisE som ligger på addressen, säger om den ska vara in/output
volatile int* portE = (volatile int*) 0xbf886110; //Pointer till portE som ligger på addressen, där värdet som vi skriver ligger
int step = 0;                                     //värdet för de 8 bitarna vilket sätter LEDs som av eller på

char textstring[] = "text, more text, and even more text!";

int timeoutcounter = 0;

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  *trisE &= ~0xff; //maskar och sätter bit 7 till 0 som 0 för att deklarera dessa som output
  TRISD |= (0x7f << 5); //sätter dem första 7 bitarna till 1 och shiftar till rätt plats           
  T2CON = 0x8070; //kolla PIC32 family reference manual section 14. s. 9. Sätter på timer 2 och prescalar till 1:256
  TMR2 = 0; //sätter timer värdet till 0
  PR2 = 31250; //sätter periodlängden till 100 ms 80M/256/10
  
  return; 
}         

/* This function is called repetitively from the main program */
void labwork( void )
{
  if((IFS(0) & 0x100) != 0) //Ifall bit 8 i IFS0 är 1 innebär det att vi har en timeout och vi återställer flaggan(bit 8 i IFS0) till 0
  {                         //IFS0 & 0x00000100 != 0 kör vi, om talet blir 0 kör vi inte
    IFS(0) &= 0xFEFF;        //sätter 8:e biten till 0
    timeoutcounter++;       //sätter en "flagga" som vi använder för att kolla om det har skett en timeout
  }      

  if(timeoutcounter == 10) //om det har skett en timeout kör vi följande        
  {
  //delay( 1000 ); //sätt den som kommentar för att testa åvanstående
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  step++; //stegar upp värdet för de 8 bitarna vilket ändrar LEDs 
  *portE = step;  //sätter värdet för de 8 bitarna
  timeoutcounter = 0; //återställer flaggan
  }

  display_image(96, icon);
 
  int btns = getbtns();
  int sw = getsw(); //0x0f00, 0xf000

  if(btns & 0x80) //klockan = X0:00
  {
    mytime = (mytime & 0x0fff) | (sw << 4); //maskar bort siffran vi vill ersätta 0x0f00 << 0xf000
  }

  if(btns & 0x40) //klockan = 0X:00
  {
    mytime = (mytime & 0xf0ff) | (sw); //maskar bort siffran vi vill ersätta 0x0f00
  }

  if(btns & 0x20) //klockan = 00:X0
  {
    mytime = (mytime & 0xff0f) | (sw>>4); //maskar bort siffran vi vill ersätta 0x0f00 >> 0x00f0
  }
}


//TRISE, TRISESET & TRISECLR handlar alla om input och output - SET(input) & CLR(output) behandlar specifika bitar medans TRISE behandlar alla i port E
//