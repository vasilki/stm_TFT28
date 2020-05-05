// adapted from LCD_ID_Reader from http://misc.ws/lcd_information
// controllers either read as 16-bit or as a sequence of 8-bit values

//-- Arduino UNO or Mega 2560 Plugged as shield
#include "main.h"
#include "uart.h"
#include "dwt_stm32_delay.h"


#define LCD_RST LCD_RST_Pin
#define LCD_CS A3_Pin
#define LCD_RS A2_Pin
#define LCD_WR A1_Pin
#define LCD_RD A0_Pin

#define LCD_RST_GPIO LCD_RST_GPIO_Port
#define LCD_CS_GPIO A3_GPIO_Port
#define LCD_RS_GPIO A2_GPIO_Port
#define LCD_WR_GPIO A1_GPIO_Port
#define LCD_RD_GPIO A0_GPIO_Port


#define LCD_D0 D0_Pin
#define LCD_D1 D1_Pin
#define LCD_D2 D2_Pin
#define LCD_D3 D3_Pin
#define LCD_D4 D4_Pin
#define LCD_D5 D5_Pin
#define LCD_D6 D6_Pin
#define LCD_D7 LCD_DC_Pin


#define LCD_D0_GPIO D0_GPIO_Port
#define LCD_D1_GPIO D1_GPIO_Port
#define LCD_D2_GPIO D2_GPIO_Port
#define LCD_D3_GPIO D3_GPIO_Port
#define LCD_D4_GPIO D4_GPIO_Port
#define LCD_D5_GPIO D5_GPIO_Port
#define LCD_D6_GPIO D6_GPIO_Port
#define LCD_D7_GPIO LCD_DC_GPIO_Port

uint8_t unlock_1520[]     = { (0xB0), 2, 0x00, 0x00 };
uint8_t unlock_1526[]     = { (0xB0), 2, 0x3F, 0x3F };
uint8_t unlock_8357[]     = { (0xB9), 3, 0xFF, 0x83, 0x57};
uint8_t unlock_5310[] = { (0xED), 2, 0x01, 0xFE};
uint8_t d5310_0_in[] = { (0xEE), 2, 0xDE, 0x21}; //enter CMD3 8bit args
//uint8_t d5310_1[] = { (0x??), 2, 0xDE, 0x21};
uint8_t d5310_1_in[] = { (0xBF), 1, 0xAA}; //enter page#1 16bit args
uint8_t d5310_1_out[] = { (0x00), 1, 0xAA}; //leave page#1 16bit args
uint8_t d1526nvm[]  = { (0xE2), 1, 0x3F};
uint8_t *unlock     = NULL;
uint8_t *page_N     = NULL;

static void LCD_ID_read_regs(char *title);
static void lcdInit();
static void lcdReset();
static void LCD_ID_read_regs(char *title);

void lcdWrite8(uint16_t data);
uint16_t lcdRead8();

void lcdSetWriteDir();
void lcdSetReadDir();
void lcdWriteData(uint16_t data);
void lcdWriteCommand(uint16_t command);

uint8_t lcdReadData8();

uint16_t lcdReadData16();


void lcdWriteRegister(uint16_t addr, uint16_t data);
void pushCommand(uint8_t command, uint8_t *block, int8_t n);


void LCD_ID_setup()
{
   /* Serial.begin(9600);
    while (!Serial) ;*/
    uart_Printf("Read Registers on MCUFRIEND UNO shield");
    uart_Printf("controllers either read as single 16-bit");
    uart_Printf("e.g. the ID is at readReg(0)");
    uart_Printf("or as a sequence of 8-bit values");
    uart_Printf("in special locations (first is dummy)");
    uart_Printf("");
    lcdInit();
    lcdReset();      //ensures that controller is in default state
    //    unlock = unlock_1520;
    //    unlock = unlock_1526;
    //    unlock = unlock_8357;
    //    unlock = unlock_5310;
    //    page_N = d5310_1_in;
    //    for (uint16_t i = 0x00; i <= 0xFE; i++) readReg(i, 10, "f.k");
    LCD_ID_read_regs("diagnose any controller");
    //    read_xxxx("mystery");
    //    read_5310_P0("NT35310 P0");
    //    read_5310_P1("NT35310 P1");
    //    read_61509("R61509 / ILI9326");
    //    read_61526("R61520 / R61526");
    //    read_8357("HX8357X");
    //    read_9320("ILI9320");
    //    read_9327("ILI9327");
    //    read_9338("ILI9302 / ILI9329 / ILI9338 / ILI9341");
    //    read_9481("ILI9481 / HX8357-B / R61581");
    //    read_9486("ILI9486 / 1LI9488");
}

void loop()
{
    // put your main code here, to run repeatedly:

}

void printhex(uint8_t val)
{
    if (val < 0x10) uart_Printf("0");
    uart_PrintfInteger(val, "HEX");
}

void readReg(uint16_t reg, uint8_t n, const char *msg)
{
    uint8_t val8;
    lcdReset();
    lcdSetWriteDir();
    if (unlock) pushCommand(unlock[0], unlock + 2, unlock[1]);
    if (page_N) pushCommand(page_N[0], page_N + 2, page_N[1]);
    uart_Printf("reg(0x");
    uart_PrintfInteger(reg >> 8,"HEX");
    uart_PrintfInteger(reg,"HEX");
    uart_Printf(")");
    lcdWriteCommand(reg);
    lcdSetReadDir();
    while (n--) {
        val8 = lcdReadData8();
        uart_Printf(" ");
        uart_PrintfInteger(val8,"HEX");
    }
    lcdSetWriteDir();
    HAL_GPIO_WritePin(LCD_CS_GPIO, LCD_CS, GPIO_PIN_SET);

    uart_Printf("\t");
    uart_Printf(msg);
}

static void lcdInit()
{
    //@pinMode(LCD_CS, OUTPUT);
    HAL_GPIO_WritePin(LCD_CS_GPIO, LCD_CS, GPIO_PIN_SET);
    //@pinMode(LCD_RS, OUTPUT);
    HAL_GPIO_WritePin(LCD_RS_GPIO, LCD_RS, GPIO_PIN_SET);
    //@pinMode(LCD_WR, OUTPUT);
    HAL_GPIO_WritePin(LCD_WR_GPIO, LCD_WR, GPIO_PIN_SET);
    //@pinMode(LCD_RD, OUTPUT);
    HAL_GPIO_WritePin(LCD_RD_GPIO, LCD_RD, GPIO_PIN_SET);
    //@pinMode(LCD_RST, OUTPUT);
    HAL_GPIO_WritePin(LCD_RST_GPIO, LCD_RST, GPIO_PIN_SET);
}

static void lcdReset()
{
    HAL_GPIO_WritePin(LCD_RST_GPIO, LCD_RST, GPIO_PIN_RESET);
    HAL_Delay(2);
    HAL_GPIO_WritePin(LCD_RST_GPIO, LCD_RST, GPIO_PIN_SET);
    HAL_Delay(10);             //allow controller to re-start
}

void lcdWrite8(uint16_t data)
{
    HAL_GPIO_WritePin(LCD_D0_GPIO, LCD_D0, data & 1);
    HAL_GPIO_WritePin(LCD_D1_GPIO, LCD_D1, (data & 2) >> 1);
    HAL_GPIO_WritePin(LCD_D2_GPIO, LCD_D2, (data & 4) >> 2);
    HAL_GPIO_WritePin(LCD_D3_GPIO, LCD_D3, (data & 8) >> 3);
    HAL_GPIO_WritePin(LCD_D4_GPIO, LCD_D4, (data & 16) >> 4);
    HAL_GPIO_WritePin(LCD_D5_GPIO, LCD_D5, (data & 32) >> 5);
    HAL_GPIO_WritePin(LCD_D6_GPIO, LCD_D6, (data & 64) >> 6);
    HAL_GPIO_WritePin(LCD_D7_GPIO, LCD_D7, (data & 128) >> 7);
}

uint16_t lcdRead8()
{
    uint16_t result = HAL_GPIO_ReadPin(LCD_D7_GPIO, LCD_D7);
    result <<= 1;
    result |= HAL_GPIO_ReadPin(LCD_D6_GPIO, LCD_D6);
    result <<= 1;
    result |= HAL_GPIO_ReadPin(LCD_D5_GPIO, LCD_D5);
    result <<= 1;
    result |= HAL_GPIO_ReadPin(LCD_D4_GPIO, LCD_D4);
    result <<= 1;
    result |= HAL_GPIO_ReadPin(LCD_D3_GPIO, LCD_D3);
    result <<= 1;
    result |= HAL_GPIO_ReadPin(LCD_D2_GPIO, LCD_D2);
    result <<= 1;
    result |= HAL_GPIO_ReadPin(LCD_D1_GPIO, LCD_D1);
    result <<= 1;
    result |= HAL_GPIO_ReadPin(LCD_D0_GPIO, LCD_D0);

    return result;
}

void lcdSetWriteDir()
{
    uint8_t mode = GPIO_PIN_RESET;
    //@pinMode(LCD_D0, mode);
    //@pinMode(LCD_D1, mode);
    //@pinMode(LCD_D2, mode);
    //@pinMode(LCD_D3, mode);
    //@pinMode(LCD_D4, mode);
    //@pinMode(LCD_D5, mode);
    //@pinMode(LCD_D6, mode);
    //@pinMode(LCD_D7, mode);
}


void lcdSetReadDir()
{
    uint8_t mode = GPIO_PIN_SET;
    //@pinMode(LCD_D0, mode);
    //@pinMode(LCD_D1, mode);
    //@pinMode(LCD_D2, mode);
    //@pinMode(LCD_D3, mode);
    //@pinMode(LCD_D4, mode);
    //@pinMode(LCD_D5, mode);
    //@pinMode(LCD_D6, mode);
    //@pinMode(LCD_D7, mode);
}

void lcdWriteData(uint16_t data)
{
    lcdSetWriteDir();
    HAL_GPIO_WritePin(LCD_CS_GPIO, LCD_CS, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_RS_GPIO, LCD_RS, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_RD_GPIO, LCD_RD, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_WR_GPIO, LCD_WR, GPIO_PIN_SET);

    lcdWrite8(data >> 8);

    HAL_GPIO_WritePin(LCD_WR_GPIO, LCD_WR, GPIO_PIN_RESET);
    DWT_Delay_us(10);
    HAL_GPIO_WritePin(LCD_WR_GPIO, LCD_WR, GPIO_PIN_SET);

    lcdWrite8(data);

    HAL_GPIO_WritePin(LCD_WR_GPIO, LCD_WR, GPIO_PIN_RESET);
    DWT_Delay_us(10);
    HAL_GPIO_WritePin(LCD_WR_GPIO, LCD_WR, GPIO_PIN_SET);

    HAL_GPIO_WritePin(LCD_CS_GPIO, LCD_CS, GPIO_PIN_SET);
}

void lcdWriteCommand(uint16_t command)
{
    lcdSetWriteDir();
    HAL_GPIO_WritePin(LCD_CS_GPIO, LCD_CS, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_RS_GPIO, LCD_RS, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_RD_GPIO, LCD_RD, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_WR_GPIO, LCD_WR, GPIO_PIN_SET);
    lcdWrite8(command >> 8);
    HAL_GPIO_WritePin(LCD_WR_GPIO, LCD_WR, GPIO_PIN_RESET);
    DWT_Delay_us(10);
    HAL_GPIO_WritePin(LCD_WR_GPIO, LCD_WR, GPIO_PIN_SET);
    lcdWrite8(command);
    HAL_GPIO_WritePin(LCD_WR_GPIO, LCD_WR, GPIO_PIN_RESET);
    DWT_Delay_us(10);
    HAL_GPIO_WritePin(LCD_WR_GPIO, LCD_WR, GPIO_PIN_SET);
    //    HAL_GPIO_WritePin(LCD_CS_GPIO, LCD_CS, GPIO_PIN_SET);
}

uint8_t lcdReadData8()
{
    uint8_t result;
    lcdSetReadDir();
    HAL_GPIO_WritePin(LCD_CS_GPIO, LCD_CS, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_RS_GPIO, LCD_RS, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_RD_GPIO, LCD_RD, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_WR_GPIO, LCD_WR, GPIO_PIN_SET);

    HAL_GPIO_WritePin(LCD_RD_GPIO, LCD_RD, GPIO_PIN_RESET);
    DWT_Delay_us(10);
    result = lcdRead8();
    HAL_GPIO_WritePin(LCD_RD_GPIO, LCD_RD, GPIO_PIN_SET);

    DWT_Delay_us(10);

    return result;
}


uint16_t lcdReadData16()
{
    uint16_t result;
    result = lcdReadData8() << 8;
    result |= lcdReadData8();
    return result;
}


void lcdWriteRegister(uint16_t addr, uint16_t data)
{
    lcdWriteCommand(addr);
    lcdWriteData(data);
}

void pushCommand(uint8_t command, uint8_t *block, int8_t n)
{
    lcdSetWriteDir();
    HAL_GPIO_WritePin(LCD_CS_GPIO, LCD_CS, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_RS_GPIO, LCD_RS, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_RD_GPIO, LCD_RD, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_WR_GPIO, LCD_WR, GPIO_PIN_SET);
    lcdWrite8(command);
    HAL_GPIO_WritePin(LCD_WR_GPIO, LCD_WR, GPIO_PIN_RESET);
    DWT_Delay_us(10);
    HAL_GPIO_WritePin(LCD_WR_GPIO, LCD_WR, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_RS_GPIO, LCD_RS, GPIO_PIN_SET);
    while (n--) {
        lcdWrite8(*block++);
        HAL_GPIO_WritePin(LCD_WR_GPIO, LCD_WR, GPIO_PIN_RESET);
        DWT_Delay_us(10);
        HAL_GPIO_WritePin(LCD_WR_GPIO, LCD_WR, GPIO_PIN_SET);
    }
    HAL_GPIO_WritePin(LCD_CS_GPIO, LCD_CS, GPIO_PIN_SET);

}

// make all the functions static.
// the linker will discard unused anonymous strings.

static void LCD_ID_read_regs(char *title)
{
    uart_Printf(title);
    readReg(0x00, 2, "ID: ILI9320, ILI9325, ILI9335, ...");
    readReg(0x04, 4, "Manufacturer ID");
    readReg(0x09, 5, "Status Register");
    readReg(0x0A, 2, "Get Powsr Mode");
    readReg(0x0C, 2, "Get Pixel Format");
    readReg(0x30, 5, "PTLAR");
    readReg(0x33, 7, "VSCRLDEF");
    readReg(0x61, 2, "RDID1 HX8347-G");
    readReg(0x62, 2, "RDID2 HX8347-G");
    readReg(0x63, 2, "RDID3 HX8347-G");
    readReg(0x64, 2, "RDID1 HX8347-A");
    readReg(0x65, 2, "RDID2 HX8347-A");
    readReg(0x66, 2, "RDID3 HX8347-A");
    readReg(0x67, 2, "RDID Himax HX8347-A");
    readReg(0x70, 2, "Panel Himax HX8347-A");
    readReg(0xA1, 5, "RD_DDB SSD1963");
    readReg(0xB0, 2, "RGB Interface Signal Control");
    readReg(0xB3, 5, "Frame Memory");
    readReg(0xB4, 2, "Frame Mode");
    readReg(0xB6, 5, "Display Control");
    readReg(0xB7, 2, "Entry Mode Set");
    readReg(0xBF, 6, "ILI9481, HX8357-B");
    readReg(0xC0, 9, "Panel Control");
    readReg(0xC1, 4, "Display Timing");
    readReg(0xC5, 2, "Frame Rate");
    readReg(0xC8, 13, "GAMMA");
    readReg(0xCC, 2, "Panel Control");
    readReg(0xD0, 4, "Power Control");
    readReg(0xD1, 4, "VCOM Control");
    readReg(0xD2, 3, "Power Normal");
    readReg(0xD3, 4, "ILI9341, ILI9488");
    readReg(0xD4, 4, "Novatek");
    readReg(0xDA, 2, "RDID1");
    readReg(0xDB, 2, "RDID2");
    readReg(0xDC, 2, "RDID3");
    readReg(0xE0, 16, "GAMMA-P");
    readReg(0xE1, 16, "GAMMA-N");
    readReg(0xEF, 6, "ILI9327");
    readReg(0xF2, 12, "Adjust Control 2");
    readReg(0xF6, 4, "Interface Control");
}

static void read_5310_P0(char *title)
{
    uart_Printf(title);
    readReg(0xB0, 2, "DISPLAY_CTRL");
    readReg(0xB1, 4, "PORCH_CTRL");
    readReg(0xB2, 4, "FRAME_CTRL");
    readReg(0xB3, 2, "SPI_RGB");
    readReg(0xB6, 7, "SOURCE_EQ");
    readReg(0xC0, 5, "PWR_CTRL1");
    readReg(0xC1, 3, "PWR_CTRL2");
    readReg(0xC2, 4, "PWR_CTRL3");
    readReg(0xC3, 2, "PWR_CTRL5");
    readReg(0xC4, 2, "PWR_CTRL6");
    readReg(0xC5, 5, "PWR_CTRL7");
    readReg(0xC6, 5, "PWR_CTRL8");
    readReg(0xD1, 2, "WRID");
    readReg(0xD2, 2, "WRID");
    readReg(0xD3, 2, "WRID");
    readReg(0xD4, 5, "RDID4");
    readReg(0xD5, 5, "WRDDB");
    readReg(0xDE, 4, "EPWR");
    readReg(0xFF, 2, "PAGE_STATUS");
}

static void read_5310_P1(char *title)
{
    uart_Printf(title);
    /*
        readReg(0xB0, 19, "f.k");
        readReg(0xB1, 7, "f.k");
        readReg(0xB2, 7, "f.k");
        readReg(0xB3, 25, "f.k");
        readReg(0xB4, 7, "f.k");
        readReg(0xB5, 7, "f.k");
        readReg(0xB6, 3, "f.k");
        readReg(0xB7, 23, "f.k");
        readReg(0xB8, 7, "f.k");
        readReg(0xBA, 5, "f.k");
        readReg(0xC0, 19, "f.k");
        readReg(0xC1, 7, "f.k");
        readReg(0xC2, 5, "f.k");
        readReg(0xC3, 49, "f.k");
        readReg(0xC4, 27, "f.k");
        readReg(0xC5, 11, "f.k");
        readReg(0xC6, 7, "f.k");
        readReg(0xC7, 5, "f.k");
        readReg(0xC8, 5, "f.k");
        readReg(0xC9, 17, "f.k");
    */
    readReg(0xE0, 37, "GAMMA_RED_P");
    readReg(0xE1, 37, "GAMMA_RED_N");
    readReg(0xE2, 37, "GAMMA_GREEN_P");
    readReg(0xE3, 37, "GAMMA_GREEN_N");
    readReg(0xE4, 37, "GAMMA_BLUE_P");
    readReg(0xE5, 37, "GAMMA_BLUE_N");
    readReg(0xE6, 33, "CABC_RED");
    readReg(0xE7, 33, "CABC_GREEN");
    readReg(0xE8, 33, "CABC_BLUE");
    //    readReg(0xE9, 5, "f.k.");
    readReg(0xFF, 2, "PAGE_STATUS");
}

static void read_61509(char *title)
{
    uart_Printf(title);
    readReg(0x0000, 2, "Device Code Read");
    readReg(0x0001, 2, "Device Output Control");
    readReg(0x0002, 2, "LCD Waveform Control");
    readReg(0x0003, 2, "Entry Mode");
    readReg(0x0007, 2, "Display Control 1");
    readReg(0x0008, 2, "Display Control 2");
    readReg(0x0009, 2, "Display Control 3");
    readReg(0x0010, 2, "Panel Interface Control 1");
    readReg(0x0011, 2, "Panel Interface Control 2");
    readReg(0x0012, 2, "Panel Interface Control 3");
    readReg(0x0013, 2, "Panel Interface Control 4");
    readReg(0x0100, 2, "Power Control 1");
    readReg(0x0101, 2, "Power Control 2");
    readReg(0x0102, 2, "Power Control 3");
    readReg(0x0103, 2, "Power Control 4");
    readReg(0x0210, 2, "Horiz SA");
    readReg(0x0211, 2, "Horiz EA");
    readReg(0x0212, 2, "Vert SA");
    readReg(0x0213, 2, "Vert EA");
    readReg(0x0400, 2, "Base Image NL");
    readReg(0x0401, 2, "Base Image Control");
    readReg(0x0404, 2, "Base Image Scroll");
}

static void read_61526(char *title)
{
    uart_Printf(title);
    readReg(0x04, 4, "Manufacturer ID");
    readReg(0x0A, 2, "Get Power Mode");
    readReg(0x0B, 2, "Get Address Mode");
    readReg(0x0C, 2, "Get Pixel Format");
    readReg(0x0D, 2, "Get Display Mode");
    readReg(0x0E, 2, "Get Signal Mode");
    readReg(0x0F, 2, "Get Diagnostic Result");
    readReg(0xA1, 6, "RD_DDB Start");
    readReg(0xB0, 3, "Command Access Protect");
    readReg(0xB3, 6, "Frame Memory");
    readReg(0xB4, 2, "Frame Mode");
    readReg(0xBF, 5, "Device Code Read");
    readReg(0xC0, 9, "Panel Control");
    readReg(0xC1, 6, "Display Timing Normal");
    readReg(0xC3, 6, "Display Timing Idle");
    readReg(0xC4, 6, "Timing setting");
    readReg(0xC8, 23, "GAMMA");
    readReg(0xC9, 23, "GAMMA");
    readReg(0xCA, 23, "GAMMA");
    readReg(0xD0, 7, "Power Control");
    readReg(0xD1, 4, "VCOM Control");
    readReg(0xD2, 3, "Power Normal");
    readReg(0xD4, 3, "Power Idle");
    readReg(0xE0, 4, "NVM Access");
    readReg(0xE1, 2, "set_DDB");
    readReg(0xE2, 2, "NVM Load Control");
}

static void read_8357(char *title)
{
    uart_Printf(title);
    readReg(0x0A, 2, "Get Power Mode");
    readReg(0x0B, 2, "Get Address Mode");
    readReg(0x0C, 2, "Get Pixel Format");
    readReg(0x0D, 2, "Get Display Mode");
    readReg(0x0E, 2, "Get Signal Mode");
    readReg(0x0F, 2, "Get Diagnostic Result");
    readReg(0xA1, 6, "RD_DDB Start");
    readReg(0xB0, 3, "SETOSC");
    readReg(0xB1, 8, "SETPOWER");
    readReg(0xB2, 6, "SETDISPLAY");
    readReg(0xB3, 5, "SETRGB");
    readReg(0xB4, 8, "SETCYC");
    readReg(0xB5, 4, "SETBGP");
    readReg(0xB6, 3, "SETVCOM");
    readReg(0xB7, 6, "SETOTP");
    readReg(0xB9, 4, "SETEXTC");
    readReg(0xC0, 7, "SETSTBA");
    readReg(0xC1, 11, "SETDGC");
    readReg(0xC3, 5, "SETID");
    readReg(0xC4, 5, "SETDDB");
    readReg(0xC9, 3, "SETCABC");
    readReg(0xCC, 2, "SETPANEL");
    readReg(0xD0, 4, "GETICID");
    readReg(0xE0, 35, "SETGAMMA");
    readReg(0xE9, 2, "SETIMAGEI");
    readReg(0xEA, 2, "SETMESSI");
}

static void read_fk(char *title)
{
    uart_Printf(title);
    readReg(0x0A, 2, "Get Powsr Mode");
    readReg(0x0B, 2, "Get Address Mode");
    readReg(0x0C, 2, "Get Pixel Format");
    readReg(0x0D, 2, "Get Display Mode");
    readReg(0x0E, 2, "Get Signal Mode");
    readReg(0x0F, 2, "Get Diagnostic Result");
    readReg(0xA1, 6, "RD_DDB Start");
    readReg(0xB0, 3, "Command Access Protect");
    readReg(0xBF, 5, "Device Code Read");
    readReg(0xF0, 4, "f.k.");
    readReg(0xF2, 18, "f.k.");
    readReg(0xF3, 2, "f.k.");
    readReg(0xF4, 14, "f.k.");
    readReg(0xF5, 11, "f.k.");
    readReg(0xF6, 10, "f.k.");
    readReg(0xF7, 4, "f.k.");
    readReg(0xF8, 2, "f.k.");
    readReg(0xF9, 2, "f.k.");
    readReg(0xFA, 12, "f.k.");
    readReg(0xFB, 2, "f.k.");
    readReg(0xFC, 2, "f.k.");
    readReg(0xFD, 12, "f.k.");
    readReg(0xFE, 2, "f.k.");
}

static void read_xxxx(char *title)
{
    uart_Printf(title);
    readReg(0x09, 5, "Status Register");
    readReg(0x0A, 2, "Get Powsr Mode");
    readReg(0x0B, 2, "Get Address Mode");
    readReg(0x0C, 2, "Get Pixel Format");
    readReg(0x0D, 2, "Get Display Mode");
    readReg(0x0E, 2, "Get Signal Mode");
    readReg(0x0F, 2, "Get Diagnostic Result");
    readReg(0xA1, 6, "RD_DDB Start");
    readReg(0xB0, 3, "Command Access Protect");
    readReg(0xBF, 5, "Device Code Read");
    readReg(0xC6, 2, "f.k.");
    readReg(0xD6, 4, "f.k.");
    readReg(0xD7, 5, "f.k.");
    readReg(0xD8, 5, "f.k.");
    readReg(0xD9, 4, "f.k.");
    readReg(0xE0, 2, "f.k.");
    readReg(0xE1, 3, "f.k.");
    readReg(0xF0, 2, "f.k.");
    readReg(0xF1, 2, "f.k.");
    readReg(0xF2, 12, "f.k.");
    readReg(0xF3, 9, "f.k.");
    readReg(0xF4, 6, "f.k.");
    readReg(0xF5, 7, "f.k.");
    readReg(0xF6, 5, "f.k.");
    readReg(0xF7, 16, "f.k.");
    readReg(0xFD, 4, "f.k.");
    readReg(0xFE, 2, "f.k.");
    readReg(0xFF, 2, "f.k.");
}

static void read_9320(char *title)
{
    uart_Printf(title);
    readReg(0x0000, 2, "Device Code Read");
    readReg(0x0001, 2, "Drive Output Control");
    readReg(0x0002, 2, "LCD Waveform Control");
    readReg(0x0003, 2, "Entry Mode");
    readReg(0x0007, 2, "Display Control 1");
    readReg(0x0008, 2, "Display Control 2");
    readReg(0x0009, 2, "Display Control 3");
    readReg(0x000A, 2, "Display Control 4");
    readReg(0x0010, 2, "Power Control 1");
    readReg(0x0011, 2, "Power Control 2");
    readReg(0x0012, 2, "Power Control 3");
    readReg(0x0013, 2, "Power Control 4");
    readReg(0x0014, 2, "Power Control 5");
    readReg(0x0015, 2, "Power Control 6");
    readReg(0x0029, 2, "Power Control 7");
    readReg(0x002B, 2, "Frame Rate");
}

static void read_9327(char *title)
{
    uart_Printf(title);
    readReg(0x0A, 2, "Get Powsr Mode");
    readReg(0x0B, 2, "Get Address Mode");
    readReg(0x0C, 2, "Get Pixel Format");
    readReg(0x0D, 2, "Get Display Mode");
    readReg(0x0E, 2, "Get Signal Mode");
    readReg(0x0F, 2, "Get Diagnostic Result");
    readReg(0xA1, 6, "RD_DDB Start");
    readReg(0xB0, 2, "Command Access Protect");
    readReg(0xB1, 2, "Low Power Control");
    readReg(0xB3, 5, "Frame Memory");
    readReg(0xB4, 2, "Frame Mode");
    readReg(0xB5, 2, "Sub Panel Control");
    readReg(0xBF, 2, "Backlight Control");
    readReg(0xC0, 7, "Panel Control");
    readReg(0xC1, 4, "Display Timing Normal");
    readReg(0xC3, 4, "Display Timing Idle");
    readReg(0xC4, 2, "VCOM Timing");
    readReg(0xC5, 2, "Frame Rate");
    readReg(0xC6, 2, "Interface Control");
    readReg(0xC8, 13, "GAMMA");
    readReg(0xC9, 13, "GAMMA Red/Blue");
    readReg(0xCC, 2, "Panel Control");
    readReg(0xD0, 4, "Power Control");
    readReg(0xD1, 4, "VCOM Control");
    readReg(0xD2, 3, "Power Normal");
    readReg(0xD3, 3, "Power Partial");
    readReg(0xD4, 3, "Power Idle");
    readReg(0xEF, 6, "Device Code Read");
}

static void read_9338(char *title)
{
    uart_Printf(title);
    readReg(0x04, 4, "Manufacturer ID");
    //    readReg(0x05, 2, "DSI errors");
    readReg(0x09, 5, "Status Register");
    readReg(0x0A, 2, "Get Powsr Mode");
    readReg(0x0B, 2, "Get Address Mode");
    readReg(0x0C, 2, "Get Pixel Format");
    readReg(0x0D, 2, "Get Display Mode");
    readReg(0x0E, 2, "Get Signal Mode");
    readReg(0x0F, 2, "Get Diagnostic Result");
    readReg(0xB0, 2, "Interface Mode");
    readReg(0xB1, 3, "Frame Rate Normal");
    readReg(0xB2, 3, "Frame Rate Idle");
    readReg(0xB3, 3, "Frame Rate Partial");
    readReg(0xB4, 3, "Inversion Control");
    readReg(0xB5, 5, "Blanking Porch");
    readReg(0xB6, 4, "Display Control");
    readReg(0xB7, 2, "Entry Mode Set");
    readReg(0xC0, 2, "Power Control 1");
    readReg(0xC1, 2, "Power Control 2");
    readReg(0xC2, 2, "Power Control 3");
    readReg(0xC3, 2, "Power Control 4");
    readReg(0xC4, 2, "Power Control 5");
    readReg(0xC5, 3, "VCOM Control 1");
    readReg(0xC7, 2, "VCOM Control 2");
    /*
        readReg(0xD0, 3, "NVM Write");
        readReg(0xD1, 4, "NVM key");
    */
    readReg(0xD2, 3, "NVM Status");
    readReg(0xD3, 4, "RDID4");
    readReg(0xDA, 2, "RDID1");
    readReg(0xDB, 2, "RDID2");
    readReg(0xDC, 2, "RDID3");
    readReg(0xE0, 16, "GAMMA-P");
    readReg(0xE1, 16, "GAMMA-N");
    readReg(0xF2, 2, "GAMMA-3G");
    readReg(0xF6, 4, "Interface Control");
}

static void read_9481(char *title)
{
    uart_Printf(title);
    readReg(0x0A, 2, "Get Powsr Mode");
    readReg(0x0B, 2, "Get Address Mode");
    readReg(0x0C, 2, "Get Pixel Format");
    readReg(0x0D, 2, "Get Display Mode");
    readReg(0x0E, 2, "Get Signal Mode");
    readReg(0x0F, 2, "Get Diagnostic Result");
    readReg(0xA1, 6, "RD_DDB Start");
    readReg(0xB0, 2, "Command Access Protect");
    readReg(0xB3, 5, "Frame Memory");
    readReg(0xB4, 2, "Frame Mode");
    readReg(0xBF, 6, "Device Code Read");
    readReg(0xC0, 6, "Panel Control");
    readReg(0xC1, 4, "Display Timing Normal");
    readReg(0xC2, 4, "Display Timing Partial");
    readReg(0xC3, 4, "Display Timing Idle");
    readReg(0xC5, 2, "Frame Rate");
    readReg(0xC6, 2, "Interface Control");
    readReg(0xC8, 13, "GAMMA");
    readReg(0xCC, 2, "Panel Control");
    readReg(0xD0, 4, "Power Control");
    readReg(0xD1, 4, "VCOM Control");
    readReg(0xD2, 3, "Power Normal");
    readReg(0xD3, 3, "Power Partial");
    readReg(0xD4, 3, "Power Idle");
    readReg(0xE4, 4, "? SETCABC(HX) (f.k. ILI)");
    readReg(0xE9, 4, "? Set Panel Related(HX)");
    readReg(0xEE, 5, "? Set EQ Function(HX)");
    readReg(0xF0, 4, "f.k (ILI)");
    readReg(0xF1, 2, "f.k");
    readReg(0xF2, 4, "f.k");
    readReg(0xF3, 4, "f.k (ILI)");
    readReg(0xF4, 4, "f.k");
    readReg(0xF5, 2, "f.k");
    readReg(0xF6, 2, "f.k");
    readReg(0xF7, 4, "f.k");
    readReg(0xF8, 3, "f.k");
    readReg(0xF9, 2, "f.k");
}

static void read_9486(char *title)
{
    uart_Printf(title);
    readReg(0x04, 4, "Manufacturer ID");
    readReg(0x05, 2, "DSI errors");
    readReg(0x09, 5, "Status Register");
    readReg(0x0A, 2, "Get Powsr Mode");
    readReg(0x0B, 2, "Get Address Mode");
    readReg(0x0C, 2, "Get Pixel Format");
    readReg(0x0D, 2, "Get Display Mode");
    readReg(0x0E, 2, "Get Signal Mode");
    readReg(0x0F, 2, "Get Diagnostic Result");
    readReg(0xB0, 2, "Interface Mode");
    readReg(0xB1, 3, "Frame Rate Normal");
    readReg(0xB2, 3, "Frame Rate Idle");
    readReg(0xB3, 3, "Frame Rate Partial");
    readReg(0xB4, 2, "Inversion Control");
    readReg(0xB5, 5, "Blanking Porch");
    readReg(0xB6, 4, "Display Control");
    readReg(0xB7, 2, "Entry Mode Set");
    readReg(0xBF, 6, "NON-Ilitek Device Code Read");
    readReg(0xC0, 3, "Power Control 1");
    readReg(0xC1, 3, "Power Control 2");
    readReg(0xC2, 2, "Power Control 3");
    readReg(0xC3, 2, "Power Control 4");
    readReg(0xC4, 2, "Power Control 5");
    readReg(0xC5, 5, "VCOM Control 1");
    /*
        readReg(0xC6, 3, "CABC Control 1");
        readReg(0xC8, 3, "CABC Control 2");
        readReg(0xC9, 2, "CABC Control 3");
        readReg(0xCA, 2, "CABC Control 4");
        readReg(0xCB, 2, "CABC Control 5");
        readReg(0xCC, 2, "CABC Control 6");
        readReg(0xCD, 2, "CABC Control 7");
        readReg(0xCE, 2, "CABC Control 8");
        readReg(0xCF, 2, "CABC Control 9");
        readReg(0xD0, 3, "NVM Write");
        readReg(0xD1, 4, "NVM key");
        readReg(0xD2, 5, "NVM Status");
    */
    readReg(0xD3, 4, "RDID4");
    readReg(0xDA, 2, "RDID1");
    readReg(0xDB, 2, "RDID2");
    readReg(0xDC, 2, "RDID3");
    readReg(0xE0, 16, "GAMMA-P");
    readReg(0xE1, 16, "GAMMA-N");
    readReg(0xF2, 10, "Adjust 2");
    readReg(0xF7, 5, "Adjust 3");
    readReg(0xF8, 3, "Adjust 4");
    readReg(0xF9, 3, "Adjust 5");
    readReg(0xFB, 2, "SPI Read");
    readReg(0xFC, 3, "Adjust 6");
}


