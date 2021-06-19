#include <Servo.h>
#define JOY_X A7
#define JOY_Y A6
#define SERVO_X 5
#define SERVO_Y 6
#define DEFAULT_ANGLE 90
#define INPUT_RANGE 1023

static const int input_mapping[] = {-3, -2, -1, 0, 1, 2, 3};
static int inputMapSize;
static double inputMapModifier;
int x_angle = DEFAULT_ANGLE;
int y_angle = DEFAULT_ANGLE;
Servo servoX;
Servo servoY;

void setup() {
  Serial.begin(9600);
  servoX.attach(SERVO_X);
  servoY.attach(SERVO_Y);
  servoX.write(DEFAULT_ANGLE);
  servoY.write(DEFAULT_ANGLE);
  inputMapSize = sizeof(input_mapping) / sizeof(*input_mapping);
  Serial.print(inputMapSize);
  Serial.print("\n");
  inputMapModifier = (double) inputMapSize / (double) (INPUT_RANGE-1);
  Serial.print("\t");
  Serial.print(inputMapModifier, 4);
  Serial.print("\n");
}

void loop() {
  int xVal = analogRead(JOY_X);
  int yVal = analogRead(JOY_Y);
  xVal *= inputMapModifier;
  xVal = min(xVal, inputMapSize-1);
  yVal *= inputMapModifier;
  yVal = min(yVal, inputMapSize-1);
  xVal = input_mapping[xVal];
  yVal = input_mapping[yVal];
  x_angle += xVal;
  y_angle += yVal;
  if (x_angle > 180) x_angle = 180;
  if (x_angle < 0) x_angle = 0;
  if (y_angle > 180) y_angle = 180;
  if (y_angle < 0) y_angle = 0;
  servoX.write(x_angle);
  servoY.write(y_angle);
}
