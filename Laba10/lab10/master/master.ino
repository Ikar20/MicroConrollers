#define BAUD 14400
#define MODE 20
#define TRANSMIT HIGH
#define RECEIVE LOW
#define ID 1
#define SLAVE1_ID 53
#define SLAVE2_ID 78

char symbol;
int i = 0;
int lastMessageFrom;
char* bufferPtr;
long crcRecieved;
bool crcHasChanged;

void setup(void) {
  Serial1.begin(BAUD);
  Serial.begin(19200);
  pinMode(MODE, OUTPUT);
}

void loop()
{
  if (Serial.available()) {
    int inByte = Serial.read();
    if (inByte == 49) {
      sendMessage(SLAVE1_ID, "Give");
    } else if (inByte == 50) {
      sendMessage(SLAVE2_ID, "Give");
    }
  }
  
  i = 0;
  crcRecieved = 0;
  crcHasChanged = false;
  if (Serial1.available() ) {
    bufferPtr = (char*)malloc(50 * sizeof(char));
    delay(3);
    while (Serial1.available()) {
      symbol = Serial1.read();
      if (symbol == ';') {
        bufferPtr[i++] = '\0';
        i = 0;
        int c;
        sscanf(bufferPtr, "%d", &c);
        if (c != ID) {
          while (Serial1.available()) {
            Serial1.read();
          }
          free(bufferPtr);
          return;
        }
      } else if (symbol == ':') {
        bufferPtr[i++] = '\0';
        i = 0;
        int c;
        sscanf(bufferPtr, "%d", &c);
        lastMessageFrom = c;
      } else if (symbol == '!') {
        bufferPtr[i++] = '\0';
        i = 0;
        sscanf(bufferPtr, "%lx", &crcRecieved);
        crcHasChanged = true;
      } else {
        bufferPtr[i++] = symbol;
      }
    }
    bufferPtr[i++] = '\0';
  }
  
  if (crcHasChanged && strlen(bufferPtr) > 0 && i > 0) {
    sendToUI(bufferPtr);
  } else if (!crcHasChanged && strlen(bufferPtr) > 0 && i > 0){
    Serial.print(bufferPtr);
  }
  
  free(bufferPtr);
}

void sendToUI(char str[]) {
  char buffer[30];
  sprintf(buffer, "#%lx;%s", crcRecieved, str);
  Serial.print(buffer);
}

void sendMessage(int recevierId, char str[]) {
  digitalWrite(MODE, TRANSMIT);
  delay(60);
  char buffer[20];
  sprintf(buffer, "%d;%s", recevierId, str);
  Serial1.print(buffer);
  delay(60);
  digitalWrite(MODE, RECEIVE);
}
