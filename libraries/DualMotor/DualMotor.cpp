/** 
  *
  * Biblioteca DualMotor
  * @autor Marco Mello - Engenharia LdG
  * @acesse www.labdegaragem.com
  *
  **/

  
#include "DualMotor.h"
#include "Arduino.h"

DualMotor::DualMotor()
{
	pwmPinM1=5;
    sentidoPinM1=8;
	pwmPinM2=6;
	sentidoPinM2=7;
	 
	pinMode(pwmPinM1, OUTPUT);
	pinMode(pwmPinM2, OUTPUT);
	pinMode(sentidoPinM1, OUTPUT);
	pinMode(sentidoPinM2, OUTPUT);
}

void DualMotor::M1move(int velocidade, int sentido)
{
	analogWrite(pwmPinM1, velocidade);
    digitalWrite(sentidoPinM1, sentido);
}

void DualMotor::M1parar()
{
    analogWrite(pwmPinM1, 0);
}

void DualMotor::M2move(int velocidade, int sentido)
{
	analogWrite(pwmPinM2, velocidade);
    digitalWrite(sentidoPinM2, sentido);
}

void DualMotor::M2parar()
{
    analogWrite(pwmPinM2, 0);
}