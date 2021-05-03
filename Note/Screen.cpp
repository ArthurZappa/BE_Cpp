#include "Screen.h"

Screen::Screen() : u8g2(U8G2_R0, /* clock=*/ PIN_SCL, /* data=*/ PIN_SDA, /* reset=*/ U8X8_PIN_NONE){}   // Adafruit Feather M0 Basic Proto + FeatherWing OLED

void Screen::Init_Screen(void) {
  u8g2.begin();
  u8g2.setFont(u8g2_font_courR24_tr); //set display parameters = transparent characters with variable width and with unicode 32 to 255 included
  u8g2.setFontRefHeightExtendedText();//set calculation method for the ascent and descent of the font 
  u8g2.setDrawColor(1);               //set colors to bright caracters and black background
  u8g2.setFontPosCenter();            //set caracters position reference to the center 
  u8g2.setFontDirection(0);           //set writing direction to "left to right"
}

void Screen::Display_Note(uint16_t Note1, uint16_t Note2) {
  u8g2.clearBuffer();
  u8g2.drawGlyph(50, 20, Note1);
  u8g2.drawGlyph(70, 20, Note2);
  u8g2.sendBuffer();
}

void Screen::Display_All_Notes(void){
  int delais = 1000;
  Display_Note(0x44, 0x4F); //display DO
  delay(delais);
  Display_Note(0x52, 0x45); //display RE
  delay(delais);
  Display_Note(0x4D, 0x49); //display MI
  delay(delais);
  Display_Note(0x46, 0x41); //display FA
  delay(delais);
  Display_Note(0x53, 0x4F); //display SOL
  delay(delais);
  Display_Note(0x4C, 0x41); //display LA
  delay(delais);
  Display_Note(0x53, 0x49); //display SI
  delay(delais);
}

void Screen::Recognize_Display(void) {
  note.Recognize();
  Display_Note(note.Get_Name(1), note.Get_Name(2));
}
