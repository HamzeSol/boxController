#include <mega32a.h>
#include <delay.h>
#include <io.h>
#include <alcd.h>

typedef enum
{
    GPIO_PIN_0 = (0x01),    /*!< Pin 0 selected */
    GPIO_PIN_1 = (0x02),    /*!< Pin 1 selected */
    GPIO_PIN_2 = (0x04),    /*!< Pin 2 selected */
    GPIO_PIN_3 = (0x08),    /*!< Pin 3 selected */
    GPIO_PIN_4 = (0x10),    /*!< Pin 4 selected */
    GPIO_PIN_5 = (0x20),    /*!< Pin 5 selected */
    GPIO_PIN_6 = (0x40),    /*!< Pin 6 selected */
    GPIO_PIN_7 = (0x80),    /*!< Pin 7 selected */
    GPIO_PIN_LNIB = (0x0F), /*!< Low nibble pins selected */
    GPIO_PIN_HNIB = (0xF0), /*!< High nibble pins selected */
    GPIO_PIN_ALL = (0xFF)   /*!< All pins selected */
} GPIO_Pin_TypeDef;

#define LCD_BACKLIGHT_PORT (PORTD)
#define LCD_BACKLIGHT_PIN (GPIO_PIN_2)

#define KEY1_PORT (PINC)
#define KEY1_PIN (GPIO_PIN_5)

#define KEY2_PORT (PINC)
#define KEY2_PIN (GPIO_PIN_6)

#define KEY3_PORT (PINC)
#define KEY3_PIN (GPIO_PIN_7)

#define BUZZ_PORT (PORTC)
#define BUZZ_PIN (GPIO_PIN_3)

#define POMP1_PORT (PORTD)
#define POMP1_PIN (GPIO_PIN_7)

#define POMP2_PORT (PORTD)
#define POMP2_PIN (GPIO_PIN_6)

#define RELAY_PORT (PORTA)
#define RELAY_PIN (GPIO_PIN_0)
