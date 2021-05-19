#ifndef SHEET_H
#define SHEET_H

#include "Note.h"
#include <vector>
using namespace std;

class Sheet {
  
private : 
  static vector<String> tab_name;
  static vector<String> tab_duration;
  vector<String> tab_name_temp;
  vector<String> tab_duration_temp;
  
  /*static String * tab_name;
  static String * tab_duration;
  String tab_name_temp[16];
  String tab_duration_temp[16];*/
  
  int cnt_temp;

  // time management for multi-threading
  uint16_t previous_millis;
  uint16_t current_millis;



public : 
  Sheet();
  Note note;
  /**
   * @brief Construction of a measure (8 times)
   * @param none
   * @return none
   */
  void Construct_Measure(uint16_t time_duration);

  vector<String> Get_Tab_Name();
  vector<String> Get_Tab_Duration();

};
#endif 
