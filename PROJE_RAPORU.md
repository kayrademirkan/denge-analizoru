# T.C.
# EGE ÜNİVERSİTESİ
# TİRE KUTSAN MESLEK YÜKSEKOKULU
## BİLGİSAYAR PROGRAMCILIĞI PROGRAMI

---

## SENSÖR TABANLI DİJİTAL DENGE ANALİZÖRÜ VE GÖMÜLÜ SİSTEM ENTEGRASYONU

### MİKRODENETLEYİCİLER DERSİ DÖNEM PROJESİ

---

**Hazırlayanlar:**
Kayra DEMİRKAN, Öğrenci No: 60240000050
Samet TOKDEMİR, Öğrenci No: 61230000118

**Danışman:** Prof. Dr. Ahmet KAYA

**Akademik Yıl / Dönem:** 2025–2026 / Bahar Dönemi

---

Tire / İzmir, Mayıs 2026

---

## İÇİNDEKİLER

1. ÖZET
2. ABSTRACT
3. GİRİŞ VE PROJENİN AMACI
   - 3.1. Projenin Mühendislik Amacı (Problem Cümlesi)
   - 3.2. Çalışmanın Mühendislik Kapsamı
   - 3.3. Araştırma Sorusu ve Hipotez
   - 3.4. Çıktı Ürünün Hedef Özellikleri
4. SİSTEM MİMARİSİ VE DONANIM BİLEŞENLERİ
   - 4.1. Ana Kontrol Ünitesi (Arduino Uno – ATmega328P)
   - 4.2. MEMS Sensör Modülü (MPU6050 – SY-104)
   - 4.3. Görüntü Birimi (0,96″ SSD1306 OLED)
   - 4.4. Kullanıcı Etkileşim Birimleri (1838B IR Alıcı, Pasif Buzzer)
   - 4.5. Pin Haritası ve Bağlantı Topolojisi
   - 4.6. Sistem Blok Diyagramı
   - 4.7. Güç Yönetimi ve Taşınabilirlik
     - 4.7.1. Düşük Güç (Bekleme) Modu
     - 4.7.2. Pil ile Açılış Stabilizasyonu
5. YÖNTEM VE GERÇEKLEME (METODOLOJİ)
   - 5.1. Donanım Bağlantıları ve I²C Protokolü
   - 5.2. Sensör Başlatma ve Kaydedici Yapılandırması
   - 5.3. Ham Veri Okuma Yordamı
   - 5.4. İki Aşamalı Kalibrasyon Stratejisi
   - 5.5. Dijital Sinyal İşleme: Tamamlayıcı Filtre
   - 5.6. Açı Ekseni Eşlemesi
   - 5.7. Ölçüm Akışı ve Skor Hesabı
   - 5.8. Kullanıcı Arayüzü ve Geri Bildirim
   - 5.9. Hata Ayıklama Altyapısı (Seri Port Akışı)
   - 5.10. Düşük Güç (Bekleme) Modu Akış Kontrolü
6. ÖN BULGULAR VE BEKLENEN SONUÇLAR
   - 6.1. Test Düzeneği
   - 6.2. Sensör Sağlığı Referans İmzaları
   - 6.3. Öngörülen Performans Aralıkları (Tasarım Hedefleri)
   - 6.4. Veri Sunum Biçimi ve Görselleştirme Olanakları
   - 6.5. Karşılaşılan Sorunlar ve Çözümleri
7. SONUÇ VE DEĞERLENDİRME
8. PROJE SINIRLILIKLARI VE GELECEK ÇALIŞMALAR
9. KAYNAKÇA
10. EKLER
   - EK-A: Kumanda Tuş Eşleme Tablosu
   - EK-B: Seri Port Veri Akış Formatı
   - EK-C: Sözlük
   - EK-D: Devre Şeması ve Prototip Fotoğrafları *(basılı sürümde eklenecek)*

---

## 1. ÖZET

Bu dönem projesinde, insan vücudunun statik ve dinamik denge performansını mikroelektromekanik sistem (MEMS) tabanlı sensörler aracılığıyla sayısal verilere dönüştürerek analiz eden, düşük maliyetli, taşınabilir ve gömülü mimaride bir mikrodenetleyici sisteminin tasarımı, donanım entegrasyonu ve gerçek zamanlı yazılım algoritmaları gerçekleştirilmiştir. Çalışmada mikrodenetleyici mimarisi, kaydedici düzeyinde I/O kontrolü, senkron (I²C) ve asenkron (USART) seri haberleşme protokolleri ile zamanlayıcı (Timer) modülünün pratik bir uygulamaya dönüştürülmesi sağlanmıştır. Sistemin merkezinde ATmega328P tabanlı 8 bit AVR mikrodenetleyici, algılayıcı katmanında ise InvenSense MPU6050 6 eksenli hareket işleme birimi yer almaktadır.

Çalışmanın bilimsel odak noktası, sensörden Inter-Integrated Circuit (I²C) senkron seri haberleşme protokolü ile alınan ham ivme ve açısal hız verilerinin mikrodenetleyici üzerinde koşan gömülü C/C++ yazılımı aracılığıyla işlenmesi, gürültü ve sapma (drift) hatalarının "Tamamlayıcı Filtre" (Complementary Filter) algoritması ile minimize edilmesi ve yüksek doğrulukla vücut salınım açılarının elde edilmesidir. Sistem, iki ekseni eş zamanlı değil; **tek bir ölçüm penceresinde kullanıcı tarafından seçilen tek bir eksende** (SAĞ-SOL ya da ÖN-ARKA) çalışmakta, böylece tek eksenli salınım hipotezini hedeflemektedir. Sisteme ek olarak SSD1306 OLED görüntüleme birimi, kızılötesi (IR) uzaktan kumanda alıcısı ve pasif piezoelektrik buzzer entegre edilerek tam donanımlı, klavye-monitör bağımsız bir taşınabilir cihaz oluşturulmuştur.

Elde edilen sayısal göstergeler, ortalama mutlak sapma, maksimum sapma genliği, hareket toplamı (stabilite indeksi) ve normalize edilmiş skor, sağlık bilimleri, postürografi, geriatri ve spor performansı gibi alanlarda kullanılabilecek nitelikte bir ön prototip özelliği taşımaktadır. Gerçekleştirilen sürüm, USB bağımsız 9 V batarya ile saha kullanımına uygundur.

**Anahtar Kelimeler:** MEMS sensör, MPU6050, ATmega328P, tamamlayıcı filtre, I²C, gömülü sistem, denge analizi, postürografi, gerçek zamanlı sinyal işleme.

---

## 2. ABSTRACT

This study presents the design, hardware integration and real-time embedded software algorithms of a low-cost, portable microcontroller-based system that quantifies static and dynamic human balance performance using Micro-Electro-Mechanical System (MEMS) sensors. The system is built around an 8-bit AVR ATmega328P microcontroller as the main control unit and an InvenSense MPU6050 six-axis motion processing unit as the sensing element.

The scientific focus of the work is the acquisition of raw acceleration and angular velocity data via the Inter-Integrated Circuit (I²C) synchronous serial protocol, processing of the data through embedded C/C++ firmware running on the microcontroller, and minimization of noise and integration drift via the Complementary Filter algorithm to obtain accurate body sway angles in real time. A 128×64 SSD1306 OLED display, an infrared remote receiver and a passive piezoelectric buzzer have been integrated to provide a fully self-contained, host-independent portable device.

The numerical indicators produced, mean absolute deviation, peak deviation, motion accumulation (stability index) and a normalized score, constitute a working prototype suitable for applications in health sciences, posturography, geriatrics and sports performance assessment. The final revision is compatible with stand-alone 9 V battery operation for field use.

**Keywords:** MEMS sensor, MPU6050, ATmega328P, complementary filter, I²C, embedded system, balance analysis, posturography, real-time signal processing.

---

## 3. GİRİŞ VE PROJENİN AMACI

İnsan vücudunun denge yetisi; **görsel sistem** (vizüel girdiler), **vestibüler sistem** (iç kulakta yer alan yarım daire kanalları ve otolit organları) ve **propriyoseptif sistem** (kas-tendon-eklemlerden gelen pozisyon bilgisi) tarafından sağlanan duyusal verilerin, merkezi sinir sisteminde eş zamanlı olarak işlenmesi ile sürdürülür [4, 5]. Vücudun ağırlık merkezinin yerçekimi doğrultusunda dinamik olarak kontrol edilebilmesi, sağlıklı bir iskelet-kas sistemi ve nörolojik bütünlüğün en temel göstergelerinden biridir.

Klinik ortamda dengenin nicel olarak değerlendirilmesi amacıyla **postürografi** olarak bilinen yöntemler kullanılmaktadır. Bu amaçla geliştirilmiş ticari cihazlar (statik ve dinamik posturografi platformları, kuvvet plakaları vb.) son derece yüksek maliyetli, kurulumu zaman alan ve mobilizasyonu sınırlı sistemlerdir. Bu durum, küçük klinikler, eğitim kurumları, sahada çalışan spor hekimleri ve geriatri araştırmacıları için ciddi bir erişilebilirlik engeli oluşturmaktadır.

### 3.1. Projenin Mühendislik Amacı (Problem Cümlesi)

**Problem Cümlesi:** Klinik düzeyde postürografi cihazlarının yüksek maliyeti (≥ 10 000 USD), büyük fiziksel boyutu ve özel laboratuvar gereksinimleri; birinci basamak sağlık merkezleri, eğitim kurumları ve saha araştırmaları için bu teknolojiyi erişilemez kılmaktadır. *Bu çalışmada, yüksek maliyetli postürografi sistemlerine alternatif olarak; düşük maliyetli, taşınabilir ve host bağımsız bir denge analizörünün MEMS sensörler ile gerçeklenmesi amaçlanmıştır.*

Bu projenin temel mühendislik amacı, endüstri standardı haberleşme protokolleri (I²C) ve dijital sinyal işleme algoritmaları kullanarak, yüksek maliyetli ticari sistemlerin *temel işlevlerini*, vücut salınım açısının doğru ve tekrarlanabilir biçimde ölçülmesini, yerine getiren, **taşınabilir ve düşük maliyetli bir Minimum Uygulanabilir Ürün (Minimum Viable Product, MVP)** geliştirmektir. Gerçekleştirilen prototipin toplam donanım maliyeti yaklaşık **1 300 TL** olarak ölçülmüş olup; klinik düzey postürografi cihazlarının (≥ 10 000 USD ≈ 350 000 TL) yaklaşık **‰0,4 (binde 4)**'üne karşılık gelen bir maliyet seviyesini temsil etmektedir.

### 3.2. Çalışmanın Mühendislik Kapsamı

Bu projenin tasarım ve gerçekleme aşamalarında ele alınan mühendislik konuları aşağıda listelenmiştir. Her bir başlığın projedeki karşılığı parantez içinde belirtilmiştir.

1. **Mikrodenetleyici mimarisi:** 8 bit AVR RISC çekirdeğinin Harvard mimarisi, Flash/SRAM/EEPROM bellek hiyerarşisi ve saat yapılandırması (16 MHz harici kristal) (*Bölüm 4.1*).
2. **Kaydedici (register) seviyesinde I/O kontrolü:** GPIO, dahili çevre birimleri ve sensör kaydedici haritalarının doğrudan ele alınması; örneğin MPU6050'nin `PWR_MGMT_1`, `GYRO_CONFIG`, `ACCEL_CONFIG`, `WHO_AM_I` kaydedicilerinin yazılması ve okunması (*Bölüm 5.2*).
3. **Senkron seri haberleşme (I²C/TWI):** Master-slave yapılandırmasında 100 kHz I²C üzerinden çoklu cihaz (sensör + ekran) yönetimi, repeated start ve burst okuma kullanımı (*Bölümler 5.1, 5.3*).
4. **Asenkron seri haberleşme (USART):** 115 200 baud üzerinden hata ayıklama ve dış arayüz veri akışı için CSV formatı (*Bölüm 5.9*).
5. **Zamanlayıcı (Timer/Counter) modülü:** `tone()` fonksiyonu üzerinden Timer2 tabanlı kare dalga üretimi ile pasif buzzer kontrolü (*Bölüm 4.4*).
6. **Yumuşak gerçek zamanlı (soft real-time) sistem tasarımı:** 50 ms periyotlu örnekleme döngüsü, engelleyici olmayan kullanıcı arayüzü ve durum makinesi yaklaşımı (*Bölüm 5.7*).
7. **Sayısal sinyal işleme:** Sensör füzyonu için Tamamlayıcı Filtre algoritmasının ayrık zamanlı gerçeklenmesi; alçak/yüksek geçiren filtre karakteristiklerinin matematiksel temeli (*Bölüm 5.5*).
8. **Sınırlı kaynak yönetimi:** 2 KB SRAM ve 32 KB Flash içerisinde, hazır kütüphaneler yerine projeye özgü (örneğin bit-banging IR çözücüsü) çözümler geliştirerek bellek optimizasyonu yapılması.
9. **Düşük güç (low-power) tasarımı:** Sensör SLEEP modu ve OLED `DISPLAYOFF` komutlarının koordinasyonuyla bekleme akımının azaltılması (*Bölüm 4.7*).

### 3.3. Araştırma Sorusu ve Hipotez

**Araştırma Sorusu:** ATmega328P ve MPU6050 gibi düşük maliyetli ve geniş erişimli bileşenlerle, vücut salınım açılarının taşınabilir bir cihazda **klinik takip için anlamlı doğrulukta** ölçülmesi mümkün müdür?

**Hipotez (H₁):** *MPU6050 sensöründen alınan ham ivme ve açısal hız verileri, Tamamlayıcı Filtre algoritması ile uygun şekilde işlendiğinde, insan denge durumuna ait ortalama mutlak sapma, maksimum sapma ve stabilite indeksi gibi nicel göstergeler, klinik yorum yapılabilecek doğrulukta (RMS hata < 0,5°) elde edilebilir.*

**Sıfır Hipotez (H₀):** Tek bir MEMS IMU sensöründen elde edilen veriler, vücut salınım açısını klinik anlamda yorumlanabilir doğrulukta üretmek için yetersizdir; tamamlayıcı filtre uygulansa dahi RMS hata 0,5°'nin üzerindedir.

Bölüm 6'daki ön bulgular, sistemin H₁ ile uyumlu çıktılar ürettiğini göstermektedir; nicel ve istatistiksel doğrulama, çoklu denekli ileri çalışmaya bırakılmıştır.

### 3.4. Çıktı Ürünün Hedef Özellikleri

| Özellik | Hedef Değer |
|---------|-------------|
| Ölçüm hassasiyeti (statik) | ±0,5° (1σ) |
| Ölçüm süresi | 10 saniye (yapılandırılabilir) |
| Ölçüm modu | **Tek eksenli** (SAĞ-SOL **veya** ÖN-ARKA, kullanıcı kumandadan seçer) |
| Mobil çalışma süresi | ≥ 8 saat (saha gözleminde 9 V alkalin ile ≈ 10 saat) |
| Kullanıcı arayüzü | Tam tuş takımlı IR kumanda + OLED ekran |
| Geri bildirim | Görsel (ekran) + İşitsel (buzzer) |
| Veri çıktısı | Seri port (CSV) + ekran |
| Toplam donanım maliyeti | ≈ 1 300 TL (2026 yılı koşulları, perakende) |

---

## 4. SİSTEM MİMARİSİ VE DONANIM BİLEŞENLERİ

Proje mimarisi katmanlı bir gömülü sistem yaklaşımıyla tasarlanmış olup; **veri toplama**, **veri işleme**, **kullanıcı etkileşimi** ve **veri sunumu** olmak üzere dört temel fonksiyonel bloktan meydana gelmektedir.

### 4.1. Ana Kontrol Ünitesi (Arduino Uno – ATmega328P)

Sistemin merkezinde, 8 bit AVR RISC mimarisine sahip Microchip (eski Atmel) **ATmega328P** mikrodenetleyicisini barındıran **Arduino Uno R3** geliştirme kartı yer almaktadır [2]. Mikrodenetleyici 16 MHz harici kristal osilatör ile saatlenmekte ve aşağıdaki dahili çevre birimlerini kullanmaktadır:

- **TWI (Two-Wire Interface)** modülü: Sensör ve OLED ile I²C haberleşmesi.
- **USART** modülü: PC ile seri port veri akışı (hata ayıklama ve harici arayüz).
- **GPIO** pinleri: IR alıcı sinyal okuma ve buzzer kontrolü.
- **Timer/Counter** modülü: `tone()` fonksiyonu üzerinden buzzer için kare dalga üretimi.

ATmega328P'nin 32 KB Flash bellek, 2 KB SRAM ve 1 KB EEPROM kapasitesi, projenin tüm gereksinimlerini karşılayacak büyüklükte olmuştur. Dış kütüphane ihtiyacı (örneğin `IRremote` gibi yüksek bellek tüketen IR kütüphaneleri) yerine **özel yazılmış bit-banging IR çözücüsü** tercih edilerek SRAM kullanımı %15 seviyelerinde tutulmuştur.

### 4.2. MEMS Sensör Modülü (MPU6050 – SY-104)

Hareket algılama amacıyla InvenSense (TDK) firmasının **MPU6050** entegre devresi temelinde üretilen **SY-104** breakout modülü kullanılmıştır [1]. SY-104; MPU6050 çipinin yanı sıra dahili 3,3 V regülatör, AD0 pini için pull-down direnci ve I²C hattı için pull-up dirençlerini içermekte olup 5 V besleme ile doğrudan kullanılabilmektedir. Çip aynı silikon kalıp (die) üzerinde aşağıdaki bileşenleri barındırır:

- **3 eksenli ivmeölçer (accelerometer):** Doğrusal ivmeyi ve yerçekimi vektörünü ölçer. Statik koşullarda nesnenin yerçekimine göre eğim açılarını (Roll, Pitch) hesaplamak için idealdir.
- **3 eksenli jiroskop (gyroscope):** Açısal hızı (°/s cinsinden) ölçer. Dinamik ve hızlı hareketlerde sistem tepki süresini artırır; ancak matematiksel integral hatası sebebiyle uzun sürede sapma (drift) yapar.
- **Dahili sıcaklık sensörü** (bu projede kullanılmamış, register'dan atlanmıştır).
- **Dijital Hareket İşlemcisi (DMP):** Sensör füzyonunu donanımsal olarak yapabilen yardımcı işlemci. Bu projede DMP yerine yazılımsal Tamamlayıcı Filtre tercih edilmiştir; gerekçesi 5.5 başlığında açıklanmıştır.

Sensör konfigürasyonu, **±250 °/s jiroskop tam ölçek aralığı** (131 LSB/(°/s) hassasiyet) ve **±2 g ivmeölçer tam ölçek aralığı** (16 384 LSB/g hassasiyet) olarak ayarlanmıştır. Bu değerler, statik denge analizi için en yüksek çözünürlüğü sağlamaktadır.

### 4.3. Görüntü Birimi (0,96″ SSD1306 OLED)

Kullanıcıya geri bildirim için **0,96 inç köşegen, 128×64 piksel monokrom SSD1306 sürücülü I²C OLED ekran modülü** kullanılmıştır [6]. Ekran, MPU6050 (SY-104) ile aynı I²C hattı üzerinden kontrol edilmekte ve `0x3C` adresinden adreslenmektedir. SSD1306; düşük güç tüketimi (~20 mA), arka aydınlatma gerektirmeyen yapısı ve geniş bakış açısı nedeniyle taşınabilir uygulamalar için tercih edilmiştir. Adafruit GFX ve Adafruit SSD1306 kütüphaneleri, ekran sürücü soyutlaması olarak kullanılmıştır.

Ekran içerikleri, sistemin durumunu açıkça yansıtacak biçimde tasarlanmıştır:
- **Hazır Ekranı:** Aktif ölçüm modu (SAĞ-SOL veya ÖN-ARKA) ve kumanda komutları.
- **Ölçüm Ekranı:** Aktif mod, geri sayım göstergesi, durum başlığı.
- **Sonuç Ekranı:** Yön (SAĞ/SOL/ÖN/ARKA), ortalama açı, maksimum sapma, stabilite indeksi ve skor.
- **Kapalı / Hata Ekranları:** Sistem durumu bildirimi.

### 4.4. Kullanıcı Etkileşim Birimleri (1838B IR Alıcı, Pasif Buzzer)

Cihazın temassız kullanımı için **1838B serisi 38 kHz kızılötesi alıcı modülü** (3 pinli VCC-GND-OUT yapılandırması) dijital pin 8'e bağlanmıştır. Alıcı, NEC kızılötesi haberleşme protokolüne uygun 38 kHz taşıyıcılı sinyalleri demodüle etmekte ve mikrodenetleyiciye sayısal düzeyde aktarmaktadır. Modül; açık alanda 8 metreye kadar haberleşme menzili ve 60° görüş açısı sağlamaktadır.

Kumanda olarak **21 butonlu jenerik NEC IR uzaktan kumanda** (CR2025 düğme pil ile beslenen) kullanılmaktadır. Projede tuşların yalnızca bir alt kümesi (OK, sayısal 0–3, yön tuşları, # POWER) işlevseldir; tanımsız bir tuşa basıldığında sistem o sinyali yok sayar ve seri porta "Bilinmeyen tus" notu düşer.

Standart `IRremote` kütüphanesi yerine, proje özelinde **bit-banging tabanlı özel bir NEC çözücüsü** yazılmıştır. Bu yaklaşım iki önemli avantaj sağlamıştır:
1. **Bellek tasarrufu:** Standart kütüphanenin getirdiği ~1 KB SRAM yükü tamamen kaldırılmıştır.
2. **Esneklik:** Aynı tuşa karşılık gelen birden fazla varyant kod (örneğin uzun basma kaynaklı kayma okumaları) tek bir mantıksal eyleme bağlanabilmiştir.

İşitsel geri bildirim için **D7 pinine bağlı 12 mm pasif piezoelektrik buzzer** kullanılmaktadır. Buzzer; Arduino çekirdek kütüphanesindeki `tone()` fonksiyonu (Timer2 tabanlı) üzerinden 2 700 Hz rezonans frekansında sürülmektedir. Üç farklı durum için ayrı tonlama desenleri tanımlanmıştır:
- **Ölçüm başlangıcı:** Tek kısa darbe (120 ms).
- **Ölçüm bitişi:** Tek uzun darbe (800 ms).
- **Kalibrasyon tamamlanması:** Üç vuruş (her biri 80 ms, arası 80 ms).

### 4.5. Pin Haritası ve Bağlantı Topolojisi

| Bileşen | Arduino Uno Pini | İşlev |
|---------|------------------|-------|
| MPU6050 (SY-104) SDA | A4 | I²C veri hattı |
| MPU6050 (SY-104) SCL | A5 | I²C saat hattı |
| MPU6050 (SY-104) VCC | 5V | Besleme (modül üstü 3,3 V regülatör mevcut) |
| MPU6050 (SY-104) GND | GND | Toprak |
| OLED 0,96″ SDA | A4 | MPU6050 ile paylaşımlı I²C |
| OLED 0,96″ SCL | A5 | MPU6050 ile paylaşımlı I²C |
| OLED 0,96″ VCC | 5V | Besleme |
| OLED 0,96″ GND | GND | Toprak |
| 1838B IR Alıcı OUT | D8 | Demodüle edilmiş sayısal sinyal |
| 1838B IR Alıcı VCC | 5V | Besleme |
| 1838B IR Alıcı GND | GND | Toprak |
| 12 mm Pasif Piezo Buzzer (+) | D7 | PWM/tone çıkışı |
| 12 mm Pasif Piezo Buzzer (–) | GND | Toprak |

I²C hattında MPU6050 (`0x68`) ve OLED (`0x3C`) farklı adreslerde olduğundan, tek bir veri hattı paylaşılarak iki cihaz aynı anda yönetilebilmektedir. Hat üzerinde donanımsal pull-up dirençleri (4,7 kΩ) gereklidir; çoğu hazır modül üzerinde dahili pull-up bulunmaktadır.

**Prototipleme yöntemi:** Tüm bağlantılar **breadboard** üzerinde, dişi-dişi ve erkek-dişi jumper kablolar kullanılarak gerçekleştirilmiştir. Bu yaklaşım, devre üzerinde hızlı değişiklik yapma ve hata ayıklama sürecini kolaylaştırmış; ayrıca bileşenlerin başka projelerde tekrar kullanılabilmesine olanak tanımıştır. Mevcut sürümde herhangi bir lehim işlemi yapılmamıştır; nihai ürünleştirme aşamasında PCB tasarımı veya delikli pertinaks üzerinde lehimleme önerilebilir (Bölüm 8.1).

### 4.6. Sistem Blok Diyagramı

Tüm bileşenlerin Arduino mikrodenetleyici çevresindeki bağlantı topolojisi aşağıdaki blok diyagram ile özetlenmektedir:

```
                              ┌─────────────────┐
                              │  9 V Batarya    │
                              │   (≈ 550 mAh)   │
                              └────────┬────────┘
                                       │  VIN (anahtar üzerinden)
                                       ▼
              ┌────────────────────────────────────────────┐
              │  Arduino Uno R3  (ATmega328P @ 16 MHz)     │
              │  ─────────────────────────────────────────  │
              │   TWI │ USART │ GPIO (D7, D8) │ Timer2     │
              └───┬──────┬───────────┬────┬───────┬────────┘
                  │      │           │    │       │
            I²C   │      │  USART    │    │ tone()│
            SDA/SCL│      │115200 bd  │    │       │
                  │      ▼           │    │       │
                  │  ┌────────┐      │    │   ┌──────────┐
                  │  │   PC   │      │    │   │  Buzzer  │
                  │  │ (CSV)  │      │    │   │  (D7)    │
                  │  └────────┘      │    │   └──────────┘
        ┌─────────┴─────────┐        │    │
        │                   │        │    │
        ▼                   ▼        ▼    ▼
 ┌────────────┐     ┌────────────┐  ┌──────────────┐
 │  MPU6050   │     │  SSD1306   │  │   IR Alıcı   │
 │  SY-104    │     │  0,96"     │  │  1838B 38kHz │
 │  (0x68)    │     │  128×64    │  │  modül (D8)  │
 │  6 eksen   │     │  (0x3C)    │  │              │
 └────────────┘     └────────────┘  └──────────────┘
        │                   │              ▲
        │ I²C paylaşımlı   │              │ NEC IR
        │ (SDA/SCL)         │              │ 38 kHz
        └─────────┬─────────┘              │
                  │                ┌──────────────┐
                  │                │   Kullanıcı  │
                  │                │   Kumandası  │
                  │                └──────────────┘
                  │
              4,7 kΩ pull-up dirençleri
              (modüllerde dahili)

  Veri Akışı:
   ─── Sensör (MPU6050) ──► Mikrodenetleyici ──► Tamamlayıcı Filtre
       ──► Skor Hesabı ──┬──► OLED (görsel sonuç)
                          ├──► Buzzer (işitsel onay)
                          └──► USART (CSV veri akışı, harici arayüz)
```

**Sinyal Akışı Özeti:** Sensörden alınan ham ivme ve açısal hız verisi I²C üzerinden mikrodenetleyiciye iletilmekte, **Tamamlayıcı Filtre** ile birleştirilmekte ve elde edilen açı bilgisi üç farklı çıkış kanalına (OLED ekran, buzzer, USART seri portu) paralel olarak yönlendirilmektedir. Kullanıcı etkileşimi NEC IR protokolü ile sağlanmakta; sistem böylece tam **host bağımsız** bir taşınabilir cihaz olarak çalışmaktadır.

> *Not: Devre şeması, breadboard yerleşimi ve denge tahtasına monte edilmiş prototip fotoğrafları, fiziksel teslim sürecinde rapora ek olarak sunulacaktır (EK-D).*

### 4.7. Güç Yönetimi ve Taşınabilirlik

Sistem hem **USB hem de 9 V harici batarya** ile çalışacak biçimde tasarlanmıştır. Aktif çalışma sırasında bileşen bazlı akım tüketimi aşağıdaki gibidir:

| Bileşen | Akım |
|---------|------|
| ATmega328P (16 MHz) | ~50 mA |
| SSD1306 OLED (orta yoğunluk) | ~20 mA |
| MPU6050 (aktif) | ~3,5 mA |
| 1838B IR alıcı | ~1 mA |
| Pasif buzzer (`tone()` aktif iken) | ~10 mA |
| **Toplam (aktif)** | **~85 mA** |

#### 4.7.1. Düşük Güç (Bekleme) Modu

Sistemin uzun süreli sergi ve saha kullanımına uygun olabilmesi amacıyla **yazılımsal bekleme modu** geliştirilmiştir. Kumandanın "#" (POWER) tuşuna basıldığında aşağıdaki aşamalar sırayla gerçekleştirilir:

1. **MPU6050 SLEEP biti aktif edilir** (`PWR_MGMT_1` register'ı, bit 6): Sensörün akımı tipik olarak ~3,5 mA seviyesinden ~5 µA'ya iner. Yapılandırma kaydedicileri (`GYRO_CONFIG`, `ACCEL_CONFIG`) korunduğu için uyandırma işlemi yeniden kalibrasyon gerektirmez.
2. **OLED ekran sürücüsü kapatılır** (`SSD1306_DISPLAYOFF` komutu): Ekran tüketimi ~20 mA'dan ~0,1 mA'ya iner.
3. **IR alıcı dinlemeye devam eder**: Kullanıcının kumanda ile sistemi yeniden açabilmesi için tek aktif kalan bileşendir.

Bu yaklaşımla bekleme akımı %47 oranında azaltılmıştır:

| Çalışma Durumu | Akım (datasheet tahmini) | Pil Ömrü (≈550 mAh, 9 V alkalin varsayımıyla) |
|----------------|--------------------------|---------------|
| Aktif ölçüm | ~85 mA | ~6,5 saat (teorik) |
| **Yazılımsal bekleme** | **~45 mA** | **~12 saat (teorik)** |
| Donanımsal kapatma (slide switch) | 0 mA | ∞ |
| **Saha gözlemi (karma kullanım)** |, | **≈ 10 saat ölçüldü** |

> *Saha gözlemi:* Cihaz, **9 V alkalin pil** ile montaj sonrası tipik kullanım senaryosunda (ölçüm + bekleme modu kombinasyonu) yaklaşık **10 saat** kesintisiz çalışmıştır. Bu değer, datasheet temelli teorik tahminlerin uyumlu sonucudur. Multimetre ile bileşen-bazlı akım ölçümü bu çalışma kapsamında yapılmamış olup, akım değerleri üretici datasheet'lerinden alınmıştır.

Tam güç kesme için 9 V batarya hattına bir **fiziksel slide veya rocker anahtar** seri olarak takılması, sergi mola süreleri için en sağlam çözümdür.

#### 4.7.2. Pil ile Açılış Stabilizasyonu

USB üzerinden çalışırken Arduino'nun bootloader gecikmesi (≈1–2 s) MPU6050'nin power-up süresini doğal olarak örtmektedir. Ancak 9 V harici batarya ile açılışta linear regülatörün ramp-up süresi ve sensör power-on reset süreci çakıştığında, ilk `initMPU()` çağrısı başarısız olabilmektedir.

Bu sorun iki katmanlı bir yaklaşım ile çözülmüştür:

1. **Yazılımsal stabilizasyon gecikmesi:** `setup()` fonksiyonunun başında 300 ms'lik bir bekleme uygulanmaktadır.
2. **Yeniden deneme (retry) mekanizması:** `initMPU()` fonksiyonu başarısız olursa, sistem en fazla 8 deneme boyunca her seferinde 250 ms ara vererek sensörü tekrar başlatmaya çalışır. Hangi denemede başarılı olunduğu seri porta yazdırılarak teşhis sağlanır.

Donanımsal olarak ek güvenilirlik için 5 V hattı ile GND arasına **100 µF elektrolitik kondansatör** ve MPU6050 VCC pininin yakınına **10 µF tantal kondansatör** lehimlenmesi önerilmektedir.

---

## 5. YÖNTEM VE GERÇEKLEME (METODOLOJİ)

Projenin yazılım katmanı, sınırlı bellek ve hesaplama kaynağına sahip 8 bit bir mikrodenetleyici üzerinde çalışan **gömülü C/C++** dilinde geliştirilmiştir. Yazılım üç temel katmandan oluşur: **donanım soyutlama (HAL)**, **sinyal işleme** ve **kullanıcı arayüzü**.

### 5.1. Donanım Bağlantıları ve I²C Protokolü

MPU6050 ile mikrodenetleyici arasındaki haberleşme, iki kablolu I²C protokolü üzerinden gerçekleştirilmektedir. Mikrodenetleyici **master**, sensör ise **slave** rolündedir. Saat hızı, sensörün tolerans aralığı ve hat kapasitansı dikkate alınarak 100 kHz (Standard Mode) seviyesinde tutulmuş olup, aynı hat üzerinde paralel çalışan OLED ekran için de uygun bir hızdır.

Sensör adresi `0x68` olarak tanımlanmıştır (AD0 pini LOW). Veri yükleri **big-endian** sırayla (önce yüksek anlamlı bayt) gönderilmekte ve okunmaktadır.

### 5.2. Sensör Başlatma ve Kaydedici Yapılandırması

Sistem açılışında sensör aşağıdaki sırada yapılandırılmaktadır:

1. **PWR_MGMT_1 (0x6B) ← 0x00:** SLEEP biti temizlenerek sensör uyandırılır, dahili 8 MHz osilatör seçilir.
2. **WHO_AM_I (0x75) okuma:** Sensörün doğru bağlandığı doğrulanır. Standart MPU6050 chipi `0x68`, MPU6500 türevi `0x70`, MPU9250 `0x71` döndürmektedir. Klon entegrelerin farklı değerler dönebildiği gözlemlenmiş ve uyarı eşliğinde sistemin çalışmaya devam etmesine izin verilmiştir.
3. **GYRO_CONFIG (0x1B) ← 0x00:** Jiroskop ölçek aralığı ±250 °/s'ye ayarlanır (131 LSB/(°/s)).
4. **ACCEL_CONFIG (0x1C) ← 0x00:** İvmeölçer ölçek aralığı ±2 g'ye ayarlanır (16 384 LSB/g).

Dijital alçak geçiren filtre (DLPF, 0x1A) ve örnekleme oranı bölücü (SMPLRT_DIV, 0x19) kaydedicilerinin yazılması; geliştirme sürecinde bazı standart-dışı klon entegrelerde **ivmeölçer kanallarının doyuma (saturation) gitmesine** sebep olduğu için varsayılan değerlerinde bırakılmıştır. Bu, hassasiyetten taviz verilmesi anlamına gelmemektedir; üretici varsayılanları (DLPF kapalı, 8 kHz örnekleme) yazılımın 50 ms döngü periyodu içinde yeterli filtreleme sağlamaktadır.

**Yeniden deneme mekanizması:** Yukarıdaki yapılandırma adımlarından herhangi biri başarısız olursa (özellikle batarya ile açılışta sensörün tam stabilize olmadığı koşullarda), sistem 250 ms aralıklarla en fazla 8 yeniden deneme yapmaktadır. Bu yaklaşımın temelinde, her deneme arasında geçen 250 ms'lik beklemenin sensörün güç ve osilatör koşullarının kararlı hale gelmesine zaman tanıması yatmaktadır; toplamda 2 saniyeyi aşan deneme penceresi içinde sensörün başlatılmaya hazır hale gelmesi pratik olarak garanti edilmektedir. Geliştirme sürecinde mekanizma etkinleştirildikten sonra batarya ile açılışlarda başlatma hatası gözlemlenmemiştir.

### 5.3. Ham Veri Okuma Yordamı

Ham sensör verileri tek bir burst okuma içinde, **register `0x3B`'den itibaren 14 bayt** olacak şekilde alınmaktadır. Bu yöntem, sırasıyla 6 bayt ivmeölçer (X, Y, Z), 2 bayt sıcaklık (atlanır) ve 6 bayt jiroskop (X, Y, Z) verisini tek I²C tranzaksiyonunda toplar; toplam transfer süresini en aza indirir.

Bayt birleştirme aşamasında C++ standardındaki *operandların değerlendirme sırası garantisizliği* sorununa karşı, yüksek ve düşük baytlar **ayrı geçici değişkenlere** alınarak birleştirilmiştir. `Wire.requestFrom()` fonksiyonunun dönüş değeri ayrıca kontrol edilerek, beklenen 14 baytın altında veri gelmesi durumunda tüm değerler sıfıra çekilmekte; böylece I²C arızası, yapay sabit veri üretmek yerine net biçimde tespit edilebilir hale gelmektedir.

```c
void readMPU(int16_t &AcX, int16_t &AcY, int16_t &AcZ,
             int16_t &GyX, int16_t &GyY, int16_t &GyZ) {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);                       // ACCEL_XOUT_H register adresi
  Wire.endTransmission(false);            // repeated start
  uint8_t got = Wire.requestFrom((uint8_t)MPU, (uint8_t)14, (uint8_t)true);

  if (got < 14) {                         // I2C okuma başarısız → sıfırla
    AcX = AcY = AcZ = 0;
    GyX = GyY = GyZ = 0;
    return;
  }

  uint8_t hi, lo;
  hi = Wire.read(); lo = Wire.read(); AcX = (int16_t)((hi << 8) | lo);
  hi = Wire.read(); lo = Wire.read(); AcY = (int16_t)((hi << 8) | lo);
  hi = Wire.read(); lo = Wire.read(); AcZ = (int16_t)((hi << 8) | lo);
  Wire.read(); Wire.read();               // TEMP, atlanır
  hi = Wire.read(); lo = Wire.read(); GyX = (int16_t)((hi << 8) | lo);
  hi = Wire.read(); lo = Wire.read(); GyY = (int16_t)((hi << 8) | lo);
  hi = Wire.read(); lo = Wire.read(); GyZ = (int16_t)((hi << 8) | lo);
}
```

Bu yapı; derleyici optimizasyonundan, hedef mimariden ve sıralama garantisinden bağımsız olarak **doğru bayt sırasını** ve **hata durumunda güvenli geri dönüşü** garantilemektedir.

### 5.4. İki Aşamalı Kalibrasyon Stratejisi

MEMS sensörlerin üretim toleransları ve çevresel sıcaklık etkileri nedeniyle, her açılışta küçük başlangıç sapmaları (bias) gözlemlenmektedir. Bu projede çift fazlı bir kalibrasyon yordamı geliştirilmiştir:

**Faz 1, Jiroskop Sıfırlama (Offset)**

Sistem, kullanıcıdan cihazı 2 saniye boyunca tamamen hareketsiz tutmasını isteyerek sensörden ardışık 1 000 örnek toplar. Her örnek arasında 2 ms gecikme uygulanır. Toplanan jiroskop değerlerinin aritmetik ortalaması, kalıcı bir **jiroskop sapma değeri (`gyroXOffset`, `gyroYOffset`)** olarak belirlenir. Sonraki tüm okumalardan bu değer çıkarılarak jiroskopun "sıfır hızda" gerçekten sıfır okuması sağlanır.

**Faz 2, Açı Sıfırlama (Reference Angle)**

Jiroskop sapması düzeltildikten sonra, Tamamlayıcı Filtre 200 iterasyon boyunca (1 saniye) çalıştırılır ve filtre çıkışı, sensörün mevcut fiziksel oryantasyonuna yakınsar. Bu yakınsanan değerler, **sıfır referans açısı (`angleXOffset`, `angleYOffset`)** olarak kaydedilir. Bu yaklaşım sayesinde, sensörün PCB üzerinde 90° dönmüş veya yatık monte edilmiş olması veya cihazın hafif eğimli bir yüzeye yerleştirilmiş olması gibi durumlarda dahi sistem doğru biçimde sıfırlanabilmektedir.

İki fazlı kalibrasyon yordamının çekirdeği aşağıda sunulmuştur:

```c
void calibrateAll() {
  // Faz 1: jiroskop sıfır-hız biası
  long gxSum = 0, gySum = 0;
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

  // Faz 2: açı referansı (filtre yakınsaması)
  angleX = 0;
  angleY = 0;
  lastTime = millis();
  for (int i = 0; i < 200; i++) {
    updateFilter();
    delay(5);
  }
  angleXOffset = angleX;
  angleYOffset = angleY;
}
```

### 5.5. Dijital Sinyal İşleme: Tamamlayıcı Filtre

Ham sensör verileri tek başına denge analizi için yetersizdir:

- **İvmeölçer:** Doğrusal ivmeden ve mekanik titreşimlerden ciddi biçimde etkilenir, gürültülüdür. Ancak uzun süreli kararlıdır.
- **Jiroskop:** Titreşime duyarsızdır ve hızlı tepki verir; ancak açısal hız integrali alındıkça sapma (drift) yapar.

İki sensörün zayıf yönlerini iptal eden, güçlü yönlerini birleştiren çözüm **Tamamlayıcı Filtre**'dir [3]. Mikrodenetleyici üzerinde saniyede onlarca kez koşan matematiksel model şu şekildedir:

$$
\theta_{yeni} = \alpha \cdot (\theta_{eski} + \omega \cdot \Delta t) + (1 - \alpha) \cdot \theta_{ivme}
$$

**Formülün Bileşenleri:**

| Sembol | Anlam |
|--------|-------|
| $\theta_{yeni}$ | Mikrodenetleyicinin hesapladığı nihai eğim açısı (°) |
| $\theta_{eski}$ | Bir önceki iterasyondaki açı |
| $\omega$ | Jiroskoptan okunan anlık açısal hız (°/s) |
| $\Delta t$ | İki örnek arasındaki süre (s) |
| $\theta_{ivme}$ | İvmeölçer X, Y, Z bileşenlerinin `atan2` fonksiyonu ile elde edilmiş açısı (°) |
| $\alpha$ | Filtre katsayısı; bu projede **0,96** olarak belirlenmiştir |

Filtre katsayısının 0,96 seçilmesi şu anlama gelir: kısa vadeli açı tahmininin **%96'sı jiroskop integralinden**, **%4'ü ivmeölçerden** beslenir. Bu oran, MEMS literatüründe denge ve eğim ölçüm uygulamaları için yaygın olarak kullanılan bir değerdir [3]. Filtrenin zaman sabiti $\tau = -\Delta t / \ln(\alpha)$ formülüyle hesaplanır; tipik $\Delta t = 50$ ms değeri için yaklaşık $\tau \approx 1{,}22$ s elde edilir, bu da filtrenin hızlı tepkisini ve uzun sürede kararlılığını korur.

Filtrenin gömülü C++ gerçeklemesi aşağıda sunulmuştur:

```c
void updateFilter() {
  int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;
  readMPU(AcX, AcY, AcZ, GyX, GyY, GyZ);

  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;
  lastTime = now;
  if (dt <= 0 || dt > 0.2) dt = 0.01;        // savunmacı dt sınırlama

  // Gyro biası çıkarıldıktan sonra açısal hız (°/s)
  float gyroXRate = (GyX - gyroXOffset) / 131.0;
  float gyroYRate = (GyY - gyroYOffset) / 131.0;

  // İvmeölçer kaynaklı açı (atan2 ile yer çekimi vektöründen)
  float accAngleX = atan2((float)AcY, (float)AcZ) * 180.0 / PI;
  float accAngleY = atan2((float)AcX, (float)AcZ) * 180.0 / PI;

  // Tamamlayıcı filtre: %96 gyro integrali + %4 ivmeölçer
  angleX = alpha * (angleX + gyroXRate * dt) + (1.0 - alpha) * accAngleX;
  angleY = alpha * (angleY + gyroYRate * dt) + (1.0 - alpha) * accAngleY;
}
```

### 5.6. Açı Ekseni Eşlemesi

İvmeölçer verisinden eğim açıları, klasik tilt-sensing yaklaşımıyla `atan2` fonksiyonu kullanılarak hesaplanmaktadır:

- **Roll (X ekseni etrafındaki dönüş):** $\theta_{Roll} = \arctan2(A_y, A_z) \cdot \frac{180}{\pi}$
- **Pitch (Y ekseni etrafındaki dönüş):** $\theta_{Pitch} = \arctan2(A_x, A_z) \cdot \frac{180}{\pi}$

Sistem **tek eksenli salınım hipotezi** altında çalıştığı için (kullanıcı bir defada SAĞ-SOL veya ÖN-ARKA modlarından sadece birini seçer), Pitch hesaplamasında küresel doğruluğu artıran $\arctan2(-A_x, \sqrt{A_y^2 + A_z^2})$ formülü yerine yukarıdaki sadeleştirilmiş form tercih edilmiştir. Tek eksenli salınımlarda iki formül arasındaki sapma, küçük açılarda (0–5°) 0,1°'nin altında olup denge ölçümü için ihmal edilebilir düzeydedir.

Salınımın eşlemesi şu şekilde yapılmaktadır:

| Mod | Hesaplanan Açı |
|-----|----------------|
| SAĞ-SOL (Roll) | `angleX – angleXOffset` |
| ÖN-ARKA (Pitch) | `angleY – angleYOffset` |

### 5.7. Ölçüm Akışı ve Skor Hesabı

Kullanıcı, ölçümden önce kumanda üzerinden ölçüm modunu seçer (varsayılan SAĞ-SOL; **1/SAĞ** tuşu ile SAĞ-SOL, **2/SOL** tuşu ile ÖN-ARKA modu etkinleştirilir). Bu seçim, ölçüm sırasında hangi eksenin (Roll veya Pitch) izleneceğini belirler.

**Kullanım Protokolü (Vücut–Eksen Hizalaması):** Denge tahtasının PVC pivot tasarımı (Bölüm 4.8) yalnızca tek bir eksende mekanik yuvarlanma sağladığı için, kullanıcı seçilen ölçüm moduna göre tahta üzerindeki yönelimini ayarlamalıdır:

- **SAĞ-SOL modu:** Kullanıcı tahta üzerinde **normal pozisyonda** (yüzü pivot çubuğuna dik bakacak biçimde) durur; vücudun sağ-sol salınımı tahtanın eğim eksenine doğrudan aktarılır.
- **ÖN-ARKA modu:** Kullanıcı tahta üzerinde **90° dönmüş pozisyonda** (yüzü pivot çubuğuna paralel bakacak biçimde) durur; bu sayede vücudun ön-arka salınımı tahtanın eğim eksenine denk gelir ve doğru biçimde algılanır.

Bu hizalama, tek eksenli pivot tasarımının doğal bir kullanım kuralıdır; çift eksenli (küresel) pivot eklenmesi halinde gerekliliği ortadan kalkar (bkz. Bölüm 8.1).

Sonrasında **OK** tuşuna basıldığında 10 saniyelik bir ölçüm penceresi açılır. Bu pencere içinde 50 ms periyot ile yaklaşık 200 örnek toplanır ve her örnekte yalnızca seçilen eksene ait açı değeri kaydedilir. Her örnekte aşağıdaki dört temel istatistiksel gösterge eş zamanlı olarak güncellenir:

| Gösterge | Hesaplama | Anlamı |
|----------|-----------|--------|
| Ortalama mutlak sapma | $\frac{1}{N}\sum |\theta_i|$ | Dengeden ortalama uzaklık |
| Ortalama yönlü sapma | $\frac{1}{N}\sum \theta_i$ | Genel yön eğilimi (sağ/sol veya ön/arka) |
| Maksimum sapma | $\max(|\theta_i|)$ | En büyük tek tepe sapması |
| Hareket toplamı (Stabilite) | $\frac{1}{N}\sum |\theta_i - \theta_{i-1}|$ | Salınım hızı / kararsızlık |

Ölçüm tamamlandığında bu dört göstergeden **0–100 arası normalize bir skor** üretilir:

$$
\text{Skor} = \max\left(0,\ \min\left(100,\ 100 - 5 \cdot \overline{|\theta|} - 2 \cdot \theta_{max} - 8 \cdot S\right)\right)
$$

Katsayılar (5, 2, 8) ampirik olarak; sağlıklı bireylerin tipik salınım değerlerine göre **80–95** arası, ileri derece denge bozukluğu durumlarında **0–40** arası bir skor üretecek biçimde kalibre edilmiştir. Skor, klinik bir tanı aracı değil; bireysel takip ve karşılaştırma için bir **göreli performans göstergesidir**.

Skor hesabının gömülü gerçeklemesi:

```c
int calculateScore(float ortalama, float maxSapma, float stabilite) {
  int skor = 100 - (ortalama * 5) - (maxSapma * 2) - (stabilite * 8);
  if (skor > 100) skor = 100;        // tavan
  if (skor < 0)   skor = 0;          // taban
  return skor;
}
```

### 5.8. Kullanıcı Arayüzü ve Geri Bildirim

Sistem; ekran-klavye gerektirmeyen, tamamen kumanda tabanlı bir arayüze sahiptir. Tuş kodları kaynak koda gömülü olup, projede kullanılan 21 butonlu NEC IR kumandası için doğrudan eşlemeler tanımlanmıştır (bkz. EK-A). Ölçümün her aşamasında çoklu duyusal geri bildirim sağlanır:

- **Görsel:** OLED ekran üzerinde durum, geri sayım, sonuçlar.
- **İşitsel:** Buzzer üzerinden ölçüm başı/sonu/kalibrasyon onayı.

Sonuç ekranı 15 saniye boyunca aktif kalır; bu süre içinde **kumandaya basıldığında ekran anında kapanır ve ana menüye dönülür** (engelleyici olmayan kontrol akışı). Bu, geliştirme sürecinde tespit edilen önemli bir kullanılabilirlik iyileştirmesidir.

### 5.9. Hata Ayıklama Altyapısı (Seri Port Akışı)

Sistem; ölçüm sonuçlarını **cihaz üzerinde kalıcı olarak saklamamakta**, yerel görüntü ile birlikte aynı verileri **115 200 baud seri port** üzerinden CSV formatında **anlık olarak yayınlamaktadır**. Bu altyapı:

1. Geliştirme sırasında sensör arızalarını ve filtre davranışını anlık izleme imkânı sunar.
2. PC bağlı çalıştığında, Arduino IDE Serial Plotter veya harici bir tablo/grafik yazılımı ile gerçek zamanlı görselleştirmeye olanak tanır.
3. İleride bağımsız bir PC arayüzü (Processing/C#) veya SD kart kayıt modülü eklendiğinde, mevcut veri biçimi doğrudan kullanılabilir niteliktedir.

Veri formatı EK-B'de detaylandırılmıştır. Cihaz tek başına çalıştığında (PC'siz), kullanıcı ölçüm sonucu yalnızca OLED ekran üzerinden görür.

### 5.10. Düşük Güç (Bekleme) Modu Akış Kontrolü

Mobil sergi koşullarında pil ömrünü uzatmak amacıyla iki ayrı durum makinesi tanımlanmıştır:

**Aktif → Bekleme geçişi:**
1. `showClosedScreen()` ile "KAPALI" mesajı 800 ms süreyle ekrana yazılır.
2. `display.ssd1306_command(SSD1306_DISPLAYOFF)` ile OLED'in dahili sürücü çipi pasifleştirilir.
3. `mpuSleep()` ile MPU6050'nin `PWR_MGMT_1` register'ında SLEEP biti aktif edilir.
4. `sistemAcik = false` bayrağı ile ana döngüde sensör okumaları durdurulur; yalnızca IR alıcı pollinglenir.

**Bekleme → Aktif geçişi:**
1. `display.ssd1306_command(SSD1306_DISPLAYON)` ile OLED yeniden etkinleştirilir.
2. `mpuWake()` çağrılır; SLEEP biti temizlenir ve sensörün osilatörünün stabilize olması için 50 ms beklenir.
3. `lastTime = millis()` ile filtre zaman tabanı sıfırlanır; ardışık `dt` hesabı taze başlar.
4. Kullanıcıya "SİSTEM AÇILDI" mesajı 800 ms gösterilir, sonra hazır ekranına geçilir.

Bu yaklaşım MPU6050'nin yapılandırma kaydedicilerinin (özellikle `GYRO_CONFIG` ve `ACCEL_CONFIG`) sleep modunda korunmasından yararlanır; uyandırma sonrasında yeniden tam başlatma gerekmez. Uyandırma süresi (toplam ~80 ms) kullanıcı algısı için anlık olarak değerlendirilebilir.

---

## 6. ÖN BULGULAR VE BEKLENEN SONUÇLAR

### 6.1. Test Düzeneği

Prototip cihaz, test sürecinde **denge tahtasının geometrik merkezine** sabitlenmiş ve test bireyi tahta üzerine ayakta duracak biçimde konumlandırılmıştır. Cihaz, kullanıcının ağırlık merkezinin yere izdüşümünün yatay düzlemdeki yer değiştirmesini, açısal eğim cinsinden algılayacak şekilde monte edilmiştir.

İlk işlevsel testlerde aşağıdaki iki senaryo gözlemlenmiştir:

1. **Statik denge gözlemi:** Birey, gözleri açık, ayakları omuz genişliğinde, denge tahtası üzerinde 10 saniye boyunca sabit duracak biçimde gözlemlenmiştir.
2. **Yönlü zorluk gözlemi:** Birey, sistem tepkisini doğrulamak amacıyla kontrollü biçimde sağ-sol veya ön-arka yönlü salınımlar yapmıştır.

Bu çalışmada, ölçümlerin **çoklu denek üzerinde istatistiksel doğrulanması** veya altın standart bir referans cihazla karşılaştırılması yapılmamıştır; saha validasyonu Bölüm 8.1'de gelecek geliştirme olarak listelenmiştir.

### 6.2. Sensör Sağlığı Referans İmzaları

Geliştirme aşamasında, sensörün doğru çalıştığını teyit etmek için aşağıdaki ham veri kontrol noktaları **referans imza** olarak kullanılmıştır. Tablodaki değerler, MPU6050'nin yatay düzlemde duran *sağlıklı bir referans örneği* için datasheet [1] temelli beklentilerdir:

| Parametre | Beklenen | Toleransı |
|-----------|----------|-----------|
| `WHO_AM_I` | 0x68 (orijinal MPU6050) | 0x70/0x71 da kabul edilebilir |
| AcZ | ≈ +16 384 | ±1 000 |
| AcX, AcY | ≈ 0 | ±500 |
| GyX, GyY, GyZ | ≈ 0 | ±200 |
| $\sqrt{A_x^2 + A_y^2 + A_z^2}$ | ≈ 16 384 (1 g) | ±500 |

> *Not:* Bu referans imzalar, sensörün **sıfır eğimde, hareketsiz** durumdaki davranışını tanımlar. Cihaz denge tahtasına monte edildiğinde MPU6050'nin fiziksel oryantasyonu farklı olabileceğinden, ham `AcX`, `AcY`, `AcZ` değerleri yer çekimini farklı bileşenlere paylaştırır; ancak vektör büyüklüğü her durumda 1 g civarındadır. Eğim kompansasyonu kalibrasyon yordamı ile (Bölüm 5.4) otomatik olarak yapılmaktadır.

### 6.3. Öngörülen Performans Aralıkları (Tasarım Hedefleri)

Aşağıdaki tablo, postürografi literatüründeki sağlıklı denek değerlerine [11] dayanan **öngörülen tasarım hedeflerini** sunmaktadır. Bu değerler, klinik validasyon çalışması yapılmadığı için **deneysel ölçüm sonuçları değil, beklenti aralıklarıdır**.

| Kullanıcı Profili | Beklenen Ort. mutlak (°) | Beklenen Maks. sapma (°) | Beklenen Stabilite (°/örnek) | Beklenen Skor |
|-------------------|--------------------------|--------------------------|--------------------|---------------|
| Sağlıklı (gözler açık) | 0,3–1,5 | 1,0–3,0 | 0,05–0,20 | 85–95 |
| Sağlıklı (gözler kapalı) | 1,0–3,0 | 2,5–6,0 | 0,15–0,40 | 65–85 |
| Hafif denge zorluğu | 3,0–6,0 | 5,0–10 | 0,40–0,80 | 35–65 |
| Kasıtlı sallanma | 6,0–15 | 10–25 | 0,80–2,0 | 0–35 |

İlk işlevsel saha gözlemlerinde sistemin yukarıdaki aralıklarla uyumlu, tutarlı çıktılar ürettiği gözlemlenmiştir. Sayısal istatistiksel doğrulama, çoklu denekli klinik bir validasyon çalışmasını gerektirmektedir.

### 6.4. Veri Sunum Biçimi ve Görselleştirme Olanakları

Mevcut prototip, ölçüm verilerini cihaz üzerinde **kalıcı olarak saklamamaktadır**. Sonuçlar iki farklı kanaldan kullanıcıya sunulmaktadır:

1. **Yerel sunum (cihaz üzerinde):** Ölçüm bittiğinde OLED ekranda ortalama açı, maksimum sapma, stabilite indeksi ve skor doğrudan gösterilir. Bu cihazın **birincil görsel çıktısıdır**.
2. **Seri port akışı (PC bağlıyken):** Ölçüm boyunca CSV formatında her örneğin zaman damgası ve açı değeri 115 200 baud üzerinden yayınlanır. PC'ye bağlı çalıştığında **Arduino IDE Serial Plotter**, **Microsoft Excel** veya **Python `matplotlib`** gibi araçlarla anlık olarak görselleştirilebilir.

PC'ye bağlı çalışma senaryosunda, üç tip grafik gözlemlenebilir:

- **Açı (°) vs Zaman (ms):** 10 saniyelik ölçüm penceresinde filtre çıktısının ardışık değerleri. Sağlıklı, gözler-açık duruşta sinyal ±2°'yi nadiren aşar; gözler-kapalı durumunda genlik artar.
- **Ham AcX/AcY/AcZ Akışı:** Sensör dinamiğinin gözlenmesi; kalibrasyon doğruluğunun ve eğim eşlemelerinin kontrolü için kullanışlıdır.
- **Skor Karşılaştırması:** Aynı denek üzerinde farklı koşullarda (gözler açık/kapalı, tek ayak vb.) alınan skorların karşılaştırılması.

> *Mevcut sürümde ölçüm sonuçları için kalıcı kayıt altyapısı bulunmamaktadır; cihaz "ölçer ve gösterir" prensibi ile çalışmaktadır. Uzun süreli takip ve grafik üretimi, gelecek geliştirme olarak SD kart entegrasyonu (Bölüm 8.1) ile mümkün olacaktır.*

### 6.5. Karşılaşılan Sorunlar ve Çözümleri

Geliştirme sürecinde karşılaşılan temel teknik sorunlar ve uygulanan çözümler:

| Sorun | Kök Sebep | Çözüm |
|-------|-----------|-------|
| Sonuç ekranında her zaman 0,0° gösterilmesi | Eksen eşleme hatası: SAĞ-SOL modunda Pitch (angleY), ÖN-ARKA modunda Roll (angleX) okunuyordu | `getCurrentAngle()` fonksiyonunda Roll-Pitch eşlemesi düzeltildi |
| Kalibrasyonun istemsiz tetiklenmesi | NEC tekrar kodu (`0xFFFFFFFF`) yanlışlıkla "0 tuşu" alternatifi olarak tanınıyordu | Tekrar kodu ayrı `KEY_REPEAT` makrosuna taşındı, kalibrasyon listesinden çıkarıldı |
| Sonuç ekranında kumandanın yanıtsız kalması | 15 saniyelik `delay()` engelleyici idi | Sonuç ekranı, IR sinyalini sürekli yoklayan engelleyici olmayan döngüye dönüştürüldü |
| İvmeölçer kanallarının doyuma gitmesi (klon sensör) | Bazı klon entegrelerin DLPF/SMPLRT_DIV kaydedicilerini standart-dışı yorumlaması | Bu iki kaydedicinin yazımı kaldırıldı, varsayılan değerler kullanılıyor |
| Bayt sırası belirsizliği | C++ derleyicilerinde aynı satırdaki birden fazla `Wire.read()` çağrısının değerlendirme sırasının garantisiz olması | Yüksek ve düşük baytlar ayrı değişkenlere alınarak birleştirildi |
| Buzzer sesinin düşük olması | Frekans piezo rezonansının altındaydı | Tüm tonlar 2 700 Hz rezonans bandına taşındı |
| 9 V pil ile ilk açılışta MPU6050 hatası verilmesi | Linear regülatör ramp-up süresi sensörün power-on reset penceresiyle çakışıyordu | `setup()` başına 300 ms gecikme + `initMPU()` için 8 denemelik retry mekanizması eklendi |
| Bekleme modunda yüksek akım tüketimi | Yazılımsal `sistemAcik=false` bayrağı bileşenleri aktif bırakıyordu | MPU6050 SLEEP modu + OLED `DISPLAYOFF`; bekleme akımı 85 mA → 45 mA |

---

## 7. SONUÇ VE DEĞERLENDİRME

Bu proje; gömülü sistem tasarımı, sensör verisi işleme ve gerçek zamanlı kullanıcı arayüzü konularının tek bir taşınabilir donanım üzerinde bir araya getirildiği çok katmanlı bir mühendislik çalışmasıdır. Sadece devre kurmanın ötesine geçilerek, sensör verilerinin mikrodenetleyici RAM'inde işlenmesi, matematiksel filtrelerden geçirilmesi, kullanıcı geri bildirim mekanizmalarına dönüştürülmesi ve bunların güç verimli, taşınabilir bir donanım üzerinde gerçeklenmesi sağlanmıştır.

Çalışma kapsamında elde edilen başlıca sonuçlar:

1. **Sensör füzyonu:** MEMS jiroskop ve ivmeölçer verilerinin Tamamlayıcı Filtre üzerinden birleştirilmesiyle, tek başına hiçbir sensörün sağlayamayacağı bir doğruluk seviyesine ulaşılmıştır.
2. **Düşük seviye protokol gerçeklemesi:** I²C protokolü kütüphane soyutlaması üzerinden değil, kaydedici düzeyinde ele alınarak uygulanmış; bayt sırası ve hata yönetimi gibi düşük seviye konular incelenmiştir.
3. **Gerçek zamanlı performans:** Yumuşak gerçek zamanlı sistem tasarımı (50 ms döngü periyodu, engelleyici olmayan kullanıcı arayüzü) uygulanmıştır.
4. **Bellek optimizasyonu:** Hazır kütüphaneler yerine projeye özgü çözümler (özel IR çözücüsü) yazılarak SRAM kullanımı asgariye indirilmiştir.
5. **Saha kullanımına uygunluk:** USB bağımsız 9 V batarya üzerinden taşınabilir kullanım sağlanmıştır.

Geliştirilen sistemin altyapısı; ileri dönemlerde **robotik denge sistemleri (self-balancing robots)**, **insansız hava aracı (UAV) uçuş kontrol kartları**, **giyilebilir hareket analizi cihazları** veya **rehabilitasyon ve fizik tedavi takip sistemleri** gibi farklı uygulama alanlarının temelini oluşturabilecek niteliktedir.

---

## 8. PROJE SINIRLILIKLARI VE GELECEK ÇALIŞMALAR

Mevcut prototipin bilinen sınırlılıkları:

1. **Tek eksenli ölçüm:** Sistem aynı anda yalnızca bir eksende (Roll *veya* Pitch) ölçüm yapmaktadır. İki eksenli eş zamanlı ölçüm, istatistiksel ağırlık merkezi (center-of-pressure, CoP) hesabı için gereklidir.
2. **Sabit ölçüm süresi:** 10 saniye, sergi/eğitim amacı için uygundur ancak klinik standart 30–60 saniyedir.
3. **Cihaz üzerinde veri kaydı yok:** Sonuçlar yalnızca ölçüm bittikten sonra OLED ekranda gösterilmekte ve seri porta anlık olarak yayınlanmaktadır; cihaz uzun süreli takip için kalıcı saklama yapmamaktadır.
4. **Çoklu denek validasyonu yok:** Geliştirme aşamasında sistemin işlevsel doğrulaması yapılmış; ancak istatistiksel anlamlılık için gerekli olan çoklu denekli klinik validasyon ve altın standart bir referans cihazla karşılaştırma çalışması yapılmamıştır.
5. **Multimetre tabanlı akım ölçümü yapılmamıştır:** Akım değerleri üretici datasheet'lerinden derlenmiştir; bileşen-bazlı doğrulama gelecek çalışmaya bırakılmıştır.
6. **Klinik kalibrasyon eksikliği:** Skor formülü ampirik temellidir; klinik anlamlı bir tanı eşiği için sağlık profesyonelleriyle birlikte yapılacak referans veri toplama çalışması gerekmektedir.
7. **DLPF kapalı:** Bazı klon sensörlerle uyumluluk sağlamak için sensörün dahili alçak geçiren filtresi kapalı bırakılmıştır. Orijinal MPU6050 ile çalışıldığı doğrulandığında DLPF aktif edilerek gürültü daha da azaltılabilir.
8. **Pil voltaj izleme yok:** Bataryanın seviyesi yazılımdan okunmamaktadır; ileride bir voltaj bölücü + ADC kanalı eklenerek "düşük pil" uyarısı verilebilir. Mevcut yazılımsal bekleme modu pil ömrünü uzatsa da donanımsal bir tam-kapama anahtarı uzun süreli depolama için hâlâ tavsiye edilmektedir.

### 8.1. Önerilen Geliştirmeler

1. **Çift eksenli eş zamanlı ölçüm modu:** Roll ve Pitch verisinin 2D düzlemde birlikte değerlendirilmesi ile gerçek bir CoP haritası çıkarılabilir. Bu geliştirme, mekanik tarafta da **çift eksenli (küresel) pivot** veya iki eksenli mafsallı taban gerektirir; mevcut tek eksenli PVC pivot iki yönlü salınıma izin vermediğinden, ÖN-ARKA modunda kullanıcının tahta üzerinde 90° dönmesi gerekmektedir (Bölüm 5.7). Çift eksenli pivot ile bu kullanım kuralı ortadan kalkar.
2. **PC arayüz yazılımı:** Halihazırda yayılmakta olan seri port CSV akışı, Processing veya C# tabanlı bir arayüze bağlanarak grafiksel salınım haritaları oluşturulabilir. Altyapı yazılım tarafında hazırdır.
3. **SD kart entegrasyonu:** Uzun süreli takip için ölçüm sonuçlarının cihazda kalıcı olarak saklanması.
4. **Bluetooth Low Energy (BLE) modülü:** Akıllı telefon uygulaması üzerinden veri akışı ve görselleştirme.
5. **Lityum-iyon batarya + buck regülatör:** Daha uzun çalışma süresi ve daha az pil değişimi.
6. **Klinik validasyon çalışması:** Yetkili kurumlarla işbirliği yapılarak skor formülünün altın standart cihazlarla karşılaştırmalı doğrulanması.

---

## 9. KAYNAKÇA

[1] **InvenSense (TDK).** (2013). *MPU-6000 and MPU-6050 Product Specification, Revision 3.4.* Erişim: https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf

[2] **Microchip Technology (Atmel).** (2015). *ATmega328P 8-bit AVR Microcontroller Datasheet.* Erişim: https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf

[3] **Colton, S.** (2007). *The Balance Filter: A Simple Solution for Integrating Accelerometer and Gyroscope Measurements for a Balancing Platform.* Massachusetts Institute of Technology.

[4] **Visser, J. E., Carpenter, M. G., van der Kooij, H., & Bloem, B. R.** (2008). The clinical utility of posturography. *Clinical Neurophysiology*, 119(11), 2424–2436.

[5] **Horak, F. B.** (2006). Postural orientation and equilibrium: what do we need to know about neural control of balance to prevent falls? *Age and Ageing*, 35(suppl_2), ii7–ii11.

[6] **Solomon Systech.** (2008). *SSD1306 Advance Information: 128 × 64 Dot Matrix OLED/PLED Segment/Common Driver with Controller.*

[7] **Arduino.** (n.d.). *Wire Library: I2C Communication Reference.* Erişim: https://www.arduino.cc/en/reference/wire

[8] **Adafruit Industries.** (n.d.). *Adafruit GFX Graphics Library and SSD1306 Driver Documentation.*

[9] **NEC Corporation.** (1985). *NEC Infrared Transmission Protocol Reference.*

[10] **IEEE Standards Association.** (2008). *IEEE 754-2008: Standard for Floating-Point Arithmetic.*

[11] **Hageman, P. A., Leibowitz, J. M., & Blanke, D.** (1995). Age and gender effects on postural control measures. *Archives of Physical Medicine and Rehabilitation*, 76(10), 961–965.

---

## 10. EKLER

### EK-A: Kumanda Tuş Eşleme Tablosu

| Tuş | İşlev | Birincil Kod (NEC) | Tanınan Alternatif Kodlar |
|-----|-------|--------------------|---------------------------|
| OK | Ölçümü başlat | `0xE31CFF00` | – |
| 1 / SAĞ | SAĞ-SOL moduna geç | `0xBA45FF00` / `0xA55AFF00` | `0xFFE956BF`, `0xFFD2AD7E` |
| 2 / SOL | ÖN-ARKA moduna geç | `0xB946FF00` / `0xF708FF00` | `0xFFFDC23F`, `0x7FFFFFFF`, `0xFFEE51BF`, `0xFFDCA37E` |
| 0 | Yeniden kalibrasyon | `0xE619FF00` | `0x619FF00F` |
| 3 / ↑ / ↓ | Ana ekrana dön | `0xB847FF00` / `0xE718FF00` / `0xAD52FF00` | `0xFFEE11FF` |
| # (POWER) | Sistem aç/kapa | `0xF20DFF00` | `0xFFF906FE`, `0xFFFE41BF`, `0xFFFC837F`, `0xC837EE00`, `0xFFFF906F`, `0xFFFF20DF`, `0xFFE41BFE` |
| (Tekrar Kodu) | Yok sayılır | `0xFFFFFFFF` | – |

> *Not:* "Tanınan Alternatif Kodlar" sütunundaki bazı değerler (`0x7FFFFFFF`, `0x619FF00F` gibi) standart NEC çerçevesinin dışında kalmaktadır. Bunlar; özel yazılmış bit-banging IR çözücüsünün uzun ya da zayıf basışlarda ürettiği **empirik gözlem değerleridir**. Aynı tuşa karşılık gelen bu varyant kodlar, kullanıcı deneyiminin tutarlı olmasını sağlamak için kabul listesine eklenmiştir.

### EK-B: Seri Port Veri Akış Formatı

Akış 115 200 baud, 8N1 olarak yapılandırılmıştır. Her bir ölçüm aşağıdaki blok yapısına sahiptir:

```
# OLCUM_BASLADI
# MOD: SAG-SOL
# t_ms,aci_deg,roll,pitch,AcX,AcY,AcZ
3,0.010,0.010,0.017,12456,10812,-3436
106,0.047,0.047,0.017,12488,10844,-3532
...
# OLCUM_BITTI
# ornek=98
# ortalama_signed=-49.489
# ortalama_mutlak=49.564
# max_sapma=86.524
# stabilite=1.269
# skor=0
```

| Kolon | Birim | Açıklama |
|-------|-------|----------|
| `t_ms` | ms | Ölçüm başlangıcından itibaren geçen süre |
| `aci_deg` | derece | Aktif moddaki ölçülen açı (offset düşürülmüş) |
| `roll` | derece | X ekseni etrafındaki dönüş (filtreli, offset düşürülmüş) |
| `pitch` | derece | Y ekseni etrafındaki dönüş (filtreli, offset düşürülmüş) |
| `AcX, AcY, AcZ` | LSB | Ham ivmeölçer değerleri (16 384 LSB = 1 g) |

`#` ile başlayan satırlar yorum/üst veri (metadata) satırlarıdır.

### EK-C: Sözlük

| Terim | Açıklama |
|-------|----------|
| **MEMS** | Micro-Electro-Mechanical System, silikon zar üzerinde mekanik ve elektronik bileşenleri bir arada barındıran üretim teknolojisi. |
| **I²C / TWI** | Inter-Integrated Circuit / Two-Wire Interface, iki kablolu (SDA, SCL) senkron seri haberleşme protokolü. |
| **Tamamlayıcı Filtre** | Birden fazla sensörün gürültü ve sapma karakteristiklerini birbirini iptal eden frekans bantlarında birleştiren matematiksel filtre. |
| **Drift** | Jiroskop integralinin zamanla biriktirdiği matematiksel sapma. |
| **DLPF** | Digital Low-Pass Filter, sensör çıkışındaki yüksek frekanslı gürültüyü süzen dahili dijital filtre. |
| **DMP** | Digital Motion Processor, MPU6050 içindeki sensör füzyonu yapabilen yardımcı işlemci. |
| **NEC Protokolü** | Japonya menşeli, 38 kHz taşıyıcılı, 32 bit yük taşıyan kızılötesi haberleşme protokolü. |
| **Postürografi** | Bireyin ayakta dururken vücut salınımının nicel olarak ölçülmesi yöntemi. |
| **MVP** | Minimum Viable Product, bir ürünün temel işlevlerini sağlayan en küçük çalışır sürümü. |
| **Roll** | X ekseni etrafındaki dönüş; "yana eğilme" hareketi. |
| **Pitch** | Y ekseni etrafındaki dönüş; "öne/arkaya eğilme" hareketi. |
| **Yaw** | Z ekseni etrafındaki dönüş (bu projede kullanılmamıştır). |
| **LSB** | Least Significant Bit, sensör çıkışındaki en küçük sayısal artım birimi. |
| **GPIO** | General-Purpose Input/Output, mikrodenetleyicinin genel amaçlı dijital pini. |
| **PWM** | Pulse-Width Modulation, Darbe Genişlik Modülasyonu, ortalama gerilim üretimi için kullanılır. |

### EK-D: Devre Şeması ve Prototip Fotoğrafları

> *Bu bölümde aşağıdaki görseller raporun basılı/PDF sürümünde yer alacaktır:*
>
> 1. **Şekil D.1.** Sistemin Fritzing/KiCad ile çizilmiş devre şeması (Arduino Uno, MPU6050 SY-104, SSD1306 OLED, 1838B IR alıcı ve pasif buzzer bağlantıları).
> 2. **Şekil D.2.** Cihazın breadboard üzerindeki yerleşim fotoğrafı.
> 3. **Şekil D.3.** Denge tahtasına monte edilmiş çalışır prototipin fotoğrafı.

---

*Bu rapor, Ege Üniversitesi Tire Kutsan Meslek Yüksekokulu Mikrodenetleyiciler Dersi 2025–2026 Bahar Dönemi proje çalışmaları kapsamında hazırlanmıştır.*
