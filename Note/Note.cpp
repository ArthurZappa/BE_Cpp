#include "Note.h"
#include "Micro.h"



uint16_t * name = new uint16_t[2];
//uint16_t Note::name[1] = 0x20;
  
Note::Note() {
  note_duration = 'n';
  time_duration = 60*1000/app.Get_Tempo(); // time duration in milliseconds
  is_note = false;
  micro.Init_Micro();
}


void Note::Note_Detected(void) {
  is_note=true;
  delay(time_duration/4);
}



void Note::Recognize_Name(void){

  double frequence = micro.Get_Fondamental();
 //Serial.println(frequence);
  if ( ((frequence>260)&&(frequence<270)) || ((frequence>520)&&(frequence<540)) ){
    Serial.println('C'); //do
    name[0] = 0x43;  
    name[1] = 0x20;
    Note_Detected();
  }
  else if ( ((frequence>292)&&(frequence<302)) || ((frequence>584)&&(frequence<604)) ){
    Serial.println('D'); //re
    name[0] = 0x44;
    name[1] = 0x20;
    Note_Detected();
  }
  else if ( ((frequence>325)&&(frequence<335)) || ((frequence>650)&&(frequence<670)) ){
    Serial.println('E'); //mi
    name[0] = 0x45;
    name[1] = 0x20;
    Note_Detected();
  }
  else if ( ((frequence>347)&&(frequence<357)) || ((frequence>694)&&(frequence<714)) ){
    Serial.println('F'); //fa
    name[0] = 0x46;
    name[1] = 0x20;
    is_note = true;
  }
  else if ( ((frequence>390)&&(frequence<400)) || ((frequence>780)&&(frequence<800)) ){
    Serial.println('G'); //sol
    name[0] = 0x47;
    name[1] = 0x20;
    Note_Detected();
  }
  else if ( ((frequence>435)&&(frequence<445)) || ((frequence>870)&&(frequence<890)) ){
    Serial.println('A'); //la
    name[0] = 0x41;
    name[1] = 0x20;
    Note_Detected();
  }

  else if ( ((frequence>490)&&(frequence<500)) || ((frequence>980)&&(frequence<1000)) ){
    Serial.println('B'); //si
    name[0] = 0x42;
    name[1] = 0x20;
    Note_Detected();
  }

  else {is_note = false;}
}


void Note::Recognize_Duration(void) {
  
  for (float i=0; i<(this->time_duration/2) ; i= i + micro.Get_Delay()) { // we count at the frequency that the micro needs to calculate the FFT
    
    //note_already_detected = false;
    
    if (is_note){ //&& !note_already_detected) {         // check if there is a note at the instant i between 0 and the half of the time and if didn't already detect a note
      switch (this->note_duration) {
        case 'n' : this->note_duration = '4'; // if during the previous half time, there wasn't a note --> this note is a quarter note
        case '4' : this->note_duration = '8'; // if during the previous half time, there was a quarter note --> this note is a eight note
      }
     // note_already_detected = true;
    }
    
    else if (!is_note) { // && !note_already_detected) { 
      this->note_duration = 'n'; 
    }
    delay(micro.Get_Delay());
    
  }

}

uint16_t Note::Get_Name(int i) {
  return name[i];
}

bool Note::Is_Note() {
  return this->is_note;
}

char Note::Get_Duration() {
  return this->note_duration;
}
