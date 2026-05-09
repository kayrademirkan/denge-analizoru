# SUNUM TASLAĞI, Dijital Denge Analizörü

> **Hedef süre:** 10–12 dakika anlatım + 3–5 dakika soru-cevap
> **Slayt sayısı:** 14 ana + 1 kapanış
> **Dil:** Sade, jargonsuz Türkçe
> **Format:** Bu dosyanın en altında **Claude için sunum üretme prompt'u** vardır.

---

## SLAYT 1, Kapak

**Başlık (büyük):**
SENSÖR TABANLI DİJİTAL DENGE ANALİZÖRÜ

**Alt başlık:**
Mikrodenetleyiciler Dersi Dönem Projesi

**Hazırlayanlar:**
Kayra DEMİRKAN, 60240000050
Samet TOKDEMİR, 61230000118

**Danışman:** Prof. Dr. Ahmet KAYA

**Kurum:**
T.C. Ege Üniversitesi
Tire Kutsan Meslek Yüksekokulu
Bilgisayar Programcılığı Programı

**Tarih:** Mayıs 2026

**Görsel önerisi:** Cihazın gerçek fotoğrafı (denge tahtası üzerinde monte halde)

---

## SLAYT 2, Problem: Denge Neden Önemli?

**Maddeler:**
- Denge, vücudun ayakta sabit durabilme yetisidir
- Sağlıklı sinir sistemi ve kas-iskelet sisteminin göstergesidir
- Yaşlılarda ve bazı hastalıklarda denge kaybı, **düşme riski** demektir
- Hastanelerde "postürografi" denilen ölçüm yöntemiyle takip edilir

**Sunucu Notu:**
> "Denge, çoğu zaman önemini fark etmediğimiz ama yaşlılıkta ve nörolojik hastalıklarda hayati hale gelen bir yetidir. Düşme riskini önceden anlamanın yolu, dengeyi sayısal olarak ölçebilmektir."

**Görsel önerisi:** Üç duyu sisteminin (göz, iç kulak, propriyosepsiyon) basit illüstrasyonu

---

## SLAYT 3, Mevcut Cihazların Sorunu

**Maddeler:**
- Klinik düzeydeki postürografi cihazları **350 000 TL'den** başlıyor
- Büyük, taşınmaz, özel laboratuvar gerektiriyor
- Küçük klinikler, okullar ve sahada çalışan araştırmacılar **erişemiyor**

**Sunucu Notu:**
> "Mevcut profesyonel cihazlar hassas ama çok pahalı ve mobilizasyonu yok. Bu durum birçok ortamda denge ölçümünü imkansız kılıyor."

**Görsel önerisi:** Klinik denge platformu fotoğrafı (internet), yanına fiyat etiketi

---

## SLAYT 4, Çözümümüz

**Maddeler:**
- **1 300 TL** maliyetle, **avucunuza sığacak** boyutta bir cihaz
- 9 V pille **10 saat** kesintisiz çalışıyor
- Bilgisayar gerekmiyor, **ekrandan ve sesten** geri bildirim veriyor
- Kullanımı: kumandadan OK'a bas, 10 saniye sabit dur, sonucu oku

**Sunucu Notu:**
> "Klinik cihazların binde 4'ü kadar bir maliyetle, aynı temel ölçümü yapan bir cihaz geliştirdik. Tamamen taşınabilir ve eğitimli personel gerektirmiyor."

**Görsel önerisi:** Cihazın yakın çekim fotoğrafı, sıklığı, OLED'de bir sonuç ekranı

---

## SLAYT 5, Sistem Mimarisi (Donanım Bileşenleri)

**Maddeler:**
- **Arduino Uno R3**, Cihazın beyni
- **MPU6050 Sensörü**, Hareket ve eğim ölçer
- **0,96″ OLED Ekran**, Sonuç gösterici
- **1838B Kızılötesi Alıcı**, Kumanda komutlarını alır
- **Pasif Buzzer**, Sesli geri bildirim
- **9 V Pil**, Taşınabilir güç

**Sunucu Notu:**
> "Cihazımızın 6 ana parçası var. Her biri kendi işini yapıyor; Arduino bunları birleştiriyor. Toplam fiyat 1300 TL ve bu parçaların hepsi Türkiye'de kolayca bulunuyor."

**Görsel önerisi:** Bileşenlerin ayrı ayrı fotoğrafları, her biri etiketli

---

## SLAYT 6, Sistem Blok Diyagramı

**Görsel önerisi (ana içerik):**
Blok diyagram (PROJE_RAPORU.md Bölüm 4.6'daki ASCII şemanın görsel versiyonu):
- Sensör → Arduino → 3 çıkış (Ekran, Buzzer, Bilgisayar/Seri Port)
- Kumanda → Kızılötesi Alıcı → Arduino

**Maddeler:**
- Tüm parçalar Arduino'ya bağlı
- Sensör ve ekran aynı iki kabloyu paylaşıyor (I²C protokolü)
- Veri akışı: Sensör → Beyin → Ekran/Ses

**Sunucu Notu:**
> "Görüntüde görüldüğü gibi sensörden gelen ham veri Arduino'da işleniyor, sonra üç farklı kanaldan kullanıcıya sunuluyor: ekran, ses ve isteğe bağlı bilgisayar bağlantısı."

---

## SLAYT 7, Ölçümün Kalbi: Tamamlayıcı Filtre

**Maddeler:**
- Sensörümüzde **iki tip ölçüm** var: ivmeölçer ve jiroskop
- İvmeölçer titreşimden etkileniyor → veriler dalgalanıyor
- Jiroskop ise zamanla **kayma yapıyor** (drift)
- Çözüm: **iki sensörün verisini akıllıca birleştirmek**

**Formül (büyük yazılı):**
$$\theta_{yeni} = 0{,}96 \cdot (\theta_{eski} + \omega \cdot \Delta t) + 0{,}04 \cdot \theta_{ivme}$$

**Sunucu Notu:**
> "Tek bir sensör yeterli değil. Bu yüzden iki sensörün verisini, her birinin güçlü yönünü öne çıkaracak şekilde birleştiriyoruz. %96 jiroskoptan, %4 ivmeölçerden alıyoruz. Bu Tamamlayıcı Filtre denilen yöntem akademik literatürde de yaygın."

**Görsel önerisi:** İki ayrı grafik (titreşimli ivmeölçer vs kayan jiroskop) ile birleştirilmiş düzgün grafik (filtre çıkışı)

---

## SLAYT 8, Kalibrasyon (Sıfırlama)

**Maddeler:**
- Cihaz açıldığında otomatik kalibrasyon başlıyor
- **2 saniye** boyunca cihaz sabit durmalı
- Bu süreçte sensörün ortalama değerleri **"sıfır noktası"** olarak kaydediliyor
- Sonraki ölçümler bu sıfıra göre yorumlanıyor
- Kullanıcı **"0" tuşuna basarak istediği zaman tekrar kalibre edebilir**

**Sunucu Notu:**
> "Cihaz her açıldığında kendini ayarlıyor. Bu işleme kalibrasyon diyoruz. Sensör küçük üretim hatalarından dolayı sıfırda bile küçük sayılar verir; biz bunları otomatik olarak temizliyoruz."

**Görsel önerisi:** Akış şeması, Açılış → 2 sn sabit → Kalibrasyon Tamam tonları → Hazır

---

## SLAYT 9, Ölçüm Akışı

**Maddeler:**
1. Kullanıcı **mod seçer:** SAĞ-SOL veya ÖN-ARKA (kumanda)
2. **OK tuşu** → Ölçüm başlar (kısa bip sesi)
3. **10 saniye** boyunca cihaz açıyı kaydeder (saniyede 20 kez)
4. Bittiğinde uzun bip sesi
5. Ekranda sonuç: **yön + ortalama açı + skor**

**Sunucu Notu:**
> "Kullanıcı önce hangi yönde ölçeceğini seçiyor, sonra OK'a basıyor. 10 saniye boyunca cihaz vücudun salınımını ölçüyor. Sonunda dört değer çıkıyor: ortalama sapma, en büyük sapma, kararlılık ve genel skor."

**Görsel önerisi:** OLED'in 4 farklı ekran görüntüsü yan yana: Hazır → Ölçüm → Sonuç

---

## SLAYT 10, Skor Nasıl Hesaplanır?

**Formül:**
$$\text{Skor} = 100 - 5 \cdot \overline{|\theta|} - 2 \cdot \theta_{\max} - 8 \cdot S$$
*(0–100 arasına sınırlanır)*

**Maddeler:**
- **Ortalama sapma:** Dengeden ne kadar uzaktasınız?
- **En büyük sapma:** Bir anda ne kadar saptınız?
- **Kararlılık:** Ne kadar dalgalandınız? (en önemli faktör)
- Sağlıklı: **85–95** | Denge zorluğu: **0–40**

**Sunucu Notu:**
> "Skoru üç şeyi cezalandırarak hesaplıyoruz: ortalama uzaklık, ani sapmalar ve kararsızlık. Kararsızlığa en yüksek katsayıyı (8) verdik çünkü literatürde düşme riskinin en güçlü göstergesi olarak belirtiliyor."

**Görsel önerisi:** Renkli skor barı (yeşil 80-100, sarı 50-80, kırmızı 0-50)

---

## SLAYT 11, Düşük Güç Tasarımı

**Maddeler:**
- Aktif kullanım: ~85 mA → **6,5 saat teorik**
- Kumanda **#** tuşu ile bekleme moduna geçiş:
  - Sensör uyku moduna alınıyor (3,5 mA → 5 µA)
  - Ekran kapatılıyor (20 mA → 0,1 mA)
  - Akım yarı yarıya iniyor: ~45 mA
- **Ölçülen gerçek değer: 9 V pille 10 saat**

**Sunucu Notu:**
> "Pil ömrünü uzatmak için yazılımsal bir uyku modu ekledik. Cihaz tamamen kapanmıyor, sadece ekran ve sensör 'uykuya dalıyor'. Kumandayla bir tuşla anında uyanıyor. Bu sayede bekleme süreleri pil yemiyor."

**Görsel önerisi:** İki sütun: Aktif (yanan ekran) vs Bekleme (siyah ekran), yanına akım değerleri

---

## SLAYT 12, Karşılaştığımız Sorunlar ve Çözümler

**Tablo formatında:**

| Sorun | Çözüm |
|-------|-------|
| Sürekli "0,0°" gösteriyordu | Yazılımda eksenler ters bağlanmış, düzelttik |
| Pille açılışta sensör hatası | 8 denemelik otomatik tekrar mekanizması ekledik |
| Kumandada uzun basınca yanlış komut çalışıyordu | Tekrar kodunu ayrı işaretledik |
| Buzzer sesi çok kısıktı | Frekansı 2700 Hz'e çekince ses arttı |

**Sunucu Notu:**
> "Geliştirme süreci sadece teori değil, gerçek sorunlarla baş etmektir. Bu tablo, projede karşılaştığımız teknik sorunları ve mühendislik çözümlerini özetliyor."

**Görsel önerisi:** Yok, tablo zaten yeterli

---

## SLAYT 13, Demo (Canlı Gösterim)

**Maddeler:**
1. Cihazı açıyoruz, kalibrasyonu görüyorsunuz
2. Test bireyi denge tahtasına çıkıyor
3. SAĞ-SOL modunda 10 saniyelik ölçüm
4. Sonuç ekranı + skor
5. (Opsiyonel) Bilgisayara bağlayıp Serial Plotter ile gerçek zamanlı grafik

**Sunucu Notu:**
> "Şimdi sizlere sistemi canlı göstereceğiz. Bu süre sonunda istediğiniz soruları sorabilirsiniz."

**Görsel önerisi:** Sadece "DEMO" yazılı büyük slayt, projektörden cihaz/kullanıcıya geçiş

---

## SLAYT 14, Sınırlılıklar ve Gelecek

**Mevcut Sınırlılıklar:**
- Tek seferde tek eksen ölçüyor (sağ-sol VEYA ön-arka)
- Çoklu denek üzerinde istatistiksel doğrulama yapılmadı
- Veri saklamıyor, sadece o anki ölçüm gösteriliyor
- Klinik tanı aracı değil, kişisel takip için

**Gelecek Geliştirmeler:**
- Çift eksen aynı anda → 2D denge haritası
- SD kart eklenip uzun süreli takip
- Bluetooth ile telefon uygulaması
- Klinik kalibrasyon çalışması

**Sunucu Notu:**
> "Cihaz işlevsel; ama klinik düzeyde kullanım için daha fazla doğrulama gerekiyor. Bu yönde gelecek çalışmalarımızı sıraladık."

**Görsel önerisi:** Sol kolon "Şu an" / Sağ kolon "Gelecek", iki ayrı kutu

---

## SLAYT 15, Teşekkür ve Sorular

**İçerik:**
- Büyük "TEŞEKKÜRLER"
- Danışman: Prof. Dr. Ahmet KAYA
- Bizi dinlediğiniz için teşekkür ederiz
- "Sorularınız?"

**Sunucu Notu:**
> "Dinlediğiniz için teşekkür ederiz. Şimdi sorularınızı bekliyoruz."

**Görsel önerisi:** Cihazın mevcut çalışır halinin fotoğrafı + iletişim bilgisi (opsiyonel)

---

# CLAUDE PROMPT, SUNUM ÜRETME

> Aşağıdaki prompt'u **yeni bir Claude oturumunda** kullanın; bu Markdown taslağına göre kullanılabilir slayt içeriği üretecektir. PowerPoint'e doğrudan yapıştırabileceğiniz formatta çıktı verir.

---

```
Sen profesyonel bir akademik sunum tasarımcısısın. Sana bir proje sunum
taslağı (Markdown formatında) vereceğim. Görevin, bu taslağı kullanılabilir
ve görsel olarak güçlü PowerPoint slayt içeriklerine dönüştürmek.

ÇIKTI KURALLARI:
1. Her slayt için ayrı bir bölüm üret. Format:
   ---
   # Slayt N: [Başlık]

   ## Slayt İçeriği (madde madde, 5 maddeyi geçme)
   - ...

   ## Sunucu Notları (60-90 saniyelik konuşma metni)
   "..."

   ## Görsel Önerisi
   [Detaylı açıklama: görselin nasıl olması gerektiği, hangi öğeler içermesi
   gerektiği, renk şeması önerisi]

   ## Tasarım İpuçları
   - Yazı tipi: ...
   - Renk paleti: ...
   - Düzen: tek sütun / iki sütun / ortalanmış vs.
   ---

2. Sunum dili: Türkçe, sade, jargonsuz. Akademik ama kuru değil.

3. Renk şeması (önerilen):
   - Ana renk: koyu lacivert (#1A2B4C)
   - Vurgu: turkuaz (#00A8B5)
   - Arka plan: krem-beyaz (#FAFAF7)
   - Metin: koyu gri (#2C3E50)

4. Yazı tipleri:
   - Başlıklar: Montserrat Bold veya Roboto Slab
   - Gövde: Open Sans veya Roboto

5. Slayt başına ortalama 5-8 saniyede okunabilen kadar yazı koy. Aşırı
   yazıdan kaçın. Görsel ağırlıklı tasarım önerileri ver.

6. Formül slaytlarında LaTeX gibi görünen düzgün matematiksel ifadeler kullan
   (PowerPoint Equation Editor ile uyumlu).

7. Demo ve Teşekkür slaytlarında minimal tasarım öner (sadece tek bir büyük
   yazı + arka plan görseli).

8. Sunum 12-15 dakika hedefli; her slaytta 60-90 saniye konuşulacak.

9. Çıktının sonunda: PowerPoint'e geçiş için kısa bir uygulama rehberi ekle
   (hangi slayt ne tip layout, slide master ayarı vb.).

ŞİMDİ AŞAĞIDAKİ SUNUM TASLAĞINI BU FORMATA ÇEVİR:

[Buraya SUNUM_TASLAGI.md dosyasının içeriğini yapıştır]
```

---

## ALTERNATİF: Marp / Reveal.js İçin Hızlı Üretim Prompt'u

> Eğer slaytları doğrudan Markdown'dan üretmek istiyorsanız (Marp veya
> Reveal.js gibi araçlarla):

```
Aşağıdaki sunum taslağını Marp formatında bir Markdown dosyasına çevir.
- Her slayt arasında "---" kullan
- Yatay 16:9 oran
- Tema: gaia veya default
- Başlık slaytında ortalama metin
- Tablolar ve formüller olduğu gibi kalsın
- Sunucu notları HTML yorumu (<!-- ... -->) olarak yazılsın
- Renk şeması: lacivert + turkuaz + beyaz

[Sunum taslağı içeriği burada]
```

---

*Hazırlayan: Kayra DEMİRKAN, Samet TOKDEMİR, Mayıs 2026*
