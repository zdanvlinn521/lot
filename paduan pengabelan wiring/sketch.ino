#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <ESP32Servo.h>

// Konfigurasi Pin
#define DHTPIN 15
#define DHTTYPE DHT22
#define LDR_PIN 34
#define LED_PIN 12
#define SERVO_PIN 13

// Inisialisasi Objek
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo ventilasiServo;

// Threshold/Batas Otomatisasi
const float BATAS_SUHU_PANAS = 30.0; 
const int BATAS_GELAP = 2000; // Nilai ADC ESP32 (0-4095), semakin tinggi semakin gelap pada beberapa modul

void setup() {
  Serial.begin(115200);
  
  // Inisialisasi Sensor & Output
  dht.begin();
  lcd.init();
  lcd.backlight();
  
  pinMode(LED_PIN, OUTPUT);
  
  // Inisialisasi Servo
  ESP32PWM::allocateTimer(0);
  ventilasiServo.setPeriodHertz(50);
  ventilasiServo.attach(SERVO_PIN, 500, 2400);
  
  // Posisi awal servo (Atap Tertutup = 0 derajat)
  ventilasiServo.write(0); 
  
  lcd.setCursor(0, 0);
  lcd.print("Smart Greenhouse");
  lcd.setCursor(0, 1);
  lcd.print("Sistem Dimulai..");
  delay(2000);
  lcd.clear();
}

void loop() {
  // 1. Membaca Data dari Sensor (Input)
  float suhu = dht.readTemperature();
  float kelembapan = dht.readHumidity();
  int nilaiLDR = analogRead(LDR_PIN);

  // Validasi pembacaan sensor DHT
  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println("Gagal membaca dari sensor DHT!");
    return;
  }

  // Tampilkan data di Serial Monitor untuk debugging
  Serial.print("Suhu: "); Serial.print(suhu); Serial.print("C | ");
  Serial.print("LDR: "); Serial.println(nilaiLDR);

  // 2. Logika Otomatisasi & Pengendalian Aktuator (Output)
  
  // Otomatisasi Atap Ventilasi berdasarkan Suhu
  if (suhu > BATAS_SUHU_PANAS) {
    ventilasiServo.write(90); // Membuka ventilasi (90 derajat)
  } else {
    ventilasiServo.write(0);  // Menutup ventilasi (0 derajat)
  }

  // Otomatisasi Lampu Pertumbuhan berdasarkan Cahaya Sekitar
  if (nilaiLDR > BATAS_GELAP) {
    digitalWrite(LED_PIN, HIGH); // Nyalakan lampu jika gelap
  } else {
    digitalWrite(LED_PIN, LOW);  // Matikan lampu jika terang
  }

  // 3. Menampilkan Informasi pada Layar LCD
  lcd.setCursor(0, 0);
  lcd.print("T:" + String(suhu, 1) + "C  H:" + String(kelembapan, 0) + "% ");
  
  lcd.setCursor(0, 1);
  if (suhu > BATAS_SUHU_PANAS) {
    lcd.print("Atap:BUKA ");
  } else {
    lcd.print("Atap:TUTUP");
  }
  
  if (nilaiLDR > BATAS_GELAP) {
    lcd.print(" L:ON ");
  } else {
    lcd.print(" L:OFF");
  }

  delay(1500); // Sensor DHT22 membutuhkan jeda pembacaan minimal 1-2 detik
}
