# SUNUM ÖNCESİ BİLİNMESİ GEREKENLER

> Bu dosya; jüri sunumu öncesinde projeyi anlatırken ve gelebilecek sorulara cevap verirken kullanacağınız temel bilgileri içerir. Dil sade tutulmuştur. Her başlığı bir kez okuyun, kafanızda kalsın.

---

## 1. PROJEYİ 30 SANİYEDE ANLATMAK

> *"Cihazımız, bir kişinin denge durumunu sayısal olarak ölçen taşınabilir bir araçtır. Üzerine çıktığınız küçük bir tahta üzerinde 10 saniye sabit duruyorsunuz; cihaz vücudunuzun ne kadar sallandığını sensörle algılıyor, bunu bir ekrana yön ve puan olarak yazıyor. Hastanelerde kullanılan denge ölçüm cihazları yaklaşık 350 bin TL iken, bizimki yaklaşık 1300 TL. Yani aynı temel ölçümü yapan, çok daha ucuz ve taşınabilir bir alternatif geliştirdik."*

Bu paragrafı ezberleyin. Sunum başında ve "projeyi tanıtın" sorusunda direkt söyleyebilirsiniz.

---

## 2. CİHAZIN PARÇALARI VE GÖREVLERİ (Basit Anlatım)

| Parça | Ne İş Yapar? |
|-------|--------------|
| **Arduino Uno** | Cihazın beyni. Tüm hesaplamalar burada yapılıyor. |
| **MPU6050 sensörü** | Eğim ve hareket ölçer. İçinde iki tip sensör var: ivmeölçer (eğim için) ve jiroskop (dönüş hızı için). |
| **OLED ekran** | Sonuçları gösteriyor. Telefon ekranı gibi küçük (0,96 inç). |
| **Kızılötesi alıcı** | TV kumandası gibi bir kumandadan komut almamızı sağlıyor. |
| **Kumanda** | Kullanıcı buradan ölçümü başlatıyor, mod seçiyor. |
| **Buzzer** | Ölçüm başında ve sonunda ses çıkarıyor; kullanıcıya geri bildirim. |
| **9 V pil** | Cihazı bilgisayara bağlamadan kullanmamızı sağlıyor (taşınabilirlik). |

---

## 3. SİSTEM NASIL ÇALIŞIYOR? (3 Adımlık Basit Akış)

1. **Sensör ölçer:** İvmeölçer ve jiroskop, vücudunuzun eğim açılarını saniyede 20 kez ölçüyor.
2. **Beyin hesaplar:** Arduino, iki sensörden gelen verileri akıllı bir matematik formülüyle birleştiriyor (Tamamlayıcı Filtre). Ortaya tek ve doğru bir açı değeri çıkıyor.
3. **Sonuç gösterilir:** 10 saniyelik ölçüm bittiğinde ekran şunları yazıyor: hangi yöne sallanıyorsunuz (sağ/sol veya ön/arka), ortalama açı, en büyük sapma, kararlılık ve genel bir puan (0–100).

---

## 4. NEDEN İKİ SENSÖR + FİLTRE?

Bu, sunumun en önemli noktalarından biri. Basit anlatım:

> *"Tek başına ivmeölçer kullansak, en ufak titreşimden bile etkilenir, sayılar zıplar. Tek başına jiroskop kullansak, zaman geçtikçe değer kaymaya başlar (drift). İkisini birleştirince ivmeölçerin titreme problemini jiroskop, jiroskopun kayma problemini ivmeölçer dengeliyor. Bu birleştirme işine **Tamamlayıcı Filtre** diyoruz. %96 jiroskoptan, %4 ivmeölçerden alıyor."*

Eğer "neden 0,96?" diye sorulursa: *"Bu literatürde denge ve eğim ölçümü için yaygın kullanılan bir orandır; jiroskoba daha çok güveniyoruz çünkü hızlı ve titreşimsiz, ama uzun vadede ivmeölçerle düzeltme yapıyoruz."*

---

## 5. KALİBRASYON (Sıfırlama)

> *"Cihaz açıldığında sensör küçük üretim hatalarından dolayı sıfır değerinde bile küçük sayılar veriyor. Bunu düzeltmek için cihaz 2 saniye sabit duruyor, biz bu sürede sensör değerlerinin ortalamasını alıp 'işte bu sıfır' diyoruz. Sonra her okumadan bu değeri çıkarıyoruz."*

Kalibrasyon iki aşamalı:
1. **Birinci aşama (~2 sn):** Jiroskobun sıfır değerini bul.
2. **İkinci aşama (~1 sn):** Cihazın o anki duruş açısını "sıfır" olarak kaydet, böylece eğri bir yüzeye konsa bile çalışır.

---

## 6. SKOR NASIL HESAPLANIYOR?

```
Skor = 100 - 5×(Ortalama sapma)  - 2×(En büyük sapma) - 8×(Kararlılık)
```

Sonuç negatifse 0, 100'den büyükse 100 olarak sınırlanıyor.

> *"Üç şeye bakıyoruz: ortalama olarak ne kadar saptınız, bir tek anda ne kadar büyük saptınız, ve ne kadar dalgalandınız. Bu üçü ne kadar küçükse skor o kadar yüksek. Sağlıklı kişilerde 85–95 arası, denge bozukluğu olanlarda 0–40 arası bir skor bekliyoruz."*

> *"Bu skor klinik tanı için değil, kişinin kendi takibi için. Yani 'bu kişi hasta' demiyor, 'bugün dünden 5 puan iyiyim' diyebilmek için."*

---

## 7. İKİ AYRI MOD (Önemli!)

Cihaz **aynı anda iki ekseni ölçmüyor.** Kullanıcı kumanda ile seçiyor:
- **SAĞ-SOL modu (1 tuşu):** Sağa-sola sallanmaya bakıyor
- **ÖN-ARKA modu (2 tuşu):** Öne-arkaya sallanmaya bakıyor

> *"Tek seferde tek bir yöne odaklanıyoruz. Bu, hem hesaplamayı basitleştiriyor hem de kullanıcının sonucu yorumlamasını kolaylaştırıyor."*

---

## 8. PİL VE GÜÇ TASARRUFU

- 9 V alkalin pil ile **yaklaşık 10 saat** kesintisiz çalışıyor (bunu gerçekten ölçtük)
- Kumanda üzerindeki **#** tuşuna basınca cihaz "uyku moduna" giriyor: ekran kapanıyor, sensör bekleme moduna geçiyor, sadece kumanda dinleniyor
- Bu sayede uzun bekleme sürelerinde pil yarı yarıya tasarruflu kullanılıyor
- Tekrar **#** basınca cihaz hemen uyanıyor

---

## 9. PİL İLE AÇILIŞ SORUNU VE ÇÖZÜMÜ

USB ile çalıştırınca cihaz hemen açılıyordu, ama 9 V pile bağlayınca ilk açılışta bazen "MPU6050 HATA" yazıyordu.

**Sebep:** Pil bağlandığında bütün parçalar aynı anda elektrik almaya başlıyor; sensör hazır olmadan beyin sensöre soru soruyor.

**Çözüm:** Cihaz önce 300 milisaniye bekliyor, sonra sensöre soruyor. Eğer cevap gelmezse 250 milisaniye bekleyip tekrar soruyor, en fazla 8 kez. Toplam 2 saniyelik bir pencere açıyoruz.

> *"Bu pencere; sensörün ve pilin yavaş açılışını rahatça karşılıyor. Bunu eklediğimizden beri pil ile açılışta bir daha hata görmedik."*

---

## 10. KARŞILAŞTIĞIMIZ SORUNLAR (Geliştirme Sürecinde)

Bunları sunumda anlatmak iyi olur, gerçek mühendislik gözlemi olduğunu gösterir.

| Sorun | Nasıl Çözdük |
|-------|--------------|
| Ekranda sürekli **"0,0°"** yazıyordu | Programda eksenleri yanlış eşlemişiz; sağ-sol modu yanlış sensör eksenine bakıyordu, düzelttik |
| Kumanda tuşları bazen **kalibrasyonu istemsiz tetikliyordu** | Bir tuşa uzun basınca kumanda "tekrar kodu" yolluyor; biz onu yanlışlıkla "0 tuşu" sanmıştık, ayırdık |
| Sonuç ekranı **kumandayı dinlemiyordu** | 15 saniyelik bekleme tüm sistemi durduruyordu; bunu sürekli kumanda dinleyen bir döngüye çevirdik |
| Buzzer **sesi çok kısıktı** | Frekans yanlıştı, 2700 Hz'e çekince ses belirgin biçimde arttı |
| Pille **açılışta sensör hatası** veriyordu | Yukarıda anlattığımız retry sistemi |

---

## 11. SIKÇA SORULABİLECEK SORULAR VE HAZIR CEVAPLAR

### "Bu cihaz tıbbi olarak kullanılabilir mi?"
> *"Hayır, bu cihaz **klinik tanı aracı değildir**. Bireysel takip ve göreceli karşılaştırma için tasarlandı. Yani kişinin kendi denge performansını zamana göre takip etmesini sağlayabilir, ama 'bu kişide vestibüler bozukluk var' gibi tanı koymak için kullanılamaz. Bunun için sağlık profesyonelleriyle yapılacak klinik kalibrasyon çalışması gerekir."*

### "Sensörünüz ne kadar hassas?"
> *"MPU6050 sensörünün kendi hassasiyeti yaklaşık 0,1 derece. Filtremizle birlikte sistem genelinde yaklaşık 0,5 derecenin altında bir hassasiyet hedefliyoruz. Klinik düzeydeki kuvvet plakaları yaklaşık 0,05 derece, yani yaklaşık 10 kat daha hassas, ama onların maliyeti 100 kat fazla."*

### "Test ettiniz mi?"
> *"Evet, cihazı denge tahtasının ortasına monte ettik, üzerine çıkıp ölçüm aldık. Sistem çalışıyor ve mantıklı sonuçlar veriyor. Ancak çoklu denek üzerinde istatistiksel doğrulama yapmadık, bu gelecek çalışmamız."*

### "Pille ne kadar gidiyor?"
> *"Yaklaşık 10 saat. Bunu gerçekten ölçtük. Uyku modunu da aktif kullanarak."*

### "Maliyetiniz?"
> *"Yaklaşık 1300 TL. Klinik cihazlar 350 bin TL civarı, yani bizimki **binde 4'ü** kadar."*

### "Aynı anda iki ekseni neden ölçmüyorsunuz?"
> *"Kullanıcı sağa-sola sallanırken aynı zamanda öne-arkaya da hafif sallanır, bu doğru. Ama biz tek bir eksene odaklanmayı tercih ettik çünkü hem hesaplama daha basit, hem ekrandaki sonucu yorumlamak daha kolay. İki ekseni birlikte ölçmek (ağırlık merkezi haritası) gelecek geliştirmemiz."*

### "Neden Kalman filtresi değil de Tamamlayıcı filtre?"
> *"Kalman filtresi daha hassas ama matematiği çok ağır. Bizim kullandığımız Arduino Uno'nun işlemcisi 8 bitlik, sınırlı güçte. Kalman'ı bu işlemcide gerçek zamanlı çalıştırmak zor. Tamamlayıcı filtre ise Kalman'a çok yakın doğruluk veriyor ama matematiği basit, birkaç çarpma ve toplama. Bu yüzden tercih ettik. Bu seçim akademik literatürde de yaygın."*

### "Neden bu kadar pahalı (1300 TL)? Daha ucuz olamaz mıydı?"
> *"Türkiye'de perakende fiyatlardan oluşuyor. Toplu üretimde veya direkt ithalatla bu yarı yarıya düşebilir. Ayrıca biz orijinal Arduino Uno aldık, klon kullansaydık ~400 TL daha az olurdu."*

### "Klon Arduino kullansaydınız ne fark ederdi?"
> *"İşlevsel olarak aynı. Sadece kalite kontrolü ve uzun ömür açısından orijinali tercih ettik."*

### "Veri saklıyor mu cihaz?"
> *"Hayır, mevcut sürümde cihaz sadece o anki ölçümü ekrana yazıyor. SD kart ekleyerek geçmiş ölçümleri saklamayı gelecek geliştirmemize ekledik."*

### "Kodu kim yazdı? Kütüphane kullandınız mı?"
> *"İki kişi birlikte yazdık. Standart Arduino kütüphanelerini (Wire, Adafruit GFX, Adafruit SSD1306) kullandık. Ama IR kumanda için **kendi kodumuzu yazdık**, hazır kütüphane yaklaşık 1 KB hafıza yiyordu, biz onu sıfıra indirdik."*

---

## 12. DEMO AKIŞI (Canlı Gösterim Sırası)

Sunumda canlı demo yapacaksanız bu sırayı izleyin:

1. **Cihazı açın** (USB veya pil), "Sistem Başlıyor" yazısı görünür
2. **Kalibrasyon çalışsın**, kalibrasyon sırasında cihaza dokunmayın, sabit tutun
3. **Buzzer 3 kez "tık tık tık" ötecek**, kalibrasyon tamam demek
4. **"SAĞ-SOL" modu yazıyor**, varsayılan mod
5. **Test bireyi denge tahtasına çıksın**
6. **Kumandadan OK tuşuna basın**, "Ölçüm Başlıyor" + kısa bip sesi
7. **10 saniye sayım**, ekranda geri sayım var
8. **Bitince uzun bip** + sonuç ekranı: yön, ortalama açı, max sapma, skor
9. **Sonuç 15 saniye ekrandadır**, herhangi bir tuşa basınca menüye dönülür
10. **Mod değiştirin**, 2 tuşuna basınca "ÖN-ARKA" oluyor
11. **Tekrar ölçüm**, bu kez öne-arkaya sallanın

Eğer **bilgisayara bağlıysanız**, Arduino IDE'deki **Serial Plotter**'ı açıp jüriye gerçek zamanlı grafik gösterebilirsiniz, bu çok etkileyici olur.

---

## 13. ANAHTAR TERİMLER (Eğer Sorulursa)

| Terim | Basit Anlam |
|-------|-------------|
| **MEMS** | Çok küçük (milimetre boyutunda) mekanik+elektronik sensör |
| **I²C** | İki kabloyla cihazların konuşmasını sağlayan bir haberleşme yöntemi |
| **Tamamlayıcı Filtre** | İki sensörün verisini akıllıca birleştiren matematiksel formül |
| **Roll** | Yan-yan eğilme |
| **Pitch** | Öne-arka eğilme |
| **Kalibrasyon** | Cihazı "şu noktadan başla" diye sıfırlamak |
| **Drift / Kayma** | Jiroskop verilerinin zamanla yavaş yavaş yanlış yöne kayması |
| **Bekleme modu** | Cihazın güç tasarrufu için ekran ve sensörü kapatması |
| **Postürografi** | İnsanların denge durumunu ölçen tıbbi yöntem |
| **CSV** | Virgülle ayrılmış sayı dizisi (Excel'de açılır) |

---

## 14. SUNUMDA DİKKAT EDİLECEKLER

- **Demo öncesi pili kontrol edin.** Pil bittiyse "MPU6050 HATA" yazabilir.
- **Cihazı düz yüzeye koyun**, kalibrasyon sırasında titretmeyin.
- **Ölçüm sırasında hareket ettirin**, yoksa "0,0°" görünür ve sayılar değişmez.
- **Kumandayı yakın tutun** (en az 1-2 metre)- uzaktaki sinyaller karışabilir.
- **"Bilmiyorum" demekten korkmayın.** Soruları çevirmek yerine "bunu test etmedik, ileri çalışmaya bıraktık" demek daha güvenli.

---

## 15. BÜTÜNCÜL HAFIZA NOTU

| Sayı | Anlamı |
|------|--------|
| **1 300 TL** | Toplam donanım maliyeti |
| **350 000 TL** | Klinik cihaz fiyat referansı (≥ 10 000 USD) |
| **~10 saat** | 9 V pil ile çalışma süresi (ölçüldü) |
| **10 saniye** | Tek ölçüm süresi |
| **20 Hz** | Saniyede 20 ölçüm |
| **1 000 örnek** | Kalibrasyon ölçümü sayısı |
| **0,96** | Tamamlayıcı filtre katsayısı |
| **2 700 Hz** | Buzzer çalma frekansı |
| **115 200 baud** | Bilgisayara veri yollama hızı |
| **±2 g** | İvmeölçer ölçüm aralığı |
| **±250 °/s** | Jiroskop ölçüm aralığı |
| **0x68** | Sensörün I²C adresi |
| **0x3C** | Ekranın I²C adresi |
| **D7, D8** | Buzzer ve IR alıcı pinleri |
| **A4, A5** | I²C SDA ve SCL pinleri |

Bu sayıları aklınızda tutarsanız her soruyu cevaplayabilirsiniz.

---

*Hazırlayan: Kayra DEMİRKAN, Samet TOKDEMİR, Mayıs 2026*
