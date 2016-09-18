#include <IRremote.h>

//PIN 11 -  read signal
int irPin = 11;
//PIN 10 - send signal
int sendPin = 10;
//PIN 13 - reserved to receiver module
//PIN 12 - LED TRANSMITTER
int transmitterLed=12;
long irCode;

IRrecv irrecv(irPin);
decode_results results;

IRsend irsend;

void setup() {
  Serial.begin(9600);
  
  //starts the receiver
  irrecv.enableIRIn();
  irrecv.blink13(true);
  
  //init led
  pinMode(transmitterLed, OUTPUT);
}
//20DF10EF/551489775 - turn on/off lg tv
//20DFC03F/551534655 - volume down lg tv
//20DF40BF/551502015 - volume up lg tv
//E17A48B7/3782887607 - turn on/off net
//FFA25D/16753245 - turn on control
//FFE21D/16769565 - turn off control
//FF22DD/16720605 - volume up
//FF02FD/16712445 - volume down
//3782901887 - net 1
//3782885567 - net 2
//3782918207 - net 3
//3782877407 - net 4
//3782910047 - net 5
//3782893727 - net 6
//3782926367 - net 7
//3782873327 - net 8
//3782905967 - net 9
//3782869247 - net 0
void loop() {
   read();
   send();
   //delay(500);
}

void send() {
  switch(irCode) {
    case 16753245:
      //turn on
      sendValue(551489775,"on tv");
      sendValue(3782887607,"on net");
      delay(15000);
      sendValue(3782910047,"5");
      sendValue(3782901887,"1");
      sendValue(3782885567,"2");
      break;
    case 16769565:
      //turn off
      sendValue(551489775,"off tv");
      sendValue(3782887607,"off net");
      break;
    case 16720605:
      //volume up
      sendValue(551502015, "volume up tv");
      break;
    case 16712445:
      //volume down
      sendValue(551534655, "volume down tv");
      break;
  }
  //Serial.println("before clean ir code");
  irCode=0;
  //Serial.println("after clean ir code");
}
void sendValue(long value, String irCommand) {
  Serial.println("sending code " + irCommand + "."+value);
  
  digitalWrite(transmitterLed, HIGH);
  irsend.sendNEC(value, 32);
  delay(200);  
  digitalWrite(transmitterLed, LOW);

  Serial.println("code sent");
  irrecv.enableIRIn();
}

void read() {
   if (irrecv.decode(&results)) {
      if (results.value!=4294967295) {
        type();
        Serial.println(results.value, HEX);
        Serial.print(results.value, DEC); 
        irCode = results.value;
        Serial.println();
      } else {
         irCode=0; 
      }
     irrecv.resume();
  }  
}
void type() {
  Serial.println(results.bits);
 if (results.decode_type == NEC) {
      Serial.print("NEC: ");
    } else if (results.decode_type == SONY) {
      Serial.print("SONY: ");
    } else if (results.decode_type == RC5) {
      Serial.print("RC5: ");
    } else if (results.decode_type == RC6) {
      Serial.print("RC6: ");
    } else if (results.decode_type == UNKNOWN) {
      Serial.print("UNKNOWN: ");
    } 
}
