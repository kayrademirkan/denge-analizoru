// ====================================================================
//  MPU6050 EKSEN TESTI
//  Amac: Denge tahtasina monte etmeden once, MPU6050'nin hangi ekseninin
//        SAG-SOL (Roll) ve hangisinin ON-ARKA (Pitch) yonunde tepki
//        verdigini gormek.
//
//  Donanim: Ana proje ile aynidir (MPU6050 + SSD1306 OLED + Arduino).
//  Yukleme: Bu .ino'yu kendi sketch klasorunde acin (Arduino IDE).
//
//  Kullanim:
//    1. Cihaz yatay sabit dururken acilis kalibrasyonunu BEKLE.
//    2. OLED ekranda iki sayi goreceksin:
//         R: ... -> Roll  (angleX, X ekseni etrafinda donus)
//         P: ... -> Pitch (angleY, Y ekseni etrafinda donus)
//    3. TEST 1 - Cihazi SAGA EGDIR:
//         R degisiyorsa  -> NORMAL: SAG-SOL = Roll = X ekseni
//         P degisiyorsa  -> TERS:   MPU 90 derece donmus, denge tahtasina
//                                   monte ederken ekseni cevir
//                                   (veya kodda angleX/angleY swap)
//    4. TEST 2 - Cihazi ONE EGDIR:
//         Diger sayi (P veya R) degismeli, dogrulama icin kullanilir.
//
//  Seri Monitor (115200 baud): Roll ve Pitch sayilari surekli akar.
//                              Ham AcX/AcY/AcZ degerleri de yazilir.
// ====================================================================

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
#define MPU 0x68

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

float gyroXOffset = 0, gyroYOffset = 0;
float angleX = 0, angleY = 0;
float angleXOffset = 0, angleYOffset = 0;
unsigned long lastTime = 0;
const float alpha = 0.96;

int16_t lastAcX = 0, lastAcY = 0, lastAcZ = 0;

// -------------------- MPU6050 ----------------------------------------

bool initMPU() {
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  if (Wire.endTransmission(true) != 0) return false;

  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(0x00);
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0x00);
  Wire.endTransmission(true);

  return true;
}

void readMPU(int16_t &AcX, int16_t &AcY, int16_t &AcZ,
             int16_t &GyX, int16_t &GyY, int16_t &GyZ) {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  uint8_t got = Wire.requestFrom((uint8_t)MPU, (uint8_t)14, (uint8_t)true);

  if (got < 14) {
    AcX = AcY = AcZ = 0;
    GyX = GyY = GyZ = 0;
    return;
  }

  uint8_t hi, lo;
  hi = Wire.read(); lo = Wire.read(); AcX = (int16_t)((hi << 8) | lo);
  hi = Wire.read(); lo = Wire.read(); AcY = (int16_t)((hi << 8) | lo);
  hi = Wire.read(); lo = Wire.read(); AcZ = (int16_t)((hi << 8) | lo);
  Wire.read(); Wire.read();  // TEMP
  hi = Wire.read(); lo = Wire.read(); GyX = (int16_t)((hi << 8) | lo);
  hi = Wire.read(); lo = Wire.read(); GyY = (int16_t)((hi << 8) | lo);
  hi = Wire.read(); lo = Wire.read(); GyZ = (int16_t)((hi << 8) | lo);

  lastAcX = AcX; lastAcY = AcY; lastAcZ = AcZ;
}

void updateFilter() {
  int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;
  readMPU(AcX, AcY, AcZ, GyX, GyY, GyZ);

  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;
  lastTime = now;
  if (dt <= 0 || dt > 0.2) dt = 0.01;

  float gyroXRate = (GyX - gyroXOffset) / 131.0;
  float gyroYRate = (GyY - gyroYOffset) / 131.0;

  float accAngleX = atan2((float)AcY, (float)AcZ) * 180.0 / PI;
  float accAngleY = atan2((float)AcX, (float)AcZ) * 180.0 / PI;

  angleX = alpha * (angleX + gyroXRate * dt) + (1.0 - alpha) * accAngleX;
  angleY = alpha * (angleY + gyroYRate * dt) + (1.0 - alpha) * accAngleY;
}

void calibrate() {
  Serial.println(F("# Kalibrasyon basliyor, cihazi 2 saniye boyunca SABIT TUT"));
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("KALIBRASYON"));
  display.println();
  display.println(F("Cihazi sabit tut"));
  display.display();
  delay(700);

  // Faz 1: gyro bias
  long gxSum = 0, gySum = 0;
  const int N = 1000;
  for (int i = 0; i < N; i++) {
    int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;
    readMPU(AcX, AcY, AcZ, GyX, GyY, GyZ);
    gxSum += GyX;
    gySum += GyY;
    delay(2);
  }
  gyroXOffset = gxSum / (float)N;
  gyroYOffset = gySum / (float)N;

  // Faz 2: referans aci
  angleX = 0;
  angleY = 0;
  lastTime = millis();
  for (int i = 0; i < 200; i++) {
    updateFilter();
    delay(5);
  }
  angleXOffset = angleX;
  angleYOffset = angleY;

  Serial.println(F("# Kalibrasyon TAMAM"));
  Serial.print(F("# gyroXOffset=")); Serial.println(gyroXOffset, 2);
  Serial.print(F("# gyroYOffset=")); Serial.println(gyroYOffset, 2);
  Serial.print(F("# angleXOffset=")); Serial.println(angleXOffset, 3);
  Serial.print(F("# angleYOffset=")); Serial.println(angleYOffset, 3);
}

// -------------------- Setup / Loop -----------------------------------

void setup() {
  delay(300);

  Wire.begin();
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("OLED HATA"));
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("EKSEN TESTI"));
  display.println();
  display.println(F("MPU6050 baslatiliyor"));
  display.display();

  Serial.println();
  Serial.println(F("======================================"));
  Serial.println(F("  MPU6050 EKSEN TESTI"));
  Serial.println(F("======================================"));

  bool ok = false;
  for (int i = 0; i < 8; i++) {
    if (initMPU()) { ok = true; break; }
    Serial.print(F("# initMPU deneme "));
    Serial.print(i + 1);
    Serial.println(F(" basarisiz, tekrar deneniyor..."));
    delay(250);
  }
  if (!ok) {
    display.clearDisplay();
    display.setCursor(0, 20);
    display.setTextSize(2);
    display.print(F("MPU HATA"));
    display.display();
    Serial.println(F("# MPU baglanamadi, dur."));
    while (true);
  }

  delay(500);
  calibrate();

  Serial.println();
  Serial.println(F("--------------------------------------"));
  Serial.println(F("MAX ACI VE EKSEN TESTI"));
  Serial.println();
  Serial.println(F("SENARYO A (cihaz tahtaya monte):"));
  Serial.println(F("  Tahta tek eksenli yuvarlandigi icin yalnizca"));
  Serial.println(F("  RMAX veya PMAX'tan biri yukselir, digeri ~0 kalir."));
  Serial.println(F("  Yukselen deger = tahtanin mekanik max acisi."));
  Serial.println();
  Serial.println(F("SENARYO B (cihaz elde, manuel):"));
  Serial.println(F("  Cihazi 4 yone yatirin; her iki MAX da yukselir."));
  Serial.println(F("  Bu sensorun fiziksel kapasitesini gosterir."));
  Serial.println();
  Serial.println(F("Hareket ettirirken R/P degismiyorsa AcX/Y/Z'ye bakin:"));
  Serial.println(F("  Hic degismiyorsa donanim sorunu (sensor doyumda)."));
  Serial.println(F("--------------------------------------"));
  Serial.println(F("Roll\tPitch\tRMAX\tPMAX\tAcX\tAcY\tAcZ"));

  lastTime = millis();
}

// Mutlak max takibi
float maxRoll  = 0.0;
float maxPitch = 0.0;

void loop() {
  updateFilter();

  float roll  = angleX - angleXOffset;
  float pitch = angleY - angleYOffset;

  // Mutlak maksimumlari guncelle
  if (fabs(roll)  > maxRoll)  maxRoll  = fabs(roll);
  if (fabs(pitch) > maxPitch) maxPitch = fabs(pitch);

  // Seri porta her 100 ms
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 100) {
    lastPrint = millis();
    Serial.print(roll, 2);     Serial.print('\t');
    Serial.print(pitch, 2);    Serial.print('\t');
    Serial.print(maxRoll, 2);  Serial.print('\t');
    Serial.print(maxPitch, 2); Serial.print('\t');
    Serial.print(lastAcX);     Serial.print('\t');
    Serial.print(lastAcY);     Serial.print('\t');
    Serial.println(lastAcZ);
  }

  // OLED her 200 ms
  static unsigned long lastDisp = 0;
  if (millis() - lastDisp > 200) {
    lastDisp = millis();
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    // Üst satir: o anki Roll ve Pitch
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print(F("R:"));
    display.print(roll, 1);
    display.setCursor(64, 0);
    display.print(F("P:"));
    display.print(pitch, 1);

    // Orta: MAX degerler (büyük yazı)
    display.setTextSize(2);
    display.setCursor(0, 16);
    display.print(F("RMAX:"));
    display.print(maxRoll, 1);

    display.setCursor(0, 40);
    display.print(F("PMAX:"));
    display.print(maxPitch, 1);

    display.display();
  }

  delay(10);
}
