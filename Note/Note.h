#ifndef NOTE_H
#define NOTE_H

#include <Arduino.h>
#include <U8g2lib.h>
#include "Micro.h"

class Note{

private :

uint16_t name[2];
Micro micro;

public:

Note();
Note(uint16_t note1, uint16_t note2);

void Recognize(void);

uint16_t Get_Name(int i);

  
};

#endif
