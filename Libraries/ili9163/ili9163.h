

//#define ili9163_RST GPIO_Pin_2
#define ili9163_A0  GPIO_Pin_3
#define ili9163_CS  GPIO_Pin_4


// Screen orientation defines:
// 0 Ribbon at top
// 1 Ribbon at left
// 2 Ribbon at right
// 3 Ribbon at bottom
#define LCD_ORIENTATION0    0
#define LCD_ORIENTATION1    96
#define LCD_ORIENTATION2    160
#define LCD_ORIENTATION3    192
 
#define Black           0x0000      /*  0, 0, 0 */
#define Maroon          0x000F      /*  0, 0,15 */
#define DarkGreen       0x03C0      /*  0,15, 0 */
#define Navy            0x7800      /* 15, 0, 0 */
#define Red             0x001F      /*  0, 0,31 */
#define Green           0x07C0      /*  0,31, 0 */
#define Blue            0xF800      /* 31, 0, 0 */
#define Yellow          0x07DF      /*  0,31,31 */
#define Magenta         0xF81F      /* 31, 0,31 */
#define Cyan            0xFFC0      /* 31,31, 0 */
#define White           0xFFFF      /* 31,31,31 */



#define NOP                     0x00
#define SOFT_RESET              0x01
#define GET_RED_CHANNEL         0x06
#define GET_GREEN_CHANNEL       0x07
#define GET_BLUE_CHANNEL        0x08
#define GET_PIXEL_FORMAT        0x0C
#define GET_POWER_MODE          0x0A
#define GET_ADDRESS_MODE        0x0B
#define GET_DISPLAY_MODE        0x0D
#define GET_SIGNAL_MODE         0x0E
#define GET_DIAGNOSTIC_RESULT   0x0F
#define ENTER_SLEEP_MODE        0x10
#define EXIT_SLEEP_MODE         0x11
#define ENTER_PARTIAL_MODE      0x12
#define ENTER_NORMAL_MODE       0x13
#define EXIT_INVERT_MODE        0x20
#define ENTER_INVERT_MODE       0x21
#define SET_GAMMA_CURVE         0x26
#define SET_DISPLAY_OFF         0x28
#define SET_DISPLAY_ON          0x29
#define SET_COLUMN_ADDRESS      0x2A
#define SET_PAGE_ADDRESS        0x2B
#define WRITE_MEMORY_START      0x2C
#define WRITE_LUT               0x2D
#define READ_MEMORY_START       0x2E
#define SET_PARTIAL_AREA        0x30
#define SET_SCROLL_AREA         0x33
#define SET_TEAR_OFF            0x34
#define SET_TEAR_ON             0x35
#define SET_ADDRESS_MODE        0x36
#define SET_SCROLL_START        0x37
#define EXIT_IDLE_MODE          0x38
#define ENTER_IDLE_MODE         0x39
#define SET_PIXEL_FORMAT        0x3A
#define WRITE_MEMORY_CONTINUE   0x3C
#define READ_MEMORY_CONTINUE    0x3E
#define SET_TEAR_SCANLINE       0x44
#define GET_SCANLINE            0x45
#define READ_ID1                0xDA
#define READ_ID2                0xDB
#define READ_ID3                0xDC
#define FRAME_RATE_CONTROL1     0xB1
#define FRAME_RATE_CONTROL2     0xB2
#define FRAME_RATE_CONTROL3     0xB3
#define DISPLAY_INVERSION       0xB4
#define SOURCE_DRIVER_DIRECTION 0xB7
#define GATE_DRIVER_DIRECTION   0xB8
#define POWER_CONTROL1          0xC0
#define POWER_CONTROL2          0xC1
#define POWER_CONTROL3          0xC2
#define POWER_CONTROL4          0xC3
#define POWER_CONTROL5          0xC4
#define VCOM_CONTROL1           0xC5
#define VCOM_CONTROL2           0xC6
#define VCOM_OFFSET_CONTROL     0xC7
#define WRITE_ID4_VALUE         0xD3
#define NV_MEMORY_FUNCTION1     0xD7
#define NV_MEMORY_FUNCTION2     0xDE
#define POSITIVE_GAMMA_CORRECT  0xE0
#define NEGATIVE_GAMMA_CORRECT  0xE1
#define GAM_R_SEL               0xF2




void ili9163Init(void);
void ili9163Update(void);
