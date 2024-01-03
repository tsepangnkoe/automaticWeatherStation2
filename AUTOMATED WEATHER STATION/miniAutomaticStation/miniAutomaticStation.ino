
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial sim808(7, 8); // RX, TX pins for the SIM808
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns, 2 rows

#include <DHT.h>

#define DHTPIN A0
DHT dht(DHTPIN, DHT22);

void setup() {
  sim808.begin(9600);  // SIM808 baud rate
  Serial.begin(9600);  // Serial Monitor baud rate
  lcd.begin();     // initialize the lcd with 16 columns and 2 rows
  dht.begin();
  delay(1000);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  delay(100);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(t) + "C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: " + String(h) + "%");

  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.println(" °C");
  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.println(" %");

  if (sim808.available())
    Serial.write(sim808.read());

 sim808.println("AT");
//   delay(1000);

  sim808.println("AT+CPIN?");
  delay(1000);

  sim808.println("AT+CREG?");
  delay(1000);

  sim808.println("AT+CGATT?");
  delay(1000);

  sim808.println("AT+CIPSHUT");
  delay(1000);

  sim808.println("AT+CIPSTATUS");
  delay(2000);

  sim808.println("AT+CIPMUX=0");
  delay(2000);

  ShowSerialData();

  sim808.println("AT+CSTT=\"internet\"");//start task and setting the APN,
  delay(1000);

  ShowSerialData();

  sim808.println("AT+CIICR");//bring up wireless connection
  delay(3000);

  ShowSerialData();

  sim808.println("AT+CIFSR");//get local IP address
  delay(2000);

  ShowSerialData();

  sim808.println("AT+CIPSPRT=0");
  delay(3000);

  ShowSerialData();

  sim808.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);

  ShowSerialData();

  sim808.println("AT+CIPSEND");//begin send data to the remote server
  delay(4000);
  ShowSerialData();

  String str = "GET https://api.thingspeak.com/update?api_key=NOG2XAI8RFYAVDE1&field1=" + String(t) + "&field2=" + String(h);
  Serial.println(str);
  sim808.println(str);//begin send data to the remote server

  delay(4000);
  ShowSerialData();

  sim808.println((char)26);//sending
  delay(5000);//waiting for reply, important! the time is based on the condition of the internet 
  sim808.println();

  ShowSerialData();

  sim808.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
}

void ShowSerialData() {
  while (sim808.available() != 0)
    Serial.write(sim808.read());  // ...

  delay(5000); // Adjust this delay according to your requirements
}

