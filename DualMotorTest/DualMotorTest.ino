#include <DualMotor.h> //Inclui a biblioteca DualMotor.h
 
DualMotor dualmotor; //Instância a DualMotor

void setup()
{
  Serial.begin(9600); //Inicia a Serial com um Baud Rate de 9600bps
    dualmotor.M1parar(); //Para o motor1
    dualmotor.M2parar(); //Para o motor2
}
 
void loop()
{
 //   case '8'://FRENTE //Caso o caracter for igual a 8, vai pra FRENTE
      dualmotor.M1move(255,1);
      dualmotor.M2move(255,1);
      delay(2000);
//    case '4'://ESQUERDA //Caso o caracter for igual a 4, vira pra ESQUERDA
      dualmotor.M1move(255,0);
      dualmotor.M2move(255,1);
      delay(2000);
//    case '2'://TRÁS //Caso o caracter for igual a 2, vai pra TRAS
      dualmotor.M1move(255,0);
      dualmotor.M2move(255,0);
      delay(2000);
//    case '6'://DIREITA //Caso o caracter for igual a 6, vira pra senEITA
      dualmotor.M1move(255,1);
      dualmotor.M2move(255,0);

    delay(10000); //Delay de 10 seconds
    dualmotor.M1parar(); //Para o motor 1
    dualmotor.M2parar(); //Para o motor 2
}
