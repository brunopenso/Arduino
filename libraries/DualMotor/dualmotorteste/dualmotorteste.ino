#include <DualMotor.h> //Inclui a biblioteca DualMotor.h

DualMotor dualmotor; //Instância a DualMotor

char letra; //Cria uma variável char para armazenamento dos caraceteres lidos

void setup()
{
  Serial.begin(9600); //Inicia a Serial com um Baud Rate de 9600bps
    dualmotor.M1parar(); //Para o motor1
    dualmotor.M2parar(); //Para o motor2 
}

void loop()
{
  
  if (Serial.available() > 0) //Se algo for recebido na serial
  {
    letra = Serial.read(); //Armazena o que foi recebido na variável letra
    switch(letra) //Entra no switch para a comparação do caractere recebido
    {
      
    case '8'://FRENTE          //Caso o caracter for igual a 8, vai pra FRENTE
      dualmotor.M1move(255,1);
      dualmotor.M2move(255,1);
      break; //Sai do switch
      
    case '4'://ESQUERDA        //Caso o caracter for igual a 4, vira pra ESQUERDA
      dualmotor.M1move(255,0);
      dualmotor.M2move(255,1); 
      break; //Sai do switch
      
    case '2'://TRÁS            //Caso o caracter for igual a 2, vai pra TRAS
      dualmotor.M1move(255,0);
      dualmotor.M2move(255,0);
      break; //Sai do switch
      
    case '6'://senEITA        //Caso o caracter for igual a 6, vira pra senEITA
      dualmotor.M1move(255,1);
      dualmotor.M2move(255,0); 
      break; //Sai do switch
      
    }
    
    delay(250); //Delay de 250 milissegundos
    dualmotor.M1parar(); //Para o motor 1
    dualmotor.M2parar(); //Para o motor 2 
    

    letra = 0;//Limpa a variável letra
  }
}

