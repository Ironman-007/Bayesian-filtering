#pragma once

#include <Arduino.h>

class kalman
{
private:
    /* data */
    float _theta_M;
    float _theta_P;

    float _theta_0;
    float _x_0;

    float _K_1;

    float _K_n;
    float _Theta_n;
    float _x_n;

public:
    kalman(float theta_M, float theta_P, float theta_0, float x_0);
    float kalman_update(float measurement);
};

