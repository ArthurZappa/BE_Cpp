#include "Micro.h"


#define SAMPLES 256             //Must be a power of 2
#define SAMPLING_FREQUENCY 9000 //Hz, must be less than 10000 due to ADC 10 bits
  
#define THRESHOLD 200           //amplitude threshold

#define PIN_MICRO A0

Micro::Micro() {
  vReal = new double[SAMPLES];
  vImag = new double[SAMPLES];
  FFT_delay = SAMPLES *1000/SAMPLING_FREQUENCY;
}


double Micro::fondamental_frequency = 0;

void Micro::Init_Micro()
{
  pinMode(PIN_MICRO, INPUT);
}

void Micro::Sampling(){

  unsigned long microseconds;
  
  const int sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
      
   for(int i=0; i<SAMPLES; i++){
        microseconds = micros(); // renvoie le temps passé depuis l'execution du programme   //Overflows after around 70 minutes!
     
        vReal[i] = analogRead(PIN_MICRO);
        vImag[i] = 0;
     
       while(micros() < (microseconds + sampling_period_us)){}//on attend la fin d'un echantillonnage 
    }


}

double Micro::FFT(){
      arduinoFFT FFT = arduinoFFT();

   /*FFT*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY); // calcul la fréquence dominante = fondamentale
 
    /*PRINT RESULTS*/
    //Serial.print("La fréquence est de : ");     //Print out what frequency is the most dominant.
    //Serial.println(peak);     //Print out what frequency is the most dominant.
    
    
    //delay(1000);

    return peak;

}

 void Micro::Manage_Micro(void) {
  //if (analogRead(PIN_MICRO) > THRESHOLD) {
    Sampling();
    this->fondamental_frequency = FFT();
    //Serial.println(fondamental_frequency);
  //} 
  //else {fondamental_frequency = 0;}
 }

 double Micro::Get_Fondamental(void) {
  return this->fondamental_frequency;
 }

 float Micro::Get_Delay(void) {
  return this->FFT_delay;
 }

 
   
  
