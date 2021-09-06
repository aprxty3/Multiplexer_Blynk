#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina2191;
Adafruit_INA219 ina2192;
Adafruit_INA219 ina2193;
Adafruit_INA219 ina2194;
Adafruit_INA219 ina2195;
Adafruit_INA219 ina2196;
Adafruit_INA219 ina2197;
Adafruit_INA219 ina2198;
BlynkTimer timer;

char auth[] = "KDLCL-30D33OBWRDGtYFK_fQg_Tudvj1"; //"h44avb1Kw2uiAPbPJJmMXs8spxsV1U_x"; ganti dengan Auth Token dari aplikasi blynk yang masuk ke email
char ssid[] = "Redmi123"; //ganti dengan nama wifi anda
char pass[] = "aryanicosa"; //ganti dengan password wifi anda

int selector;               //pin dari blynk
uint8_t selectorValue = 0;  //nilai pin selector


#define TCAADDR 0x70
void tcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

BLYNK_WRITE(V1) {
  selector = param.asInt(); // ketika button di blynk di klik/push, maka akan dikirim nilai ke esp8266
}

void sendSensor() {
  Serial.print("selector channel: ");
  Serial.println(selector); // hanya untuk debugging
  if (selector == 1) {
    selectorChannel1();
  } else if (selector == 2) {
    selectorChannel2();
  } else if (selector == 3) {
    selectorChannel3();
  } else if (selector == 4) {
    selectorChannel4();
  } else if (selector == 5) {
    selectorChannel5();
  } else if (selector == 6) {
    selectorChannel6();
  } else if (selector == 7) {
    selectorChannel7();
  } else {
    selectorChannel0();
  }
}

void setup(void) {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();

  uint32_t currentFrequency;

  tcaselect(0);
  if (! ina2191.begin()) {
    Serial.println("Failed to find INA219 1 chip");
  } else {
    Serial.println("Succes to find INA219 1 chip");
  }

  tcaselect(1);
  if (! ina2192.begin()) {
    Serial.println("Failed to find INA219 2 chip");
  } else {
    Serial.println("Succes to find INA219 2 chip");
  }

  tcaselect(2);
  if (! ina2193.begin()) {
    Serial.println("Failed to find INA219 3 chip");
  } else {
    Serial.println("Succes to find INA219 3 chip");
  }

  tcaselect(3);
  if (! ina2194.begin()) {
    Serial.println("Failed to find INA219 4 chip");
  } else {
    Serial.println("Succes to find INA219 4 chip");
  }

  tcaselect(4);
  if (! ina2195.begin()) {
    Serial.println("Failed to find INA219 5 chip");
  } else {
    Serial.println("Succes to find INA219 5 chip");
  }

  tcaselect(5);
  if (! ina2196.begin()) {
    Serial.println("Failed to find INA219 6 chip");
  } else {
    Serial.println("Succes to find INA219 6 chip");
  }

  tcaselect(6);
  if (! ina2197.begin()) {
    Serial.println("Failed to find INA219 7 chip");
  } else {
    Serial.println("Succes to find INA219 7 chip");
  }

  tcaselect(7);
  if (! ina2198.begin()) {
    Serial.println("Failed to find INA219 8 chip");
  } else {
    Serial.println("Succes to find INA219 8 chip");
  }

  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  ina2191.setCalibration_16V_400mA(); ina2192.setCalibration_16V_400mA(); ina2193.setCalibration_16V_400mA(); ina2194.setCalibration_16V_400mA();
  ina2195.setCalibration_16V_400mA(); ina2196.setCalibration_16V_400mA(); ina2197.setCalibration_16V_400mA(); ina2198.setCalibration_16V_400mA();

  Serial.println("Measuring power, voltage and current with INA219 ...");

  Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8080);
  timer.setInterval(1000L, sendSensor);
}

void loop(void) {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}


void selectorChannel0() {
  tcaselect(0);
  float busvoltage = 0;
  float current_mA = 0;
  float power_mW = 0;

  busvoltage = ina2191.getBusVoltage_V();
  current_mA = ina2191.getCurrent_mA();
  power_mW = ina2191.getPower_mW();

  delay(10);

  Blynk.virtualWrite(V2, busvoltage);
  Blynk.virtualWrite(V3, current_mA);
  Blynk.virtualWrite(V4, power_mW);

  //status channel aktif
  selectorValue = 0;
  Blynk.virtualWrite(V5, selectorValue);

  Serial.print("Channel Aktif: "); Serial.print(selectorValue); Serial.println(" ");
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage);    Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA);    Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW);      Serial.println(" mW");
  Serial.println("");
}

void selectorChannel1() {
  tcaselect(1);
  float busvoltage = 0;
  float current_mA = 0;
  float power_mW = 0;

  busvoltage = ina2192.getBusVoltage_V();
  current_mA = ina2192.getCurrent_mA();
  power_mW = ina2192.getPower_mW();

  delay(10);

  Blynk.virtualWrite(V2, busvoltage);
  Blynk.virtualWrite(V3, current_mA);
  Blynk.virtualWrite(V4, power_mW);

  //status channel aktif
  selectorValue = 1;
  Blynk.virtualWrite(V5, selectorValue);

  Serial.print("Channel Aktif: "); Serial.print(selectorValue); Serial.println(" ");
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage);    Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA);    Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW);      Serial.println(" mW");
  Serial.println("");
}

void selectorChannel2() {
  tcaselect(2);
  float busvoltage = 0;
  float current_mA = 0;
  float power_mW = 0;

  busvoltage = ina2193.getBusVoltage_V();
  current_mA = ina2193.getCurrent_mA();
  power_mW = ina2193.getPower_mW();

  delay(10);

  Blynk.virtualWrite(V2, busvoltage);
  Blynk.virtualWrite(V3, current_mA);
  Blynk.virtualWrite(V4, power_mW);

  //status channel aktif
  selectorValue = 2;
  Blynk.virtualWrite(V5, selectorValue);

  Serial.print("Channel Aktif: "); Serial.print(selectorValue); Serial.println(" ");
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage);    Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA);    Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW);      Serial.println(" mW");
  Serial.println("");
}

void selectorChannel3() {
  tcaselect(3);
  float busvoltage = 0;
  float current_mA = 0;
  float power_mW = 0;

  busvoltage = ina2194.getBusVoltage_V();
  current_mA = ina2194.getCurrent_mA();
  power_mW = ina2194.getPower_mW();
  
  delay(10);
  
  Blynk.virtualWrite(V2, busvoltage);
  Blynk.virtualWrite(V3, current_mA);
  Blynk.virtualWrite(V4, power_mW);
  
  //status channel aktif
  selectorValue = 3;
  Blynk.virtualWrite(V5, selectorValue);

  Serial.print("Channel Aktif: "); Serial.print(selectorValue); Serial.println(" ");
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage);    Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA);    Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW);      Serial.println(" mW");
  Serial.println("");
}

void selectorChannel4() {
  tcaselect(4);
  float busvoltage = 0;
  float current_mA = 0;
  float power_mW = 0;

  busvoltage = ina2195.getBusVoltage_V();
  current_mA = ina2195.getCurrent_mA();
  power_mW = ina2195.getPower_mW();
  
  delay(10);
  
  Blynk.virtualWrite(V2, busvoltage);
  Blynk.virtualWrite(V3, current_mA);
  Blynk.virtualWrite(V4, power_mW);
  
  //status channel aktif
  selectorValue = 4;
  Blynk.virtualWrite(V5, selectorValue);

  Serial.print("Channel Aktif: "); Serial.print(selectorValue); Serial.println(" ");
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage);    Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA);    Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW);      Serial.println(" mW");
  Serial.println("");
}

void selectorChannel5() {
  tcaselect(5);
  float busvoltage = 0;
  float current_mA = 0;
  float power_mW = 0;

  busvoltage = ina2196.getBusVoltage_V();
  current_mA = ina2196.getCurrent_mA();
  power_mW = ina2196.getPower_mW();
  
  delay(10);
  
  Blynk.virtualWrite(V2, busvoltage);
  Blynk.virtualWrite(V3, current_mA);
  Blynk.virtualWrite(V4, power_mW);
  
  //status channel aktif
  selectorValue = 5;
  Blynk.virtualWrite(V5, selectorValue);

  Serial.print("Channel Aktif: "); Serial.print(selectorValue); Serial.println(" ");
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage);    Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA);    Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW);      Serial.println(" mW");
  Serial.println("");
}

void selectorChannel6() {
  tcaselect(6);
  float busvoltage = 0;
  float current_mA = 0;
  float power_mW = 0;

  busvoltage = ina2197.getBusVoltage_V();
  current_mA = ina2197.getCurrent_mA();
  power_mW = ina2197.getPower_mW();
  
  delay(10);
  
  Blynk.virtualWrite(V2, busvoltage);
  Blynk.virtualWrite(V3, current_mA);
  Blynk.virtualWrite(V4, power_mW);
  
  //status channel aktif
  selectorValue = 6;
  Blynk.virtualWrite(V5, selectorValue);

  Serial.print("Channel Aktif: "); Serial.print(selectorValue); Serial.println(" ");
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage);    Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA);    Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW);      Serial.println(" mW");
  Serial.println("");
}

void selectorChannel7() {
  tcaselect(7);
  float busvoltage = 0;
  float current_mA = 0;
  float power_mW = 0;

  busvoltage = ina2198.getBusVoltage_V();
  current_mA = ina2198.getCurrent_mA();
  power_mW = ina2198.getPower_mW();
  
  delay(10);
  
  Blynk.virtualWrite(V2, busvoltage);
  Blynk.virtualWrite(V3, current_mA);
  Blynk.virtualWrite(V4, power_mW);
  
  //status channel aktif
  selectorValue = 7;
  Blynk.virtualWrite(V5, selectorValue);

  Serial.print("Channel Aktif: "); Serial.print(selectorValue); Serial.println(" ");
  Serial.print("Bus Voltage:   "); Serial.print(busvoltage);    Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA);    Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW);      Serial.println(" mW");
  Serial.println("");
}
