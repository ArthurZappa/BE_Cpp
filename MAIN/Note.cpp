#include "Note.h"


int Note::cnt_note = 0;
String Note::note_duration = "n";
uint16_t * Note::note_name = new uint16_t[2];

Note::Note() {
  is_note = false;
  micro.Init_Micro();
  previous_millis_name = 0;
  previous_millis_duration = 0;
  current_millis = 0;
}


void Note::Note_Detected(float time_duration) {
  is_note=true;
  delay(time_duration/4);
}



void Note::Recognize_Name(float time_duration){
  current_millis = millis();
  
  if (current_millis - previous_millis_name >= micro.Get_Delay() ) {
    previous_millis_name = current_millis;
    
    micro.Manage_Micro();
    double frequence = micro.Get_Fondamental();
   //Serial.println(frequence);
    if ( ((frequence>260)&&(frequence<270)) || ((frequence>520)&&(frequence<540)) ){
      Serial.println('C'); //do
      note_name[0] = 0x43;  
      note_name[1] = 0x20;
      Note_Detected(time_duration);
    }
    else if ( ((frequence>292)&&(frequence<302)) || ((frequence>584)&&(frequence<604)) ){
      Serial.println('D'); //re
      note_name[0] = 0x44;
      note_name[1] = 0x20;
      Note_Detected(time_duration);
    }
    else if ( ((frequence>325)&&(frequence<335)) || ((frequence>650)&&(frequence<670)) ){
      Serial.println('E'); //mi
      note_name[0] = 0x45;
      note_name[1] = 0x20;
      Note_Detected(time_duration);
    }
    else if ( ((frequence>347)&&(frequence<357)) || ((frequence>694)&&(frequence<714)) ){
      Serial.println('F'); //fa
      note_name[0] = 0x46;
      note_name[1] = 0x20;
      Note_Detected(time_duration);
    }
    else if ( ((frequence>390)&&(frequence<400)) || ((frequence>780)&&(frequence<800)) ){
      Serial.println('G'); //sol
      note_name[0] = 0x47;
      note_name[1] = 0x20;
      Note_Detected(time_duration);
    }
    else if ( ((frequence>435)&&(frequence<445)) || ((frequence>870)&&(frequence<890)) ){
      Serial.println('A'); //la
      note_name[0] = 0x41;
      note_name[1] = 0x20;
      Note_Detected(time_duration);
    }
  
    else if ( ((frequence>490)&&(frequence<500)) || ((frequence>980)&&(frequence<1000)) ){
      Serial.println('B'); //si
      note_name[0] = 0x42;
      note_name[1] = 0x20;
      Note_Detected(time_duration);
    }
  
    else if (frequence > 1000 && frequence < 1100) {throw Too_High(); is_note = false;}
    else if (frequence >200 && frequence < 240) {throw Too_Low(); is_note = false;}
  }
  
}


void Note::Recognize_Duration(float time_duration) {
  
  note_already_detected = false;
  
  float last_iteration = (int)(time_duration/(2*micro.Get_Delay()))*micro.Get_Delay();
  
  for (float i=0; i<(time_duration/2) ; i= i + micro.Get_Delay()) { // we count at the frequency that the micro needs to calculate the FFT
     current_millis = millis();
     if (current_millis - previous_millis_duration >= micro.Get_Delay()) {
      previous_millis_duration = current_millis;
      
       if ((is_note) && (!note_already_detected)) {         // check if there is a note at the instant i between 0 and the half of the time and if we didn't already detect a note
         if (note_duration == "n") note_duration = "4";     // if during the previous half time, there wasn't a note --> this note is a quarter note
         if (note_duration == "4") note_duration = "4";     // if during the previous half time, there was a quarter note --> this note is a eight note
         cnt_note++;
         note_already_detected = true;
       }
      
       else if (((int)i==(int)last_iteration) && (!note_already_detected)) { // if we didn't detected a note during the all half time, we put the duration at 'n'
         note_duration = "4"; 
         cnt_note++;
       }
     }
   }

}

uint16_t Note::Get_Name(int i) {
  return note_name[i];
}



String Note::Get_Duration() {
  return note_duration;
}

int Note::Get_Cnt(){
  return cnt_note;
  
}
