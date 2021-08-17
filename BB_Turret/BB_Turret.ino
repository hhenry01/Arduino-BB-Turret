#include <Servo.h>
#define MOTOR_ENABLE 6
#define MOTOR_CONTROL_1 11
#define MOTOR_CONTROL_2 12
#define BUTTON 2
#define JOY_X A7
#define JOY_Y A6
#define SERVO_X 5
#define SERVO_Y 3
#define DEFAULT_ANGLE 90
#define INPUT_RANGE 1023
#define X_MAX 180
#define X_MIN 0
#define Y_MAX 140
#define Y_MIN 60

static const int input_mapping[] = {-3, -2, -1, 0, 1, 2, 3}; //Change for different speed options
static int inputMapSize;
static double inputMapModifier;
int x_angle = DEFAULT_ANGLE;
int y_angle = DEFAULT_ANGLE;
Servo servoX;
Servo servoY;

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_ENABLE, OUTPUT);
  pinMode(BUTTON, INPUT);
  servoX.attach(SERVO_X);
  servoY.attach(SERVO_Y);
  servoX.write(DEFAULT_ANGLE);
  servoY.write(DEFAULT_ANGLE);
  inputMapSize = sizeof(input_mapping) / sizeof(*input_mapping);
  inputMapModifier = (double) inputMapSize / (double) (INPUT_RANGE-1);
}

void loop() {
  if (digitalRead(BUTTON) == HIGH) {
   analogWrite(MOTOR_ENABLE, 128);
   digitalWrite(MOTOR_CONTROL_1, HIGH);
   digitalWrite(MOTOR_CONTROL_2, LOW);
  } else {
   analogWrite(MOTOR_ENABLE, 0);
   digitalWrite(MOTOR_CONTROL_1, LOW);
   digitalWrite(MOTOR_CONTROL_2, LOW);
  }
  int xVal = analogRead(JOY_X);
  int yVal = analogRead(JOY_Y);
  xVal *= inputMapModifier;
  xVal = min(xVal, inputMapSize-1); //min is necessary to fit xVal within the range of the inputMap array, else it will access an out of bounds index
  yVal *= inputMapModifier;
  yVal = min(yVal, inputMapSize-1);
  xVal = input_mapping[xVal];
  yVal = input_mapping[yVal];
  x_angle += xVal;
  y_angle += yVal;

  // The servos cannot go past their maximum ranges, but a limit needs to be set in the code to avoid it increasing indefinitely
  if (x_angle > X_MAX) x_angle = X_MAX;
  else if (x_angle < X_MIN) x_angle = X_MIN;
  
  if (y_angle > Y_MAX) y_angle = Y_MAX;
  else if (y_angle < Y_MIN) y_angle = Y_MIN;
  
  servoX.write(x_angle);
  servoY.write(y_angle);
  delay(10); // Delay to slow down overall speed. Modify to adjust overall speed.
}
