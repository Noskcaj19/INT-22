#define RELAY 8

void setup() {
  pinMode(RELAY, OUTPUT);
  Serial.begin(9600);
}

void loop() {
    digitalWrite(RELAY, HIGH);
    delay(2000);
    digitalWrite(RELAY, LOW);
    delay(2000);
}
   
