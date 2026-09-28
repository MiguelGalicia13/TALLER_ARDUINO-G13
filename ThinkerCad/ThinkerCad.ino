// -- Pines --
/*
Pin lectura del sensor
pin salida a led azul -> frio
pin salida a led verde -> estable
pin salida a led roja -> caliente
*/
const int PIN_TEMP = A0;
const int LED_AZUL = 5;
const int LED_VERDE = 6;
const int LED_ROJO = 7;
const int PIN_MOTOR = 3;

// Umbrales
/*
temperatura < 15 -> Frio
temperatura >= 35 - > Caliente
*/
const float T_FRIO = 15.0;
const float T_CALOR = 35.0;


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
}

float leerTemperatura() {
  long suma = 0;
  for (int i = 0; i < 10; i++) {
    suma += analogRead(PIN_TEMP);
    delay(2);
  }
  float lectura = suma / 10.0;
  float voltaje = lectura * 5.0 / 1024.0;
  return (voltaje - 0.5) * 100.0;   // TMP36: 500 mV a 0 °C, 10 mV por °C
}




void loop() {
  // put your main code here, to run repeatedly:
  float temp = leerTemperatura();
  if (temp < T_FRIO){
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
