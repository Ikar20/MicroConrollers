
int pins[7] = {53, 52, 51, 50, 10, 11, 12};
const int buzzerPin = 33;
byte numbers[12] = { 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
                     0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111,
                     0b01110111, 0b01111100,
                   };
int digits[6] = {23, 24, 25, 26, 27, 28};
byte second = 0;
int daley = 0;
int bip = 0;
int a = 0;
int A = 1;
int b = 0;
int B = 0;
int t1 = 1;
int t2 = 1;
int sec1 = 0;
int sec2 = 0;
int sec3 = 0;
int minut1 = 0;
int minut2 = 0;
int minut3 = 0;
int hour1 = 0;
int hour2 = 0;
int hour3 = 0;
int sec4 = 0;
int sec5 = 0;
int sec6 = 0;
int minut4 = 0;
int minut5 = 0;
int minut6 = 0;
int hour4 = 0;
int hour5 = 0;
int hour6 = 0;
int c = 0;
int d = 0;
int e = 0;
int i;
int j;

ISR(TIMER0_COMPA_vect) {
  second++;
  if (daley > 0) {
    daley--;
  }
  if (second == 28) {
    second = 0;
    if (t1 == 0) {
      sec1 = sec1 - 1;
      if (sec1 == -1) {
        sec1 = 59;
        minut1 = minut1 - 1;
        a = 1;
      }
      if ((minut1 == -1) && (a == 1)) {
        hour1 = hour1 - 1;
        minut1 = 59;
        a = 0;
      }
      if (hour1 == -1) {
        t1 = 1;
        hour1 = 0;
        minut1 = 0;
        sec1 = 0;
        bip = 1;
        e = 0;
      }
    }
    if (t2 == 0) {
      sec4 = sec4 - 1;
      if (sec4 == -1) {
        sec4 = 59;
        minut4 = minut4 - 1;
        b = 1;
      }
      if ((minut4 == -1) && (b == 1)) {
        hour4 = hour4 - 1;
        minut4 = 59;
        a = 0;
      }
      if (hour4 == -1) {
        t2 = 1;
        sec4 = 0;
        minut4 = 0;
        hour4 = 0;
        bip = 1;
        d = 0;
      }
    }
  }
  if (daley == 0) {
    if (bip == 2) {
      digitalWrite(buzzerPin, LOW);
      bip = 0;
    }
    if (bip == 1) {
      digitalWrite(buzzerPin, HIGH);
      bip = 2;
      daley = 25;
    }
  }
}
void delay1() {
  if (j < 100) {
    j++;
  }
  else {
    j = 0;
  }
}

void setup() {
  cli();
  TCCR0A = 0;
  TCCR0B = 0;
  OCR0A = 247;
  TCCR0B |= (1 << WGM02);
  TCCR0B |= (1 << CS00);
  TCCR0B |= (1 << CS02);
  TIMSK0 |= (1 << OCIE0A);
  sei();

  pinMode (18, INPUT);
  digitalWrite(18, HIGH);
  pinMode (19, INPUT);
  digitalWrite(19, HIGH);
  pinMode (20, INPUT);
  digitalWrite(20, HIGH);
  pinMode (21, INPUT);
  digitalWrite(21, HIGH);
  pinMode (23, OUTPUT);
  digitalWrite(23, HIGH);
  pinMode (24, OUTPUT);
  digitalWrite(24, HIGH);
  pinMode (25, OUTPUT);
  digitalWrite(25, HIGH);
  pinMode (26, OUTPUT);
  digitalWrite(26, HIGH);
  pinMode (27, OUTPUT);
  digitalWrite(27, HIGH);
  pinMode (28, OUTPUT);
  digitalWrite(28, HIGH);
  pinMode (buzzerPin, OUTPUT);
}

void loop() {
  if (A == 1) {
    sec2 = sec1 / 10;
    sec3 = sec1 % 10;
    minut2 = minut1 / 10;
    minut3 = minut1 % 10;
    hour2 = hour1 / 10;
    hour3 = hour1 % 10;
    //i = hour2;
    PORTB = numbers[10];
    digitalWrite(digits[0], LOW);
    delay1();
    digitalWrite(digits[0], HIGH);
    i = hour3;
    PORTB = numbers[i];
    digitalWrite(13, HIGH);
    digitalWrite(digits[1], LOW);
    delay1();
    digitalWrite(digits[1], HIGH);
    i = minut2;
    PORTB = numbers[i];
    digitalWrite(digits[2], LOW);
    delay1();
    digitalWrite(digits[2], HIGH);
    i = minut3;
    PORTB = numbers[i];
    digitalWrite(13, HIGH);
    digitalWrite(digits[3], LOW);
    delay1();
    digitalWrite(digits[3], HIGH);
    i = sec2;
    PORTB = numbers[i];
    digitalWrite(digits[4], LOW);
    delay1();
    digitalWrite(digits[4], HIGH);
    i = sec3;
    PORTB = numbers[i];
    digitalWrite(digits[5], LOW);
    delay1();
    digitalWrite(digits[5], HIGH);
  }
  if (A == 2) {
    sec5 = sec4 / 10;
    sec6 = sec4 % 10;
    minut5 = minut4 / 10;
    minut6 = minut4 % 10;
    hour5 = hour4 / 10;
    hour6 = hour4 % 10;
    //i = hour5;
    PORTB = numbers[11];
    delay1();
    digitalWrite(digits[0], LOW);
    delay1();
    digitalWrite(digits[0], HIGH);
    i = hour6;
    PORTB = numbers[i];
    digitalWrite(13, HIGH);
    digitalWrite(digits[1], LOW);
    delay1();
    digitalWrite(digits[1], HIGH);
    i = minut5;
    PORTB = numbers[i];
    digitalWrite(digits[2], LOW);
    delay1();
    digitalWrite(digits[2], HIGH);
    i = minut6;
    PORTB = numbers[i];
    digitalWrite(13, HIGH);
    digitalWrite(digits[3], LOW);
    delay1();
    digitalWrite(digits[3], HIGH);
    i = sec5;
    PORTB = numbers[i];
    digitalWrite(digits[4], LOW);
    delay1();
    digitalWrite(digits[4], HIGH);
    i = sec6;
    PORTB = numbers[i];
    digitalWrite(digits[5], LOW);
    delay1();
    digitalWrite(digits[5], HIGH);
  }
  if (daley == 0) {
    if (digitalRead(18) == LOW) {
      if ((A == 1) && (t1 == 1)) {
        hour1++;
      }
      if ((A == 2) && (t2 == 1)) {
        hour4++;
      }
      daley = 10;
    }
    if (digitalRead(19) == LOW) {
      if ((A == 1) && (t1 == 1)) {
        minut1++;
      }
      if ((A == 2) && (t2 == 1)) {
        minut4++;
      }
      daley = 10;
    }
    if (digitalRead(20) == LOW) {
      A++;
      if (A == 3) {
        A = 1;
      }
      daley = 10;
    }
    if (digitalRead(21) == LOW) {
      if (A == 1) {
        if (t1 == 1) {
          t1 = 0;
        } else {
          t1 = 1;
          sec1 = 0;
          minut1 = 0;
          hour1 = 0;
        }
      }
      if (A == 2) {
        if (t2 == 1) {
          t2 = 0;
        } else {
          t2 = 1;
          sec4 = 0;
          minut4 = 0;
          hour4 = 0;
        }
      }
      daley = 10;
    }
  }
}
