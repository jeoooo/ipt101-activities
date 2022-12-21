void setup()
{
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  LED_Twinkle();
}

void LED_Twinkle() // FUNCTION FOR BLINKING LED
{
  int sensorValue = analogRead(A0);
  double tempCelsius = sensorValue * (4.88 / 10) - 50;
  //if temp < 25

  if (tempCelsius < 24.66)
  {
    digitalWrite(9, LOW);
    TempUpdate();
  }

  if (tempCelsius >= 24.66 && tempCelsius <= 39.79)
  { // 25-39
    digitalWrite(9, HIGH);
    delay(1000);
    digitalWrite(9, LOW);
    delay(1000);
    TempUpdate();
  }
  if (tempCelsius >= 40.77 && tempCelsius <= 54.95)
  { // 40-54
    digitalWrite(9, HIGH);
    delay(500);
    digitalWrite(9, LOW);
    delay(500);
    TempUpdate();
  }
  if (tempCelsius >= 55.90 && tempCelsius <= 68.58)
  { // 55-69
    digitalWrite(9, HIGH);
    delay(300);
    digitalWrite(9, LOW);
    delay(300);
    TempUpdate();
  }
  if (tempCelsius >= 70.05 && tempCelsius <= 84.69)
  { // 70-84
    digitalWrite(9, HIGH);
    delay(200);
    digitalWrite(9, LOW);
    delay(200);
    TempUpdate();
  }
  if (tempCelsius >= 85.66)
  { // 85-100
    digitalWrite(9, HIGH);
    delay(100);
    digitalWrite(9, LOW);
    delay(100);
    TempUpdate();
  }
}
void TempUpdate() // FUNCTION FOR SERIAL MONITOR TEMP UPDATE
{

  int sensorValue = analogRead(A0);
  double tempCelsius = sensorValue * (4.88 / 10) - 50;

  Serial.println(tempCelsius);
  delay(1);
}