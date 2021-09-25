#include <IRremote.h>

/*                                          
 Poter IR controled by Vinicius Schreiner
 
 Features:
  IR controlled
  360º Laser Scanner RPLIDAR
  
 Bibliografia:
 http://www.criandorobocomarduino.com/2013/10/como-receber-sinal-de-um-controle.html
 http://www.robot-electronics.co.uk/htm/arduino_examples.htm#MD49%2024v%20Motor%20Driver
 http://www.robot-electronics.co.uk/files/arduino_md49.ino
 
*/

// Values of 0 being sent over serial write have to be cast as a byte so they arent misinterpreted as NULL
// This is a bug with arduino 1.0
#define CMD        (byte)0x00            // MD49 command address of 0 
#define GET_SPEED1       0x21                                         
#define SET_SPEED1       0x31
#define SET_SPEED2       0x32

byte speed1a = 0;
byte speed1b = 0;
int a, b, c, d;
unsigned int integerValue = 0; // Max value is 65535
char incomingByte;
int sensors[8] = {0};
static char outstr[15];
char inChar;
int SPD1 = 134; //Forward
int SPD2 = 122; //Reverse

 
  const int RECEBE_PINO = 2; // pino 6 no arduino    
  
  IRrecv ir_recebe(RECEBE_PINO); // declarando a variável do sensor    
  decode_results codigo_recebido; // resultado  

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);   
  ir_recebe.enableIRIn(); // inicia a recepção  
}
void loop()
{


if (ir_recebe.decode(&codigo_recebido)) {//verifica se um codigo foi recebido    
   if (codigo_recebido.value != 0 ){   
   Serial.println(codigo_recebido.value, HEX); //mostra no serial o resultado    
   }   
if ((codigo_recebido.value == 0xAD680D1B)||(codigo_recebido.value == 0x2FDD827)){// cima  
            Serial1.write(CMD);
            Serial1.write(SET_SPEED1);
            Serial1.write(SPD1);                        // Set motor 1 speed
          
            Serial1.write(CMD);
            Serial1.write(SET_SPEED2);
            Serial1.write(SPD1);                        // Set motor 2 speed   
   delay(100);    
   } 

if ((codigo_recebido.value == 0xDD8E75F )||(codigo_recebido.value == 0x2FDF807)){// baixo  
            Serial1.write(CMD);
            Serial1.write(SET_SPEED1);
            Serial1.write(SPD2);                        // Set motor 1 speed
          
            Serial1.write(CMD);
            Serial1.write(SET_SPEED2);
            Serial1.write(SPD2);                        // Set motor 2 speed
   delay(100);    
   }  
if((codigo_recebido.value == 0x2B8BE5F)||(codigo_recebido.value == 0x2FD58A7)) {// esq 
            Serial1.write(CMD);
            Serial1.write(SET_SPEED1);
            Serial1.write(SPD1-10);                        // Set motor 1 speed
          
            Serial1.write(CMD);
            Serial1.write(SET_SPEED2);
            Serial1.write(SPD2+15);                        // Set motor 2 speed
   delay(100);    
   }  
if((codigo_recebido.value == 0x1CF3ACDB)||(codigo_recebido.value == 0x2FD7887)) {// dir 
            Serial1.write(CMD);
            Serial1.write(SET_SPEED1);
            Serial1.write(SPD2+15);                        // Set motor 1 speed
          
            Serial1.write(CMD);
            Serial1.write(SET_SPEED2);
            Serial1.write(SPD1-10);                        // Set motor 2 speed
   delay(100);    
   }  
if((codigo_recebido.value == 0x6F46633F)||(codigo_recebido.value == 0x2FD38C7)){ //Increase speed var
  SPD1 = SPD1+10;
  SPD2 = SPD2-10;
}
if((codigo_recebido.value == 0xB514653F)||(codigo_recebido.value == 0x2FDC837)){ //Decrease speed var

  SPD1 = SPD1-10;
  SPD2 = SPD2+10;
}

  
   
   
  

   ir_recebe.resume(); // recebe o próximo código   
   delay(200);    
  } 
}


