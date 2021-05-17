#ifndef NOTE_H
#define NOTE_H

#include <Arduino.h>
#include <U8g2lib.h>
#include "Micro.h"
#include "App.h"

class Note{

private :

  static uint16_t * name;
  bool is_note; // true if a note is detected, false if not

  Micro micro;
  App app;
  float time_duration;  // duration of a time calculate with the tempo set by the client in the app in milliseconds
  char note_duration;   //'n' = none ; '4' = quarter note (1 time) ; '8' = eight note (1/2 time)
  //bool note_already_detected;
 

/**
   * @brief Wait an half of time and pass is_note = true when a note is detected
   * @param none
   *        
   * @return none
   */
void Note_Detected(void);

public:

Note();

/**
   * @brief Recognize the note name according its frequency
   * @param none
   *        
   * @return none
   */
void Recognize_Name(void);

/**
   * @brief Recognize the duration of the note (quarter or eight note)
   * @param none
   * @return none
   */
void Recognize_Duration(void);

/**
   * @brief Getter of the value of is_note -> true if a note is detected, else if not
   * @param none
   * @return bool is_note
   */
bool Is_Note(void);


uint16_t Get_Name(int i);

char Get_Duration(void);



  
};

#endif
