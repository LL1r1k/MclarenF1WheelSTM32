/*
 * 8 bit paralell LCD/TOUCH GPIO driver for STM32F1
 * 5 controll pins (CS, RS, WR, RD, RST) + 8 data pins + backlight pin

 * note: since the LCD and touch are on the same pins, 
 * the simultaneous use of these should be excluded.
 * In multi-threaded interruption mode, collision prevention must be avoided!
 */

//=============================================================================
/* Lcd controll pins assign (A..K, 0..15) */
#define LCD_CS            B, 5
#define LCD_RS            A, 0
#define LCD_WR            A, 1
#define LCD_RD            B, 1  /* If not used leave it that way */
#define LCD_RST           B, 0  /* If not used leave it that way */

/* Lcd data pins assign (A..K, 0..15) */
#define LCD_D0            B, 8
#define LCD_D1            B, 9
#define LCD_D2            B, 10
#define LCD_D3            B, 11
#define LCD_D4            B, 12
#define LCD_D5            B, 13
#define LCD_D6            B, 14
#define LCD_D7            B, 15

/* Backlight control
   - BL: A..K, 0..15 (if not used -> X, 0)
   - BL_ON: 0 = active low level, 1 = active high level */
#define LCD_BL            X, 0  /* If not used leave it that way */
#define LCD_BLON          0

/*-----------------------------------------------------------------------------
Touch I/O pins and A/D channels
In the lcd board are paralell pins
 - TS_XM <- LCD_RS
 - TS_XP <- LCD_D6
 - TS_YM <- LCD_D7
 - TS_YP <- LCD_WR */

/* ADC converter number (1, 2, 3, or 0 if not used)
   - 0: analog touchscreen driver not used
   - 1..3: A/D converter number */
#define TS_ADC            0

/* Select the AD channels */
#define TS_XM_ADCCH       0
#define TS_YP_ADCCH       0

/* Wait time for LCD write and read pulse and touchscreen AD converter
   - First, give 10, 20, 500 values, then lower them to speed up the program.
     (values also depend on processor speed and LCD display speed) */
#define LCD_WRITE_DELAY  0
#define LCD_READ_DELAY   1
#define TS_AD_DELAY     500

/*=============================================================================
I/O group optimization so that GPIO operations are not performed bit by bit:
Note: If the pins are in order, they will automatically optimize.
The example belongs to the following pins:
      LCD_D0<-D14, LCD_D1<-D15, LCD_D2<-D0, LCD_D3<-D1
      LCD_D4<-E7,  LCD_D5<-E8,  LCD_D6<-E9, LCD_D7<-E10 */
#if 0
/* datapins setting to output (data direction: STM32 -> LCD) */
#define LCD_DIRWRITE { /* D0..D1, D14..D15, E7..E10 <- 0x3 */ \
GPIOD->CRH = (GPIOD->CRH & ~0xFF000000) | 0x33000000; \
GPIOD->CRL = (GPIOD->CRL & ~0x000000FF) | 0x00000033; \
GPIOE->CRL = (GPIOE->CRL & ~0xF0000000) | 0x30000000; \
GPIOE->CRH = (GPIOE->CRH & ~0x00000FFF) | 0x00000333; }
/* datapins setting to input (data direction: STM32 <- LCD) */
#define LCD_DIRREAD { /* D0..D1, D14..D15, E7..E10 <- 0x4 */ \
GPIOD->CRH = (GPIOD->CRH & ~0xFF000000) | 0x44000000; \
GPIOD->CRL = (GPIOD->CRL & ~0x000000FF) | 0x00000044; \
GPIOE->CRL = (GPIOE->CRL & ~0xF0000000) | 0x40000000; \
GPIOE->CRH = (GPIOE->CRH & ~0x00000FFF) | 0x00000444; }
/* datapins write, STM32 -> LCD (write I/O pins from dt data) */
#define LCD_WRITE(dt) { /* D14..15 <- dt0..1, D0..1 <- dt2..3, E7..10 <- dt4..7 */ \
GPIOD->ODR = (GPIOD->ODR & ~0b1100000000000011) | (((dt & 0b00000011) << 14) | ((dt & 0b00001100) >> 2)); \
GPIOE->ODR = (GPIOE->ODR & ~0b0000011110000000) | ((dt & 0b11110000) << 3); }
/* datapins read, STM32 <- LCD (read from I/O pins and store to dt data) */
#define LCD_READ(dt) { /* dt0..1 <- D14..15, dt2..3 <- D0..1, dt4..7 <- E7..10 */ \
dt = ((GPIOD->IDR & 0b1100000000000000) >> 14) | ((GPIOD->IDR & 0b0000000000000011) << 2) | \
     ((GPIOE->IDR & 0b0000011110000000) >> 3); }
/* Note: the keil compiler cannot use binary numbers, convert it to hexadecimal */	 
#endif
