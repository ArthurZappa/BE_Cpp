#include "Sheet.h"

Sheet::Sheet() {
  note_duration = 'n';
  time_duration = 60*1000/app.Get_Tempo(); // time duration in milliseconds
}

void Sheet::Recognize_Duration(void) {
  for (float i=0; i<this->time_duration/2 ; i= i + note.micro.Get_Delay()) { // we count at the frequency that the micro needs to calculate the FFT
    
    if (note.Is_Note()) {         // check if there is a note at the instant i between 0 and the half of the time
      switch (this->note_duration) {
        case 'n' : this->note_duration = 'q'; // if during the previous half time, there wasn't a note --> this note is a quarter note
        case 'q' : this->note_duration = 'e'; // if during the previous half time, there was a quarter note --> this note is a eight note
      }
    }
    else { this->note_duration = 'n'; }
    delay(note.micro.Get_Delay());
    Serial.println(this->note_duration);
  }

  
}
