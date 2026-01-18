#include "arduino_secrets.h"
/* Arduino IoT Cloud - Profesyonel Peri Led (V5 - Google Home Destekli)
   Özellikler:
   - Sesli Komutla Mod Değiştirme (Sanal Anahtarlar)
   - Parlaklık Kontrolü
   - Flicker Önleyici
*/

#include "thingProperties.h"

#define LED_PIN 5       // Yeni güvenli pinimiz
#define MAX_LIMIT 100 // Titreme yapmayan max sınırın

// PWM Ayarları
const int frekans = 5000;
const int ledKanal = 0;
const int cozunurluk = 8;

// Animasyon Zamanlayıcıları
unsigned long sonZaman = 0;
int nefesDegeri = 0;
int nefesYon = 1;

void setup() {
  Serial.begin(115200);
  delay(1500); 

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  ledcSetup(ledKanal, frekans, cozunurluk);
  ledcAttachPin(LED_PIN, ledKanal);
}

void loop() {
  ArduinoCloud.update();
  
  // Ana Lamba Kapalıysa Hepsini Kes
  if (!lamba.getSwitch()) {
    ledcWrite(ledKanal, 0); 
    return; 
  }

  // Parlaklık Hesabı
  int cloudParlaklik = lamba.getBrightness();
  int hedefLimit = map(cloudParlaklik, 0, 100, 0, MAX_LIMIT);

  // Modlara Göre Çalışma
  switch (ledModu) {
    case 0: // SABİT
      ledcWrite(ledKanal, hedefLimit);
      break;

    case 1: // NEFES
      if (millis() - sonZaman > 20) { 
        nefesDegeri += nefesYon; 
        if (nefesDegeri >= hedefLimit) { nefesDegeri = hedefLimit; nefesYon = -1; }
        if (nefesDegeri <= 5) { nefesYon = 1; }
        ledcWrite(ledKanal, nefesDegeri);
        sonZaman = millis();
      }
      break;

    case 2: // MUM
      if (millis() - sonZaman > 100) { 
        int minIsik = hedefLimit / 2;
        if (minIsik < 2) minIsik = 2;
        int titreme = random(minIsik, hedefLimit);
        ledcWrite(ledKanal, titreme);
        sonZaman = millis();
      }
      break;

    case 3: // PARTİ
      if (millis() - sonZaman > 100) { 
        static bool flash = false;
        flash = !flash;
        ledcWrite(ledKanal, flash ? hedefLimit : 0);
        sonZaman = millis();
      }
      break;
  }
}

// --- OTOMATİK MOD DEĞİŞTİRME FONKSİYONLARI ---

void onLambaChange()  {
  // Lamba açıldığında en son hangi modda kaldıysa oradan devam eder
}

void onLedModuChange()  {
  // Dashboard'dan (Dropdown menüden) elle mod değiştirilirse butonları güncelle
  if (ledModu == 1) { btnNefes = true; btnMum = false; btnParti = false; }
  else if (ledModu == 2) { btnNefes = false; btnMum = true; btnParti = false; }
  else if (ledModu == 3) { btnNefes = false; btnMum = false; btnParti = true; }
  else { btnNefes = false; btnMum = false; btnParti = false; }
}

// 1. NEFES BUTONU AÇILINCA
void onBtnNefesChange() {
  if (btnNefes) {
    ledModu = 1;      // Modu ayarla
    btnMum = false;   // Diğerlerini kapat
    btnParti = false;
  } else {
    if (ledModu == 1) ledModu = 0; // Kapatırsan Sabit moda dön
  }
}

// 2. MUM BUTONU AÇILINCA
void onBtnMumChange() {
  if (btnMum) {
    ledModu = 2;
    btnNefes = false;
    btnParti = false;
  } else {
    if (ledModu == 2) ledModu = 0;
  }
}

// 3. PARTİ BUTONU AÇILINCA
void onBtnPartiChange() {
  if (btnParti) {
    ledModu = 3;
    btnNefes = false;
    btnMum = false;
  } else {
    if (ledModu == 3) ledModu = 0;
  }
}