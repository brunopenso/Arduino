#include <DualMotor.h> //Inclui a biblioteca DualMotor.h
DualMotor dualmotor; //Inst√¢ncia a DualMotor
// VERSION 3
// pins used for this shield 5,6,7,8
// pins used for ultrasensor 13,12,11
int trigPin = 13;//ultra sensor send sound wave
int echoPin = 11; //ultra sensor receive sound wave
int greenLed = 2; // green led means that no obstacule was found
int redLed = 3; // red led means that obstacule was found

int maximumRange = 30; //if distance is less than this value the strategy to avoid will be started
int minTime = 10; //min time to go forward
int timeBack = 1500; //when going backwards this time will be considered
int turnTime = 150; //time to turn for left or right
int motorSpeed = 255; // define the motor speed angle

bool showLog = false; // when true show log
int logDelay = 500; // delay time to show logs

void setup() {
  stopMotor();
  
  Serial.begin (9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLed, OUTPUT);     
  pinMode(redLed, OUTPUT);
  
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, HIGH);
  delay(5000);
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
      dualmotor.M1move(motorSpeed, 0);
      dualmotor.M2move(motorSpeed, 0);
      delay(minTime);
    }
  }
}

void goBackward() {
  stopMotor();
  goBackward(timeBack);
}

void goBackward(int timeTo) {
  stopMotor();
  dualmotor.M1move(motorSpeed, 1);
  dualmotor.M2move(motorSpeed, 1);
  delay(timeTo);
}


void turn() {
  stopMotor();
  int maxTurns = 5;
  int strategy = random(0, 2); // values -> 0 - 1
  debug("turn strategy", strategy);
  while(!canGo() && maxTurns > 0) {
    if (strategy == 0) {
      debug("turning M1");
      dualmotor.M1move(motorSpeed, 0);
      //dualmotor.M2move(motorSpeed, 1);    
    } else {
      debug("turning M2");
      //dualmotor.M1move(motorSpeed, 1);
      dualmotor.M2move(motorSpeed, 0);    
    }
    maxTurns--;
    delay(turnTime);
  }
  stopMotor();
}

void stopMotor() {
  dualmotor.M1parar();
  dualmotor.M2parar();
}

void avoidObstacle() {
  stopMotor();
  int strategy = random(0, 2); // values -> 0 - 1
  debug("Strategy selected", strategy);
  switch (strategy) {
    case 0: strategy0(); break;
    case 1: strategy1(); break;
    default: break;
  }
}
void strategy0() {
  debug("Strategy 0 started");
  turn();
  debug("Strategy 0 finished");
}
void strategy1() {
  debug("Strategy 1 started");
  goBackward();
  turn();
  debug("Strategy 1 finished");
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
    stopMotor();
    digitalWrite(redLed, HIGH);
  }
  //Delay 50ms before next reading.
  delay(20);
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, LOW);
  return distance;
}

void debug(String msg) {
  if (showLog) {
    Serial.println(msg);
    delay(logDelay);
  }
}

void debug(String msg, long number) {
  if (showLog) {
    Serial.print(msg + "->");
    Serial.println(number);
    delay(logDelay);
  }
}
