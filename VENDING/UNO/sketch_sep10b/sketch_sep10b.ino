

#include <Wire.h>
//#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>
Servo myservo; //ประกาศตัวแปรแทน Servo

// กำหนดไลบรารี Adafruit PWM
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// ค่า PWM สำหรับ Servo 360 องศา (Continuous Rotation)


void setup() {
  
  Serial.begin(9600);  // เริ่มต้น Serial เพื่อรับข้อมูลจาก ESP32
  //pwm.begin();
  //pwm.setPWMFreq(60);  // ตั้งค่า PWM frequency ที่ 60 Hz

  Serial.println("Servo control ready.");

   // กำหนดขา 9 ควบคุม Servo
}

void loop() {
  
  if (Serial.available()) {
    char command = Serial.read();  // รับคำสั่งจาก ESP32
    int servoIndex = command - '0';  // แปลงอักขระตัวเลขเป็นตัวเลขจริง

    Serial.println(command);
    Serial.println(servoIndex);

   

    if (servoIndex >= 1 && servoIndex <= 9) {  // กำหนดขอบเขตของ Servo หมายเลข 1 ถึง 9
      int servoPin = servoIndex + 1;  // แปลงให้ servoPin ตรงกับพินที่เชื่อมต่อ Servo
    
      if ( servoPin == 5 || servoPin == 6 || servoPin == 7 ){
        myservo.attach(servoPin);  // ผูก Servo กับพินที่ถูกต้อง
        myservo.writeMicroseconds(0);  // สั่งให้ Servo หมุนตามเข็มนาฬิกา
        delay(1250);  // หน่วงเวลา 1200ms
        myservo.writeMicroseconds(1500);  // หยุดการหมุน Servo (ค่า 1500 เป็นการหยุด)
        myservo.detach();  // ปล่อยพินของ Servo
      }
      if ( servoPin == 4  ){
        myservo.attach(servoPin);  // ผูก Servo กับพินที่ถูกต้อง
        myservo.writeMicroseconds(3000);  // สั่งให้ Servo หมุนตามเข็มนาฬิกา
        delay(1750);  // หน่วงเวลา 1200ms
        myservo.writeMicroseconds(1500);  // หยุดการหมุน Servo (ค่า 1500 เป็นการหยุด)
        myservo.detach();  // ปล่อยพินของ Servo
      }
      if (servoPin == 3) {
        myservo.attach(servoPin);  // ผูก Servo กับพินที่ถูกต้อง
        myservo.writeMicroseconds(3000);  // สั่งให้ Servo หมุนตามเข็มนาฬิกา
        delay(1280);  // หน่วงเวลา 1200ms
        myservo.writeMicroseconds(1500);  // หยุดการหมุน Servo (ค่า 1500 เป็นการหยุด)
        myservo.detach();  // ปล่อยพินของ Servo
      }
      if (servoPin == 2) {
        myservo.attach(servoPin);  // ผูก Servo กับพินที่ถูกต้อง
        myservo.writeMicroseconds(3000);  // สั่งให้ Servo หมุนตามเข็มนาฬิกา
        delay(1380);  // หน่วงเวลา 1200ms
        myservo.writeMicroseconds(1500);  // หยุดการหมุน Servo (ค่า 1500 เป็นการหยุด)
        myservo.detach();  // ปล่อยพินของ Servo
      }
      if (servoPin == 9) {
        myservo.attach(servoPin);  // ผูก Servo กับพินที่ถูกต้อง
        myservo.writeMicroseconds(3000);  // สั่งให้ Servo หมุนตามเข็มนาฬิกา
        delay(1840);  // หน่วงเวลา 1200ms
        myservo.writeMicroseconds(1500);  // หยุดการหมุน Servo (ค่า 1500 เป็นการหยุด)
        myservo.detach();  // ปล่อยพินของ Servo
      }
        if (servoPin == 10) {
        myservo.attach(servoPin);  // ผูก Servo กับพินที่ถูกต้อง
        myservo.writeMicroseconds(3000);  // สั่งให้ Servo หมุนตามเข็มนาฬิกา
        delay(2000);  // หน่วงเวลา 1200ms
        myservo.writeMicroseconds(1500);  // หยุดการหมุน Servo (ค่า 1500 เป็นการหยุด)
        myservo.detach();  // ปล่อยพินของ Servo
        Serial.println("-9");
      }
      if (servoPin == 8) {
        myservo.attach(servoPin);  // ผูก Servo กับพินที่ถูกต้อง
        myservo.writeMicroseconds(3000);  // สั่งให้ Servo หมุนตามเข็มนาฬิกา
        delay(1850);  // หน่วงเวลา 1200ms
        myservo.writeMicroseconds(1500);  // หยุดการหมุน Servo (ค่า 1500 เป็นการหยุด)
        myservo.detach();  // ปล่อยพินของ Servo
        Serial.println("-9");
      }
     
    
    }
  }
}
