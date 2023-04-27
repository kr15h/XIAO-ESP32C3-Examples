// define led according to pin diagram
int led = D10;
int btn = D6;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello");
  // initialize digital pin led as an output
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
}

void loop() {
  int reading = digitalRead(btn);
  delay(10);
  if (reading == HIGH) {
    digitalWrite(led, HIGH);
    Serial.println("LED ON");
  } else {
    digitalWrite(led, LOW);
    Serial.println("LED OFF");
  }
}