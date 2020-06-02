int leds[8] = {49, 48, 47, 46, 45, 44, 43, 42};

void setup() {
  int i;
  Serial.begin(9600);
  pinMode (25, INPUT_PULLUP);
  pinMode (27, INPUT_PULLUP);
  for (i = 0; i < 8; i++) {
    digitalWrite(leds[i], LOW);
  }
  for (i = 0; i < 8; i++) {
    pinMode (leds[i], OUTPUT);
  }
}

void loop() {
  int i;
  // read from port 0:
  if (Serial.available()) {
    int inByte = Serial.read();
    if (inByte == 0xA1) {
      digitalWrite (leds[0], HIGH);
      delay (1000);
      digitalWrite (leds[0], LOW);
      delay (50);
      digitalWrite (leds[2], HIGH);
      delay (1000);
      digitalWrite (leds[2], LOW);
      delay (50);
      digitalWrite (leds[4], HIGH);
      delay (1000);
      digitalWrite (leds[4], LOW);
      delay (50);
      digitalWrite (leds[6], HIGH);
      delay (1000);
      digitalWrite (leds[6], LOW);
      delay (50);
      digitalWrite (leds[1], HIGH);
      delay (1000);
      digitalWrite (leds[1], LOW);
      delay (50);
      digitalWrite (leds[3], HIGH);
      delay (1000);
      digitalWrite (leds[3], LOW);
      delay (50);
      digitalWrite (leds[5], HIGH);
      delay (1000);
      digitalWrite (leds[5], LOW);
      delay (50);
      digitalWrite (leds[7], HIGH);
      delay (1000);
      digitalWrite (leds[7], LOW);
      delay (50);
    } else if (inByte == 0xB1) {
      digitalWrite (leds[0], HIGH);
      digitalWrite (leds[7], HIGH);
      delay(1000);
      digitalWrite (leds[0], LOW);
      digitalWrite (leds[7], LOW);
      delay(50);
      digitalWrite (leds[1], HIGH);
      digitalWrite (leds[6], HIGH);
      delay(1000);
      digitalWrite (leds[1], LOW);
      digitalWrite (leds[6], LOW);
      delay(50);
      digitalWrite (leds[2], HIGH);
      digitalWrite (leds[5], HIGH);
      delay(1000);
      digitalWrite (leds[2], LOW);
      digitalWrite (leds[5], LOW);
      delay(50);
      digitalWrite (leds[3], HIGH);
      digitalWrite (leds[4], HIGH);
      delay(1000);
      digitalWrite (leds[3], LOW);
      digitalWrite (leds[4], LOW);
      delay(50);
    }
  }

  // write to port 0:
  if (digitalRead(25) == LOW) {
    Serial.write(0xB1);
    delay(100);
  }
  if (digitalRead(27) == LOW) {
    Serial.write(0xB2);
    delay(10);
  }
}
