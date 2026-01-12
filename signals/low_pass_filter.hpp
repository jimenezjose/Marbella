/*******************************************************************************
                                                    Jose Jorge Jimenez-Olivas

File Name:       low_pass_filter.hpp
Description:     Data smoothing algorithm using a low-pass filter.
*******************************************************************************/
#ifndef LOW_PASS_FILTER_HPP
#define LOW_PASS_FILTER_HPP /* multiple inclusion guard */

/**
 * LowPassFilter:
 * y(k) = w * y(k-1) +  (1-w) * x(k)
 */
class LowPassFilter {
private:
  long y;
  double w;
public:
  LowPassFilter(double weight, long y_init=0) : y(y_init) {
    if( weight < 0 || weight > 1 ) {
      Serial.println("LowPassFilter weight out of bounds [0,1]. Setting to 0.5");
      weight = 0.5;
    }
    w = (weight < 0 || weight > 1) ? 0.5 : weight;
  }

  long read(long x) {
    y = w * y + (1-w) * x;
    return y;
  }
  
  long current() { 
    return y; 
  }
};

#endif /* LOW_PASS_FILTER_HPP */