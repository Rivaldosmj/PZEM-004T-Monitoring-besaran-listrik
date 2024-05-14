
#include <PZEM004Tv30.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//variabel untuk koneksi ke blynk
//token yang didapatkan dari project blink 
char auth[] = "";
//SSID untuk Wifi
char ssid[] ="";
//password Wifi
char pass[] = "";

//inisialisasi objek untuk Pzem (sensor arus)
PZEM004Tv30 pzem(12,13);//12 = D6 (Rx), 13=D7 (Tx)

//variabel penampung untuk nilai sensor arus
float Power, Energy, Voltase, Current;

void setup() {
  // aktifkan serial
  Serial.begin(9600);
  //koneksi ke blynk
  Blynk.begin(auth,ssid, pass);
}

void loop() {
  //baca nilai power (kW)
  Power = pzem.power();
  //jika gagal membaca power
  if(isnan(Power))
  {
    Serial.println ("Gagal Membaca power");
    
  }
  else 
  {
    Serial.println ("Power : ");
    Serial.print(Power);
    Serial.println("kW");
    
  }

  //baca energy (kWh)
  Energy = pzem.energy();
  //jika gagal membaca power
  if(isnan(Energy))
  {
    Serial.println ("Gagal Membaca energy");
    
  }
  else 
  {
    Serial.println ("Energy : ");
    Serial.print(Energy);
    Serial.println("kWh");
  }

   //baca nilai voltase (Volt)
  Voltase = pzem.voltage();
  //jika gagal membaca power
  if(isnan(Voltase))
  {
    Serial.println ("Gagal Membaca voltase");
    
  }
  else 
  {
    Serial.println ("Voltase : ");
    Serial.print(Voltase);
    Serial.println("Volt");
    
  }

   //baca nilai Current (Ampere)
  Current = pzem.current();
  //jika gagal membaca power
  if(isnan(Current))
  {
    Serial.println ("Gagal Membaca current");
    
  }
  else 
  {
    Serial.println ("Current : ");
    Serial.print(Current);
    Serial.println("Ampere");
  }

  Serial.println();

  //kirim data ke Blynk
  // Power = V0 (Virtual pin0), Energy = V1, Voltase =V2, Current=V3

  Blynk.virtualWrite (V0, Power);
  Blynk.virtualWrite (V1,Energy);
  Blynk.virtualWrite (V2,Voltase);
  Blynk.virtualWrite (V3,Current);
  Blynk.run();
  delay(1000);
  }
