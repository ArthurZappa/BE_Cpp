#ifndef SHEET_H
#define SHEET_H

#include "Note.h"
#include "App.h"

class Sheet {
  
  private : 
  
  Note note;
  App app;
  float time_duration;  // duration of a time calculate with the tempo set by the client in the app in milliseconds
  char note_duration;   //'n' = none ; 'q' = quarter note (1 time) ; 'e' = eight note (1/2 time)

  
  public : 
  Sheet();

/**
   * @brief Recognize the duration of the note (quarter or eight note)
   * @param none
   * @return none
   */
  void Recognize_Duration(void);
  
};
#endif 
