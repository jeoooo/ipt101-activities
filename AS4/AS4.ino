int buttonState = 0;

void setup()
{
  pinMode(2, INPUT);
  pinMode(11, OUTPUT);
}

void loop()
{
  buttonState = digitalRead(2);
  
  if(buttonState == HIGH)
  {
    digitalWrite(11, LOW);
    delay(2000);
  }
  else
  {
    digitalWrite(11, HIGH);
  }
}