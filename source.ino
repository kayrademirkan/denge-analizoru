#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

#define MPU 0x68
#define IR_PIN 8
#define BUZZER_PIN 7

// Kumanda Kodlari
#define KEY_OK     0xE31CFF00UL
#define KEY_RIGHT  0xA55AFF00UL
#define KEY_LEFT   0xF708FF00UL
#define KEY_UP     0xE718FF00UL
#define KEY_DOWN   0xAD52FF00UL

#define KEY_0      0xE619FF00UL
// KEY_0_ALT: ozel IR decoder'in 0 tusunu uzun/zayif basta kaydirmali
// okumasindan dogan empirik degerdir. Diger alt kodlarla ayni kategori.
#define KEY_0_ALT  0x619FF00FUL
#define KEY_1      0xBA45FF00UL
#define KEY_2      0xB946FF00UL
#define KEY_3      0xB847FF00UL
#define KEY_POWER  0xF20DFF00UL   // # tusu

// NEC protokolunde tus basili tutuldugunda gonderilen tekrar kodu
#define KEY_REPEAT 0xFFFFFFFFUL

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

bool sagSolModu = true;   // true = SAG-SOL, false = ON-ARKA
bool sistemAcik = true;

float gyroXOffset = 0;
float gyroYOffset = 0;

float angleX = 0;
float angleY = 0;

float angleXOffset = 0;
float angleYOffset = 0;

unsigned long lastTime = 0;
unsigned long lastIRTime = 0;

// Debug: son okunan ham MPU degerleri
int16_t lastAcX = 0, lastAcY = 0, lastAcZ = 0;

const float alpha = 0.96;
const unsigned long measurementTime = 10000; // 10 saniye

void setup() {
  // Pil ile aciliste 9V regulator rampa hizi USB'den daha yavastir.
  // Sensor + OLED + IR'nin VCC stabil hale gelmesi icin baslangic gecikmesi.
  delay(300);

  Wire.begin();
  Serial.begin(115200);

  pinMode(IR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("OLED HATA"));
    while (true);
  }

  showText(F("SISTEM"), F("BASLIYOR"));

  // MPU6050 ilk acilista hazir olmayabilir (ozellikle 9V pille).
  // Birkaç deneme yap, her basarisizlikta kisa bekle.
  bool mpuOk = false;
  for (int i = 0; i < 8; i++) {
    if (initMPU()) {
      mpuOk = true;
      Serial.print(F("# initMPU basarili (deneme="));
      Serial.print(i + 1);
      Serial.println(F(")"));
      break;
    }
    Serial.print(F("# initMPU deneme "));
    Serial.print(i + 1);
    Serial.println(F(" basarisiz, tekrar deneniyor..."));
    delay(250);
  }

  if (!mpuOk) {
    showText(F("MPU6050"), F("HATA"));
    while (true);
  }

  delay(1000);

  calibrateAll();

  lastTime = millis();
  showReadyScreen();
}

void loop() {
  unsigned long irCode = readIR();

  if (irCode != 0 && irCode != KEY_REPEAT && millis() - lastIRTime > 250) {
    lastIRTime = millis();

    Serial.print(F("IR: "));
    Serial.println(irCode, HEX);

    handleRemote(irCode);
  }

  if (!sistemAcik) {
    delay(50);
    return;
  }

  updateFilter();

  delay(10);
}

unsigned long readIR() {
  if (digitalRead(IR_PIN) != LOW) {
    return 0;
  }

  unsigned long startTime = micros();

  while (digitalRead(IR_PIN) == LOW) {
    if (micros() - startTime > 12000) return 0;
  }

  delayMicroseconds(4500);

  unsigned long data = 0;

  for (int i = 0; i < 32; i++) {
    unsigned long timeout = micros();

    while (digitalRead(IR_PIN) == LOW) {
      if (micros() - timeout > 3000) return 0;
    }

    unsigned long highStart = micros();

    while (digitalRead(IR_PIN) == HIGH) {
      if (micros() - highStart > 3000) break;
    }

    unsigned long highTime = micros() - highStart;

    if (highTime > 1000) {
      data |= (1UL << i);
    }
  }

  return data;
}

void handleRemote(unsigned long code) {

  // POWER (#) - bit-banging IR decoder, IRremote kutuphanesi olmadigi icin
  // ayni tusu farkli bit dizileri olarak okuyabiliyor. Gozlenen tum varyantlari
  // KEY_POWER ailesine ekledik; her durumda dogru sekilde toggle eder.
  if (
    code == KEY_POWER ||
    code == 0xFFF906FEUL ||
    code == 0xFFFE41BFUL ||
    code == 0xFFFC837FUL ||
    code == 0xC837EE00UL ||
    code == 0xFFFF906FUL ||
    code == 0xFFFF20DFUL ||
    code == 0xFFE41BFEUL
  ) {
    sistemAcik = !sistemAcik;

    if (sistemAcik) {
      display.ssd1306_command(SSD1306_DISPLAYON);
      mpuWake();
      lastTime = millis();
      showText(F("SISTEM"), F("ACILDI"));
      delay(800);
      showReadyScreen();
    } else {
      showClosedScreen();
      delay(800);
      display.ssd1306_command(SSD1306_DISPLAYOFF);
      mpuSleep();
    }
    return;
  }

  if (!sistemAcik) return;

  // OK -> olcum baslat
  if (code == KEY_OK) {
    startMeasurement();
  }

  // SAG / 1
  else if (
    code == KEY_RIGHT ||
    code == KEY_1 ||
    code == 0xFFE956BFUL ||
    code == 0xFFD2AD7EUL
  ) {
    sagSolModu = true;
    showReadyScreen();
  }

  // SOL / 2
  else if (
    code == KEY_LEFT ||
    code == KEY_2 ||
    code == 0xFFFDC23FUL ||
    code == 0x7FFFFFFFUL ||
    code == 0xFFEE51BFUL ||
    code == 0xFFDCA37EUL
  ) {
    sagSolModu = false;
    showReadyScreen();
  }

  // KALIBRASYON (0)
  // NOT: NEC repeat kodu (0xFFFFFFFF) buraya eklenmemeli;
  // herhangi bir tus basili tutulunca istemsiz kalibrasyon tetiklenir.
  else if (code == KEY_0 || code == KEY_0_ALT) {
    calibrateAll();
    showReadyScreen();
  }

  // MENU (3 + yukari + asagi) -> ana ekrana don
  else if (
    code == KEY_3 ||
    code == KEY_UP ||
    code == KEY_DOWN ||
    code == 0xFFEE11FFUL
  ) {
    showReadyScreen();
  }

  else {
    Serial.print(F("Bilinmeyen tus: "));
    Serial.println(code, HEX);
  }
}

bool initMPU() {
  // PWR_MGMT_1: uyku modunu kapat
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  if (Wire.endTransmission(true) != 0) {
    Serial.println(F("# initMPU: PWR_MGMT_1 yazimi BASARISIZ"));
    return false;
  }

  // WHO_AM_I (0x75) kontrolu - tanidik degerleri yaz, ama init'i durdurma
  Wire.beginTransmission(MPU);
  Wire.write(0x75);
  Wire.endTransmission(false);
  uint8_t got = Wire.requestFrom((uint8_t)MPU, (uint8_t)1, (uint8_t)true);
  uint8_t whoami = (got > 0) ? Wire.read() : 0xFF;
  Serial.print(F("# WHO_AM_I = 0x"));
  Serial.println(whoami, HEX);

  // GYRO_CONFIG (0x1B) = 0x00 -> +-250 deg/s, hassasiyet 131 LSB/(deg/s)
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(0x00);
  Wire.endTransmission(true);

  // ACCEL_CONFIG (0x1C) = 0x00 -> +-2g, hassasiyet 16384 LSB/g
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0x00);
  Wire.endTransmission(true);

  // NOT: DLPF (0x1A) ve SMPLRT_DIV (0x19) yazimi BAZI klon chiplerde
  // standart-disi davranisa neden oluyordu (accel kanallari sature). Default
  // degerlerle birakiyoruz; gerektiginde dikkatli sekilde tekrar eklenebilir.

  return true;
}

// MPU6050 SLEEP modu: PWR_MGMT_1 register'inda SLEEP biti (0x40) set edilir.
// Tipik akim ~3.5 mA -> ~5 uA. GYRO_CONFIG ve ACCEL_CONFIG ayarlari korunur.
void mpuSleep() {
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0x40);
  Wire.endTransmission(true);
}

// SLEEP bitini temizle ve sensorun kararli hale gelmesi icin kisa sure bekle.
void mpuWake() {
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  delay(50);
}

void readMPU(int16_t &AcX, int16_t &AcY, int16_t &AcZ, int16_t &GyX, int16_t &GyY, int16_t &GyZ) {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  uint8_t got = Wire.requestFrom((uint8_t)MPU, (uint8_t)14, (uint8_t)true);

  if (got < 14) {
    // I2C okuma basarisiz: degerleri 0'a cek ki sahte sabit veri uretmesin
    AcX = AcY = AcZ = 0;
    GyX = GyY = GyZ = 0;
    return;
  }

  // Evaluation order garantisi icin ayri satirlar
  uint8_t hi, lo;
  hi = Wire.read(); lo = Wire.read(); AcX = (int16_t)((hi << 8) | lo);
  hi = Wire.read(); lo = Wire.read(); AcY = (int16_t)((hi << 8) | lo);
  hi = Wire.read(); lo = Wire.read(); AcZ = (int16_t)((hi << 8) | lo);

  Wire.read(); Wire.read();  // TEMP, atlanir

  hi = Wire.read(); lo = Wire.read(); GyX = (int16_t)((hi << 8) | lo);
  hi = Wire.read(); lo = Wire.read(); GyY = (int16_t)((hi << 8) | lo);
  hi = Wire.read(); lo = Wire.read(); GyZ = (int16_t)((hi << 8) | lo);

  lastAcX = AcX;
  lastAcY = AcY;
  lastAcZ = AcZ;
}

void calibrateAll() {
  showText(F("KALIBRASYON"), F("SABIT TUT"));
  delay(700);

  long gxSum = 0;
  long gySum = 0;

  const int samples = 1000;

  for (int i = 0; i < samples; i++) {
    int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;
    readMPU(AcX, AcY, AcZ, GyX, GyY, GyZ);

    gxSum += GyX;
    gySum += GyY;

    delay(2);
  }

  gyroXOffset = gxSum / (float)samples;
  gyroYOffset = gySum / (float)samples;

  angleX = 0;
  angleY = 0;
  lastTime = millis();

  for (int i = 0; i < 200; i++) {
    updateFilter();
    delay(5);
  }

  angleXOffset = angleX;
  angleYOffset = angleY;

  // Teshis: kalibrasyon sonrasi durum
  Serial.println(F("# KALIBRASYON_TAMAM"));
  Serial.print(F("# gyroXOffset=")); Serial.println(gyroXOffset, 2);
  Serial.print(F("# gyroYOffset=")); Serial.println(gyroYOffset, 2);
  Serial.print(F("# angleXOffset=")); Serial.println(angleXOffset, 3);
  Serial.print(F("# angleYOffset=")); Serial.println(angleYOffset, 3);

  // MPU saglik kontrolu: ham bir okuma yazdir
  int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;
  readMPU(AcX, AcY, AcZ, GyX, GyY, GyZ);
  Serial.print(F("# RAW AcX=")); Serial.print(AcX);
  Serial.print(F(" AcY="));      Serial.print(AcY);
  Serial.print(F(" AcZ="));      Serial.print(AcZ);
  Serial.print(F(" GyX="));      Serial.print(GyX);
  Serial.print(F(" GyY="));      Serial.print(GyY);
  Serial.print(F(" GyZ="));      Serial.println(GyZ);

  showText(F("KALIBRASYON"), F("TAMAM"));
  beepCalibrationDone();
  delay(1000);
}

void updateFilter() {
  int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;
  readMPU(AcX, AcY, AcZ, GyX, GyY, GyZ);

  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;
  lastTime = now;

  if (dt <= 0 || dt > 0.2) {
    dt = 0.01;
  }

  float gyroXRate = (GyX - gyroXOffset) / 131.0;
  float gyroYRate = (GyY - gyroYOffset) / 131.0;

  float accAngleX = atan2((float)AcY, (float)AcZ) * 180.0 / PI;
  float accAngleY = atan2((float)AcX, (float)AcZ) * 180.0 / PI;

  angleX = alpha * (angleX + gyroXRate * dt) + (1.0 - alpha) * accAngleX;
  angleY = alpha * (angleY + gyroYRate * dt) + (1.0 - alpha) * accAngleY;
}

float getCurrentAngle() {
  // Denge tahtasi tek eksenli pivot ile yapilmistir; tahta her iki modda
  // da AYNI sensor ekseninde (Roll = angleX) yatar.
  // Kullanici "90 derece donme" protokolu (Bolum 5.7) ile vucut salinim
  // yonunu tahta eksenine hizalar; bu yuzden ÖN-ARKA modunda da
  // sensorden ayni ekseni (angleX) okuyoruz. Mod secimi sadece sonuc
  // ekranindaki yon etiketini (SAG/SOL veya ON/ARKA) degistirir.
  return angleX - angleXOffset;
}

void startMeasurement() {
  showText(F("OLCUM"), F("BASLIYOR"));
  beepStartMeasurement();
  delay(700);

  float toplamMutlak = 0;
  float toplamSigned = 0;
  float maxSapma = 0;
  float oncekiAci = getCurrentAngle();
  float hareketToplami = 0;

  int count = 0;

  Serial.println(F("# OLCUM_BASLADI"));
  Serial.print(F("# MOD: "));
  Serial.println(sagSolModu ? F("SAG-SOL") : F("ON-ARKA"));
  // Hata teshisi icin her iki ekseni de yazdiriyoruz:
  //   aci_deg = aktif moddaki secilen eksen (offset dusurulmus)
  //   roll    = angleX - angleXOffset (sag-sol filtreli)
  //   pitch   = angleY - angleYOffset (on-arka filtreli)
  Serial.println(F("# t_ms,aci_deg,roll,pitch,AcX,AcY,AcZ"));

  unsigned long startTime = millis();

  while (millis() - startTime < measurementTime) {
    updateFilter();

    float angle = getCurrentAngle();
    float absAngle = fabs(angle);

    toplamMutlak += absAngle;
    toplamSigned += angle;

    if (absAngle > maxSapma) {
      maxSapma = absAngle;
    }

    hareketToplami += fabs(angle - oncekiAci);
    oncekiAci = angle;

    count++;

    // Veri akisi: PC arayuzu (C#/Processing) veya Serial Plotter icin
    // + ham AcX/AcY/AcZ (donanim teshisi: hareket ettirince degisiyor mu?)
    Serial.print(millis() - startTime);
    Serial.print(',');
    Serial.print(angle, 3);
    Serial.print(',');
    Serial.print(angleX - angleXOffset, 3);
    Serial.print(',');
    Serial.print(angleY - angleYOffset, 3);
    Serial.print(',');
    Serial.print(lastAcX);
    Serial.print(',');
    Serial.print(lastAcY);
    Serial.print(',');
    Serial.println(lastAcZ);

    int kalan = 10 - ((millis() - startTime) / 1000);
    if (kalan < 0) kalan = 0;

    showMeasuringScreen(kalan);

    delay(50);
  }

  float ortalamaMutlak = toplamMutlak / count;
  float ortalamaSigned = toplamSigned / count;
  float stabilite = hareketToplami / count;

  int skor = calculateScore(ortalamaMutlak, maxSapma, stabilite);

  // Sonuc ozeti seri porta (debug + arayuz icin)
  Serial.println(F("# OLCUM_BITTI"));
  Serial.print(F("# ornek="));         Serial.println(count);
  Serial.print(F("# ortalama_signed="));Serial.println(ortalamaSigned, 3);
  Serial.print(F("# ortalama_mutlak="));Serial.println(ortalamaMutlak, 3);
  Serial.print(F("# max_sapma="));     Serial.println(maxSapma, 3);
  Serial.print(F("# stabilite="));     Serial.println(stabilite, 3);
  Serial.print(F("# skor="));          Serial.println(skor);

  beepEndMeasurement();
  showResult(ortalamaSigned, ortalamaMutlak, maxSapma, stabilite, skor);
}

int calculateScore(float ortalama, float maxSapma, float stabilite) {
  int skor = 100 - (ortalama * 5) - (maxSapma * 2) - (stabilite * 8);

  if (skor > 100) skor = 100;
  if (skor < 0) skor = 0;

  return skor;
}

void showReadyScreen() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(15, 4);

  if (sagSolModu) {
    display.print(F("SAG-SOL"));
  } else {
    display.print(F("ON-ARKA"));
  }

  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print(F("OK: OLCUM"));

  display.setCursor(0, 42);
  display.print(F("1/SAG: SAG-SOL"));

  display.setCursor(0, 53);
  display.print(F("2/SOL 0:KALIB"));

  display.display();
}

void showClosedScreen() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(20, 18);
  display.print(F("KAPALI"));

  display.setTextSize(1);
  display.setCursor(20, 48);
  display.print(F("# ile ac"));

  display.display();
}

void showMeasuringScreen(int kalan) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);

  if (sagSolModu) {
    display.print(F("MOD: SAG-SOL"));
  } else {
    display.print(F("MOD: ON-ARKA"));
  }

  display.setTextSize(2);
  display.setCursor(15, 22);
  display.print(F("OLCUM"));

  display.setCursor(35, 45);
  display.print(kalan);
  display.print(F(" SN"));

  display.display();
}

void showResult(float signedAngle, float avgAngle, float maxAngle, float stabilite, int skor) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);

  if (sagSolModu) {
    if (signedAngle >= 0) {
      display.setCursor(35, 0);
      display.print(F("SAG"));
    } else {
      display.setCursor(35, 0);
      display.print(F("SOL"));
    }
  } else {
    if (signedAngle >= 0) {
      display.setCursor(45, 0);
      display.print(F("ON"));
    } else {
      display.setCursor(25, 0);
      display.print(F("ARKA"));
    }
  }

  display.setCursor(25, 22);
  display.print(avgAngle, 1);
  display.print(F(" D"));

  display.setTextSize(1);
  display.setCursor(0, 45);
  display.print(F("MAX:"));
  display.print(maxAngle, 1);

  display.setCursor(68, 45);
  display.print(F("SKOR:"));
  display.print(skor);

  display.setCursor(0, 56);
  display.print(F("STAB:"));
  display.print(stabilite, 2);

  display.display();

  // 15 sn boyunca sonucu goster, herhangi bir IR tusu gelirse hemen islet.
  // Eski blocking delay(15000) sonuc ekraninda power dahil tum tuslari oluyordu.
  unsigned long resultStart = millis();
  while (millis() - resultStart < 15000) {
    unsigned long irCode = readIR();
    if (irCode != 0 && irCode != KEY_REPEAT && millis() - lastIRTime > 250) {
      lastIRTime = millis();
      handleRemote(irCode);
      return;
    }
    delay(10);
  }
  showReadyScreen();
}

void showText(const __FlashStringHelper* line1, const __FlashStringHelper* line2) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(20, 15);
  display.print(line1);

  display.setTextSize(2);
  display.setCursor(15, 35);
  display.print(line2);

  display.display();
}

// ---- Buzzer ----
// Kucuk pasif piezo buzzer'larin rezonansi tipik olarak 2.5-3 kHz arasidir.
// Bu frekanslar maksimum ses seviyesi icin secilmistir.
// tone() pasif buzzer icin idealdir; aktif buzzer'da da sorunsuz tetiklenir.
void beep(unsigned int freq, unsigned long durationMs) {
  tone(BUZZER_PIN, freq, durationMs);
  delay(durationMs);
  noTone(BUZZER_PIN);
}

void beepStartMeasurement() {
  beep(2700, 120);
}

void beepEndMeasurement() {
  beep(2700, 800);
}

void beepCalibrationDone() {
  for (int i = 0; i < 3; i++) {
    beep(2700, 80);
    if (i < 2) delay(80);
  }
}