#include "Sheet.h"

String * Sheet::tab_duration = new String[8];
String * Sheet::tab_name = new String[8];

Sheet::Sheet(){
   for (int i =0; i<8;i++){
        tab_name[i]="";
        tab_duration[i]="";
   }
  cnt_tamp=0;
}


void Sheet::Construct_Measure(void){

  if (cnt_tamp != note.Get_Cnt()){    // every half time (if note_cnt was incremented)
    
    if (note.Get_Cnt()%8 == 0){       // if we start a new measure, we re initialize tabs
      for (int i =0; i<8;i++){
        Serial.println(tab_name[i] + "  "+tab_duration[i]);
        tab_name[i]="";
        tab_duration[i]="";
      }      
    }
    if (note.Get_Duration() != "n") {  // we check if there is a note during this half time and we fill tabs with the right value
      if (note.Get_Name(0)==67) tab_name[note.Get_Cnt()%8] = "c/4"; // conversion from int (needed for the screen) to string (needed for the application)
      else if (note.Get_Name(0)==68) tab_name[note.Get_Cnt()%8] = "d/4";
      else if (note.Get_Name(0)==69) tab_name[note.Get_Cnt()%8] = "e/4";
      else if (note.Get_Name(0)==70) tab_name[note.Get_Cnt()%8] = "f/4";
      else if (note.Get_Name(0)==71) tab_name[note.Get_Cnt()%8] = "g/4";
      else if (note.Get_Name(0)==65) tab_name[note.Get_Cnt()%8] = "a/4";
      else if (note.Get_Name(0)==66) tab_name[note.Get_Cnt()%8] = "b/4";
      
      tab_duration[note.Get_Cnt()%8] = note.Get_Duration();
     
    }
    
    cnt_tamp = note.Get_Cnt();
  }

  
}

 String Sheet::Get_Tab_Name(int i){
  return tab_name[i];
 }

 
 String Sheet::Get_Tab_Duration(int i){
  return tab_duration[i];
 }
