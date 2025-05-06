#include <ESP32Servo.h>
#include <math.h>
#include <complex>

double x=10;
double y=5;

const double pi = std::acos(-1);

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;

void setup() {

    Serial.begin(9600);

    while (!Serial);  // Wait for Serial Monitor

    myservo1.attach(12);  
    myservo2.attach(14);
    myservo3.attach(27);
    myservo4.attach(26);
    myservo5.attach(25);
    myservo6.attach(33);

}
	
void loop() {

    Serial.println("Please enter a number for x-coordinate:");
  
    while (Serial.available() == 0) {
    }

    x = Serial.parseFloat();

    Serial.print("You entered: ");
    Serial.println(x, 6);

    Serial.println("Please enter a number for y-coordinate:");
  
    while (Serial.available() == 0) {
    }

    y = Serial.parseFloat(); 

    Serial.print("You entered: ");
    Serial.println(y, 6); 

    double L1=10;
    double L2=10;
    double L3=4;
    double H1=5;
    double L=sqrt(x*x + y*y);

    std::complex<double> guess = 1;
    std::complex<double> T1 = pi/2;
    std::complex<double> diff = 1;

    if (L-L3-L1 > sqrt(L2*L2 - H1*H1)) {
        Serial.println("Object cannot be reached");
        return;
    }

    while (std::abs(diff) >= 0.1) {
        guess = asin((L2*sin(acos((L - L3 - L1*cos(T1))/L2)) - H1)/L1);
        diff = T1 - guess;
        T1 = guess;
    }

    double t1 = T1.real();
    double t2 = pi - t1 - acos((L-L3- L1*cos(t1))/L2);
    double t3 = t1 + t2;
    double t4 = pi/2;
    double t5 = atan(x/y);

    t1 = t1 * 180 / pi; 
    t2 = t2 * 180 / pi;
    t3 = t3 * 180 / pi;
    t4 = t4 * 180 / pi;
    t5 = t5 * 180 / pi;

    Serial.print("Solved for angles, angle 1 is: ");
    Serial.println(t1, 6);
    Serial.print("Angle 2 is: ");
    Serial.println(t2, 6);
    Serial.print("Angle 3 is: ");
    Serial.println(t3, 6);

    Serial.println("Going to starting position ...");

    myservo1.write(90);
    myservo2.write(70);
    myservo3.write(110);
    myservo4.write(20);
    myservo5.write(90);
    myservo6.write(90);

    delay(2000);

    Serial.println("Locating object ...");

    myservo1.write(90-t5);
    myservo2.write(t1);
    myservo3.write(180-t1);
    myservo4.write(t2);
    myservo5.write(t3);

    delay(2000);

    Serial.println("Grabbing ...");

    myservo6.write(0);

    delay(2000);

    Serial.println("Retracting ...");

    myservo1.write(90);
    myservo2.write(70);
    myservo3.write(110);
    myservo4.write(20);
    myservo5.write(90);

}