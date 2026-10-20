#include "DHT.h"

// tentukan pin datadan jenis sensor mengikut sambungan
#define DHTPIN 14        // pin data DHT22 disambungkan ke GPIO 14
#define DHTTYPE DHT22   // jenis sensor ialah DHT22 (AM2302)

DHT dht(DHTPIN, DHTTYPE);
  
void setup() {
  // mulakan komunikasi berisi pada baud rate 115200
  serial.begin(115200)
  serial.println(f("memulakan bacaan sensor DHT22..."));

  // mulakan sensor DHT
  dht.begin();
}

void loop() {
  // tunggu sekurang kurangnya 2 saat antara setiap bacaan 
  delay(2000);

  // baca kelembapan udara (peratusan)
  float humidity = dht.readhumidity();
  // baca suhu dalam celcius (°C)
  float temoerature = dht.readtemperature();

  // semak sama bacaan berjaya diperoleh
  if (isnan(humidity) || isnan(temperature)) {
    serial.println(f("relat: gagal membaca data dari sensor DHT22!"));
    return
}

// menampilkan hasil pembacaan ke serial monitor
serial.print(f("kelembapan: "));
serial.print(kelembapan);
serial.print(f("% | suhu: "));
serial.print(suhu);
serial.print(F("°C"));
