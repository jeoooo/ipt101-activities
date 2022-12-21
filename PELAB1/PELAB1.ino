void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop()
{
  /* 
  //	TO GET THE RESULT //
  	where:
          - 0 km/h represents an ADC value of 0
          - 140 km/h represents an ADC value of 1023
         
    then: 
    
    (1023/140(km/h) = 7.30714.... or appox. 7.30)
    
    
    take 7.30.... and multiply it by 100(km/h) 
    to get the respective
    ADC value of 100 km/h
    
    7.30 * 100 = 730
    
    thus, 730 is the ADC value of 100 km/h

    to get the speed, just divide SensorValue by 7.3
         
  */

  int SensorValue = analogRead(A5);

  int speed = SensorValue / 7.3;

  //PLS CHECK THE SERIAL MONITOR
  Serial.println(speed);
  delay(1);

  if (SensorValue >= 730)
  {
    digitalWrite(13, HIGH);
  }
  else
  {
    digitalWrite(13, LOW);
  }
}