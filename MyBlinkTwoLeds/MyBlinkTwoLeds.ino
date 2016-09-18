/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int ledR = 13;
int ledY = 12;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(ledR, OUTPUT);     
  pinMode(ledY, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(ledR, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(ledY, LOW);
  delay(1000);               // wait for a second
  digitalWrite(ledR, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(ledY, HIGH);
  delay(500);               // wait for a second
}
