#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Arduino.h>

#include "kalman.h"

Adafruit_MPU6050 mpu;
kalman           kalman_filter_accx(0.015, 0.01, 0.01, 0.0); // theta_M, theta_P, theta_0, x_0

float acc_x          = 0.0;
float filtered_acc_x = 0.0;

void setup(void) {
  Serial.begin(115200);

  while (!Serial) delay(10); // will pause Zero, Leonardo, etc until serial console opens

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  //setupt motion detection
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(20);
  mpu.setInterruptPinLatch(true);	// Keep it latched.  Will turn off when reinitialized.
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);

  Serial.println("");
  delay(100);
}

void loop() {
//   if(mpu.getMotionInterruptStatus()) {
    /* Get new sensor events with the readings */
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    acc_x = a.acceleration.x;
    filtered_acc_x = kalman_filter_accx.kalman_update(acc_x);

    /* Print out the values */
    Serial.print("AccelX:");
    Serial.print(acc_x);
    Serial.print(",");
    Serial.print("filtered_AccelX:");
    Serial.println(filtered_acc_x);

    // Serial.print("AccelY:");
    // Serial.print(a.acceleration.y);
    // Serial.print(",");
    // Serial.print("AccelZ:");
    // Serial.print(a.acceleration.z);
    // Serial.print(", ");
    // Serial.print("GyroX:");
    // Serial.print(g.gyro.x);
    // Serial.print(",");
    // Serial.print("GyroY:");
    // Serial.print(g.gyro.y);
    // Serial.print(",");
    // Serial.print("GyroZ:");
    // Serial.print(g.gyro.z);
    // Serial.println("");
//   }

  delay(20);
}