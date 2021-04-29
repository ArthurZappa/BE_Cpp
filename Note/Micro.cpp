#include "Micro.h"


#define SAMPLES 128             //Must be a power of 2
#define SAMPLING_FREQUENCY 9000 //Hz, must be less than 10000 due to ADC 10 bits
  
double vReal[SAMPLES];
double vImag[SAMPLES];


void Micro::pins_init()
{
  pinMode(this->PIN_MICRO, INPUT);
}

void Micro::sampling(){

  unsigned long microseconds;
  
  
  const int sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
      
   for(int i=0; i<SAMPLES; i++)
    {
      
      
        microseconds = micros(); // renvoie le temps passé depuis l'execution du programme   //Overflows after around 70 minutes!
     
        vReal[i] = analogRead(this->PIN_MICRO);
        vImag[i] = 0;
     
       while(micros() < (microseconds + sampling_period_us)){//on attend la fin d'un echantillonnage
        }
    }


}

void Micro::FFT(){
      arduinoFFT FFT = arduinoFFT();

   /*FFT*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY); // calcul la fréquence dominante = fondamentale
 
    /*PRINT RESULTS*/
    Serial.print("La fréquence est de : ");     //Print out what frequency is the most dominant.
    Serial.println(peak);     //Print out what frequency is the most dominant.
    if ((peak<445)&&(peak>438)){
      Serial.println("C'est un LA 440");      
    }
    else if ((peak<405)&&(peak>400)){ Serial.println("C'est un SOL");    }
    else if ((peak<300)&&(peak>287)){ Serial.println("C'est un RE");    }
    else if ((peak<198)&&(peak>250)){ Serial.println("C'est un LA");    }
    
    delay(1000);

};

 
   
  
