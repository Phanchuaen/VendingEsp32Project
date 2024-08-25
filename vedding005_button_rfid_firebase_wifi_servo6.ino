#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <MFRC522.h>
#include <ESP32Firebase.h>
#include <WiFi.h>

#define _SSID "NapadoniPhone"                                             // Your WiFi SSID
#define _PASSWORD "11111111"                                              // Your WiFi Password
#define REFERENCE_URL "https://esp32-bab4d-default-rtdb.firebaseio.com/"  // Your Firebase project reference url
#define buzzerPin 25
#define Button1Pin 17
#define Button2Pin 16
#define Button3Pin 36
#define Button4Pin 26
#define Button5Pin 32
#define Button6Pin 4
#define SS_PIN 5    // RFID SS pin
#define RST_PIN 27  // RFID RST pin

Firebase firebase(REFERENCE_URL);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  pwm.begin();
  pwm.setPWMFreq(60);  // ตั้งความถี่ PWM ที่ 60 Hz
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, HIGH);
  pinMode(Button1Pin, INPUT_PULLUP);
  pinMode(Button2Pin, INPUT_PULLUP);
  pinMode(Button3Pin, INPUT_PULLUP);
  pinMode(Button4Pin, INPUT_PULLUP);
  pinMode(Button5Pin, INPUT_PULLUP);
  pinMode(Button6Pin, INPUT_PULLUP);
  rfid.PCD_Init();
  // ช่องเซอร์โวที่ต้องการควบคุม


  delay(1000);
  SetWiFi();
  CheckWiFi();
  int data1 = firebase.getInt("Example/data1");
  delay(1000);
  Serial.println(data1);

  int data2 = firebase.getInt("Example/data2");
  delay(1000);
  Serial.println(data2);

  int data3 = firebase.getInt("Example/data3");
  delay(1000);
  Serial.println(data3);

  int data4 = firebase.getInt("Example/data4");
  delay(1000);
  Serial.println(data4);

  int data5 = firebase.getInt("Example/data5");
  delay(1000);
  Serial.println(data5);

  int data6 = firebase.getInt("Example/data6");
  delay(1000);
  Serial.println(data6);
}

void loop() {
  // Nothing
  digitalWrite(buzzerPin, HIGH);
  int startTime = millis();  // start timer
  int servoMin = 150;
  CheckWiFi();


  if (digitalRead(Button1Pin) == LOW) {
    while (millis() - startTime < 5000) {  // loop for 5 seconds
      if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        String uid = "";
        for (byte i = 0; i < rfid.uid.size; i++) {
          uid += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "") + String(rfid.uid.uidByte[i], HEX);
        }
        Serial.println("UID: " + uid);
        if (uid == "dae44547" || uid == "da e4 45 47" || uid == "DA E4 45 47") {
          digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
          delay(100);                    // Beep for 500ms
          digitalWrite(buzzerPin, HIGH);
          delay(100);
          digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
          delay(100);                    // Beep for 500ms
          digitalWrite(buzzerPin, HIGH);
          pwm.setPWM(0, 0, 150);
          delay(3000);
          pwm.setPWM(0, 0, 0);
          //delay(2000);  // รอ 2 วินาที
          digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
          delay(1000);                   // Beep for 500ms
          digitalWrite(buzzerPin, HIGH);
          Data1();
          break;  // exit the loop
        } else {
          ErrorUid();
        }
      }
    }
    ErrorUid();
  }

  if (digitalRead(Button2Pin) == LOW) {
    while (millis() - startTime < 5000) {  // loop for 5 seconds
      if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        String uid = "";
        for (byte i = 0; i < rfid.uid.size; i++) {
          uid += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "") + String(rfid.uid.uidByte[i], HEX);
        }
        Serial.println("UID: " + uid);
        if (uid == "dae44547" || uid == "da e4 45 47" || uid == "DA E4 45 47") {
          digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
          delay(100);                    // Beep for 500ms
          digitalWrite(buzzerPin, HIGH);
          delay(100);
          digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
          delay(100);                    // Beep for 500ms
          digitalWrite(buzzerPin, HIGH);
          pwm.setPWM(2, 0, 150);
          delay(3000);
          pwm.setPWM(2, 0, 0);
          //delay(2000);  // รอ 2 วินาที
          digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
          delay(1000);                   // Beep for 500ms
          digitalWrite(buzzerPin, HIGH);
          Data2();
          break;  // exit the loop
        } else {
          ErrorUid();
        }
      }
    }
    ErrorUid();
  }

  if (digitalRead(Button3Pin) == LOW) {
    while (millis() - startTime < 5000) {  // loop for 5 seconds
      if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        String uid = "";
        for (byte i = 0; i < rfid.uid.size; i++) {
          uid += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "") + String(rfid.uid.uidByte[i], HEX);
        }
        Serial.println("UID: " + uid);
        if (uid == "dae44547" || uid == "da e4 45 47" || uid == "DA E4 45 47") {
          digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
          delay(100);                    // Beep for 500ms
          digitalWrite(buzzerPin, HIGH);
          delay(100);
          digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
          delay(100);                    // Beep for 500ms
          digitalWrite(buzzerPin, HIGH);
          pwm.setPWM(4, 0, 150);
          delay(3000);
          pwm.setPWM(4, 0, 0);
          //delay(2000);  // รอ 2 วินาที
          digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
          delay(1000);                   // Beep for 500ms
          digitalWrite(buzzerPin, HIGH);
          Data3();
          break;  // exit the loop
        } else {
          ErrorUid();
        }
      }
    }
    ErrorUid();
  }

  if (digitalRead(Button4Pin) == LOW) {
    while (millis() - startTime < 5000) {  // loop for 5 seconds
      if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        String uid = "";
        for (byte i = 0; i < rfid.uid.size; i++) {
          uid += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "") + String(rfid.uid.uidByte[i], HEX);
        }
        Serial.println("UID: " + uid);
        if (uid == "dae44547" || uid == "da e4 45 47" || uid == "DA E4 45 47") {
          digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
          delay(100);                    // Beep for 500ms
          digitalWrite(buzzerPin, HIGH);
          delay(100);
          digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
          delay(100);                    // Beep for 500ms
          digitalWrite(buzzerPin, HIGH);
          pwm.setPWM(13, 0, 150);
          delay(3000);
          pwm.setPWM(13, 0, 0);
          //delay(2000);  // รอ 2 วินาที
          digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
          delay(1000);                   // Beep for 500ms
          digitalWrite(buzzerPin, HIGH);
          Data4();
          break;  // exit the loop
        } else {
          ErrorUid();
        }
      }
    }
    ErrorUid();
  }

  if (digitalRead(Button5Pin) == LOW) {
    while (millis() - startTime < 5000) {  // loop for 5 seconds
      if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        String uid = "";
        for (byte i = 0; i < rfid.uid.size; i++) {
          uid += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "") + String(rfid.uid.uidByte[i], HEX);
        }
        Serial.println("UID: " + uid);
        if (uid == "dae44547" || uid == "da e4 45 47" || uid == "DA E4 45 47") {
          digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
          delay(100);                    // Beep for 500ms
          digitalWrite(buzzerPin, HIGH);
          delay(100);
          digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
          delay(100);                    // Beep for 500ms
          digitalWrite(buzzerPin, HIGH);
          pwm.setPWM(15, 0, 150);
          delay(3000);
          pwm.setPWM(15, 0, 0);
          //delay(2000);  // รอ 2 วินาที
          digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
          delay(1000);                   // Beep for 500ms
          digitalWrite(buzzerPin, HIGH);
          Data5();
          break;  // exit the loop
        } else {
          ErrorUid();
        }
      }
    }
    ErrorUid();
  }

  if (digitalRead(Button6Pin) == LOW) {
    while (millis() - startTime < 5000) {  // loop for 5 seconds
      if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        String uid = "";
        for (byte i = 0; i < rfid.uid.size; i++) {
          uid += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "") + String(rfid.uid.uidByte[i], HEX);
        }
        Serial.println("UID: " + uid);
        if (uid == "dae44547" || uid == "da e4 45 47" || uid == "DA E4 45 47") {
          digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
          delay(100);                    // Beep for 500ms
          digitalWrite(buzzerPin, HIGH);
          delay(100);
          digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
          delay(100);                    // Beep for 500ms
          digitalWrite(buzzerPin, HIGH);
          pwm.setPWM(7, 0, 150);
          delay(3000);
          pwm.setPWM(7, 0, 0);
          //delay(2000);  // รอ 2 วินาที
          digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
          delay(1000);                   // Beep for 500ms
          digitalWrite(buzzerPin, HIGH);
          Data6();
          break;  // exit the loop
        } else {
          ErrorUid();
        }
      }
    }
    ErrorUid();
  }







}  //loopend


void Data1() {
  int data1 = firebase.getInt("Example/data1");
  delay(500);
  Serial.println(data1);
  data1++;
  firebase.setInt("Example/data1", data1);
  if (data1 > 4) {
    firebase.setInt("Example/data1", 1);
  }
  Serial.println(data1);
}

void Data2() {
  int data2 = firebase.getInt("Example/data2");
  delay(500);
  Serial.println(data2);
  data2++;
  firebase.setInt("Example/data2", data2);
  if (data2 > 4) {
    firebase.setInt("Example/data2", 1);
  }
  Serial.println(data2);
}

void Data3() {
  int data3 = firebase.getInt("Example/data3");
  delay(500);
  Serial.println(data3);
  data3++;
  firebase.setInt("Example/data3", data3);
  if (data3 > 4) {
    firebase.setInt("Example/data3", 1);
  }
  Serial.println(data3);
}

void Data4() {
  int data4 = firebase.getInt("Example/data4");
  delay(500);
  Serial.println(data4);
  data4++;
  firebase.setInt("Example/data4", data4);
  if (data4 > 4) {
    firebase.setInt("Example/data4", 1);
  }
  Serial.println(data4);
}

void Data5() {
  int data5 = firebase.getInt("Example/data5");
  delay(500);
  Serial.println(data5);
  data5++;
  firebase.setInt("Example/data5", data5);
  if (data5 > 4) {
    firebase.setInt("Example/data5", 1);
  }
  Serial.println(data5);
}

void Data6() {
  int data6 = firebase.getInt("Example/data6");
  delay(500);
  Serial.println(data6);
  data6++;
  firebase.setInt("Example/data6", data6);
  if (data6 > 4) {
    firebase.setInt("Example/data6", 1);
  }
  Serial.println(data6);
}

void ErrorUid() {
  digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
  delay(100);                    // Beep for 500ms
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);  // Turn on the buzzer
  delay(100);                    // Beep for 500ms
  digitalWrite(buzzerPin, HIGH);
}

void CheckWiFi() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
    delay(1000);
  }
}

void SetWiFi() {
  Serial.print("\n\nElectricl Engineering Enterprise Group\n");
  WiFi.begin(_SSID, _PASSWORD);
  Serial.println("Connecting Wifi...");
  delay(2000);
  Serial.println("Connecting Wifi...");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}
