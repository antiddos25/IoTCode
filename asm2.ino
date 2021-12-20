// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLLJOTbv8m"
#define BLYNK_DEVICE_NAME "HandTCheck"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

//DHT22
#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

void setup()
{
  //Blynk
  Serial.begin(115200);
  delay(100);
  pinMode(2, OUTPUT);
  BlynkEdgent.begin();

  dht.begin();
}

BLYNK_WRITE(V2)
{
  int pinLED = param.asInt();
  digitalWrite(2, pinLED);
}

void loop() {
  //DHT22
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!!!");
    return;
  }
  
  Serial.println(h);
  Serial.println(t);
  Blynk.virtualWrite(V0, h);
  Blynk.virtualWrite(V1, t);
  BlynkEdgent.run();
}
