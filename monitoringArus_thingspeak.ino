#include <ESP8266WiFi.h>
#include <PZEM004Tv30.h>
#include <ThingSpeak.h>

//inisialisasi objek untuk Pzem (sensor arus)
PZEM004Tv30 pzem(12,13);//12 = D6 (Rx), 13=D7 (Tx)

WiFiClient client;

const char *ssid =  "Kim";  
const char *pass =  "bayern30";

long myChannelNumber = 2517206;
const char myWriteAPIKey[] = "P436BMZE4ZW9U9AM";

//variabel penampung untuk nilai sensor arus
float Power, Energy, Voltase, Current;

void setup() {
  // aktifkan serial
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
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
    ThingSpeak.writeField(myChannelNumber, 1, Power, myWriteAPIKey);
    
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
    ThingSpeak.writeField(myChannelNumber, 2, Energy, myWriteAPIKey);
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
    ThingSpeak.writeField(myChannelNumber, 3, Voltase, myWriteAPIKey);
    
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
    ThingSpeak.writeField(myChannelNumber, 4, Current, myWriteAPIKey);
  }

  Serial.println();
  delay(1000);
  }
