/*
 *  Simple test to push data to an MQTT server - uses library from https://pubsubclient.knolleary.net
 *  André Bourgeois
 *  November 2021
 *
 *  Forked from Duncan Wilson
 *  CASA0014 - 2 - Plant Monitor Workshop
 *  May 2020
 */

 #include <ESP8266WiFi.h> //import libraries
 #include <ezTime.h>
 #include <PubSubClient.h>

 const char* ssid = "CE-Hub"; //declare constants
 const char* password = "wifipass"; //edit for specified wifi network
 const char* mqtt_server = "mqtt.cetools.org"; //and mqtt server
 const char* mqttuser = "student";
 const char* mqttpass = "mqttpass";

 Timezone GB; //declare a timezone for ezTime

 WiFiClient espClient;
 PubSubClient client(espClient);
 long lastMsg = 0;
 char msg[50];
 int value = 0;


 void setup() { //initialize variables’ values,
 //setup communications (ex: Serial),
 //setup modes for digital pins (input/output),
 //initialize any hardware component (sensor/actuator) plugged to the Arduino

   pinMode(BUILTIN_LED, OUTPUT); //initialize the BUILTIN_LED as an output
   digitalWrite(BUILTIN_LED, HIGH); //turn the LED of by making the voltage high
   // open serial connection via the wifi to the mqtt broker
   Serial.begin(115200);
   delay(100); // to give time for the serial connection to open

   startWifi(); //start a Wi-Fi access point, and try to connect to some given access points

   //get real date an time
   waitForSync();
   Serial.println("UTC: " + UTC.dateTime());
   GB.setLocation("Europe/London");
   Serial.println("London time: " + GB.dateTime());

   // Once connected to wifi establish connection to mqtt broker
   client.setServer(mqtt_server, 1884);

  // The callback in this case listens for instructions to
  // change the state of the LED - here we are initialising
  // that function
   client.setCallback(callback);

 }

void loop() {
  delay(5000);
  sendMQTT();
}

void startWifi() {
  // start by connecting to the wifi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid); //visual feedback of which wifi we're connecting to
  WiFi.begin(ssid, password);

  //check to see if connected and wait until you are
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); //tells us that we're connected to wifi
  Serial.print("IP address: "); //shows device IP
  Serial.println(WiFi.localIP());
}

void sendMQTT() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  ++value;
  snprintf(msg, 50, "hello world #%ld, this is a test", value);
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/ucfnbou", msg);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  //switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    //but actually the LED is on; this is because it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  //loop until reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    //create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    //attempt to connect
    
    if (client.connect(clientId.c_str(), mqttuser, mqttpass)) {
      Serial.println("connected");
      //...and subscribe to messages on broker
      client.subscribe("student/CASA0014/plant/ucfnbou/inTopic");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      //wait 5 seconds before retrying
      delay(5000);
    }
  }
}
