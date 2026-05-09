# Sensör Tabanlı Dijital Denge Analizörü

> Düşük maliyetli, taşınabilir bir **postürografi** cihazı. ATmega328P + MPU6050 + Tamamlayıcı Filtre tabanlı; vücut salınım açılarını ölçüp 0–100 arası bir denge skoru üretir.

![Status](https://img.shields.io/badge/durum-prototip-success)
![Platform](https://img.shields.io/badge/platform-Arduino_Uno-blue)
![Language](https://img.shields.io/badge/dil-C%2B%2B-orange)
![License](https://img.shields.io/badge/lisans-MIT-green)
![Cost](https://img.shields.io/badge/maliyet-~1300_TL-yellow)

---

## 📖 Özet

Klinik düzeydeki postürografi cihazları **350 000 TL'den** başlıyor, büyük ve taşınmaz. Bu proje, aynı temel ölçüm işlevini **~1 300 TL**'lik donanımla, 9 V pille **10 saat** çalışan, host-bağımsız bir cihazda gerçekleştiriyor. **MPU6050** 6 eksenli IMU'dan alınan ham veri, gömülü C/C++ yazılımı içinde **Tamamlayıcı Filtre** ile birleştiriliyor; sonuçlar yerel OLED ekranda ve seri portta CSV olarak sunuluyor.

> **Not:** Bu cihaz klinik tanı aracı **değildir**; bireysel takip ve göreceli karşılaştırma için tasarlanmış bir eğitim/araştırma prototipidir.

## 📖 Abstract (English)

A low-cost (~40 USD), portable posturography device based on the **ATmega328P** microcontroller and **MPU6050** 6-axis MEMS IMU. Raw acceleration and angular velocity data are fused via a **Complementary Filter** to compute body sway angles in real time. Results are displayed on a 128×64 OLED and streamed as CSV over USART (115 200 baud). The device runs ~10 hours on a single 9 V alkaline battery thanks to a software low-power standby mode (MPU SLEEP + OLED DISPLAYOFF). Total bill of materials is approximately 1 300 TRY (~40 USD), about 1/250th the cost of clinical posturography platforms.

---

## ✨ Özellikler

- 🎯 **±0,5° hassasiyetle** statik açı ölçümü
- ⚡ **Tamamlayıcı Filtre** ile sensör füzyonu (α = 0,96)
- 🔋 **9 V pil ile ~10 saat** çalışma süresi (saha gözlemi)
- 💤 Yazılımsal **bekleme modu** (akım: 85 mA → 45 mA)
- 📺 **128×64 OLED** üzerinde gerçek zamanlı görsel geri bildirim
- 🔊 **Pasif piezo buzzer** ile işitsel onay (ölçüm başı/sonu/kalibrasyon)
- 🎮 **21 butonlu IR kumanda** ile temassız kullanım
- 📊 **CSV veri akışı** (115 200 baud) — Arduino IDE Serial Plotter, Excel, Python uyumlu
- 🛠 **İki modlu ölçüm**: SAĞ-SOL (Roll) veya ÖN-ARKA (Pitch)
- 🔄 **İki aşamalı otomatik kalibrasyon** (gyro bias + açı referansı)

---

## 🔧 Donanım Gereksinimleri

| Bileşen | Model | Adet | Birim Maliyet (TL) |
|---------|-------|------|---------------------|
| Mikrodenetleyici | Arduino Uno R3 | 1 | ~600 |
| IMU sensör | MPU6050 (SY-104 modülü) | 1 | ~120 |
| OLED ekran | SSD1306 0,96″ I²C | 1 | ~150 |
| IR alıcı + kumanda kiti | 1838B + 21 buton | 1 | ~120 |
| Pasif buzzer | 12 mm piezo | 1 | ~30 |
| 9 V pil + tutucu | Alkalin | 1 | ~80 |
| Breadboard + jumper | – | – | ~80 |
| Mekanik (denge tahtası) | MDF + PVC pivot + L köşebent | – | ~120 |
| **TOPLAM** | | | **~1 300 TL** |

### Pin Haritası

| Bileşen | Arduino Uno Pini |
|---------|------------------|
| MPU6050 SDA / OLED SDA | A4 (paylaşımlı I²C) |
| MPU6050 SCL / OLED SCL | A5 (paylaşımlı I²C) |
| 1838B IR alıcı OUT | D8 |
| Pasif buzzer (+) | D7 |
| Tüm VCC | 5 V |
| Tüm GND | GND |

---

## 📥 Kurulum

### 1. Yazılım

#### Gerekli kütüphaneler (Arduino IDE → Library Manager)

- `Wire` (Arduino çekirdek)
- `Adafruit GFX Library`
- `Adafruit SSD1306`

#### Derleme ve yükleme

```bash
git clone https://github.com/kullanici-adi/denge-analizoru.git
cd denge-analizoru
```

1. Arduino IDE'de `dengeanal.ino` dosyasını aç
2. **Tools → Board → Arduino Uno** seç
3. **Tools → Port → /dev/ttyUSB0** (veya COM portunuz) seç
4. **Upload** (▶) butonu ile yükle

### 2. Donanım Bağlantısı

EK-D'deki Wokwi devre şemasını takip et: [PROJE_RAPORU.md](PROJE_RAPORU.md) — Bölüm 4.5 ve 4.6.

---

## 🎮 Kullanım

### İlk Açılış

1. Cihaza güç ver (USB veya 9 V pil)
2. **2 saniye sabit tut** — otomatik kalibrasyon (3 vuruşluk bip sesi = tamam)
3. OLED'de **"SAĞ-SOL"** moduna düştüğünü gör

### Ölçüm Almak

| Tuş | İşlev |
|-----|-------|
| **OK** | 10 saniyelik ölçümü başlat |
| **1 / SAĞ** | SAĞ-SOL moduna geç |
| **2 / SOL** | ÖN-ARKA moduna geç |
| **0** | Yeniden kalibrasyon |
| **#** | Bekleme moduna gir / çıkar |

### Sonuç Yorumlama

| Skor | Anlam |
|------|-------|
| 85 – 95 | İyi denge |
| 65 – 85 | Orta (gözler kapalı sağlıklı kişi) |
| 35 – 65 | Hafif denge zorluğu |
| 0 – 35 | Belirgin sallanma |

> Skor klinik tanı aracı **değildir**, kişisel takip için göreli bir performans göstergesidir.

---

## 📂 Klasör Yapısı

```
denge/
├── README.md                          # Bu dosya
├── LICENSE                            # MIT lisansı
├── dengeanal.ino                      # Ana firmware (Arduino sketch)
├── eksen_test/
│   └── eksen_test.ino                 # Eksen ve maksimum açı test sketch'i
├── PROJE_RAPORU.md                    # Detaylı proje raporu (akademik)
├── MikroProje.pdf                     # Raporun PDF sürümü (34 sayfa)
├── BILIMSEL_MAKALE.md                 # IEEE konferans makalesi taslağı
├── SUNUM_TASLAGI.md                   # 15 slayt sunum taslağı + Claude prompt
└── SUNUM_BILGILERI.md                 # Jüri savunması rehberi (FAQ + ipuçları)
```

---

## 📊 Teknik Detaylar

### Tamamlayıcı Filtre

Yüksek frekans gürültü (ivmeölçer) ve uzun vadeli sapma (jiroskop) sorunlarını eş zamanlı çözer:

$$\theta_{yeni} = \alpha \cdot (\theta_{eski} + \omega \cdot \Delta t) + (1 - \alpha) \cdot \theta_{ivme}$$

Bu projede $\alpha = 0{,}96$ — yani tahminin %96'sı jiroskop integralinden, %4'ü ivmeölçerden gelir. Filtre zaman sabiti $\tau \approx 1{,}22$ s.

### Skor Formülü

$$\text{Skor} = \max\left(0,\ \min\left(100,\ 100 - 5 \cdot \overline{|\theta|} - 2 \cdot \theta_{\max} - 8 \cdot S\right)\right)$$

burada:
- $\overline{|\theta|}$: ortalama mutlak sapma
- $\theta_{\max}$: pik sapma
- $S$: hareket toplamı (stabilite indeksi)

### Seri Port Veri Formatı

Ölçüm boyunca **115 200 baud** üzerinden CSV akışı:

```
# OLCUM_BASLADI
# MOD: SAG-SOL
# t_ms,aci_deg,roll,pitch,AcX,AcY,AcZ
3,0.010,0.010,0.017,12456,10812,-3436
106,0.047,0.047,0.017,12488,10844,-3532
...
# OLCUM_BITTI
# ortalama_mutlak=0.823
# max_sapma=2.341
# stabilite=0.124
# skor=92
```

---

## 🎓 Akademik Bilgiler

| Alan | Değer |
|------|-------|
| **Kurum** | Ege Üniversitesi, Tire Kutsan Meslek Yüksekokulu |
| **Program** | Bilgisayar Programcılığı |
| **Ders** | Mikrodenetleyiciler |
| **Dönem** | 2025–2026 Bahar |
| **Hazırlayanlar** | Kayra DEMİRKAN (60240000050), Samet TOKDEMİR (61230000118) |
| **Danışman** | Prof. Dr. Ahmet KAYA |

### Akademik Çıktılar

- 📄 **34 sayfa proje raporu** ([MikroProje.pdf](MikroProje.pdf))
- 📑 **IEEE konferans makalesi taslağı** ([BILIMSEL_MAKALE.md](BILIMSEL_MAKALE.md))
- 🎤 **15 slayt sunum** ([SUNUM_TASLAGI.md](SUNUM_TASLAGI.md))

---

## 🚧 Bilinen Sınırlılıklar

- Tek eksenli mekanik pivot — ÖN-ARKA modunda kullanıcının tahta üzerinde 90° dönmesi gerekir
- Çoklu denek üzerinde istatistiksel doğrulama yapılmadı
- Multimetre ile bileşen-bazlı akım ölçümü yapılmadı (datasheet temelli tahmin)
- Cihaz üzerinde kalıcı veri kaydı yok (yalnızca ekran + seri port)
- Klinik referans cihazlarla karşılaştırma yapılmadı

## 🔮 Gelecek Geliştirmeler

- [ ] **Çift eksenli (küresel) pivot** — 90° dönme gereksinimini ortadan kaldırır
- [ ] **SD kart entegrasyonu** — uzun süreli takip için kalıcı kayıt
- [ ] **Bluetooth Low Energy (BLE)** — akıllı telefon uygulaması
- [ ] **Lityum-iyon batarya + buck regülatör** — daha uzun pil ömrü
- [ ] **PC arayüz yazılımı** — Processing/C# tabanlı gerçek zamanlı görselleştirme
- [ ] **Klinik validasyon çalışması** — altın standart cihazlarla karşılaştırma

---

## 📄 Lisans

Bu proje **MIT Lisansı** ile yayınlanmıştır. Detaylar için [LICENSE](LICENSE) dosyasına bakınız.

Akademik çalışmalarda atıf vermek için:

```
Demirkan, K. & Tokdemir, S. (2026). Sensör Tabanlı Dijital Denge Analizörü.
Ege Üniversitesi Tire Kutsan MYO, Bilgisayar Programcılığı Programı,
Mikrodenetleyiciler Dersi Dönem Projesi.
```

## 🙏 Teşekkür

Bu çalışma, Ege Üniversitesi Tire Kutsan Meslek Yüksekokulu Mikrodenetleyiciler Dersi 2025–2026 Bahar Dönemi kapsamında gerçekleştirilmiştir. Yazarlar, ders danışmanı **Prof. Dr. Ahmet KAYA**'ya teorik ve uygulamalı yönlendirmeleri için teşekkür eder.

## 📬 İletişim

Soru, öneri veya katkı için issue açabilir veya pull request gönderebilirsiniz.

---

<p align="center">
  <i>Sağlık bilimleri, postürografi ve eğitim alanlarında erişilebilir teknoloji için.</i>
</p>
