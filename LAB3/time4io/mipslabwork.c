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
#define TRISD		PIC32_R (0x860C0) // Port D: mask as inputs


int mytime = 0x5957;

volatile int* trisE = (volatile int*) 0xbf886100; //Pointer till trisE som ligger på addressen, säger om den ska vara in/output
volatile int* portE = (volatile int*) 0xbf886110; //Pointer till portE som ligger på addressen, där värdet som vi skriver ligger
int step = 0;                                     //värdet för de 8 bitarna vilket sätter LEDs som av eller på

char textstring[] = "text, more text, and even more text!";

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
  return; //0000 0000 0111 1111
}         //0000 1111 1110 0000

/* This function is called repetitively from the main program */
void labwork( void )
{
  delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  step++; //stegar upp värdet för de 8 bitarna vilket ändrar LEDs 
  *portE = step;  //sätter värdet för de 8 bitarna
  display_image(96, icon);
 
  int btns = getbtns();
  int sw = getsw(); //0x0f00, 0xf000
  if(btns & 0x80) //klockan = X0:00
  {
    mytime = (mytime & 0x0fff) | (sw << 4); //0x0f00 << 0xf000
  }

    if(btns & 0x40) //klockan = 0X:00
  {
    mytime = (mytime & 0xf0ff) | (sw); //0x0f00
  }

    if(btns & 0x20) //klockan = 00:X0
  {
    mytime = (mytime & 0xff0f) | (sw>>4); //0x0f00 >> 0x00f0
  }

}


//TRISE, TRISESET & TRISECLR handlar alla om input och output - SET(input) & CLR(output) behandlar specifika bitar medans TRISE behandlar alla i port E
//