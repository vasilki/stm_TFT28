# stm_LCD_WH1602
Connecting TFT 2.8 WaveShare (HX83247D TFT and XPT2046 touch controller) to the Nucleo F401RE

Pinout:
TFT->STM32
SCLK:SCK/D13
MISO:MISO/D12
MOSI:PWM/MOSI/D11
LCD_CS:PWM/CS/D10
LCD_BL:PWM/D9
LCD_DC:D7
SD_CS:PWM/D6


Environment:
STM32 NUCLEO-F401RE
Linux Mint 18.2 Sonya
STM32Cube_1.0 version 4.24.0.Repository is STM32Cube_FW_F4_V1.25.0.
System Workbench for STM32 (Version: 1.13.2.201703061529) based on Eclipse IDE version Mars.2.Release 4.5.2


Datasheets:
https://static.chipdip.ru/lib/184/DOC001184533.pdf
http://www.elechouse.com/elechouse/images/product/7tft_shield/XPT2046.pdf

---
Diagnosing data of display controller produced by library https://github.com/prenticedavid/MCUFRIEND_kbv


Read Registers on MCUFRIEND UNO shield
controllers either read as single 16-bit
e.g. the ID is at readReg(0)
or as a sequence of 8-bit values
in special locations (first is dummy)

diagnose any controller
reg(0x0000) 01 01 ID: ILI9320, ILI9325, ILI9335, ...
reg(0x0004) 05 05 05 05 Manufacturer ID
reg(0x0009) 09 09 09 09 09 Status Register
reg(0x000a) 0b 0b Get Powsr Mode
reg(0x000c) 0d 0d Get Pixel Format
reg(0x0030) 31 31 31 31 31 PTLAR
reg(0x0033) 33 33 33 33 33 33 33 VSCRLDEF
reg(0x0061) 61 61 RDID1 HX8347-G
reg(0x0062) 63 63 RDID2 HX8347-G
reg(0x0063) 63 63 RDID3 HX8347-G
reg(0x0064) 65 65 RDID1 HX8347-A
reg(0x0065) 65 65 RDID2 HX8347-A
reg(0x0066) 67 67 RDID3 HX8347-A
reg(0x0067) 67 67 RDID Himax HX8347-A
reg(0x0070) 71 71 Panel Himax HX8347-A
reg(0x00a1) a1 a1 a1 a1 a1 RD_DDB SSD1963
reg(0x00b0) b1 b1 RGB Interface Signal Control
reg(0x00b3) b3 b3 b3 b3 b3 Frame Memory
reg(0x00b4) b5 b5 Frame Mode
reg(0x00b6) b7 b7 b7 b7 b7 Display Control
reg(0x00b7) b7 b7 Entry Mode Set
reg(0x00bf) bf bf bf bf bf bf ILI9481, HX8357-B
reg(0x00c0) c1 c1 c1 c1 c1 c1 c1 c1 c1 Panel Control
reg(0x00c1) c1 c1 c1 c1 Display Timing
reg(0x00c5) c5 c5 Frame Rate
reg(0x00c8) c9 c9 c9 c9 c9 c9 c9 c9 c9 c9 c9 c9 c9 GAMMA
reg(0x00cc) cd cd Panel Control
reg(0x00d0) d1 d1 d1 d1 Power Control
reg(0x00d1) d1 d1 d1 d1 VCOM Control
reg(0x00d2) d3 d3 d3 Power Normal
reg(0x00d3) d3 d3 d3 d3 ILI9341, ILI9488
reg(0x00d4) d5 d5 d5 d5 Novatek
reg(0x00da) db db RDID1
reg(0x00db) db db RDID2
reg(0x00dc) dd dd RDID3
reg(0x00e0) e1 e1 e1 e1 e1 e1 e1 e1 e1 e1 e1 e1 e1 e1 e1 e1 GAMMA-P
reg(0x00e1) e1 e1 e1 e1 e1 e1 e1 e1 e1 e1 e1 e1 e1 e1 e1 e1 GAMMA-N
reg(0x00ef) ef ef ef ef ef ef ILI9327
reg(0x00f2) f3 f3 f3 f3 f3 f3 f3 f3 f3 f3 f3 f3 Adjust Control 2
reg(0x00f6) f7 f7 f7 f7 Interface Control