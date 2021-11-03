/*
 *  Simple test to make sure the homemade soil sensor is working as expected
 *  André Bourgeois
 *  November 2021
 *
 *  Forked from Duncan Wilson
 *  CASA0014 - 2 - Plant Monitor Workshop
 *  May 2020
 */

uint8_t soilPin = 0; //one nail goes to +5V, the other goes to this anologue pin
int moisture_val; //initialize the moisture_val integer

int sensorVCC = 13; //initialize the sensorVCC integer
int counter = 0; //initialize the counter integer

//the void keyword is used only in function declarations, it indicates that the function is expected to return no information to the function from which it was called.

void setup() { //initialize variables’ values,
//setup communications (ex: Serial),
//setup modes for digital pins (input/output),
//initialize any hardware component (sensor/actuator) plugged to the Arduino

  Serial.begin(115200); //open serial port, sets the data rate in bits per second (baud) for serial data transmission
  pinMode(sensorVCC, OUTPUT); //configures the specified pin to behave as an output
  digitalWrite(sensorVCC, LOW); //sets voltage of output to the corresponding value
  //0V (ground) for LOW
}

void loop() { //loops consecutively,
//allowing your program to change and respond,
//use it to actively control the Arduino board

  counter++; //iterates the counter integer by 1
  if(counter > 6) //change this value to set "not powered" time, higher number bigger gap
    // power the sensor
  {
    digitalWrite(sensorVCC, HIGH); //sets voltage of the output to the corresponding value
    //5V (or 3.3V on 3.3V boards) for HIGH
    delay(1000); //delay 1000ms
    //read the value from the sensor:
    moisture_val = analogRead(soilPin); //read the resistance
    //stop power
    digitalWrite(sensorVCC, LOW); //sets voltage of output to the corresponding value
    //0V (ground) for LOW
    delay(100); //delay 100ms
    counter=0; //set counter back to 0
  }
  //wait
  Serial.print("sensor = ");
  Serial.println(moisture_val); //print moisture_val
  delay(100); //delay 100ms
}
