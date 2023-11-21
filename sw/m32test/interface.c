#include "interface.h"
#include "hw.h"

void initialize()
{
    hwInit();
    DispBacklight(1);
}

void Buzz(char _val)
{
    SetBuzz(_val);
}
char GetHumid() {}
char GetTemp() {}
char GetKeyMenu()
{
    return !GetP1Button1();
}
char GetKeySet()
{
    return !GetP1Button2();
}
void Disp(char _x, char _y, char *_str)
{
    P4CharLcd(_x, _y, _str);
}
void DispBacklight(char _val)
{
    P4CharLcdBacklight(_val);
}

void SetHumidifier(char _val)
{
    SetPomp1(_val);
}
void SetFan(char _val) {}
void SetHeater(char _val)
{
    SetPomp2(_val);
}
void SetCooler(char _val)
{
    SetRelay(_val);
}

void Delay(int _val)
{
    AvrDelayMs(_val);
}

void getTime(unsigned char *_hour, unsigned char *_min, unsigned char *_sec)
{
    getRtc(_hour, _min, _sec);
}

void setTime(unsigned char _hour, unsigned char _min, unsigned char _sec)
{
    setRtc(_hour, _min, _sec);
}
