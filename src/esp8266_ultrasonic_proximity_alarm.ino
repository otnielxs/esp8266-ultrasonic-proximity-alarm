#define TRIG    D5
#define ECHO    D6
#define BUZZER  D7

void tonePassive(int freq, int durationMs) {
  long period = 1000000L / freq;      // us
  long cycles = (long)freq * durationMs / 1000;

  for (long i = 0; i < cycles; i++) {
    digitalWrite(BUZZER, HIGH);
    delayMicroseconds(period / 2);

    digitalWrite(BUZZER, LOW);
    delayMicroseconds(period / 2);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {

  // ultrasonic 
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH);
  float distance = duration * 0.0343 / 2.0;

  // potentiometer
  int potValue = analogRead(A0);

  // Mapping frekuensi 200 Hz - 3000 Hz
  int freq = map(potValue, 0, 1023, 200, 3000);

  Serial.print("distance: ");
  Serial.print(distance);
  Serial.print(" cm\tFreq: ");
  Serial.println(freq);

  if (distance < 20) {
    tonePassive(freq, 100);
  } else {
    digitalWrite(BUZZER, LOW);
    delay(100);
  }
}
