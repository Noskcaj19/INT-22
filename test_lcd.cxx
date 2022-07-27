#include <LiquidCrystal_74HC595.h>

/// LCD
#define SHIFT_DS    13 // Shift Reg Data (input)
#define SHIFT_SH_CP 12 // Shift Reg Clock
#define SHIFT_ST_CP 11 // Shift Reg Latch

//    LCD SIDE <> Shift Reg Side (starting from 0 (i.e. if RS is connected to 2, subtract 1))
#define LCD_RS 1 // NOT Arduino pin
#define LCD_E  3 // NOT Arduino pin
#define LCD_D4 4 // NOT Arduino pin
#define LCD_D5 5 // NOT Arduino pin
#define LCD_D6 6 // NOT Arduino pin
#define LCD_D7 7 // NOT Arduino pin

LiquidCrystal_74HC595 lcd(SHIFT_DS, SHIFT_SH_CP, SHIFT_ST_CP, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {
  lcd.begin(20, 4);

  lcd.print("Testing Line 1!");
  lcd.setCursor(0, 1);
  lcd.print("Line 2 testing!");
}



void loop() {
}

// gold red 10k?