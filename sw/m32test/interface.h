
void initialize();
void Disp(char _x, char _y, char *_str);
void DispBacklight(char _val);

void Buzz(char _val);
char GetHumid();
char GetTemp();
char GetKeyMenu();
char GetKeySet();
// void PutLcd(char _x, char _y, char *_str);

void SetHumidifier(char _val);
void SetFan(char _val);
void SetHeater(char _val);
void SetCooler(char _val);

void Delay(int _val);

void getTime(unsigned char *_hour, unsigned char *_min, unsigned char *_sec);
void setTime(unsigned char _hour, unsigned char _min, unsigned char _sec);