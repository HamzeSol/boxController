char GetP1Button1();

char GetP1Button2();

char GetP1Button3();

void SetBuzz(char _val);

void P4CharLcd(char _x, char _y, char *_str);
void P4CharLcdBacklight(char _val);
void hwInit(void);
void AvrDelayMs(int _val);

void SetPomp1(char _val);
void SetPomp2(char _val);
void SetRelay(char _val);

void getRtc(unsigned char *_hour, unsigned char *_min, unsigned char *_sec);
void setRtc(unsigned char _hour, unsigned char _min, unsigned char _sec);
