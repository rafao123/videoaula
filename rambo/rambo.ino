#include "HX711.h"                    // Biblioteca HX711 
 
#define DOUT    7                    //  HX711 DATA OUT = pino A0 do Arduino 
#define CLK  6                       //  HX711 SCK IN = pino A1 do Arduino

float calibration_factor = 47060;

HX711 balanca;

void setup() {
  Serial.begin(9600);   // monitor serial 9600 Bps
  balanca.begin(DOUT, CLK);      // inicializa a balança
  Serial.println();   // salta uma linha
  Serial.println("CÉLULA DE CARGA KOSMOS");   // imprime no monitor serial
  Serial.println("HX711 - Calibracao da Balança");   // imprime no monitor serial

  balanca.set_scale();   // configura a escala da Balança
  zeraBalanca ();   // zera a Balança

}

void loop() {
  delay(200);
  balanca.set_scale(calibration_factor);   // ajusta fator de calibração
  Serial.print("FORÇA: ");   // imprime no monitor serial
  Serial.print(balanca.get_units()*9.81*2, 1);   // imprime peso da balança com 3 casas decimais
  Serial.print(" N");
  Serial.print("      Fator de Calibração: ");   // imprime no monitor serial
  Serial.println(calibration_factor);   // imprime fator de calibração
  delay(10) ;   // atraso de 0,1 segundo

  if (Serial.available())   // reconhece letra para ajuste do fator de calibração
  {
   char temp = Serial.read();
   if (temp == '+' || temp == 'a')   // a = aumenta 10
   calibration_factor += 10;
   else if (temp == '-' || temp == 'z')   // z = diminui 10 
   calibration_factor -= 10;
   else if (temp == 's')   // s = aumenta 100
   calibration_factor += 100;
   else if (temp == 'x')   // x = diminui 100
   calibration_factor -= 100;
   else if (temp == 'd')   // d = aumenta 1000
   calibration_factor += 1000;
   else if (temp == 'c')   // c = diminui 1000
   calibration_factor -= 1000;
   else if (temp == 'f')   // f = aumenta 10000
   calibration_factor += 10000;
   else if (temp == 'v')   // v = dimuni 10000
   calibration_factor -= 10000;
   else if (temp == 't') zeraBalanca ();   // t = zera a Balança
  }
}

void zeraBalanca ()
{
  Serial.println();   // salta uma linha
  balanca.tare();   // zera a Balança
  Serial.println("Balança Zerada ");
}
