#include <mega32a.h>
#include <delay.h>
#include <io.h>
#include <alcd.h>
#include "globalVariable.h"

#include "hw.h"
#include "mcu.h"

// TWI functions
#include <twi.h>

// DS1307 Real Time Clock functions for TWI
#include <ds1307_twi.h>

char GetP1Button1()
{
    return (KEY1_PORT & KEY3_PIN);
}

char GetP1Button2()
{
    return (KEY2_PORT & KEY2_PIN);
}

char GetP1Button3()
{
    return (KEY3_PORT & KEY3_PIN);
}

void SetBuzz(char _val)
{
    if (_val)
        BUZZ_PORT |= BUZZ_PIN;
    else
        BUZZ_PORT &= ~(BUZZ_PIN);
}

void P4CharLcd(char _x, char _y, char *_str)
{
    lcd_gotoxy(_x, _y);
    lcd_puts(_str);
}

void P4CharLcdBacklight(char _val)
{
    if (_val)
        LCD_BACKLIGHT_PORT |= LCD_BACKLIGHT_PIN;
    else
        LCD_BACKLIGHT_PORT &= ~(LCD_BACKLIGHT_PIN);
}

void AvrDelayMs(int _val)
{
    delay_ms(_val);
}

void SetPomp1(char _val)
{
    if (_val)
        POMP1_PORT |= POMP1_PIN;
    else
        POMP1_PORT &= ~(POMP1_PIN);
}

void SetPomp2(char _val)
{
    if (_val)
        POMP2_PORT |= POMP2_PIN;
    else
        POMP2_PORT &= ~(POMP2_PIN);
}

void SetRelay(char _val)
{
    if (_val)
        RELAY_PORT |= RELAY_PIN;
    else
        RELAY_PORT &= ~(RELAY_PIN);
}

void getRtc(unsigned char *_hour, unsigned char *_min, unsigned char *_sec)
{
    rtc_get_time(_hour, _min, _sec);
}

void setRtc(unsigned char _hour, unsigned char _min, unsigned char _sec)
{
    rtc_set_time(_hour, _min, _sec);
}

//===========================================================================
// Timer 0 overflow interrupt service routine
unsigned int make100ms = 0;
unsigned int make1s = 0;

interrupt[TIM0_OVF] void timer0_ovf_isr(void)
{
    // Reinitialize Timer 0 value
    TCNT0 = 0x06;
    // Place your code here

    if (++make100ms > 12) // 96 ms
    {
        make100ms = 0;

        blinkCounter++;
    }

    if (++make1s > 125) // 96 ms
    {
        make1s = 0;

        if (timerMenu)
            timerMenu--;
    }
}

// Declare your global variables here

void hwInit(void)
{
    // Declare your local variables here

    // Input/Output Ports initialization
    // Port A initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=Out
    DDRA = (0 << DDA7) | (0 << DDA6) | (0 << DDA5) | (0 << DDA4) | (0 << DDA3) | (0 << DDA2) | (0 << DDA1) | (1 << DDA0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=0
    PORTA = (0 << PORTA7) | (0 << PORTA6) | (0 << PORTA5) | (0 << PORTA4) | (0 << PORTA3) | (0 << PORTA2) | (0 << PORTA1) | (0 << PORTA0);

    // Port B initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
    DDRB = (0 << DDB7) | (0 << DDB6) | (0 << DDB5) | (0 << DDB4) | (0 << DDB3) | (0 << DDB2) | (0 << DDB1) | (0 << DDB0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
    PORTB = (0 << PORTB7) | (0 << PORTB6) | (0 << PORTB5) | (0 << PORTB4) | (0 << PORTB3) | (0 << PORTB2) | (0 << PORTB1) | (0 << PORTB0);

    // Port C initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=In Bit1=In Bit0=In
    DDRC = (0 << DDC7) | (0 << DDC6) | (0 << DDC5) | (0 << DDC4) | (1 << DDC3) | (0 << DDC2) | (0 << DDC1) | (0 << DDC0);
    // State: Bit7=P Bit6=P Bit5=P Bit4=T Bit3=0 Bit2=T Bit1=T Bit0=T
    PORTC = (1 << PORTC7) | (1 << PORTC6) | (1 << PORTC5) | (0 << PORTC4) | (0 << PORTC3) | (0 << PORTC2) | (0 << PORTC1) | (0 << PORTC0);

    // Port D initialization
    // Function: Bit7=Out Bit6=Out Bit5=In Bit4=In Bit3=In Bit2=Out Bit1=In Bit0=In
    DDRD = (1 << DDD7) | (1 << DDD6) | (0 << DDD5) | (0 << DDD4) | (0 << DDD3) | (1 << DDD2) | (0 << DDD1) | (0 << DDD0);
    // State: Bit7=0 Bit6=0 Bit5=T Bit4=T Bit3=T Bit2=0 Bit1=T Bit0=T
    PORTD = (0 << PORTD7) | (0 << PORTD6) | (0 << PORTD5) | (0 << PORTD4) | (0 << PORTD3) | (0 << PORTD2) | (0 << PORTD1) | (0 << PORTD0);

    // Timer/Counter 0 initialization
    // Clock source: System Clock
    // Clock value: 31.250 kHz
    // Mode: Normal top=0xFF
    // OC0 output: Disconnected
    // Timer Period: 8 ms
    TCCR0 = (0 << WGM00) | (0 << COM01) | (0 << COM00) | (0 << WGM01) | (1 << CS02) | (0 << CS01) | (0 << CS00);
    TCNT0 = 0x06;
    OCR0 = 0x00;

    // Timer(s)/Counter(s) Interrupt(s) initialization
    TIMSK = (0 << OCIE2) | (0 << TOIE2) | (0 << TICIE1) | (0 << OCIE1A) | (0 << OCIE1B) | (0 << TOIE1) | (0 << OCIE0) | (1 << TOIE0);

    // TWI initialization
    // Mode: TWI Master
    // Bit Rate: 100 kHz
    twi_master_init(100);

    // Alphanumeric LCD initialization
    // Connections are specified in the
    // Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
    // RS: PORTB Bit 0
    // RD: PORTC Bit 2
    // EN: PORTB Bit 1
    // D4: PORTB Bit 2
    // D5: PORTB Bit 5
    // D6: PORTB Bit 6
    // D7: PORTB Bit 7
    // Characters/line: 8
    lcd_init(8);

// Globally enable interrupts
#asm("sei")

    // DS1307 Real Time Clock initialization for TWI
    // Square wave output on pin SQW/OUT: Off
    // SQW/OUT pin state: 0
    rtc_init(0, 0, 0);
}