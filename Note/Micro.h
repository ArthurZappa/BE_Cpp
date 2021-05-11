#ifndef MICRO_H
#define MICRO_H

#include "arduinoFFT.h"

class Micro{

  private :

  const uint8_t PIN_MICRO = A0;
  static double fondamental_frequency;


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
};

#endif
