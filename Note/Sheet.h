#ifndef SHEET_H
#define SHEET_H

#include "Note.h"


class Sheet {
  
private : 
  
  static String * tab_name;
  static String * tab_duration;
  int cnt_tamp;



public : 
  Sheet();
  Note note;
  void Construct_Measure(void);

  String Get_Tab_Name(int i);
  String Get_Tab_Duration(int i);

};
#endif 
