#include <ESP32Servo.h>
#include <math.h>
#include <iostream>
#include <complex>

void setup() {
    Serial.begin(9600);

    double x=10;
    double y=5;

    while (!Serial);  // Wait for Serial Monitor
    
    const double pi = std::acos(-1);

    Servo myservo1;
    Servo myservo2;
    Servo myservo3;
    Servo myservo4;
    Servo myservo5;
    Servo myservo6;

    myservo1.attach(12);  
    myservo2.attach(14);
    myservo3.attach(27);
    myservo4.attach(26);
    myservo5.attach(25);
    myservo6.attach(33);

}
	
void loop() {

    Serial.println("Please enter a number for x-coordinate:");
  
    // Wait until something is typed
    while (Serial.available() == 0) {
    // just wait
    }

    x = Serial.parseFloat();  // Reads a float (e.g., 3.14, -2.7, etc.)

    Serial.print("You entered: ");
    Serial.println(x, 6);  // Print with up to 6 decimal places

    Serial.println("Please enter a number for y-coordinate:");
  
    // Wait until something is typed
    while (Serial.available() == 0) {
    // just wait
    }

    y = Serial.parseFloat();  // Reads a float (e.g., 3.14, -2.7, etc.)

    Serial.print("You entered: ");
    Serial.println(y, 6);  // Print with up to 6 decimal places

    double L1=10;
    double L2=10;
    double L3=4;
    double H1=5;
    double L=sqrt(x*x + y*y);
    double diff=1;
    double t1=pi/2;
    double guess = 1;


    if (L >= (L1 + L2 + L3)) {
        std::cout << "Object cannot be reached" << std::endl;
    }

    while (abs(diff) >= 0.1) {
        std::complex<double> guess = asin((L2*sin(acos((L - L3 - L1*cos(t1))/L2)) - H1)/L1);
        std::complex<double> diff = t1 - guess;
        std::complex<double> t1 = guess;
    }

    double t1 = t1.real();
    double t2 = pi - t1 - acos((L-L3- L1*cos(t1))/L2);

    double t3 = t1 + t2;

    double t4 = pi/2;

    double t5 = atan(x/y);

    t1 = t1 * 180 / pi; 
    t2 = t2 * 180 / pi;
    t3 = t3 * 180 / pi;
    t4 = t4 * 180 / pi;
    t5 = t5 * 180 / pi;

    myservo1.write(90);
    myservo2.write(70);
    myservo3.write(110);
    myservo4.write(20);
    myservo5.write(90);
    myservo6.write(90);

    delay(4000);

    myservo1.write(90+t5);
    myservo2.write(t1);
    myservo3.write(180-t1);
    myservo4.write(t2);
    myservo5.write(t3);

    delay(4000);

    myservo6.write(0);

    delay(4000);

    myservo1.write(90);
    myservo2.write(70);
    myservo3.write(110);
    myservo4.write(20);
    myservo5.write(90);

}