#include <DualMotor.h> //Inclui a biblioteca DualMotor.h
DualMotor dualmotor; //Inst√¢ncia a DualMotor
// pins used for this shield 5,6,7,8
// pins used for ultrasensor 13,12,11
int trigPin = 13;//ultra sensor send sound wave
int echoPin = 11; //ultra sensor receive sound wave
int greenLed = 2;
int redLed = 3;
int maximumRange = 20; //20 cm
int minTime = 50;
int turn = 2500;// i`m supposing that 2 seconds is enough to turn 90 degress
int timeBack = 3000;
void setup() {
  Serial.begin (9600);
  stopMotor();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLed, OUTPUT);     
  pinMode(redLed, OUTPUT);
  
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, HIGH);
  delay(2000);
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, LOW);
}

void loop() {
  if (canGo()) {
    debug("Going forward");
    goForward();
  } else {
    debug("avoind obstacle");
    avoidObstacle();
  }
}

void goForward() {
  stopMotor();
  while (true) {
    if (!canGo()) {
      break;
    } else {
      dualmotor.M1move(255, 0);
      dualmotor.M2move(255, 0);
      delay(minTime); //enough time make a curve
    }
  }
}

void goBackward() {
  stopMotor();
  dualmotor.M1move(255, 1);
  dualmotor.M2move(255, 1);
  delay(timeBack);
}

void turnLeft() {
  stopMotor();
  dualmotor.M1move(255, 0);
  //dualmotor.M2move(255, 1);
  delay(turn); //enough time make a curve
  stopMotor();
}

void turnRight() {
  stopMotor();
  //dualmotor.M1move(255, 1);
  dualmotor.M2move(255, 0);
  delay(turn); //enough time make a curve
  stopMotor();
}

void stopMotor() {
  dualmotor.M1parar();
  dualmotor.M2parar();
}

void debug(String msg) {
  Serial.println(msg);
  delay(1000);
}

void debug(String msg, long number) {
  Serial.print(msg + "->");
  Serial.println(number);
  delay(1000);
}

void avoidObstacle() {
  stopMotor();
  int strategy = random(0, 3); // values -> 0 - 2
  debug("Strategy selected", strategy);
  switch (strategy) {
    case 0: strategy1(true); break;
    case 1: strategy1(false); break;
    case 2: strategy2(); break;
    default: break;
  }
}
void strategy1(boolean right) {
  debug("Strategy 1 started", (right == true));
  if (right) {
    debug("turn right");
    turnRight();
  } else {
    debug("turn left");
    turnLeft();
  }
  debug("Strategy 1 finished", (right == true));
}
void strategy2() {
  debug("Strategy 2 started");
  goBackward();
  turnLeft();
  debug("Strategy 2 finished");
}


boolean canGo() {
  if (readDistance() > maximumRange) {
    return true;
  } else {
    stopMotor();
    return false;
  }
}

long readDistance() {
  /* The following trigPin/echoPin cycle is used to determine the
   distance of the nearest object by bouncing soundwaves off of it. */
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  long distance = duration / 58.2;

  debug("Distance", distance);
  
  if (distance > maximumRange) {
      digitalWrite(greenLed, HIGH);
  } else {
    digitalWrite(redLed, HIGH);
  }
  //Delay 50ms before next reading.
  delay(50);
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, LOW);
  return distance;
}
