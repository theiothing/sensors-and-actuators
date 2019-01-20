
/*
  The example GETS temperature value from a Dallas OneWire DS18B20 temperature sensor.
  Pinout looking at the component face is: GND - DATA - VDD

  Connect
  GND to GND
  DATA to D1
  VDD to 3.3V

  ---
  code by Marco Brianza
  modified by Marco Provolo, apr 2018

  This example code is in the public domain.
*/


#include <ESP8266WiFi.h>

#include <OneWire.h>                      //https://github.com/PaulStoffregen/OneWire
#include <DallasTemperature.h>            // https://github.com/milesburton/Arduino-Temperature-Control-Library
#define ONE_WIRE_BUS D1                   // Data pin D1 for ESP2866
OneWire oneWire(ONE_WIRE_BUS);            // Setup a oneWire instance
DallasTemperature sensors(&oneWire);      // Pass our oneWire reference to Dallas Temperature.
DeviceAddress thermometer;                // variable to hold device address

void setup() {
  WiFi.mode(WIFI_OFF);

  Serial.begin(115200);
  pinMode(ONE_WIRE_BUS, INPUT_PULLUP);
  setupSensor();

}


void loop() {
  sensors.requestTemperatures(); // Send the command to get temperatures
  float t = sensors.getTempC(thermometer);
  Serial.println(t);
}

// function to print a device address
String address2Str(DeviceAddress deviceAddress)
{
  String sa;
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) sa = sa + "0";
    sa = sa + String(deviceAddress[i], HEX);
  }
  sa.toUpperCase();
  return sa;
}


void setupSensor() {
  boolean result = false;
  do {
    Serial.println("\nDallas Temperature IC Control Library Demo");

    // locate devices on the bus
    sensors.begin();
    Serial.print("Termometers found: ");
    Serial.print(sensors.getDeviceCount(), DEC);
    Serial.println();

    // report parasite power requirements
    Serial.print("Parasite power is: ");
    if (sensors.isParasitePowerMode()) Serial.println("ON");
    else Serial.println("OFF");

    if (sensors.getAddress(thermometer, 0)) {
      String thermometerStr = address2Str(thermometer);
      Serial.println(thermometerStr + " ");
      // set the resolution to 12 bit (Each Dallas/Maxim device is capable of several different resolutions)
      sensors.setResolution(thermometer, 12);
      result = true;
    }
    else {
      Serial.println("Unable to find sensor, please check wiring...");
      delay(5000);
    }
  } while (result == false);
}

/***** END OF FILE *****/
