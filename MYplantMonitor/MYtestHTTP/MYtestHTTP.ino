/*
 *  Simple HTTP get webclient test
 *  André Bourgeois
 *  November 2021
 *  forked from Duncan Wilson
 *  CASA0014 - 2 - Plant Monitor Workshop
 *  May 2020
 */

 #include <ESP8266WiFi.h>

 const char* = "SSID here";
 const char* password = "password here";
 const char* host = "iot.io";

 void setup() {
   Serial.begin(115200);
   delay(100);

   // start by connecting to the WiFi network
   Serial.println();
   Serial.print("Connecting to ");
   Serial.println(ssid);
   WiFi.begin(ssid, password);

   while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
   }

   Serial.println("");
   Serial.println("WiFi connected");
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
 }

 int value = 0;

 void loop() {
   delay(5000);
   ++value;

   Serial.println("----------------------------")
   Serial.print("Connecting to ");
   Serial.println(host);

   //use WiFiClient class to create TCP connections
   WiFiClient client;
   const int httpPort = 80;
   if (!client.connect(host, httpPort)) {
     Serial.println("connection failed");
     return;
   }

   //create a URI for the request
   String url = "/data/index.html";
   Serial.print("Requeseting URL: ");

   //this will send the request to the server
   client.print(String("GET ") + url + " HTTP/1.1\r\n" +
   "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

   delay(500);

   //read all the lines of the reply
   //from the server and print them to Serial
   while(client.available()) {
     String line = client.readStringUntil("\r");
     Serial.print(line);
   }

   Serial.println();
   Serial.println("closing connection");
 }
