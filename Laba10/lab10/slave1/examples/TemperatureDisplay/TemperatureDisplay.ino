#include <TC77.h>

/* Temperature sensor on pin 3 (data), 4 (clock) and 5 (cs). */

TC77 tempSensor(3, 4, 5);

void setup() {
	tempSensor.begin();
	Serial.begin(9600);
	tempSensor.wake();
}

void loop() {
	delay(1000);
	Serial.print("The temperature is: ");
	Serial.print(tempSensor.read());
	Serial.println(" degrees C");
}
