#ifndef MICRO_H
#define MICRO_H

#include "arduinoFFT.h"

class Micro{

  private :

  static double fondamental_frequency;
  
  double * vReal;
  double * vImag;

  float FFT_delay; //time requires to sample and do the FFT in milliseconds

  /**
   * @brief make the sampling
   * @param none
   *        
   * @return none
   */
  void Sampling(void);

  /**
   * @brief Make the FFT and print the MajorPeak
   * @param none
   * @return double : value of the fondamental frequency of the signal
   */
  
  double FFT(void);

  public :

  Micro(void);
  /**
   * @brief init the pins for the mic on A0
   * @param none
   *        
   * @return none
   */
  void Init_Micro(void);
  

  /**
   * @brief Make the samplig and the FFT
   * @param none
   * @return none
   */

  void Manage_Micro(void);

  double Get_Fondamental(void);
  float Get_Delay(void);
};

#endif
