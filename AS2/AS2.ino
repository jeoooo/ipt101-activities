/* First Arduino Program
   by Jeo Carlo M. Lubao
   on August 19,2020
*/

void setup()
{
	pinMode(13, OUTPUT);
}

void loop()
{
	digitalWrite(13, HIGH);
	delay(1000);
	digitalWrite(13, LOW);
	delay(1000);
}

