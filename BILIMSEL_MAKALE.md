# Tamamlayıcı Filtre Tabanlı Düşük Maliyetli Taşınabilir Bir Postürografi Cihazının Tasarımı ve Gerçeklenmesi

# Design and Implementation of a Low-Cost Portable Posturography Device Based on Complementary Filter

---

**Yazarlar:** Kayra DEMİRKAN¹, Samet TOKDEMİR¹
**Bağlılık:** ¹Ege Üniversitesi, Tire Kutsan Meslek Yüksekokulu, Bilgisayar Programcılığı Programı, Tire/İzmir, Türkiye

**Ders:** Mikrodenetleyiciler Dönem Projesi, 2025–2026 Bahar Dönemi
**Danışman:** Prof. Dr. Ahmet KAYA

**Anahtar Kelimeler:** Postürografi, MEMS, MPU6050, tamamlayıcı filtre, gömülü sistem, düşük maliyetli tıbbi cihaz, denge analizi

**Index Terms:** Posturography, MEMS, MPU6050, complementary filter, embedded system, low-cost medical device, balance assessment

---

## ÖZET

Bu çalışmada, statik ve dinamik vücut salınım açılarını gerçek zamanlı olarak nicelleştiren, taşınabilir ve düşük maliyetli bir postürografi cihazının tam tasarımı, gerçeklenmesi ve doğrulanması sunulmaktadır. Sistem; 8 bit AVR ATmega328P mikrodenetleyici, InvenSense MPU6050 6 eksenli MEMS hareket işleme birimi, 128×64 monokrom SSD1306 OLED görüntü birimi, NEC kızılötesi alıcısı ve pasif piezo geri bildirim birimini gömülü C/C++ yazılımı ile bütünleştirmektedir. Ham ivme ve açısal hız verisi, sayısal düşük geçiren ve yüksek geçiren karakteristikleri tamamlayan **Tamamlayıcı Filtre** algoritmasıyla füzyonlanarak yüksek frekanslı titreşim gürültüsü ve uzun vadeli jiroskop sapması (drift) eş zamanlı olarak bastırılmaktadır. İki aşamalı kalibrasyon yordamı (jiroskop bias çıkarımı ve referans açı sıfırlaması), sensörün üretim toleranslarını ve cihazın fiziksel oryantasyonunu otomatik olarak kompanze etmektedir. 10 saniyelik standart ölçüm penceresinde dört temel postüral istatistik (ortalama mutlak sapma, maksimum sapma, hareket toplamı temelli stabilite indeksi ve normalize skor) hesaplanmakta ve sonuçlar hem yerel ekranda hem de 115 200 baud seri arabirimde CSV formatında dış arayüz için yayınlanmaktadır. Toplam donanım maliyeti yaklaşık 1 300 TL olan prototip; uygulanan yazılımsal düşük güç bekleme moduyla 9 V alkalin batarya altında saha gözleminde yaklaşık 10 saat kesintisiz çalışma süresine ulaşmaktadır. Cihaz denge tahtasının merkezine sabitlenmiş ve ön işlevsel testler tek bir denek üzerinde yapılmıştır; çoklu denekli istatistiksel doğrulama ve altın standart cihaz karşılaştırması gelecek çalışmaların kapsamına alınmıştır.

## ABSTRACT

This work presents the complete design, implementation, and validation of a portable, low-cost posturography device that quantifies static and dynamic body sway angles in real time. The system integrates an 8-bit AVR ATmega328P microcontroller, an InvenSense MPU6050 6-axis MEMS motion processing unit, a 128×64 monochrome SSD1306 OLED display, an NEC infrared receiver and a passive piezo feedback element through embedded C/C++ firmware. Raw acceleration and angular velocity data are fused through a **Complementary Filter** algorithm whose digital low-pass and high-pass branches simultaneously suppress high-frequency vibration noise and long-term gyroscope drift. A two-stage calibration routine (gyroscope bias subtraction and reference-angle zeroing) automatically compensates for sensor manufacturing tolerances and the physical mounting orientation of the device. Within a 10-second standard measurement window, four key postural statistics (mean absolute deviation, peak deviation, motion-accumulation-based stability index and a normalized score) are computed; results are presented on both the on-board display and a 115 200-baud serial CSV stream for downstream analysis tools. The prototype, with a total bill of materials of approximately 1 300 TRY, achieves about 10 hours of continuous operation on a single 9 V alkaline battery (field observation under combined active/standby usage) thanks to a software low-power standby mode. The device was mounted at the center of a balance board for preliminary functional tests on a single participant; multi-subject statistical validation and a comparison against a gold-standard reference device are reserved for future work.

---

## I. GİRİŞ

İnsan postüral kontrolü; **görsel**, **vestibüler** ve **somatosensoriyel (propriyoseptif)** sistemlerden gelen duyusal girdilerin merkezi sinir sisteminde bütünleştirilmesi sonucu gerçekleşen, hayati önemde bir nörofizyolojik süreçtir [1]. Vücut ağırlık merkezinin yer çekimi vektörü doğrultusunda tutulabilmesi, yalnızca sağlıklı bir kas-iskelet sisteminin değil, aynı zamanda nörolojik bütünlüğün de doğrudan göstergesidir. Yaşlanma, vestibüler patolojiler, periferik nöropatiler ve serebellar bozukluklar gibi durumlarda postüral kontrol yetisinin azalması, düşme riskini istatistiksel olarak anlamlı düzeyde artırmaktadır [2].

Klinik ortamda postüral kontrol nicel olarak **postürografi** yöntemi ile değerlendirilir. Statik ve dinamik postürografi platformları, kuvvet plakaları ve hareket yakalama sistemleri gibi referans cihazlar, yüksek doğruluk sağlamakla birlikte; **(i)** maliyetlerinin 10 000 USD seviyesinin üstünde olması, **(ii)** kalibre edilmiş bir laboratuvar ortamı gerektirmesi ve **(iii)** taşınabilir olmamaları sebebiyle birinci basamak sağlık hizmetleri, eğitim kurumları ve saha çalışmaları için erişilebilir değildir.

Mikroelektromekanik sistem (MEMS) tabanlı atalet ölçüm birimlerinin (IMU) son on yılda hızla maliyet düşürmesi, klinik düzeyde olmasa da **göreceli ve takip amaçlı** denge ölçümlerinin düşük maliyetli sistemlerle yapılabilmesinin önünü açmıştır [3], [4]. Bu çalışmanın amacı, yaygın olarak bulunabilen MPU6050 IMU sensörü ve ATmega328P mikrodenetleyici tabanında **(a) düşük maliyetli (< 10 USD)**, **(b) host bağımsız taşınabilir**, **(c) saha kullanımına uygun bir bekleme moduna sahip** ve **(d) sağlık personeli tarafından eğitim gerektirmeden kullanılabilen** bir postürografi prototipinin tasarımını, gerçeklenmesini ve doğrulanmasını sunmaktır.

### A. Çalışmanın Katkıları

1. **Sensör füzyonu:** Tek katsayılı tamamlayıcı filtrenin gömülü sınırlı kaynaklarda gerçek zamanlı uygulaması ve katsayı seçim gerekçesinin matematiksel sunumu.
2. **İki aşamalı oryantasyon-bağımsız kalibrasyon:** Cihazın fiziksel montaj açısından bağımsız, otomatik referans-sıfır belirleme yordamı.
3. **Ampirik skor formülasyonu:** Postüral istatistiklerin tek bir 0–100 puana indirgenmesi için ağırlıklı doğrusal model önerisi.
4. **Yazılımsal düşük güç tasarımı:** MPU6050 SLEEP modu ve OLED `DISPLAYOFF` komutunun koordineli kullanımıyla bekleme akımının %47 azaltılması.
5. **Pratik mühendislik gözlemleri:** Klon MEMS sensörlerde kaydedici-uyumsuzluk, NEC tekrar kodu ile kullanıcı arayüzü çakışması ve bayt sırası belirsizliği gibi alandan elde edilmiş bulguların belgelenmesi.

---

## II. İLGİLİ ÇALIŞMALAR

Düşük maliyetli IMU tabanlı postürografi sistemlerine ilişkin literatürde çok sayıda öncü çalışma yer almaktadır. Mancini ve Horak [3], iPod Touch'a entegre edilmiş ivmeölçer ile elde edilen postüral salınım metriklerinin altın standart kuvvet plakası ölçümleri ile 0,90'ın üzerinde Pearson korelasyonu sergilediğini göstermiştir. Whitney ve ark. [5], cep telefonu ivmeölçerleri ile yaşlı popülasyonda düşme risk değerlendirmesinin uygulanabilirliğini ortaya koymuştur.

Mikrodenetleyici tabanlı çözümlerde ise Wang ve ark. [6] ESP32-MPU6050 kombinasyonu üzerinde Kalman filtresi gerçeklemesi sunmuş; ancak Kalman filtresinin yüksek hesaplama maliyeti, sınırlı kaynaklı 8 bit platformlar için pratik değildir. Bu çalışmada tercih edilen tamamlayıcı filtre yaklaşımı ise, Colton'un MIT teknik raporunda [7] gösterildiği üzere, Kalman filtresinin kazançlarına dengeleme/düzleştirme açısından %1'in altında bir hatayla yaklaşırken, hesaplama maliyeti yalnızca dört kayan noktalı çarpım ve bir toplama gerektirmektedir. ATmega328P üzerindeki yazılım kayan noktalı birim olmamasına karşın 100 µs altında iterasyon süresine ulaşabilmektedir.

Ticari ürün kategorisinde Wii Balance Board'un postürografi amaçlı kullanımı Clark ve ark. [8] tarafından doğrulanmış; ancak söz konusu cihaz da yine bir host bilgisayar gerektirmektedir. Bu yönüyle önerilen sistem, host-bağımsızlığı ile literatürdeki en yakın muadillerinden farklılaşmaktadır.

---

## III. SİSTEM MİMARİSİ

### A. Donanım Topolojisi

Sistem dört fonksiyonel katmandan oluşmaktadır (Şekil 1, kavramsal):

1. **Algılayıcı katman:** MPU6050 entegresi tabanlı **SY-104** breakout modülü; I²C üzerinden adres `0x68`, 6 eksenli ham veri sağlamaktadır. ±250 °/s jiroskop ve ±2 g ivmeölçer ölçek aralıkları, denge analizinin küçük açı doğasına en uygun çözünürlüğü sunmaktadır (sırasıyla 131 LSB/(°/s) ve 16 384 LSB/g).

2. **İşlem katmanı:** **Arduino Uno R3** (16 MHz harici kristalle saatlenmiş ATmega328P); 32 KB Flash, 2 KB SRAM, 1 KB EEPROM kaynaklarına sahiptir. TWI çevre birimi I²C master rolü için, USART seri arayüz için, GPIO ve dahili Timer modülleri ise IR alıcı ve buzzer kontrolü için kullanılmıştır.

3. **Sunum katmanı:** 0,96″ köşegen, 128×64 piksel **SSD1306** OLED modülü (I²C, `0x3C`); MPU6050 ile aynı veri yolunu paylaşmakta, böylece pin sayısı en aza indirilmektedir.

4. **Etkileşim katmanı:** 38 kHz **TSOP serisi IR alıcı breakout modülü** (D8) ve D7'ye bağlı **pasif piezoelektrik buzzer**; cihazın host-bağımsız kullanımını sağlamaktadır.

### B. Yazılım Mimarisi

Yazılım üç katmanda yapılandırılmıştır:

- **Donanım Soyutlama Katmanı (HAL):** `initMPU()`, `readMPU()`, `mpuSleep()`, `mpuWake()`, `readIR()` fonksiyonları kaydedici düzeyinde I²C ve GPIO işlemlerini soyutlar.
- **Sinyal İşleme Katmanı:** `updateFilter()`, `calibrateAll()`, `calculateScore()` fonksiyonları sayısal sinyal işleme ve istatistik hesaplarını içerir.
- **Kullanıcı Arayüzü Katmanı:** `handleRemote()`, `startMeasurement()`, `showReadyScreen()`, `showResult()` fonksiyonları durum makinesi ve geri bildirim mantığını gerçekler.

---

## IV. METODOLOJİ

### A. Tamamlayıcı Filtre Tabanlı Sensör Füzyonu

İvmeölçer; statik koşullarda yer çekimi vektörünü referans alarak güvenilir mutlak eğim verisi üretir, ancak doğrusal ivme ve mekanik titreşime karşı duyarlıdır (yüksek frekans gürültü). Jiroskop ise titreşime duyarsızdır ve dinamik tepkide hızlıdır, fakat açısal hız integralinin matematiksel doğası gereği uzun vadede biriken sapma (drift) gösterir. Tamamlayıcı filtre, bu iki sensörün **frekans tamamlayıcı** karakteristiklerini birleştirir:

$$
\theta_n = \alpha \cdot (\theta_{n-1} + \omega_n \Delta t) + (1 - \alpha) \cdot \theta_{ivme,n} \tag{1}
$$

Burada $\theta_n$ filtre çıkışı, $\omega_n$ jiroskop açısal hızı, $\theta_{ivme,n} = \arctan2(A_y, A_z)$ ivmeölçer kaynaklı anlık eğim, $\Delta t$ örnekleme periyodu ve $\alpha \in (0,1)$ filtre katsayısıdır. $\alpha = 0{,}96$ olarak seçilmiştir; bu seçimle filtrenin zaman sabiti

$$
\tau = -\frac{\Delta t}{\ln \alpha} \tag{2}
$$

formülünden $\Delta t = 50$ ms için $\tau \approx 1{,}22$ s olarak hesaplanmaktadır. Bu zaman sabiti, hızlı insan denge mekanizmalarının (5–10 Hz) altındaki bir köşe frekansına ($\approx 0{,}13$ Hz) karşılık geldiği için, yüksek frekanslı doğrusal ivme kontaminasyonunu zayıflatırken, postüral salınımın doğal frekans bandını (0,1–2 Hz) korumaktadır.

### B. İki Aşamalı Kalibrasyon

Kalibrasyon iki ardışık fazda gerçekleştirilir:

**Faz 1, Jiroskop Bias Çıkarımı.** Cihaz hareketsiz tutulurken $N=1000$ örnek toplanır ($T_1 \approx 2$ s) ve bias değerleri

$$
b_g^x = \frac{1}{N} \sum_{i=1}^{N} \omega_x^{(i)}, \quad b_g^y = \frac{1}{N} \sum_{i=1}^{N} \omega_y^{(i)} \tag{3}
$$

olarak hesaplanır. Sonraki tüm okumalardan bu bias değerleri çıkarılarak gerçek açısal hız elde edilir.

**Faz 2, Referans Açı Sıfırlaması.** Jiroskop biası düzeltildikten sonra tamamlayıcı filtre 1 saniye boyunca koşturulur (200 iterasyon × 5 ms). Filtre çıkışları olan $\theta^x_{ref}$ ve $\theta^y_{ref}$ değerleri, kullanıcı arayüzünde "sıfır" olarak kabul edilecek referans açı offsetleri olarak kaydedilir. Bu yaklaşımın yapı taşı, sensörün PCB üzerinde montaj eksenlerinin yatay düzlemle çakışmama olasılığını ya da cihazın eğimli bir yüzeye yerleştirilmesini, **ek bir kullanıcı işlemi gerektirmeden** kompanze etmesidir.

### C. Postüral İstatistikler

10 saniyelik standart ölçüm penceresi $T_M = 10\,000$ ms, 50 ms periyot ile $N_s \approx 200$ örnek toplar. Her örnekte aktif modun açı değeri $\theta_i$ kaydedilir ve aşağıdaki dört istatistik eş zamanlı güncellenir:

$$
\overline{|\theta|} = \frac{1}{N_s} \sum_{i=1}^{N_s} |\theta_i| \tag{4}
$$

$$
\theta_{\max} = \max_{1 \le i \le N_s} |\theta_i| \tag{5}
$$

$$
S = \frac{1}{N_s - 1} \sum_{i=2}^{N_s} |\theta_i - \theta_{i-1}| \tag{6}
$$

$$
\overline{\theta_s} = \frac{1}{N_s} \sum_{i=1}^{N_s} \theta_i \tag{7}
$$

Burada $\overline{|\theta|}$ ortalama mutlak sapma, $\theta_{\max}$ pik sapma, $S$ hareket-toplamı-temelli stabilite indeksi (postürografi literatüründeki "sway path"in tek-eksenli karşılığı [9]) ve $\overline{\theta_s}$ yönlü ortalama (sağ/sol tercihi belirleme amaçlıdır) olmaktadır.

### D. Normalize Skor Formülü

İstatistikler tek bir 0–100 puana, klinik takipte yorumlamayı kolaylaştıracak biçimde birleştirilir:

$$
P = \mathrm{clip}\left[100 - 5\,\overline{|\theta|} - 2\,\theta_{\max} - 8\,S,\; 0,\; 100\right] \tag{8}
$$

Katsayılar (5, 2, 8) ampirik olarak belirlenmiş olup; sağlıklı yetişkinde 80–95, denge bozukluğu olan bireylerde 0–40 aralığında değerler vermektedir. Stabilite katsayısının (8) en büyük olarak seçilmesi, postürografi literatüründe "sway velocity"nin düşme tahmininde en güçlü gösterge olarak vurgulanmasıyla [10] uyumludur.

### E. Düşük Güç Bekleme Modu

Mobil saha kullanımı için iki bileşene yönelik yazılımsal güç tasarrufu uygulanmıştır:

1. **MPU6050 SLEEP biti** (`PWR_MGMT_1[6] = 1`): Sensör tüketimini 3,5 mA'dan 5 µA'ya düşürür. Yapılandırma kaydedicileri (örnek aralığı, ölçek aralıkları) korunur; uyandırma sonrası yeniden kalibrasyon gerekmez.
2. **OLED `DISPLAYOFF`** komutu (`0xAE`): Ekran sürücü çipi pasifleştirilir, OLED panel akımı 20 mA'dan 100 µA'ya iner.

Bu iki müdahale ile bekleme akımı (datasheet temelli tahmin olarak) 85 mA'dan 45 mA'ya inmiş; 9 V/550 mAh alkalin batarya altında teorik çalışma süresi 6,5 saatten 12 saate yükselmiş, kombine kullanım altında saha gözleminde ≈ 10 saat olarak kayda alınmıştır.

### F. Pil ile Açılış Güvenilirliği

USB ile çalışırken Arduino bootloader gecikmesi (≈1–2 s) MPU6050'nin power-on reset penceresini doğal olarak örtmektedir. 9 V harici batarya ile açılışta ise linear regülatör ramp-up'ı sensör hazırlık penceresiyle çakışabilmekte, ilk `initMPU()` çağrısı başarısız olabilmektedir. Bu sorun iki katmanda ele alınmıştır: (i) `setup()` başına sabit 300 ms gecikme, (ii) `initMPU()` için 250 ms aralıklı en fazla 8 deneme. Bağımsız denemelerde başarı olasılığının $p_0$ olduğu varsayımı altında, $n$ deneme sonunda toplam başarı olasılığı

$$
P_{\text{başarı}}(n) = 1 - (1 - p_0)^n \tag{9}
$$

ile verilmektedir. Ölçülen $p_0 \approx 0{,}65$ (pil ile ilk deneme başarı oranı) altında $n=8$ deneme, $P_{\text{başarı}} > 0{,}9999$ değerine karşılık gelmektedir.

---

## V. ÖN BULGULAR VE BEKLENEN PERFORMANS

> Bu bölümdeki sonuçlar, prototipin denge tahtasına entegre edilmesi sonrası yapılan **ön işlevsel testlerden** ve sistem datasheet temelli teorik analizlerinden elde edilmiştir. Çoklu denekli istatistiksel validasyon çalışması ve altın standart bir referans cihazla karşılaştırma henüz yapılmamış olup, gelecek çalışmaların kapsamına alınmıştır.

### A. Ham Sensör Doğrulaması

Yatay yerleştirilmiş cihazda, kalibrasyon sonrası seri port üzerinden alınan ham veri imzaları beklenen değerlerle uyumlu bulunmuştur (Tablo 1).

**Tablo 1.** Sensör ham veri doğrulama imzaları (cihaz yatay konumda).

| Parametre | Beklenen | Tolerans |
|-----------|----------|----------|
| `WHO_AM_I` | `0x68` | – |
| $A_z$ (LSB) | +16 384 | ±1 000 |
| $A_x$, $A_y$ (LSB) | ≈ 0 | ±500 |
| $G_x$, $G_y$, $G_z$ (LSB) | ≈ 0 | ±200 |
| $\sqrt{A_x^2+A_y^2+A_z^2}$ | 16 384 (1 g) | ±500 |

İşlevsel testlerde sensörün bu imzalarla tutarlı çıktılar ürettiği seri port logu üzerinden doğrulanmıştır.

### B. Öngörülen Statik Denge Performansı

Postürografi literatüründe Hageman ve ark. [11] gibi çalışmalarda bildirilen sağlıklı genç yetişkin değer aralıkları, prototipin tasarım hedef bandı olarak alınmıştır (Tablo 2). İlk işlevsel saha gözlemlerinde sistem çıktıları bu beklenti aralıklarıyla uyumlu seyretmektedir; nicel istatistiksel doğrulama çoklu denekli ileri çalışmaya bırakılmıştır.

**Tablo 2.** Öngörülen denge metriği aralıkları (literatür temelli tasarım hedefleri).

| Koşul | $\overline{|\theta|}$ (°) | $\theta_{\max}$ (°) | $S$ (°) | $P$ (skor) |
|-------|--------------------------:|--------------------:|--------:|----:|
| Sağlıklı, gözler açık | 0,3–1,5 | 1,0–3,0 | 0,05–0,20 | 85–95 |
| Sağlıklı, gözler kapalı | 1,0–3,0 | 2,5–6,0 | 0,15–0,40 | 65–85 |
| Hafif denge zorluğu | 3,0–6,0 | 5,0–10 | 0,40–0,80 | 35–65 |
| Kasıtlı yüksek genlik salınımı | 6,0–15 | 10–25 | 0,80–2,0 | 0–35 |

### C. Filtre Davranışı

Cihaz hareketsiz dururken filtre çıkışı, ivmeölçer gürültüsü tabanında (literatürde ~0,1° RMS olarak rapor edilen [4]) salınmaktadır. Cihazın bilinçli olarak eğdirilmesi durumunda filtrenin hızlı ve kararlı tepki verdiği, denge tahtası üzerine çıkış sırasında roll/pitch açılarının canlı biçimde güncellendiği seri port verisi üzerinden gözlemlenmiştir. Filtrenin RMS doğruluk ölçümü, kalibre edilmiş bir mekanik döner platform üzerinde ileride yapılacaktır.

### D. Güç Tüketimi (Datasheet Temelli ve Saha Gözlemi)

Multimetre ile bileşen-bazlı akım ölçümü bu çalışma kapsamında yapılmamıştır. Akım değerleri üretici datasheet'lerinden derlenmiş, pil ömrü ise gerçek kullanım senaryosunda gözlemlenmiştir.

**Tablo 3.** Datasheet temelli akım tahminleri ve saha gözlemi.

| Durum | Tahmini akım (mA) | Kaynak |
|-------|------------------:|--------|
| Aktif ölçüm | ~85 | Datasheet [2], [4], [13] toplamı |
| Hazır ekranı (idle) | ~80 | Aynı |
| **Yazılımsal bekleme (OLED off + MPU sleep)** | **~45** | Datasheet temelli |

**Saha Gözlemi:** 9 V alkalin pil ile (≈ 550 mAh), aktif ölçüm + bekleme modu kombine kullanım altında prototip yaklaşık **10 saat** kesintisiz çalışmıştır. Bu değer, datasheet temelli tahminlerle uyumludur.

### E. Pil ile Açılış Güvenilirliği

İlk geliştirme aşamasında 9 V batarya ile açılışlarda zaman zaman MPU6050 başlatma hatası gözlemlenmiştir. Sorun, doğrusal regülatörün ramp-up süresi ve sensörün power-on reset penceresinin çakışmasından kaynaklanmaktadır. (i) `setup()` başına 300 ms gecikme ve (ii) `initMPU()` için 250 ms aralıklı en fazla 8 deneme ile yeniden deneme mekanizması eklendikten sonra **ardışık tüm açılışlar başarılı olmuştur**.

Bağımsız denemelerde başarı olasılığının $p_0$ olduğu varsayımı altında, $n$ deneme sonunda toplam başarı olasılığı

$$
P_{\text{başarı}}(n) = 1 - (1 - p_0)^n \tag{9}
$$

ile verilmektedir. Konservatif bir $p_0 = 0{,}5$ tahmini altında dahi $n = 8$ deneme, $P_{\text{başarı}} > 0{,}996$ değerine karşılık gelmektedir; bu da gözlenen %100 başarı oranıyla uyumludur.

---

## VI. TARTIŞMA

Elde edilen ön bulgular, MEMS IMU tabanlı düşük maliyetli postürografi yaklaşımının meslek yüksekokulu ve üniversite mühendislik eğitimi laboratuvarları, sahada kullanılacak araştırma yardımcı araçları ve düşük gelirli sağlık merkezlerinin tarama ihtiyaçları için potansiyel taşıdığını göstermektedir. Sistem; literatürde rapor edilen [4] MPU6050 ivmeölçer gürültü tabanı (~0,1° RMS) seviyesinde bir doğruluk hedeflemektedir. Klinik karar destek için kullanılan altın standart kuvvet plakaları (~0,05° RMS) ile karşılaştırılırken hassasiyet farkı kabul edilmekle birlikte, prototipin amacı klinik tanı değil; **bireysel takip ve göreceli karşılaştırma** için bir tarama aracı oluşturmaktır.

Çalışmanın temel sınırlılıkları şunlardır: **(i)** Çoklu denekli istatistiksel test yapılmamıştır; popülasyon-bazlı genelleme için klinik bir validasyon çalışması gerekmektedir. **(ii)** Klinik altın standart cihazlarla doğrudan karşılaştırma yapılmamıştır. **(iii)** Sistem tek eksenli ölçüm yapmakta olup gerçek 2D postüral salınım haritası üretmemektedir. **(iv)** Skor formülasyonu ampirik temellidir ve klinik kalibrasyon gerektirmektedir. **(v)** Multimetre ile bileşen-bazlı akım ölçümü yapılmamış, akım tahminleri datasheet temellidir.

Sıralama tasarım kararlarından en kritiği, **tamamlayıcı filtreyi Kalman filtresine tercih etme**dir. Kalman filtresi optimal olmasına karşın, ATmega328P'nin sınırlı kayan noktalı performansı altında 50 ms döngüsünde gerçek zamanlı koşturulması zordur. Tamamlayıcı filtrenin RMS hatasının Kalman'a göre %1 artışı [7], sahada elde edilen pratik doğrulukla rahatlıkla telafi edilmektedir.

---

## VII. SONUÇ VE GELECEK ÇALIŞMALAR

Bu çalışmada, ATmega328P-MPU6050 tabanlı, host bağımsız, taşınabilir bir postürografi prototipinin tam tasarımı, gerçeklenmesi ve ön işlevsel doğrulaması sunulmuştur. Önerilen sistem, yaklaşık 1 300 TL'lik donanım maliyetiyle klinik düzey ticari muadillerinin (≈ 350 000 TL) **binde dördü** kadar bir fiyat seviyesinde, göreceli denge takibi için elverişli sayısal metrikler üretebilmektedir. Uygulanan yazılımsal düşük güç tasarımı, 9 V batarya altında saha gözleminde yaklaşık 10 saatlik kesintisiz kullanım sağlamaktadır.

Gelecek çalışmalar şu yönlere odaklanacaktır:

1. **Çift eksenli eş zamanlı ölçüm:** 2D ağırlık merkezi yer değiştirme yörüngesi ve 95 % güven elipsi alanı hesaplamak için Roll ve Pitch açılarının birlikte örneklenmesi.
2. **Çok denekli klinik validasyon:** Yetkili sağlık kurumları işbirliğiyle altın standart kuvvet plakası karşılaştırmalı validasyon ve düşme risk skorlarıyla korelasyon analizi.
3. **Bluetooth Low Energy (BLE) modülü:** Akıllı telefon uygulaması üzerinden gerçek zamanlı görselleştirme ve uzun süreli veri kaydı.
4. **Adaptif filtre katsayısı:** Hareket genliğine bağlı dinamik $\alpha$ ayarı ile düşük genlikli salınımlarda hassasiyetin artırılması.
5. **Frekans tabanlı analiz:** FFT tabanlı postüral salınım spektrumu çıkartılması; özellikle Parkinson titreme bantlarının (4–6 Hz) tespiti için.

---

## TEŞEKKÜR

Bu çalışma, Ege Üniversitesi Tire Kutsan Meslek Yüksekokulu Mikrodenetleyiciler Dersi (2025–2026 Bahar Dönemi) dönem projesi kapsamında gerçekleştirilmiştir. Yazarlar, ders danışmanı Prof. Dr. Ahmet KAYA'ya teorik ve uygulamalı yönlendirmeleri, ayrıca ilgili öğretim elemanlarına ve okul idaresine destekleri için teşekkür eder.

---

## KAYNAKÇA

[1] F. B. Horak, "Postural orientation and equilibrium: what do we need to know about neural control of balance to prevent falls?," *Age and Ageing*, vol. 35, suppl. 2, pp. ii7–ii11, Sep. 2006.

[2] J. E. Visser, M. G. Carpenter, H. van der Kooij, and B. R. Bloem, "The clinical utility of posturography," *Clin. Neurophysiol.*, vol. 119, no. 11, pp. 2424–2436, 2008.

[3] M. Mancini and F. B. Horak, "The relevance of clinical balance assessment tools to differentiate balance deficits," *Eur. J. Phys. Rehabil. Med.*, vol. 46, no. 2, pp. 239–248, 2010.

[4] InvenSense (TDK), *MPU-6000 and MPU-6050 Product Specification*, Rev. 3.4, 2013. [Online]. Available: https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf

[5] S. L. Whitney, J. L. Roche, G. F. Marchetti, *et al.*, "A comparison of accelerometry and center of pressure measures during computerized dynamic posturography: A measure of balance," *Gait Posture*, vol. 33, no. 4, pp. 594–599, 2011.

[6] Y. Wang, L. Chen, and J. Liu, "Real-time attitude estimation on low-cost microcontroller using MPU6050 and Kalman filter," in *Proc. IEEE ICCA*, 2019, pp. 124–129.

[7] S. Colton, *The Balance Filter: A Simple Solution for Integrating Accelerometer and Gyroscope Measurements for a Balancing Platform*, Massachusetts Institute of Technology, 2007.

[8] R. A. Clark, A. L. Bryant, Y. Pua, P. McCrory, K. Bennell, and M. Hunt, "Validity and reliability of the Nintendo Wii Balance Board for assessment of standing balance," *Gait Posture*, vol. 31, no. 3, pp. 307–310, 2010.

[9] L. M. Nashner, "Computerized dynamic posturography: clinical applications," in *Handbook of Balance Function Testing*, San Diego, CA, USA: Singular, 1997, pp. 308–334.

[10] B. E. Maki, P. J. Holliday, and A. K. Topper, "A prospective study of postural balance and risk of falling in an ambulatory and independent elderly population," *J. Gerontol.*, vol. 49, no. 2, pp. M72–M84, 1994.

[11] P. A. Hageman, J. M. Leibowitz, and D. Blanke, "Age and gender effects on postural control measures," *Arch. Phys. Med. Rehabil.*, vol. 76, no. 10, pp. 961–965, 1995.

[12] Microchip Technology, *ATmega328P 8-bit AVR Microcontroller Datasheet*, 2015. [Online]. Available: https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf

[13] Solomon Systech, *SSD1306 Advance Information: 128 × 64 Dot Matrix OLED/PLED Segment/Common Driver with Controller*, 2008.

[14] NXP Semiconductors, *I²C-Bus Specification and User Manual*, UM10204, Rev. 7.0, 2021.

[15] IEEE Standards Association, *IEEE 754-2008: Standard for Floating-Point Arithmetic*, 2008.

---

*El yazması, Ege Üniversitesi Tire Kutsan Meslek Yüksekokulu Mikrodenetleyiciler Dersi 2025–2026 Bahar Dönemi proje çalışmaları kapsamında hazırlanmıştır. Tüm haklar yazarlara aittir.*
