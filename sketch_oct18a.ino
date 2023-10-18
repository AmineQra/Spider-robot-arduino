#include <Servo.h>

Servo servo[4][3];
const int servo_pin[4][3] = { {4, 2, 3}, {7, 5, 6}, {16, 14, 15}, {19, 17, 18} };

const float calibration_angles[4][3] = {
  {124.99, 21.92, 86.46},  // Jambe R2 - {H, F, T}
  {55.01, 158.08, 93.54},   // Jambe R1 - {H, F, T}
  {55.01, 158.08, 103.54},  // Jambe L1 - {H, F, T}
  {124.99, 21.92, 86.46} // Jambe L2 - {H, F, T}
};

const float a = 53.0;       // mm
const float b = 79.5;       // mm
const float c = 30.5;       // mm

void applyCalibrationAngles() {
  for (int leg = 0; leg < 4; leg++) {
    for (int segment = 0; segment < 3; segment++) {
      servo[leg][segment].write(calibration_angles[leg][segment]);
    }
  }
}

// Convert radians to degrees
float radToDeg(float rad) {
    return rad * 180.0 / PI;
}

// Calculate gamma angle based on x and y
float calculateGamma(float x, float y) {
    return radToDeg(atan2(y, x));
}

// Calculate alpha angle based on x, y, and z
float calculateAlpha(float x, float y, float z) {
    float d = sqrt(x * x + y * y) - c;
    float l = sqrt(d * d + z * z);
    return radToDeg(atan2(z, d) + acos((a * a + l * l - b * b) / (2 * a * l)));
}

// Calculate beta angle based on x, y, and z
float calculateBeta(float x, float y, float z) {
    float d = sqrt(x * x + y * y) - c;
    float l = sqrt(d * d + z * z);
    return radToDeg(acos((a * a + b * b - l * l) / (2 * a * b)));
}

void setup() {
  // Attach the servos to the pins
  for (int leg = 0; leg < 4; leg++) {
    for (int segment = 0; segment < 3; segment++) {
      servo[leg][segment].attach(servo_pin[leg][segment]);
    }
  }
  applyCalibrationAngles();

}


void loop() {
  delay(1500);

  


  delay(1500);  // Pause to see the robot's leg move
}
