#ifndef NOTE_H
#define NOTE_H

#include <Arduino.h>
#include <U8g2lib.h>
#include "Micro.h"


class Note{

private :

  Micro micro;

  
  static uint16_t* note_name;
  static String note_duration;   //'n' = none ; '4' = quarter note (1 time) ; '8' = eight note (1/2 time)
  static int cnt_note ;          // counter incremented every half time

  bool is_note;                  // true if a note is detected, false if not
 
  
  
  bool note_already_detected;
 

/**
   * @brief Wait an half of time and pass is_note = true when a note is detected
   * @param none
   *        
   * @return none
   */
void Note_Detected(float time_duration);

public:

Note();

/**
   * @brief Recognize the note name according its frequency
   * @param none
   *        
   * @return none
   */
void Recognize_Name(float time_duration);

/**
   * @brief Recognize the duration of the note (quarter or eight note)
   * @param Duration of one time, calculate with the value of tempo in App
   * @return none
   */
void Recognize_Duration(float time_duration);




uint16_t Get_Name(int i);

String Get_Duration(void);

int Get_Cnt(void);


  
};

#endif
