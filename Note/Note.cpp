#include "Note.h"
#include "Micro.h"



Note::Note() {
  this->name[0] = 0x20;
  this->name[1] = 0x20;
}


Note::Note(uint16_t note1, uint16_t note2) {
  this->name[0] = note1;
  this->name[1] = note2;
}


void Note::Recognize(void){

  double frequence = micro.Get_Fondamental();
  Serial.println(frequence);
  if ((frequence>260)&&(frequence<270)){
    Serial.println('C'); //do
    this->name[0] = 0x43;  
    this->name[1] = 0x20;
  }
  else if ((frequence>292)&&(frequence<302)){
    Serial.println('D'); //re
    this->name[0] = 0x44;
    this->name[1] = 0x20;
  }
  else if ((frequence>325)&&(frequence<335)){
    Serial.println('E'); //mi
    this->name[0] = 0x45;
    this->name[1] = 0x20;
  }
  else if ((frequence>347)&&(frequence<357)){
    Serial.println('F'); //fa
    this->name[0] = 0x46;
    this->name[1] = 0x20;
  }
  else if ((frequence>390)&&(frequence<400)){
    Serial.println('G'); //sol
    this->name[0] = 0x47;
    this->name[1] = 0x20;
  }
  else if ((frequence>435)&&(frequence<445)){
    Serial.println('A'); //la
    this->name[0] = 0x41;
    this->name[1] = 0x20;
  }

  else if ((frequence>490)&&(frequence<500)){
    Serial.println('B'); //si
    this->name[0] = 0x42;
    this->name[1] = 0x20;
  }
/*

  else if ((frequence<405)&&(frequence>400)){ Serial.println("SOL");    }
  else if ((frequence<300)&&(frequence>287)){ Serial.println("RE");    }
  else if ((frequence<198)&&(frequence>250)){ Serial.println("LA");    }
  */
}


uint16_t Note::Get_Name(int i) {
  return this->name[i];
}
  
