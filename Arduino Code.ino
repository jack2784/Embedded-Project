Servo myservo;  // create servo object

int pos = 0;    // variable to store the servo position

int irSensor = A0; //ir sensor pin

int analogvalue; // Here we are declaring the integer variable analogvalue, for use with the IR sensor 

void setup() {

    Serial.begin();
    
    Particle.variable("analogvalue", &analogvalue, INT); 

    myservo.attach(D0); 
    Spark.function("setpos", setPosition);
    Spark.function("openForX", openForX);
}

void loop()
{
    analogvalue = analogRead(irSensor);

    Serial.printlnf("%d", analogvalue);

    delay(100); // prevent overflowing the serial buffer
}

int setPosition(String posValue) {
    pos = posValue.toInt();
    myservo.write(pos);
    return 0;
}

int openForX(String seconds) {
    
    float X = seconds.toFloat();
    X = (X*1000)-1000; // takes the amount of seconds to reamin open as a float, then times by 1000 to make it milliseconds and removes 1000 (1 second) to account for the time of opening and closing the hatch
    
    Serial.printlnf("%d", X);
    
    myservo.write(180);
    delay(500);
    
    myservo.write(90);
    delay(X);
    
    myservo.write(0);
    delay(500);
    
    myservo.write(90);
    return 0;
}


  