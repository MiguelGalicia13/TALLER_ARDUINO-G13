// -- Pines --
/*
Pin lectura del sensor
pin salida a led azul -> frio
pin salida a led verde -> estable
pin salida a led roja -> caliente
*/
#include <DHT.h>
const int PIN_TEMP = 29;
const int LED_AZUL = 25;
const int LED_VERDE = 27;
const int LED_ROJO = 23;
const int PIN_MOTOR = 3;

// Umbrales
/*
temperatura < 15 -> Frio
temperatura >= 35 - > Caliente
*/
const float T_FRIO = 15.0;
const float T_CALOR = 35.0;

DHT dht(PIN_TEMP, DHT22);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(PIN_MOTOR, OUTPUT);
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_ROJO, LOW);
  analogWrite(PIN_MOTOR, 0);
}



void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  float temp = dht.readTemperature();
  if(isnan(temp)){
    Serial.println("ERROR EN DHT");

  }
  analogWrite(PIN_MOTOR, 240);
  if(temp < T_FRIO){
    digitalWrite(LED_AZUL, HIGH);
    digitalWrite(LED_ROJO, LOW);
    digitalWrite(LED_VERDE, 0);
    analogWrite(PIN_MOTOR, 0);
  }else if (temp >= T_CALOR){
    digitalWrite(LED_ROJO, 1);
    digitalWrite(LED_AZUL, 0);
    digitalWrite(LED_VERDE, 0);
    analogWrite(PIN_MOTOR, 240);
  }else{
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_ROJO, LOW);
    digitalWrite(LED_AZUL, LOW);
    analogWrite(PIN_MOTOR, 0);
  }
  Serial.print("TEMPERATURA: ");
  Serial.print(temp, 1);
  Serial.println(" C");
  delay(100);

}
