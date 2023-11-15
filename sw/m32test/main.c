/*******************************************************
This program was created by the CodeWizardAVR V4.00
Automatic Program Generator
� Copyright 1998-2023 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project :
Version :
Date    : 11/14/2023
Author  :
Company :
Comments:


Chip type               : ATmega32A
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

// I/O Registers definitions
// #include <mega32a.h>
// #include <delay.h>
// #include <io.h>

// Alphanumeric LCD functions
// #include <alcd.h>
#include <mega32a.h>
#include "interface.h"
#include <stdio.h>

// Declare your global variables here
void ShowMenu();
void ReadKeys();

char str[20];
void main(void)
{

      initialize();
      // lcd_puts("Hi me");
      // LcdBLight(1);
      DispBacklight(1);
      // Disp(0, 0, "Hi");
      // Disp(0, 1, "Me");

      while (1)
      {
            // if (GetKeyMenu())
            // {
            //       Buzz(1);
            // }
            // else
            // {
            //       Buzz(0);
            // }
            // if (GetKeySet())
            // {
            //       Buzz(1);
            // }
            // else
            // {
            //       Buzz(0);
            // }

            // Disp(0, 1, "Hi");

            // sprintf(str, "%d,%d,", GetKeyMenu(), GetKeySet());
            // Disp(0, 0, str);

            ShowMenu();
            ReadKeys();
            Delay(200);
      }
}

enum pageNum
{
      PAGE_MAIN = 0,
      PAGE_SET
};
unsigned char page = 0;
unsigned char humid = 86;
unsigned char temp = 0;
unsigned char itemSelect = 0;
unsigned char enteredMenu = 0;
unsigned int blinkCounter = 0;
char keyMenuPressed = 0;
char keySetPressed = 0;
char keyMenuOldFlag = 0;
char keySetOldFlag = 0;

void ReadKeys()
{
      if (GetKeyMenu())
      {
            keyMenuOldFlag = 1;
      }
      else
      {
            if (keyMenuOldFlag)
            {
                  keyMenuOldFlag = 0;
                  if (!enteredMenu)
                  {
                        enteredMenu = 1;
                        itemSelect = 0;
                  }
                  else
                  {
                        itemSelect++;
                        if (itemSelect > 1)
                        {
                              enteredMenu = 0;
                              itemSelect = 0;
                        }
                  }
            }
      }

      if (GetKeySet())
      {
            keySetOldFlag = 1;
      }
      else
      {
            if (keySetOldFlag)
            {
                  keySetOldFlag = 0;

                  if (enteredMenu && (itemSelect == 0))
                  {
                        humid += 5;
                        if (humid > 100)
                        {
                              humid = 0;
                        }
                  }
            }
      }
}

void ShowMenu()
{
      switch (page)
      {
      case PAGE_MAIN:
            if (enteredMenu == 0)
            {

                  sprintf(str, "H:%d%%  ", humid);
                  Disp(0, 0, str);
                  sprintf(str, "T:%dC  ", temp);
                  Disp(0, 1, str);
            }
            else
            {
                  switch (itemSelect)
                  {
                  case 0:
                        blinkCounter++;
                        if (blinkCounter < 3)
                        {
                              sprintf(str, "H:     ", humid);
                              Disp(0, 0, str);
                              sprintf(str, "T:%dC  ", temp);
                              Disp(0, 1, str);
                        }
                        else if (blinkCounter < 6)
                        {
                              sprintf(str, "H:%d%%  ", humid);
                              Disp(0, 0, str);
                              sprintf(str, "T:%dC  ", temp);
                              Disp(0, 1, str);
                        }
                        else
                        {
                              blinkCounter = 0;
                        }
                        break;
                  case 1:
                        blinkCounter++;
                        if (blinkCounter < 3)
                        {
                              sprintf(str, "H:%d%%  ", humid);
                              Disp(0, 0, str);
                              sprintf(str, "T:     ", temp);
                              Disp(0, 1, str);
                        }
                        else if (blinkCounter < 6)
                        {
                              sprintf(str, "H:%d%%  ", humid);
                              Disp(0, 0, str);
                              sprintf(str, "T:%dC  ", temp);
                              Disp(0, 1, str);
                        }
                        else
                        {
                              blinkCounter = 0;
                        }
                        break;

                  default:
                        break;
                  }
            }

            break;

      default:
            break;
      }
}
