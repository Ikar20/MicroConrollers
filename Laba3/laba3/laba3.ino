#include <LiquidCrystal.h>
#define DDR_KEYPAD  DDRF
#define PORT_KEYPAD PORTF
#define PIN_KEYPAD  PINF
#include <Keypad.h>

char operation, button;

const int buzzerPin = 53;

const int rs = 22, rw = 23, en = 24, d0 = 37 , d1 = 36 , d2 = 35 , d3 = 34 , d4 = 33, d5 = 32, d6 = 31, d7 = 30;
LiquidCrystal lcd(rs, rw, en, d0, d1, d2, d3, d4, d5, d6, d7);

const byte ROWS = 4; // 4 строки
const byte COLS = 4; // 4 столбца
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {49, 48, 47, 46};
byte colPins[COLS] = {45, 44, 43, 42};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const PROGMEM  char sixty[60][3] = {
  {"00"}, {"01"}, {"02"}, {"03"}, {"04"}, {"05"}, {"06"}, {"07"}, {"08"}, {"09"},
  {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"},
  {"20"}, {"21"}, {"22"}, {"23"}, {"24"}, {"25"}, {"26"}, {"27"}, {"28"}, {"29"},
  {"30"}, {"31"}, {"32"}, {"33"}, {"34"}, {"35"}, {"36"}, {"37"}, {"38"}, {"39"},
  {"40"}, {"41"}, {"42"}, {"43"}, {"44"}, {"45"}, {"46"}, {"47"}, {"48"}, {"49"},
  {"50"}, {"51"}, {"52"}, {"53"}, {"54"}, {"55"}, {"56"}, {"57"}, {"58"}, {"59"}
};
int bip = 0;
int a = 0;
int A = 0;
int b = 0;
int B = 0;
int t1 = 1;
int t2 = 1;
int sec1 = 0;
int minut1 = 0;
int hour1 = 0;
int sec2 = 0;
int minut2 = 2;
int hour2 = 0;
int reg1 = 0;
int reg2 = 0;
int num1 = 0;
int c = 0;
int e = 0;
int d = 0;
int f = 0;

struct Time
{
  unsigned char sec1, minut1, hour1;
};
Time T1 = {sec1, minut1, hour1};

void LCD_WriteStrPROGMEM(char *str, int n)  //вивід масиву символів,
{ //записаних у флеші
  for (int i = 0; i < n; i++)
    lcd.print( (char)pgm_read_byte( &(str[i]) ) );
}

ISR(TIMER1_COMPA_vect)  // Таймер Т1 по співпадінню А, кожної 1 сек.
{
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
      lcd.setCursor(0, 1);
      lcd.write("Timer A is over");
    }
    if (A == 1) {
      lcd.setCursor(0, 0);
      lcd.write("A");
      lcd.setCursor(3, 0);
      LCD_WriteStrPROGMEM(sixty[hour1], 2);
      lcd.write(':');
      LCD_WriteStrPROGMEM(sixty[minut1], 2);
      lcd.write(':');
      LCD_WriteStrPROGMEM(sixty[sec1], 2);
    }
  }
  if (t2 == 0) {
    sec2 = sec2 - 1;
    if (sec2 == -1) {
      sec2 = 59;
      minut2 = minut2 - 1;
      b = 1;
    }
    if ((minut2 == -1) && (b == 1)) {
      hour2 = hour2 - 1;
      minut2 = 59;
      a = 0;
    }
    if (hour2 == -1) {
      t2 = 1;


      bip = 1;
      d = 0;
      lcd.setCursor(0, 1);
      lcd.write("Timer B is over");
    }
    if (B == 1) {
      lcd.setCursor(0, 0);
      lcd.write("B");
      lcd.setCursor(3, 0);
      LCD_WriteStrPROGMEM(sixty[hour2], 2);
      lcd.write(':');
      LCD_WriteStrPROGMEM(sixty[minut2], 2);
      lcd.write(':');
      LCD_WriteStrPROGMEM(sixty[sec2], 2);
    }
  }
}


void setup() {
  noInterrupts();           // disable all interrupts

  // Таймер#1: Скид при співпадінні OCR1A (1sec) + дільник=256
  TCCR1A = 0x90;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);
  TIMSK1 = (1 << OCIE1A); // дозвіл на переривання по співпадінню
  OCR1A = 15624;// compare value = 1 sec (16MHz AVR)

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  lcd.begin(16, 2);
  interrupts();  // Enable global interrupts
}
void loop() {
  if (button) {
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
  }
  if (bip == 1) {
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    bip = 0;
  }
  button = keypad.getKey();
  if (button == 'A')
  {
    lcd.clear();
    reg1 = 1;
    f = 1;
  }
  if (button == 'C')
  {
    if (e == 2) {
      t1 = 1;
      A = 0;
      e = 0;
      hour1 = 0;
      minut1 = 0;
      sec1 = 0;
      lcd.clear();
    }
    if (e == 1) {
      t1 = 0;
      A = 1;
      e = 2;
      f = 0;
    }
  }
  if (reg1 > 0) {
    if (button == '#') {
      c = c + 1;
      if (num1 <= 24 & c == 1) {
        lcd.clear();
        hour1 = num1;
        num1 = 0;
        reg1 = 2;
      }
      else if (num1 <= 59 && c == 2) {
        lcd.clear();
        minut1 = num1;
        num1 = 0;
        reg1 = 0;
        c = 0;
        e = e + 1;
      }
      else if (num1 > 59 & c == 2) {
        num1 = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Repeat minutes");
        reg1 = 2;
        c = c - 1;
      }
    }
    if (reg1 == 1) {
      lcd.setCursor(0, 0);
      lcd.print("Enter hour");
      lcd.write(':');
      lcd.print(num1);
    }
    if (button >= '0' && button <= '9') {
      num1 = num1 * 10 + (button - '0');
    }
    if (reg1 == 2) {
      lcd.setCursor(0, 0);
      lcd.print("Enter minutes");
      lcd.write(':');
      lcd.print(num1);
    }
  }
  if (button == 'B')
  {
    lcd.clear();
    reg2 = 1;
    f = 1;
  }
  if (button == 'D')
  {
    if (d == 2) {
      t2 = 1;
      B = 0;
      d = 0;
      hour2 = 0;
      minut2 = 0;
      sec2 = 0;
      lcd.clear();
    }
    if (d == 1) {
      t2 = 0;
      B = 1;
      d = 2;
      f = 0;
    }
  }
  if (reg2 > 0) {
    if (button == '#') {
      c = c + 1;
      if (num1 <= 24 & c == 1) {
        lcd.clear();
        hour2 = num1;
        num1 = 0;
        reg2 = 2;
      }
      else if (num1 > 24 & c == 1) {
        num1 = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Repeat hour");
        reg2 = 1;
        c = c - 1;
      }
      if (num1 <= 59 && c == 2) {
        lcd.clear();
        minut2 = num1;
        num1 = 0;
        reg2 = 0;
        c = 0;
        t2 = 0;
        d = d + 1;
      }
      else if (num1 > 59 & c == 2) {
        num1 = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Repeat minutes");
        reg2 = 2;
        c = c - 1;
      }
    }
    if (reg2 == 1) {
      lcd.setCursor(0, 0);
      lcd.print("Enter hour");
      lcd.write(':');
      lcd.print(num1);
    }
    if (button >= '0' && button <= '9') {
      num1 = num1 * 10 + (button - '0');
    }
    if (reg2 == 2) {
      lcd.setCursor(0, 0);
      lcd.print("Enter minutes");
      lcd.write(':');
      lcd.print(num1);
    }
  }
  if (button == '1' & f == 0)
  {
    A = 1;
    B = 0;
    lcd.setCursor(0, 1);
    lcd.print("                ");
  }
  if (button == '2' & f == 0)
  {
    A = 0;
    B = 1;
    lcd.setCursor(0, 1);
    lcd.print("                ");
  }
  if (button == '*' & reg1 > 0)
  {
    A = 0;
    t1 = 1;
    hour1 = 0;
    minut1 = 0;
    sec1 = 0;
    lcd.clear();
    reg1 = 0;
    num1 = 0;
    c = 0;
  } if (button == '*' & reg2 > 0)
  {
    B = 0;
    t2 = 1;
    hour2 = 0;
    minut2 = 0;
    sec2 = 0;
    lcd.clear();
    reg2 = 0;
    num1 = 0;
    c = 0;
  }
}
