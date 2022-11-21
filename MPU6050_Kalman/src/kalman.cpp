// This is a Bayesian filtering, or as it turns out, a simplified Kalman filter
// (univariate, no control actions, no transition matrices).

#include <Arduino.h>
#include "kalman.h"

kalman::kalman(float theta_M, float theta_P, float theta_0, float x_0)
{
    this -> _theta_M = theta_M;
    this -> _theta_P = theta_P;
    this -> _theta_0 = theta_0;
    this -> _x_0     = x_0;

    // this -> _K_n;
    this -> _Theta_n = theta_0;
    // this -> _x_c = 0.0;
    this -> _x_n     = 0.0;
}

// update process of Bayesian filtering
// Refer to: https://www.magesblog.com/post/2014-12-02-measuring-temperature-with-my-arduino/
float kalman::kalman_update(float measurement)
{
    _K_n     = (sq(_Theta_n) + sq(_theta_P))/(sq(_theta_M) + sq(_Theta_n) + sq(_theta_P));
    _Theta_n = (1-_K_n) * (sq(_Theta_n) + sq(_theta_P));
    _x_n     = _K_n*measurement + (1 - _K_n)*_x_n;

    return _x_n;
}