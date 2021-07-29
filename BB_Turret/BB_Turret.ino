#include <Servo.h>
#define MOTOR_ENABLE 10
#define MOTOR_CONTROL_1 11
#define MOTOR_CONTROL_2 12
#define BUTTON 2
#define JOY_X A7
#define JOY_Y A6
#define SERVO_X 5
#define SERVO_Y 6
#define DEFAULT_ANGLE 90
#define INPUT_RANGE 1023
#define X_MAX 180
#define X_MIN 0
#define Y_MAX 140
#define Y_MIN 60

static const int input_mapping[] = {-3, -2, -1, 0, 1, 2, 3};
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
  Serial.print(inputMapSize);
  Serial.print("\n");
  inputMapModifier = (double) inputMapSize / (double) (INPUT_RANGE-1);
  Serial.print("\t");
  Serial.print(inputMapModifier, 4);
  Serial.print("\n");
}

void loop() {
  if (digitalRead(BUTTON) == HIGH) {
   analogWrite(MOTOR_ENABLE, 255);
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
  xVal = min(xVal, inputMapSize-1);
  yVal *= inputMapModifier;
  yVal = min(yVal, inputMapSize-1);
  xVal = input_mapping[xVal];
  yVal = input_mapping[yVal];
  x_angle += xVal;
  y_angle += yVal;
  if (x_angle > X_MAX) x_angle = X_MAX;
  if (x_angle < X_MIN) x_angle = X_MIN;
  if (y_angle > Y_MAX) y_angle = Y_MAX;
  if (y_angle < Y_MIN) y_angle = Y_MIN;
  servoX.write(x_angle);
  servoY.write(y_angle);
  delay(10);
}
