#define TRIG_PIN 5
#define ECHO_PIN 18
#define LED_PIN 14

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT); // TRIG memancarkan suara
  pinMode(ECHO_PIN, INPUT); // ECHO mendengarkan pantulan    
  pinMode(LED_PIN, OUTPUT); // konfigurasi pin LED sebagai output

  digitalWrite(LED_PIN, LOW); // pastikan LED mati saat awal boot
}

void loop() {
  // 1. memancarkan gelombang suara selama 10 mikrodetik
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

// 2. membaca waktu pantulan (dalam mikrodetik)
long duration = pulseIn(ECHO_PIN, HIGH);

// 3. menghitung jarak ke centimeter
float distance = duration * 0.034 / 2;

// 4. logika kontrol LED merah
if (distance < 20.0) {
  digitalWrite(LED_PIN, HIGH); // LED biru menyala
} else {
  digitalWrite(LED_PIN, LOW); // LED biru mati
}

Serial.print("jarak: ");
Serial.print(distance);
Serial.print(" cm");

delay(100); // jeda 1 detik antar pembacaan
}
