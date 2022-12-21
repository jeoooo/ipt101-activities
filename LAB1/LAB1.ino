/* Lab Activity #1 - Arduino Strobe Lights
        by Jeo Carlo M. Lubao
        on August 24,2020
        */

void setup()
{
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(8, OUTPUT);
}
bool pedestrianLight, trafficLight;
void loop()
{
    trafficLight = true;
    if (trafficLight)
    {
        digitalWrite(10,HIGH);
        Traffic_Light();
        digitalWrite(10,LOW);
    }
    trafficLight = false;
    pedestrianLight = true;

    if (Pedestrian_Light)
    {
        digitalWrite(13, HIGH);
        Pedestrian_Light();
        digitalWrite(13, LOW);
    }
    
    pedestrianLight = false;
}

void Traffic_Light()
{

    for (int j = 13; j >= 11; j--)
    {
        digitalWrite(j, HIGH);
        delay(2000);
        digitalWrite(j, LOW);
    }
}

void Pedestrian_Light()
{

    for (int i = 8; i <= 10; i++)
    {
        digitalWrite(i, HIGH);
        delay(2000);
        digitalWrite(i, LOW);
    }
}
