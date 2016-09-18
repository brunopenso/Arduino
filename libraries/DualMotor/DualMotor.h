/** 
  *
  * Biblioteca DualMotor
  * @autor Marco Mello - Engenharia LdG
  * @acesse www.labdegaragem.com
  *
  **/


#ifndef DualMotor_H
#define DualMotor_H

#include "Arduino.h"

class DualMotor 
{
public:

    DualMotor();

    void M1move(int velocidade, int sentido);
    void M1parar();
    void M2move(int velocidade, int sentido);
    void M2parar();
    
private:

    int pwmPinM1;
    int sentidoPinM1;
	int pwmPinM2;
	int sentidoPinM2;
};

#endif