#include "arduinoFFT.h"

class Micro{

  protected :

  const uint8_t PIN_MICRO = A0;
  

  public :

  /**
   * @brief init the pin for the mic on A0
   * @param none
   *        
   * @return none
   */
  void pins_init(void);
  /**
   * @brief make the sampling
   * @param none
   *        
   * @return none
   */
  void sampling(void);

  /**
   * @brief Make the FFT and print the MajorPeak
   * @param none
   * @return none
   */
  
  void FFT(void);
  
};
