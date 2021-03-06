#ifndef SCREEN_H
#define SCREEN_H

#include <Wire.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include "Note.h"
  
class Screen {
  
private :

// initialize I2C pins
const uint8_t PIN_SCL = 4; //pin scl = D2 = GPIO4
const uint8_t PIN_SDA = 5; //pin sda = D1 = GPIO5

U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2;

Note note;

public :

Screen();
/**
   * @brief Initializate the parameters of the screen
   * @param none
   * @return none
   */
void Init_Screen(void);

/**
   * @brief Display a note
   * @param none
   * @return none
   */
void Display_Note(uint16_t Note1, uint16_t Note2);

/**
   * @brief Display a all notes
   * @param none
   * @return none
   */
void Display_All_Notes(void);


void Display(void);

};

#endif
