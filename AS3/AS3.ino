/* Assignment #3 - Arduino Strobe Lights
   by Jeo Carlo M. Lubao
   on August 24,2020
*/

void setup()
{
	pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
}

void loop()
{
    // adjusted the delay from 1000ms to 100ms for all LED lights so that it will strobe much faster
	digitalWrite(13, HIGH);
	delay(100);
    digitalWrite(13, LOW);
	delay(100);

    digitalWrite(12, HIGH);
	delay(100);
	digitalWrite(12, LOW);
	delay(100);

    digitalWrite(11, HIGH);
	delay(100);
    digitalWrite(11, LOW);
	delay(100);

    digitalWrite(10, HIGH);
	delay(100);
    digitalWrite(10, LOW);
	delay(100);

    digitalWrite(9, HIGH);
	delay(100);
    digitalWrite(9, LOW);
	delay(100);

    digitalWrite(8, HIGH);
	delay(100);
    digitalWrite(8, LOW);
	delay(100);

    digitalWrite(7, HIGH);
	delay(100);
    digitalWrite(7, LOW);
	delay(100);
}