#define MOTOR_PIN 3
#define BUTTON 2

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(BUTTON, INPUT);

}

void loop() {
  if (digitalRead(BUTTON) == HIGH)
    analogWrite(MOTOR_PIN, 255);
  else
    analogWrite(MOTOR_PIN, 0);
}
