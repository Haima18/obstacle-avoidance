#define ENA 25
#define IN1 26
#define IN2 27

#define ENB 13
#define IN3 14
#define IN4 12

#define TRIG_PIN 33
#define ECHO_PIN 32

#define MOTOR_SPEED 170
#define TURN_SPEED 180
#define OBSTACLE_DISTANCE 35

const int motorAChannel = 0;
const int motorBChannel = 1;

void setupPWM() {
  ledcSetup(motorAChannel, 1000, 8);
  ledcAttachPin(ENA, motorAChannel);

  ledcSetup(motorBChannel, 1000, 8);
  ledcAttachPin(ENB, motorBChannel);
}

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  ledcWrite(motorAChannel, 0);
  ledcWrite(motorBChannel, 0);
}

void forwardRobot() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  ledcWrite(motorAChannel, MOTOR_SPEED);
  ledcWrite(motorBChannel, MOTOR_SPEED);
}

void backwardRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  ledcWrite(motorAChannel, MOTOR_SPEED);
  ledcWrite(motorBChannel, MOTOR_SPEED);
}

void leftRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  ledcWrite(motorAChannel, TURN_SPEED);
  ledcWrite(motorBChannel, TURN_SPEED);
}

void rightRobot() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  ledcWrite(motorAChannel, TURN_SPEED);
  ledcWrite(motorBChannel, TURN_SPEED);
}

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return 999.0;
  }

  return duration * 0.0343 / 2.0;
}

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  setupPWM();
  stopRobot();

  Serial.println("ULTRASONIC OBSTACLE ROBOT READY");
}

void loop() {
  float distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > OBSTACLE_DISTANCE) {
    forwardRobot();
  } else {
    stopRobot();
    delay(300);

    rightRobot();
    delay(500);

    stopRobot();
    delay(200);
  }

  delay(50);
}
