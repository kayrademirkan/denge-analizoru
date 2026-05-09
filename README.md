# Sensor-Based Digital Balance Analyzer

Düşük maliyetli, taşınabilir bir postürografi cihazı. ATmega328P mikrodenetleyici ve MPU6050 6 eksenli MEMS hareket işleme birimi tabanlı; Tamamlayıcı Filtre algoritması ile vücut salınım açılarını gerçek zamanlı olarak ölçer ve normalize bir denge skoru üretir.

![Status](https://img.shields.io/badge/status-prototype-success)
![Platform](https://img.shields.io/badge/platform-Arduino_Uno-blue)
![Language](https://img.shields.io/badge/language-C%2B%2B-orange)
![License](https://img.shields.io/badge/license-MIT-green)

---

## Abstract

This repository hosts the firmware and academic documentation of a low-cost, portable posturography device developed as a term project for the Microcontrollers course at Ege University, Tire Kutsan Vocational School (Computer Programming Program). The device is built around an 8-bit AVR ATmega328P microcontroller and an InvenSense MPU6050 6-axis MEMS Inertial Measurement Unit (IMU). Raw acceleration and angular velocity data are fused via a Complementary Filter (alpha = 0.96) to obtain body sway angles in real time. A 128x64 SSD1306 OLED display, an NEC infrared remote receiver and a passive piezoelectric buzzer provide a fully self-contained, host-independent user interface. Results are also streamed as CSV over USART at 115 200 baud for downstream analysis. The complete bill of materials is approximately 1 300 TRY, which is roughly 0.4% of the cost of clinical-grade posturography platforms. The prototype achieves about 10 hours of continuous operation on a single 9 V alkaline battery thanks to a software low-power standby mode.

> **Disclaimer.** This device is **not** a clinical diagnostic instrument. It is intended exclusively for education, research and individual longitudinal self-tracking. No medical claims are made regarding its output.

---

## Özet

Bu depo, Ege Üniversitesi Tire Kutsan Meslek Yüksekokulu Bilgisayar Programcılığı Programı Mikrodenetleyiciler Dersi kapsamında geliştirilen taşınabilir bir postürografi cihazının gömülü yazılımını ve akademik dokümantasyonunu içermektedir. Sistem, 8 bit AVR mimarisine sahip ATmega328P mikrodenetleyici ile InvenSense MPU6050 6 eksenli MEMS atalet ölçüm birimini temel almaktadır. Sensörden alınan ham ivme ve açısal hız verileri, Tamamlayıcı Filtre algoritması (alfa = 0,96) ile birleştirilerek vücut salınım açıları gerçek zamanlı olarak hesaplanmaktadır. 128x64 SSD1306 OLED ekran, NEC kızılötesi alıcı ve pasif piezoelektrik buzzer; sistemin host bağımsız bir kullanım sunmasını sağlar. Ölçüm verileri ek olarak 115 200 baud üzerinden CSV biçiminde seri porta yayınlanır. Toplam donanım maliyeti yaklaşık 1 300 TL olup klinik düzey postürografi cihazlarının yaklaşık binde dördüne karşılık gelmektedir. Yazılımsal düşük güç bekleme modu sayesinde prototip, 9 V alkalin batarya ile yaklaşık 10 saat kesintisiz çalışabilmektedir.

> **Uyarı.** Bu cihaz klinik bir tanı aracı **değildir**. Yalnızca eğitim, araştırma ve bireysel takip amacıyla geliştirilmiştir. Çıktıları üzerinde herhangi bir tıbbi iddia bulunmamaktadır.

---

## Özellikler

* Statik ölçümlerde +/- 0,5 derece hassasiyet hedefi
* alfa = 0,96 katsayılı Tamamlayıcı Filtre tabanlı sensör füzyonu
* İki aşamalı otomatik kalibrasyon (jiroskop sapma çıkarımı ve referans açı sıfırlaması)
* 9 V alkalin pil ile yaklaşık 10 saat saha çalışma süresi (gözlemsel)
* Yazılımsal bekleme modu (aktif 85 mA, bekleme 45 mA)
* 128x64 SSD1306 OLED üzerinde gerçek zamanlı görsel geri bildirim
* 12 mm pasif piezoelektrik buzzer ile işitsel onay
* 21 butonlu NEC IR uzaktan kumanda ile temassız kullanım
* 115 200 baud CSV veri akışı (Arduino IDE Serial Plotter, Excel, Python uyumlu)
* Tek eksenli ölçüm modu seçimi (SAĞ-SOL veya ÖN-ARKA)
* Bit-banging tabanlı, kütüphanesiz NEC IR çözücüsü (yaklaşık 1 KB SRAM tasarrufu)

---

## Donanım Listesi

| Bileşen | Model | Adet | Tahmini Birim Maliyet (TL) |
|---------|-------|------|----------------------------|
| Mikrodenetleyici kartı | Arduino Uno R3 | 1 | 600 |
| IMU sensör modülü | MPU6050 (SY-104 breakout) | 1 | 120 |
| OLED ekran | 0,96 inç SSD1306 I2C | 1 | 150 |
| IR alıcı + uzaktan kumanda kiti | 1838B (38 kHz) + 21 butonlu kumanda | 1 | 120 |
| Pasif buzzer | 12 mm piezoelektrik | 1 | 30 |
| Güç kaynağı | 9 V alkalin pil + tutucu | 1 | 80 |
| Prototipleme | Breadboard + jumper kablolar | 1 takım | 80 |
| Mekanik yapı | MDF tahta + PVC pivot + L köşebent + silikon tampon | 1 takım | 120 |
| **Toplam** | | | **~ 1 300 TL** |

### Pin Haritası

| Bileşen | Arduino Uno Pini | İşlev |
|---------|------------------|-------|
| MPU6050 (SY-104) SDA | A4 | I2C veri hattı |
| MPU6050 (SY-104) SCL | A5 | I2C saat hattı |
| OLED 0,96 inç SDA | A4 | MPU6050 ile paylaşımlı I2C |
| OLED 0,96 inç SCL | A5 | MPU6050 ile paylaşımlı I2C |
| 1838B IR alıcı OUT | D8 | Demodüle edilmiş sayısal sinyal |
| 12 mm pasif piezo buzzer (+) | D7 | PWM/tone çıkışı |
| Tüm VCC | 5 V | Besleme |
| Tüm GND | GND | Toprak |

I2C hattında MPU6050 (`0x68`) ve OLED (`0x3C`) farklı adreslerde olduğu için tek bir veri yolu paylaşılarak iki cihaz aynı anda yönetilebilmektedir.

---

## Kurulum

### Yazılım Bağımlılıkları

Aşağıdaki kütüphaneler Arduino IDE Library Manager üzerinden kurulmalıdır:

* `Wire` (Arduino çekirdek)
* `Adafruit GFX Library`
* `Adafruit SSD1306`

### Derleme ve Yükleme

```bash
git clone https://github.com/kayrademirkan/denge-analizoru.git
cd denge-analizoru
```

1. Arduino IDE'de `source.ino` dosyasını açınız.
2. **Tools > Board** menüsünden Arduino Uno seçiniz.
3. **Tools > Port** menüsünden ilgili seri portu seçiniz.
4. **Upload** butonu ile firmware'i karta yükleyiniz.

> Arduino IDE, sketch dosyalarının kendi adıyla eşleşen klasör içinde bulunmasını gerektirir. Bu nedenle `source.ino` dosyasını ilk derlemede `source/source.ino` yapısına taşımayı önerebilir; bu uyarıyı kabul edebilirsiniz.

---

## Kullanım

İlk açılışta sistem otomatik olarak iki saniyelik kalibrasyon sürecini başlatır. Bu süre boyunca cihaz hareketsiz tutulmalıdır. Kalibrasyon tamamlandığında üç vuruşluk bir bip sesi ile geri bildirim verilir ve sistem hazır ekranına geçer.

| Kumanda Tuşu | İşlev |
|--------------|-------|
| OK | 10 saniyelik ölçümü başlatır |
| 1 / SAĞ | SAĞ-SOL (Roll) ölçüm moduna geçer |
| 2 / SOL | ÖN-ARKA (Pitch) ölçüm moduna geçer |
| 0 | Yeniden kalibrasyon yapar |
| # | Bekleme moduna girer veya çıkar |

### Ölçüm Sonuçlarının Yorumlanması

| Skor Aralığı | Yorum |
|--------------|-------|
| 85 - 95 | Tipik sağlıklı denge |
| 65 - 85 | Sınırda performans (örneğin gözler kapalı duruş) |
| 35 - 65 | Hafif denge zorluğu |
| 0 - 35 | Belirgin sallanma veya kontrolsüz hareket |

> Skor klinik bir tanı aracı değildir. Bireyin kendi performansını zaman içinde takip etmesi için göreli bir göstergedir.

---

## Algoritmik Temel

### Tamamlayıcı Filtre

İvmeölçer verisinin yüksek frekanslı titreşimden etkilenmesi ve jiroskop verisinin uzun süreli sapma (drift) göstermesi nedeniyle, iki sensör çıktısı aşağıdaki ayrık zamanlı doğrusal birleşim ile füzyonlanmaktadır:

```
theta_yeni = alfa * (theta_eski + omega * dt) + (1 - alfa) * theta_ivme
```

Burada `alfa = 0,96` olarak seçilmiştir. Bu katsayı, kısa vadede jiroskop integraline %96, ivmeölçere %4 ağırlık vermek anlamına gelir. Filtre zaman sabiti `tau = -dt / ln(alfa)` formülüyle hesaplanır ve tipik `dt = 50 ms` için yaklaşık 1,22 saniyedir.

### Skor Hesabı

Ölçüm penceresi sonunda dört temel istatistiksel gösterge tek bir 0-100 arası normalize skora indirgenir:

```
Skor = max(0, min(100, 100 - 5 * ortalama_mutlak - 2 * maksimum_sapma - 8 * stabilite))
```

Katsayılar (5, 2, 8); sağlıklı bireylerde 80 ile 95 arası, denge bozukluğu durumlarında 0 ile 40 arası bir skor üretecek biçimde ampirik olarak belirlenmiştir.

---

## Seri Port Veri Formatı

Cihaz, ölçüm boyunca her bir örneği 115 200 baud üzerinden CSV biçiminde yayınlar:

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

Yorum satırları `#` ile başlar. Veri kolonları sırasıyla: zaman damgası (ms), aktif moddaki açı (derece), Roll (derece), Pitch (derece), ham AcX/AcY/AcZ değerleri (LSB; 16 384 LSB = 1 g).

---

## Bilinen Sınırlılıklar

1. Tek eksenli pivot mekanik tasarım nedeniyle, ÖN-ARKA modunda kullanıcının tahta üzerinde 90 derece dönmüş pozisyonda durması gerekmektedir.
2. Sistem, ölçüm sonuçlarını cihaz üzerinde kalıcı olarak saklamaz; veriler yalnızca anlık olarak ekranda gösterilir ve seri porta yayınlanır.
3. Çoklu denek üzerinde istatistiksel doğrulama ve altın standart cihazlarla karşılaştırmalı validasyon henüz yapılmamıştır.
4. Bileşen bazlı akım ölçümleri multimetre ile doğrulanmamış, üretici datasheet değerleri esas alınmıştır.
5. Bazı klon MPU6050 entegrelerinin standart-dışı davranışı nedeniyle dahili dijital alçak geçiren filtre (DLPF) varsayılan halinde bırakılmıştır.

---

## Gelecek Çalışmalar

* Çift eksenli (küresel) pivot mekanizması ile eş zamanlı Roll ve Pitch ölçümü
* SD kart entegrasyonu ile uzun süreli ölçüm kaydı
* Bluetooth Low Energy (BLE) modülü üzerinden akıllı telefon arayüzü
* Lityum-iyon batarya ve buck regülatör ile uzatılmış pil ömrü
* Yetkili sağlık kurumları ile klinik validasyon çalışması
* Processing veya C# tabanlı bilgisayar arayüz yazılımı

---

## Akademik Bilgiler

| Alan | Değer |
|------|-------|
| Kurum | Ege Üniversitesi, Tire Kutsan Meslek Yüksekokulu |
| Program | Bilgisayar Programcılığı |
| Ders | Mikrodenetleyiciler |
| Akademik Dönem | 2025-2026 Bahar |
| Hazırlayanlar | Kayra DEMİRKAN (60240000050), Samet TOKDEMİR (61230000118) |
| Danışman | Prof. Dr. Ahmet KAYA |

Detaylı 34 sayfalık akademik proje raporu için [`MikroProje.pdf`](MikroProje.pdf) dosyasına başvurunuz.

### Atıf

Bu çalışmaya akademik atıf yapmak için aşağıdaki biçim önerilmektedir:

```
Demirkan, K., Tokdemir, S. (2026). Sensör Tabanlı Dijital Denge Analizörü ve
Gömülü Sistem Entegrasyonu. Ege Üniversitesi Tire Kutsan Meslek Yüksekokulu,
Bilgisayar Programcılığı Programı, Mikrodenetleyiciler Dersi Dönem Projesi,
Mayıs 2026.
```

---

## Lisans

Bu proje [MIT Lisansı](LICENSE) ile yayınlanmıştır. Yazılım, atıf yükümlülüğü dışında serbestçe kullanılabilir, değiştirilebilir ve dağıtılabilir.

---

## Teşekkür

Bu çalışma, Ege Üniversitesi Tire Kutsan Meslek Yüksekokulu Mikrodenetleyiciler Dersi 2025-2026 Bahar Dönemi kapsamında gerçekleştirilmiştir. Yazarlar; ders danışmanı Prof. Dr. Ahmet KAYA'ya teorik ve uygulamalı yönlendirmeleri, ilgili öğretim elemanlarına ve okul idaresine destekleri için teşekkür eder.

---

## İletişim

Proje hakkında soru, öneri veya katkılarınız için GitHub Issue açabilir veya Pull Request gönderebilirsiniz.
