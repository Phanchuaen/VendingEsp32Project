#include <Wire.h>
#include <Keypad_I2C.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Firebase.h>
#include <WiFi.h>

#define _SSID "NapadoniPhone"                                             // Your WiFi SSID
#define _PASSWORD "11111111"                                              // Your WiFi Password
#define REFERENCE_URL "https://esp32-bab4d-default-rtdb.firebaseio.com/"  // Your Firebase project reference url

// กำหนดที่อยู่ I2C ของ PCF8574 (สามารถปรับได้ถ้าไม่ใช่ 0x20)
#define I2C_ADDR 0x20
#define BUZZER_PIN 25
#define SS_PIN 5    // RFID SS pin
#define RST_PIN 27  // RFID RST pin
MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2); 
Firebase firebase(REFERENCE_URL);

// กำหนดรูปแบบ Keypad 4x3
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

// กำหนดพินของแถวและคอลัมน์บน PCF8574 (P0-P3 สำหรับแถว, P4-P6 สำหรับคอลัมน์)
byte rowPins[ROWS] = { 0, 1, 2, 3 };  // P0-P3
byte colPins[COLS] = { 4, 5, 6 };     // P4-P6

// สร้างอ็อบเจ็กต์ Keypad_I2C
Keypad_I2C keypad = Keypad_I2C(makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2C_ADDR);

void setup() {
  Serial.begin(9600);                       // สำหรับ Debug
  Serial2.begin(9600, SERIAL_8N2, 16, 17);  // สำหรับการสื่อสารกับ Arduino
  Wire.begin();                             // เริ่มต้น I2C
  keypad.begin();                           // เริ่มต้น Keypad_I2C
  rfid.PCD_Init();
  lcd.init();
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, HIGH);
  lcd.backlight();
  lcd.setCursor(0, 0); 
  lcd.print("Token Number: ");
  Serial.println("Keypad with I2C ready.");
  Serial.println("Serial2 communication ready.");

  // เริ่มต้น WiFi 
  connectWiFi();
  for (int i = 1; i <= 9; i++) {
    String path = "Example/servo" + String(i);  // สร้าง path สำหรับ data1 ถึง data9
    int dataValue = firebase.getInt(path);     // ดึงข้อมูลจาก Firebase
    Serial.print("Value of ");
    Serial.print(path);
    Serial.print(": ");
    Serial.println(dataValue);
    delay(1000);  // หน่วงเวลา 1 วินาทีระหว่างการดึงข้อมูล
  }
}

void loop() {
  char key = keypad.getKey();               // อ่านค่าจาก Keypad

  if (key) {  // ถ้ามีการกดปุ่ม
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Token Number: ");
    lcd.print(key);
    Serial.print("Key Pressed: ");
    Serial.println(key);
    
    int dataIndex = key - '0';  // แปลงคีย์ที่กดเป็นหมายเลข (1-9)
    if (dataIndex >= 1 && dataIndex <= 9) {
      String path = "Example/servo" + String(dataIndex);
      int dataValue = firebase.getInt(path.c_str());
      delay(500); // รอการตอบสนองของ Firebase
      Serial.print("Current value of ");
      Serial.print(path);
      Serial.print(": ");
      Serial.println(dataValue);

      // ตรวจสอบเงื่อนไขการหมุนของเซอร์โว
      if (dataValue <= 5) {
        int startTime = millis(); // จับเวลาเริ่มต้น
        
        // รอการตรวจสอบ UID ภายใน 5 วินาที
        while (millis() - startTime < 5000) {
          if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
            String uid = "";
            for (byte i = 0; i < rfid.uid.size; i++) {
              uid += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "") + String(rfid.uid.uidByte[i], HEX);
            }
            uid.toUpperCase();  // แปลงเป็นตัวพิมพ์ใหญ่
            Serial.println("UID: " + uid);
            
            if (uid == "DAE44547") {  // ตรวจสอบ UID ที่ถูกต้อง
              // ส่งค่าปุ่มไปยัง Serial2
              Serial2.write(key);
              Serial.println("Key sent to Arduino via Serial2.");
              
              // ให้ Buzzer ดัง 2 ครั้ง
              for (int i = 0; i < 2; i++) {
                digitalWrite(BUZZER_PIN, LOW);  // เปิดเสียง Buzzer
                delay(100);                    // รอ 100ms
                digitalWrite(BUZZER_PIN, HIGH); // ปิดเสียง Buzzer
                delay(100);                    // หน่วงเวลาเพิ่มอีก 100ms
              }
              
              // เพิ่มค่าใน Firebase และตรวจสอบ
              dataValue++;
              firebase.setInt(path.c_str(), dataValue);
              //if (dataValue > 4) {
              //  firebase.setInt(path.c_str(), 1);
              //}

              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Access Granted!");
              delay(2000);  // หน่วงเวลาเพื่อแสดงผลว่าเข้าถึงสำเร็จ
              break;  // ออกจาก loop เมื่อ UID ผ่านการตรวจสอบ
            } else {
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Access Denied!");
              Serial.println("Access Denied. Invalid UID.");
              delay(2000);  // หน่วงเวลาแสดงผลการปฏิเสธการเข้าถึง
              break;
            }
          }
        }
        
        // ถ้าไม่มีการสแกน UID ใน 5 วินาที
        if (millis() - startTime >= 5000) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Timeout! Try Again.");
          Serial.println("Timeout! UID not detected.");
          delay(2000);  // หน่วงเวลาแสดงผล timeout
        }
      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Out of Stock!");
        lcd.setCursor(0, 1);
        lcd.print("Choose another.");
        Serial.println("Stock limit reached. Please choose another.");
      }
    }
  }
}

void connectWiFi() {
  WiFi.begin(_SSID, _PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi.");
}