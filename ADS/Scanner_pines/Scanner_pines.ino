/*
  I2C Multi-Scanner con Recovery para Seeed XIAO ESP32-S3
  - Prueba varias parejas SDA/SCL comunes en XIAO S3.
  - Incluye "bus recovery" si SDA está atascada en LOW.
  - Escanea @100 kHz y si no encuentra, reintenta @50 kHz.
  - Prueba WHO_AM_I en 0x68/0x69 (ICM-20948 esperado = 0xEA).
*/

#include <Wire.h>

struct Cfg { int sda; int scl; const char* name; };
Cfg cfgs[] = {
  {6, 7,  "SDA=6 (D4),  SCL=7 (D5) - DEFAULT XIAO"},
  {4, 5,  "SDA=4,       SCL=5"},
  {8, 9,  "SDA=8,       SCL=9"},
  {1, 2,  "SDA=1,       SCL=2"},
  {2, 1,  "SDA=2,       SCL=1"},
};

static const uint32_t FREQS[] = {100000, 50000}; // 100 kHz, 50 kHz

// ---------- Bus Recovery ----------
void i2c_bus_recover(int sda, int scl){
  // Coloca ambos con pullup interno
  pinMode(sda, INPUT_PULLUP);
  pinMode(scl, INPUT_PULLUP);
  delay(2);

  // Si SDA está baja, intenta liberar relojando SCL ~16 veces
  if (digitalRead(sda) == LOW) {
    pinMode(scl, OUTPUT);
    for (int i=0; i<16; i++){
      digitalWrite(scl, HIGH); delayMicroseconds(5);
      digitalWrite(scl, LOW);  delayMicroseconds(5);
    }
    // Genera STOP “manual”
    pinMode(sda, OUTPUT);
    digitalWrite(sda, LOW);    delayMicroseconds(5);
    digitalWrite(scl, HIGH);   delayMicroseconds(5);
    digitalWrite(sda, HIGH);   delayMicroseconds(5);
  }
}

// ---------- Utilidades ----------
void startBus(int sda, int scl, uint32_t hz){
  Wire.end();
  delay(10);
  i2c_bus_recover(sda, scl);
  delay(2);
  Wire.begin(sda, scl);
  Wire.setClock(hz);
#if defined(ARDUINO_ARCH_ESP32)
  Wire.setTimeOut(50);
#endif
  delay(5);
}

uint8_t readReg(uint8_t addr, uint8_t reg){
  Wire.beginTransmission(addr);
  Wire.write(reg);
  if (Wire.endTransmission(false) != 0) return 0xFF;  // repeated start
  if (Wire.requestFrom((int)addr, 1) != 1) return 0xFF;
  return Wire.read();
}

void scanOnce(int sda, int scl, uint32_t hz){
  startBus(sda, scl, hz);

  Serial.print("\nEscaneando I2C en SDA=");
  Serial.print(sda);
  Serial.print("  SCL=");
  Serial.print(scl);
  Serial.print("  @");
  Serial.print(hz/1000);
  Serial.println(" kHz");

  byte found = 0;
  for (uint8_t addr = 0x03; addr <= 0x77; addr++) {
    Wire.beginTransmission(addr);
    uint8_t err = Wire.endTransmission();
    if (err == 0) {
      Serial.print("  -> Dispositivo en 0x");
      if (addr < 16) Serial.print('0');
      Serial.println(addr, HEX);
      found++;
    } else if (err == 4) {
      Serial.print("  ! Error desconocido en 0x");
      if (addr < 16) Serial.print('0');
      Serial.println(addr, HEX);
    }
    // Muestra progreso para evitar pensar que se colgó
    if ((addr & 0x0F) == 0) Serial.print(".");
  }
  Serial.println();

  if (!found) {
    Serial.println("  (nada encontrado en esta pareja de pines)");
  } else {
    // Intento WHO_AM_I en posibles direcciones de ICM-20948
    for (uint8_t tryAddr : { (uint8_t)0x68, (uint8_t)0x69 }) {
      uint8_t who = readReg(tryAddr, 0x00); // WHO_AM_I en Bank0 = 0x00
      if (who != 0xFF) {
        Serial.print("  WHO_AM_I en 0x");
        Serial.print(tryAddr, HEX);
        Serial.print(" = 0x");
        Serial.println(who, HEX);
        if (who == 0xEA) Serial.println("  -> ICM-20948 detectado.");
      }
    }
  }
}

void setup(){
  Serial.begin(115200);
  delay(500);
  Serial.println("=== MULTI-SCAN I2C con Recovery - XIAO ESP32-S3 ===");
  Serial.println("Tips: GND común, CS/NCS en ALTO (I2C), AD0 fijo (GND=0x68 / 3V3=0x69), pull-ups a 3V3, cable corto.");

  for (auto &c : cfgs){
    Serial.print("\n== Probando "); Serial.print(c.name); Serial.println(" ==");
    for (uint32_t hz : FREQS){
      scanOnce(c.sda, c.scl, hz);
      delay(300);
    }
  }

  Serial.println("\nFin del escaneo.");
}

void loop(){}

