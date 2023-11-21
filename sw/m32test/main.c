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
#include "globalVariable.h"

#include <stdio.h>

// Declare your global variables here

unsigned char page = 0;
unsigned char humid = 0;
unsigned char temp = 0;

unsigned char humidSetPoint = 0;
unsigned char tempSetPoint = 0;

unsigned char itemSelect = 0;
unsigned char enteredMenu = 0;
// unsigned int blinkCounter = 0;
char keyMenuPressed = 0;
char keySetPressed = 0;
char keyMenuOldFlag = 0;
char keySetOldFlag = 0;

void ShowMenu();
void ReadKeys();
void controller();
char str[20];

#include <stdio.h>
#include "SHT1x.h"
#include "SHT1x_platform.h"

// void main(void)
// {
//   SHT1x_Handler_t Handler;
//   SHT1x_Sample_t  Sample;

//   SHT1x_Platform_Init(&Handler);
//   SHT1x_Init(&Handler);

//   while (1)
//   {
//     SHT1x_ReadSample(&Handler, &Sample);
//     printf("Temperature: %f°C\r\n"
//            "Humidity: %f%%\r\n\r\n",
//            Sample.TempCelsius,
//            Sample.HumidityPercent);
//   }

//   SHT1x_DeInit(&Handler);
//   //return 0;
// }

void main(void)
{
      // unsigned char hh, mm, ss;
      SHT1x_Handler_t Handler;
      SHT1x_Sample_t Sample;
      initialize();
      // SHT1x_Platform_Init(&Handler);
      // SHT1x_Init(&Handler);

      // setTime(8, 23, 12);

      while (1)
      {

            // getTime(&hh, &mm, &ss);
            // sprintf(str, "%d:%d:%d  ", hh, mm, ss);
            // Disp(0, 0, str);

            // SHT1x_ReadSample(&Handler, &Sample);
            // controller();
            ShowMenu();
            ReadKeys();

            // sprintf(str, "H:%d%%  ", Sample.HumidityPercent);
            // Disp(0, 0, str);

            // sprintf(str, "T:%dC  ", Sample.TempCelsius);
            // Disp(0, 1, str);

            Delay(100);
      }
}

void controller()
{
      if (GetHumid() >= humidSetPoint)
      {
            SetHumidifier(0);
      }
      if (GetHumid() < humidSetPoint - 10)
      {
            SetHumidifier(1);
      }
}

enum pageNum
{
      PAGE_MAIN = 0,
      PAGE_SET_HT,
      PAGE_SET_TIME_H,
      PAGE_SET_TIME_M,
      PAGE_LAST
};

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
                  timerMenu = 10;
                  if (!enteredMenu)
                  {
                        enteredMenu = 1;
                        itemSelect = 0;
                  }
                  else
                  {
                        itemSelect++;
                        if (itemSelect >= PAGE_LAST)
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

                  blinkCounter = 3;
                  if (enteredMenu && (itemSelect == PAGE_MAIN))
                  {
                        humidSetPoint += 5;
                        if (humidSetPoint > 100)
                        {
                              humidSetPoint = 0;
                        }
                  }

                  if (enteredMenu && (itemSelect == PAGE_SET_HT))
                  {
                        tempSetPoint++;
                        if (tempSetPoint > 30)
                        {
                              tempSetPoint = 15;
                        }
                  }

                  if (enteredMenu && (itemSelect == PAGE_SET_TIME_H))
                  {
                        hh++;
                        if (hh > 23)
                        {
                              hh = 0;
                        }

                        setTime(hh, mm, ss);
                  }
                  if (enteredMenu && (itemSelect == PAGE_SET_TIME_M))
                  {
                        mm++;
                        if (mm > 59)
                        {
                              mm = 0;
                        }
                        setTime(hh, mm, ss);
                  }
            }
      }

      if ((!timerMenu) && (enteredMenu))
            enteredMenu = 0;
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
                  case PAGE_MAIN:
                        // blinkCounter++;
                        if (blinkCounter < 3)
                        {
                              sprintf(str, "H:     ");
                              Disp(0, 0, str);
                              sprintf(str, "T:%dC  ", tempSetPoint);
                              Disp(0, 1, str);
                        }
                        else if (blinkCounter < 6)
                        {
                              sprintf(str, "H:%d%%  ", humidSetPoint);
                              Disp(0, 0, str);
                              sprintf(str, "T:%dC  ", tempSetPoint);
                              Disp(0, 1, str);
                        }
                        else
                        {
                              blinkCounter = 0;
                        }
                        break;
                  case PAGE_SET_HT:
                        // blinkCounter++;
                        if (blinkCounter < 3)
                        {
                              sprintf(str, "H:%d%%  ", humidSetPoint);
                              Disp(0, 0, str);
                              sprintf(str, "T:     ");
                              Disp(0, 1, str);
                        }
                        else if (blinkCounter < 6)
                        {
                              sprintf(str, "H:%d%%  ", humidSetPoint);
                              Disp(0, 0, str);
                              sprintf(str, "T:%dC  ", tempSetPoint);
                              Disp(0, 1, str);
                        }
                        else
                        {
                              blinkCounter = 0;
                        }
                        break;
                  case PAGE_SET_TIME_H:
                        // blinkCounter++;
                        if (blinkCounter < 3)
                        {
                              sprintf(str, "%d%d:%d%d:%d%d", hh / 10, hh % 10, mm / 10, mm % 10, ss / 10, ss % 10);
                              Disp(0, 0, str);
                        }
                        else if (blinkCounter < 6)
                        {
                              sprintf(str, "  :%d%d:%d%d", mm / 10, mm % 10, ss / 10, ss % 10);
                              Disp(0, 0, str);
                        }
                        else
                        {
                              blinkCounter = 0;
                        }
                        break;
                  case PAGE_SET_TIME_M:
                        // blinkCounter++;
                        if (blinkCounter < 3)
                        {
                              sprintf(str, "%d%d:%d%d:%d%d", hh / 10, hh % 10, mm / 10, mm % 10, ss / 10, ss % 10);
                              Disp(0, 0, str);
                        }
                        else if (blinkCounter < 6)
                        {
                              sprintf(str, "%d%d:  :%d%d", hh / 10, hh % 10, ss / 10, ss % 10);
                              Disp(0, 0, str);
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
