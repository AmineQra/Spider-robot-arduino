#include <Servo.h>

Servo servo[4][3];
const int servo_pin[4][3] = { {4, 2, 3}, {7, 5, 6}, {16, 14, 15}, {19, 17, 18} };

const float calibration_angles[4][3] = {
  {124.99, 21.92, 90},  // Jambe R2 - {H, F, T}
  {55.01, 158.08, 93.54},   // Jambe R1 - {H, F, T}
  {55.01, 158.08, 93.54},  // Jambe L1 - {H, F, T}
  {124.99, 21.92, 86.46} // Jambe L2 - {H, F, T}
};

const float pls_angles[4][3] = {
  {85, 90, 160},
  {90, 90, 20},
  {90, 85, 20},
  {100, 85, 170}
};

const float sit_angles[4][3] = {
    {125, 55, 90},  // Leg R2 - {H, F, T}
    {55, 130, 90},   // Leg R1 - {H, F, T}
    {55, 115, 90},  // Leg L1 - {H, F, T}
    {125, 55, 90} // Leg L2 - {H, F, T}
  };

const float stand_angles[4][3] = {
    {125, 70, 90},  // Leg R2 - {H, F, T}
    {55, 85, 90},   // Leg R1 - {H, F, T}
    {55, 70, 90},  // Leg L1 - {H, F, T}
    {125, 70, 90} // Leg L2 - {H, F, T}
  };

//correction R2 (-5, 0, 0)
// R1 (0, 0, 0)
// L1 (0, -5, 0)
// R2 (+10, -5, +10)

// Define the increment value for each step
const int increment = 1;
// Define the delay between each step
const int delayTime = 15;

void gradualWrite(int leg, int segment, float targetAngle) {
  int currentAngle = servo[leg][segment].read();
  if (currentAngle < targetAngle) {
    for (int angle = currentAngle; angle <= targetAngle; angle += increment) {
      servo[leg][segment].write(angle);
      delay(delayTime);
    }
  } else {
    for (int angle = currentAngle; angle >= targetAngle; angle -= increment) {
      servo[leg][segment].write(angle);
      delay(delayTime);
    }
  }
}

void sit() {
  for (int leg = 0; leg < 4; leg++) {
    for (int segment = 0; segment < 3; segment++) {
      gradualWrite(leg, segment, sit_angles[leg][segment]);
    }
  }
}

void stand() {
  for (int leg = 0; leg < 4; leg++) {
    for (int segment = 0; segment < 3; segment++) {
      gradualWrite(leg, segment, stand_angles[leg][segment]);
    }
  }
}


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

void plsPosition(){
  for (int leg = 0; leg < 4; leg++) {
    for (int segment = 0; segment < 3; segment++) {
      servo[leg][segment].write(pls_angles[leg][segment]);
    }
  }
}

void setup() {
  delay(1500);
  // Attach the servos to the pins
  for (int leg = 0; leg < 4; leg++) {
    for (int segment = 0; segment < 3; segment++) {
      servo[leg][segment].attach(servo_pin[leg][segment]);
    }
  }

}


void loop() {

  stand();

  delay(1500);

  sit();

  delay(1500);
}
