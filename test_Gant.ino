#include <Wire.h>
#include <DFRobot_ADS1115.h>
#include <M5EPD.h>
 
M5EPD_Canvas canvas(&M5.EPD);
DFRobot_ADS1115 ads1(&Wire);
DFRobot_ADS1115 ads2(&Wire);
 
void setup(void) {
  M5.begin();
  M5.EPD.SetRotation(180);
  M5.TP.SetRotation(180);
  M5.EPD.Clear(true);
  canvas.createCanvas(540, 960);
  canvas.setTextSize(5);
  Serial.begin(115200);
   canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
 
  ads1.setAddr_ADS1115(ADS1115_IIC_ADDRESS1); // 0x48
  ads2.setAddr_ADS1115(ADS1115_IIC_ADDRESS0); // 0x49
 
  ads1.setGain(eGAIN_TWOTHIRDS);  
  ads1.setMode(eMODE_SINGLE);      
  ads1.setRate(eRATE_128);         // 128SPS (default)
  ads1.setOSMode(eOSMODE_SINGLE);
  ads1.init();
 
  ads2.setGain(eGAIN_TWOTHIRDS);
  ads2.setMode(eMODE_SINGLE);
  ads2.setRate(eRATE_128);
  ads2.setOSMode(eOSMODE_SINGLE);
  ads2.init();
}
 
void loop(void) {
  if (ads1.checkADS1115())
  {
    int16_t adc0, adc1, adc2, adc3;
 
 canvas.drawString("adc1", 10,10);
 
    adc0 = ads1.readVoltage(0);
    Serial.print("ADS1 A0:");
    Serial.print(adc0);
    Serial.print("mV,  ");
    canvas.drawString("A0: " + String(adc0) + "mV", 10, 60);
 
    adc1 = ads1.readVoltage(1);
    Serial.print("ADS1 A1:");
    Serial.print(adc1);
    Serial.print("mV,  ");
    canvas.drawString("A1: " + String(adc1) + "mV", 10, 110);
 
    adc2 = ads1.readVoltage(2);
    Serial.print("ADS1 A2:");
    Serial.print(adc2);
    Serial.print("mV,  ");
    canvas.drawString("A2: " + String(adc2) + "mV", 10, 150);
    canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
  } else
  {
    Serial.println("ADS1115 Disconnected!");
  }
 
  //delay(50);
 
  if (ads2.checkADS1115())
  {
    int16_t adc6, adc7;
 
     canvas.drawString("adc2", 10,220);
 
    adc6 = ads2.readVoltage(2);
    Serial.print("ADS2 A2:");
    Serial.print(adc6);
    Serial.print("mV");
    canvas.drawString("A2: " + String(adc6) + "mV", 10, 260);
 
    adc7 = ads2.readVoltage(3);
    Serial.print("   ADS2 A3:");
    Serial.print(adc7);
    Serial.println("mV");
    canvas.drawString("A3: " + String(adc7) + "mV", 10, 300);
    canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
  } else
  {
    Serial.println("ADS1115 Disconnected!");
  }
 
  // Rafraîchit l'écran avec le contenu du canvas
 
 
  delay(200);
}