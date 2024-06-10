#define pinLed  10
#define sensor  11

void setup() {

  pinMode(sensor, INPUT);
  pinMode(pinLed, OUTPUT);

  Serial.begin(9600);

}

void loop () {

  int estadoPorta = digitalRead(sensor);

  if (estadoPorta == 1 ) {
    Serial.println("Porta Aberta");
    digitalWrite(pinLed, HIGH);
    delay(5000);
      
  }

  else {

    Serial.println("Porta fechada");
    digitalWrite(pinLed, LOW);
    delay(5000);
  
  }
}