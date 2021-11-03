/*
 *  Simple test to get to get data and time - uses the ezTime library at https://github.com/ropg/ezTime
 *  André Bourgeois
 *  November 2021
 *
 *  Forked from Duncan Wilson
 *  CASA0014 - 2 - Plant Monitor Workshop
 *  May 2020
 */

#include <ESP8266WiFi.h> //import libraries
#include <ezTime.h>

const char* ssid     = "CE-Hub"; //declare constants
const char* password = "pass"; //edit for specified wifi network

Timezone GB; //declare timezone

void setup() {
  Serial.begin(115200); // declare baud rate
  delay(100);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) { //visual feedback that device is
    //trying to connect
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected"); //visual feedback that wifi has connected
  Serial.println("IP address: "); //provides edvice IP address
  Serial.println(WiFi.localIP());

  waitForSync();

  Serial.println("UTC: " + UTC.dateTime()); //print date/time to serial port


  GB.setLocation("Europe/London"); //set timezone location
  Serial.println("London time: " + GB.dateTime()); //print this to serial port
  //prints data to the serial port as human-readable ASCII text

}

void loop() {
  delay(1000);
  Serial.println(GB.dateTime("H:i:s")); // UTC.dateTime("l, d-M-y H:i:s.v T")
}
