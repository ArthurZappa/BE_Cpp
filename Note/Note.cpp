#include "Note.h"
#include "Micro.h"

void Note::recognize(double frequence){


  if ((frequence>432) & (frequence<448)){
  Serial.println("LA 440");
  //mettre LA dans this->name
  }
  else if ((frequence<405)&&(frequence>400)){ Serial.println("SOL");    }
  else if ((frequence<300)&&(frequence>287)){ Serial.println("RE");    }
  else if ((frequence<198)&&(frequence>250)){ Serial.println("LA");    }
}


  
