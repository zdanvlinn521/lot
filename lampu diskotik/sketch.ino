// Sesuaikan nomor pin ini dengan tulisan di board ESP32 pada gambar
#define LED_BIRU 18   // Kabel biru
#define LED_KUNING 4   // Kabel KUNING
#define LED_PUTIH 2    // kabel putih

void setup() {
  Serial.begin(115200);
  
  // Mengatur pin LED sebagai OUTPUT
  pinMode(LED_BIRU, OUTPUT);
  pinMode(LED_KUNING, OUTPUT);
  pinMode(LED_PUTIH, OUTPUT);
}

void loop() {
  // Menyalakan LED Biru, mematikan YANG LAIN
  digitalWrite(LED_BIRU, HIGH);
  digitalWrite(LED_KUNING, LOW);
  digitalWrite(LED_PUTIH, LOW);
  delay(1000); // Tunggu 1 detik

  // menyalakan LED KUNING, matikan yang lain
  digitalWrite(LED_BIRU, LOW);
  digitalWrite(LED_KUNING, HIGH);
  digitalWrite(LED_PUTIH, LOW);
  delay(1000); // Tunggu 1 detik

  // menyalakan LED PUTIH, matikan yang lain
  digitalWrite(LED_BIRU, LOW);
  digitalWrite(LED_KUNING, LOW);
  digitalWrite(LED_PUTIH, HIGH);
  delay(1000); // tunggu 1 detik
}
