int leds[8] = {49, 48, 47, 46, 45, 44, 43, 42};
void setup() {
  pinMode (25, INPUT);
  digitalWrite(25, HIGH);
  pinMode (27, INPUT);
  digitalWrite(27, HIGH);
  pinMode (leds[0], OUTPUT);
  pinMode (leds[1], OUTPUT);
  pinMode (leds[2], OUTPUT);
  pinMode (leds[3], OUTPUT);
  pinMode (leds[4], OUTPUT);
  pinMode (leds[5], OUTPUT);
  pinMode (leds[6], OUTPUT);
  pinMode (leds[7], OUTPUT);
}
void loop() {
  if (digitalRead (25) == LOW) {
    digitalWrite (leds[1], HIGH);
  }
}
void algo1() {
  int j = 0;
  if (j < 1) {
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
    j++;
  }
}
