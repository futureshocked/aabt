#include <SPI.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <Temboo.h>
#include "TembooAccount.h" // Contains Temboo account information

#include "DHT.h"

#define DHTPI N 2     // what digital pin we're connected to
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);

float h;
float t;

int outputPin = 6;

byte ethernetMACAddress[] = ETHERNET_SHIELD_MAC;
EthernetClient client;

// The number of times to trigger the action if the condition is met
// We limit this so you won't use all of your Temboo calls while testing
int maxCalls = 10;

// The number of times this Choreo has been run so far in this sketch
int calls = 0;

int inputPin = 8;

void setup() {
  Serial.begin(9600);
  
  // For debugging, wait until the serial console is connected
  delay(4000);
  while(!Serial);

  Serial.print("DHCP:");
  if (Ethernet.begin(ethernetMACAddress) == 0) {
    Serial.println("FAIL");
    while(true);
  }
  Serial.println("OK");
  delay(5000);

  // Initialize pins
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);

  dht.begin();


  Serial.println("Setup complete.\n");
}

void loop() {
  int sensorValue = digitalRead(inputPin);
  Serial.println("Sensor: " + String(sensorValue));

  if (sensorValue == HIGH) {

    h = dht.readHumidity();
    t = dht.readTemperature();
    
    if (calls < maxCalls) {
      Serial.println("\nTriggered! Calling AppendRow Choreo...");
      runAppendRow();
      sendEmail();
      calls++;
    } else {
      Serial.println("\nTriggered! Skipping to save Temboo calls. Adjust maxCalls as required.");
    }
  }
  delay(250);
}

void sendEmail()
{
   

    TembooChoreo SendEmailChoreo(client);

    // Invoke the Temboo client
    SendEmailChoreo.begin();

    // Set Temboo account credentials
    SendEmailChoreo.setAccountName(TEMBOO_ACCOUNT);
    SendEmailChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    SendEmailChoreo.setAppKey(TEMBOO_APP_KEY);

    // Set profile to use for execution
    SendEmailChoreo.setProfile("TembooGmailExample");

    // Identify the Choreo to run
    SendEmailChoreo.setChoreo("/Library/Google/Gmail/SendEmail");

    String sensorValueMessage = "Temperature: ";
    sensorValueMessage += t;
    sensorValueMessage += ", Humidity: ";
    sensorValueMessage += h;
    SendEmailChoreo.addInput("MessageBody", sensorValueMessage);

    String SubjectValue = "Lab environment values included!";
    SendEmailChoreo.addInput("Subject", SubjectValue);

    // Run the Choreo; when results are available, print them to serial
    SendEmailChoreo.run();

    while(SendEmailChoreo.available()) {
      char c = SendEmailChoreo.read();
      Serial.print(c);
    }
    SendEmailChoreo.close();
  
}

void runAppendRow() {
  TembooChoreo AppendRowChoreo(client);

  // Set Temboo account credentials
  AppendRowChoreo.setAccountName(TEMBOO_ACCOUNT);
  AppendRowChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
  AppendRowChoreo.setAppKey(TEMBOO_APP_KEY);

  // Set profile to use for execution
  AppendRowChoreo.setProfile("txplorespreadsheetdemo");
  // Identify the Choreo to run
  AppendRowChoreo.setChoreo("/Library/Google/Spreadsheets/AppendRow");

  String sensorValue = (String)t;
  sensorValue += ",";
  sensorValue += (String)h;
  AppendRowChoreo.addInput("RowData", sensorValue);
  
  // Run the Choreo
  unsigned int returnCode = AppendRowChoreo.run();

  // A return core of zero means everything worked
  if (returnCode == 0) {
    digitalWrite(outputPin, HIGH);
  }

  // Read and print the error message
  while (AppendRowChoreo.available()) {
    char c = AppendRowChoreo.read();
    Serial.print(c);
  }
  Serial.println();
  AppendRowChoreo.close();
}
