#include "Sheet.h"

vector<String> Sheet::tab_name;
vector<String> Sheet::tab_duration;

Sheet::Sheet(){
   previous_millis = 0;
   current_millis = 0;
}


void Sheet::Construct_Measure(uint16_t time_duration){
  
  current_millis = millis();
  if (current_millis - previous_millis >= (time_duration/2) ) {
    previous_millis = current_millis;
    
    if (note.Get_Cnt()%8 == 0){       // if we start a new measure, we re initialize temporary tabs and we copy them in the definitive tabs (used in App)
      tab_name = tab_name_temp;
      tab_duration = tab_duration_temp;
      tab_name_temp.clear();
      tab_duration_temp.clear();
      Serial.println(tab_name.size());
    }
    if (note.Get_Duration() != "n") {  // we check if there is a note during this half time and we fill tabs with the right value
      if (note.Get_Name(0)==67) tab_name_temp.push_back("c/4"); // conversion from int (needed for the screen) to string (needed for the application)
      else if (note.Get_Name(0)==68) tab_name_temp.push_back("d/4");
      else if (note.Get_Name(0)==69) tab_name_temp.push_back("e/4");
      else if (note.Get_Name(0)==70) tab_name_temp.push_back("f/4");
      else if (note.Get_Name(0)==71) tab_name_temp.push_back("g/4");
      else if (note.Get_Name(0)==65) tab_name_temp.push_back("a/4");
      else if (note.Get_Name(0)==66) tab_name_temp.push_back("b/4");
      
      tab_duration_temp.push_back(note.Get_Duration());
    }
  }
}

 vector<String> Sheet::Get_Tab_Name(){
  return tab_name;
 }

 
 vector<String> Sheet::Get_Tab_Duration(){
  return tab_duration;
 }
