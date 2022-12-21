void setup(){
    pinMode(13,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(4,OUTPUT);

    Serial.begin(9600);
}

void loop(){

    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    double tempCelsius = sensorValue * (4.88/10) - 50;
    // print out the value you read:
    Serial.println(tempCelsius);
    delay(1);  

    if(tempCelsius <= -0.22){ // range < 10
      	digitalWrite(7,LOW);
        digitalWrite(6,LOW);
        digitalWrite(5,LOW);
        digitalWrite(4,LOW);

        StopPiezoSound();
    }
    if(tempCelsius >= 10.02 && tempCelsius <= 19.78){ // 10-19
        digitalWrite(7,HIGH);
        digitalWrite(6,LOW);
        digitalWrite(5,LOW);
        digitalWrite(4,LOW);

        StopPiezoSound();
    }
    if(tempCelsius >= 20.76 && tempCelsius <= 29.06){ //20-29
      	digitalWrite(7,HIGH);
        digitalWrite(6,HIGH); 
        digitalWrite(5,LOW);
        digitalWrite(4,LOW);

        StopPiezoSound();  
    }
    if(tempCelsius >= 30.03 && tempCelsius <= 38.82){ //30-39
      	digitalWrite(7,HIGH);
        digitalWrite(6,HIGH);
        digitalWrite(5,HIGH);
        digitalWrite(4,LOW);

        StopPiezoSound(); 
    }
    if(tempCelsius > 38.82){ //40 above
      	digitalWrite(7,HIGH);
        digitalWrite(6,HIGH);
        digitalWrite(5,HIGH);
        digitalWrite(4,HIGH);
        
        PlayPiezoSound();
    }

}

void PlayPiezoSound()
{
    digitalWrite(13,HIGH);
}

void StopPiezoSound()
{
    digitalWrite(13,LOW);
}
