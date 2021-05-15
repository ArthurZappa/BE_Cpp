#ifndef NOTE_H
#define NOTE_H

#include <Arduino.h>
#include <U8g2lib.h>
#include "Micro.h"

class Note{

private :

uint16_t name[2];

static bool is_note; // true if a note is detected, false if not

public:

Micro micro;

Note();
Note(uint16_t note1, uint16_t note2);

/**
   * @brief Recognize the note according its frequency
   * @param none
   *        
   * @return none
   */
void Recognize(void);
/**
   * @brief Getter of the value of is_note -> true if a note is detected, else if not
   * @param none
   * @return bool is_note
   */
bool Is_Note(void);

uint16_t Get_Name(int i);


  
};

#endif
