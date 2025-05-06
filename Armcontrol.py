from math import asin, acos, atan, sqrt, cos, sin, pi
import RPi.GPIO as GPIO
from time import delay

def Armcontrol(x,y):

    SERVO_PIN1 = 11  # Change to your GPIO pins
    SERVO_PIN2 = 12
    SERVO_PIN3 = 13
    SERVO_PIN4 = 14
    SERVO_PIN5 = 15
    SERVO_PIN6 = 16

    L1=10
    L2=10
    L3=4
    H1=5
    x=20
    y=10
    L=sqrt(x*x + y*y)
    diff=1
    t1=pi/2


    if L >= (L1 + L2 + L3):
        print("Arm cannot reach object")
        return

    while abs(diff) >= 0.1:
        guess = asin((L2*sin(acos((L - L3 - L1*cos(t1))/L2)) - H1)/L1)
        diff = t1 - guess
        t1 = guess

    t2 = pi - t1 - acos((L-L3- L1*cos(t1))/L2)

    t3 = t1 + t2

    t4 = pi/2

    t5 = atan(x/y)

    GPIO.setmode(GPIO.BOARD)

    GPIO.setup(SERVO_PIN1, GPIO.OUT)
    GPIO.setup(SERVO_PIN2, GPIO.OUT)
    GPIO.setup(SERVO_PIN3, GPIO.OUT)
    GPIO.setup(SERVO_PIN4, GPIO.OUT)
    GPIO.setup(SERVO_PIN5, GPIO.OUT)
    GPIO.setup(SERVO_PIN6, GPIO.OUT)

    pwm1 = GPIO.PWM(SERVO_PIN1, 50)
    pwm2 = GPIO.PWM(SERVO_PIN2, 50)
    pwm3 = GPIO.PWM(SERVO_PIN3, 50)
    pwm4 = GPIO.PWM(SERVO_PIN4, 50)
    pwm5 = GPIO.PWM(SERVO_PIN5, 50)
    pwm6 = GPIO.PWM(SERVO_PIN6, 50)

    pwm1.start(0)
    pwm2.start(0)
    pwm3.start(0)
    pwm4.start(0)
    pwm5.start(0)
    pwm6.start(0)

    
    def duty(angle):
    
        duty = 7.5 + angle / 36

        return duty

    def Neutralposition():
        pwm1.ChangeDutyCycle(duty(0))
        pwm2.ChangeDutyCycle(duty(25))
        pwm3.ChangeDutyCycle(duty(-25))
        pwm4.ChangeDutyCycle(duty(-70))
        pwm5.ChangeDutyCycle(duty(90))
        delay(4)
        pwm6.ChangeDutyCycle(duty(0))

    Neutralposition

    t1 = t1 * 180 / pi 
    t2 = t2 * 180 / pi
    t3 = t3 * 180 / pi
    t4 = t4 * 180 / pi
    t5 = t5 * 180 / pi

    t1 = t1 - 45
    t2 = t2 - 90
    t3 = 180 - t3

    t1 = t1.real
    t2 = t2.real
    t3 = t3.real

    delay(2)

    pwm1.ChangeDutyCycle(duty(t5))
    pwm2.ChangeDutyCycle(duty(t1))
    pwm3.ChangeDutyCycle(duty(-t1))
    pwm4.ChangeDutyCycle(duty(t2))
    pwm5.ChangeDutyCycle(duty(t3))

    delay(4)

    pwm6.ChangeDutyCycle(duty(t4))

    delay(2)

    Neutralposition