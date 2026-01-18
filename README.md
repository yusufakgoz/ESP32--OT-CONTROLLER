# 💡 Google Home Destekli ESP32 Akıllı LED Kontrolcüsü

Bu proje, standart şerit LED'leri **Google Home** ve **Arduino IoT Cloud** kullanarak akıllı bir cihaza dönüştürür. 

Sadece kod yazmakla kalmadım; ESP32 kartının sinyal ve güç sorunlarını çözmek için **donanımsal modifikasyonlar (Hardware Hacking)** yaptım.

![Durum](https://img.shields.io/badge/Durum-Tamamland%C4%B1-success)
![Platform](https://img.shields.io/badge/Platform-ESP32-blue)

## 🌟 Neler Yapabiliyor?
* 🗣️ **Sesli Kontrol:** "Hey Google, ışığı aç" veya "Mum modunu çalıştır" diyerek kontrol edilebilir.
* 🎛️ **Parlaklık Ayarı:** Işık şiddeti %0 ile %100 arasında ayarlanabilir.
* ✨ **Özel Animasyonlar:**
    * **Nefes Modu:** Işık yavaşça yanıp söner.
    * **Mum Modu:** Titreyen mum alevi efekti verir.
    * **Parti Modu:** Hızlı flaşör efekti.
* 📡 **Güçlendirilmiş Sinyal:** Özel anten modifikasyonu ile geniş çekim alanı.

## 🛠️ Karşılaşılan Sorunlar ve Çözümler (Ar-Ge Süreci)

Bu projeyi yaparken **ESP32-C3 SuperMini** kartında iki büyük donanımsal sorun yaşadım ve bunları şu şekilde çözdüm:

### 1. Sinyal Sorunu (Anten Modifikasyonu)
Kartın üzerindeki dahili seramik anten çok zayıftı ve bağlantı sürekli kopuyordu (`WiFi.status: 4` hatası).
* **Çözüm:** Dahili seramik anteni lehimle söküp iptal ettim. Yerine 2.4 GHz frekansı için tam 3.1 cm uzunluğunda hesaplanmış bir bakır tel lehimledim. Bu sayede bağlantı stabil hale geldi.

### 2. Güç Çökmesi (Brownout)
LED'leri %100 parlaklığa aldığımda ani akım çekimi yüzünden voltaj düşüyor ve cihaz kapanıyordu.
* **Çözüm:** Güç girişine (VCC ve GND arasına) bir elektrolitik kondansatör lehimleyerek voltaj dalgalanmalarını engelledim.

> **[BURAYA ANTEN VE LEHİM FOTOĞRAFINI EKLE]**
> *(Anten modifikasyonu ve kondansatör eklentisi)*

## 🧰 Kullanılan Malzemeler
* **Kart:** ESP32-C3 SuperMini
* **Sürücü:** MOSFET Modülü
* **Işık:** 12V Şerit LED (Günışığı)
* **Ekstra:** Elektrolitik Kondansatör & Bakır Tel (Anten için)

## 🔌 Bağlantı Şeması

| Bileşen | ESP32 Pini |
|---|---|
| MOSFET Sinyal Kablosu | GPIO 5 |
| Güç Girişi | 5V |
| Toprak | GND |

## 💻 Nasıl Çalışır?
1.  **Arduino IoT Cloud** üzerinde değişkenler (Switch, DimmedLight) oluşturuldu.
2.  Cihaz **Google Home** uygulaması ile eşleştirildi.
3.  Yazılan kod sayesinde internet kopsa bile cihaz yerel ağda çalışmaya devam edecek şekilde optimize edildi.

---

### Geliştirici
**Yusuf Akgoz**
