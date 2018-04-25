/* Vitalii Stadnyk
 * Senior Capstone Project
 * Smart Waste Monitoring System
 * Software for taking distance readings from Arduino and sending them to the web server
 * April 25th, 2018 */
 
#include <Process.h>

const int trigPin = 8;
const int echoPin = 7;
const int trigPin1 = 4;
const int echoPin1 = 2;

void setup() {
  Bridge.begin();
  
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT); 
  
  Serial.begin(9600);
}

void loop() {
  long data = getReading();
  runCurl(data);
}

long getReading(){
  long duration, duration1, cm, cm1;
  const int numReadings = 5;
  long readingOne[numReadings] = {};
  long readingTwo[numReadings] = {};
  const int MAXCAPACITY = 70;

  // Getting specified number of readings for each sensor
  for(int i = 0; i < numReadings; i++){
    cm = MAXCAPACITY + 10;
    cm1 = MAXCAPACITY + 10;
    
    // Getting readings for each sensor and filtering based on bin's capacity
    while ((cm > MAXCAPACITY) && (cm1 > MAXCAPACITY)){
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      duration = pulseIn(echoPin, HIGH);
      cm = microsecondsToCentimeters(duration);
      
      digitalWrite(trigPin1, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin1, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin1, LOW);
      
      duration1 = pulseIn(echoPin1, HIGH);
      cm1 = microsecondsToCentimeters(duration1);
    }
    // Saving filtered readings
    readingOne[i] = cm;
    readingTwo[i] = cm1;
  }

  // Getting "final" reading for each sensor
  long finalReadingOne = (readingOne[0] + readingOne[1] + readingOne[2])/3;
  long finalReadingTwo = (readingTwo[0] + readingTwo[1] + readingTwo[2])/3;

  // Determining which reading to send to the web server
  if (finalReadingOne > finalReadingTwo)
    return finalReadingTwo;
  else
    return finalReadingOne;

  return finalReadingOne;
}

// Converting Ultrasonic time readings into distance
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

// Sending data to the web server
void runCurl(long data){
  Process p;
  String sendData = String(data);
  
  p.begin("curl");
  p.addParameter("-k");
  p.addParameter("-H");
  p.addParameter("Content-Type: application/json");
  p.addParameter("-X");
  p.addParameter("POST");
  p.addParameter("-u");
  p.addParameter("foo:abcd.123");
  p.addParameter("https://smartwaste.herokuapp.com/data");
  p.addParameter("--data");
  p.addParameter("{\"Data\":" + sendData + "}");
  p.run();

  while (p.available()>0) {
    char c = p.read();
    Serial.print(c);
  }

  Serial.flush();
  delay(5000); 
}


