#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// กำหนดไลบรารี Adafruit PWM
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// ค่า PWM สำหรับ Servo 360 องศา (Continuous Rotation)
#define SERVOMIN  200    // ความเร็วต่ำสุด (ทวนเข็มนาฬิกา)
#define SERVOMAX  400    // ความเร็วสูงสุด (ตามเข็มนาฬิกา)
#define SERVOSLOW 310    // ความเร็วช้า (สำหรับหมุนไปช้าๆ)
#define SERVONEUTRAL 300 // หยุดการหมุน

void setup() {
  Serial.begin(9600);  // เริ่มต้น Serial เพื่อรับข้อมูลจาก ESP32
  pwm.begin();
  pwm.setPWMFreq(60);  // ตั้งค่า PWM frequency ที่ 60 Hz

  Serial.println("Servo control ready.");
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();  // รับคำสั่งจาก ESP32

    // แปลงปุ่มที่กดจาก Keypad เป็นหมายเลข Servo
    int servoIndex = command - '1';  // เช่น กด '1' คือ Servo 0, กด '2' คือ Servo 1
    Serial.println(command);

    if (servoIndex >= 0 && servoIndex < 9) {
      // หมุน Servo ในทิศทางเดียวด้วยความเร็วช้า
      pwm.setPWM(servoIndex, 0, SERVOSLOW);  // ส่งค่า PWM เพื่อหมุนไปช้าๆ
      delay(1000);  // หมุนต่อเนื่อง
      pwm.setPWM(servoIndex, 0, 0);  // ส่งค่า PWM เพื่อหมุนไปช้าๆ
      
      // หากต้องการให้หยุดเมื่อกดปุ่มอื่น (เช่นปุ่ม '0')
      
    }
  }
}
