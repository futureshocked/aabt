#include <SPI.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <Temboo.h>
#include "TembooAccount.h" // Contains Temboo account information

byte ethernetMACAddress[] = ETHERNET_SHIELD_MAC;
EthernetClient client;

// The number of times to trigger the action if the condition is met
// We limit this so you won't use all of your Temboo calls while testing
int maxCalls = 10;

// The number of times this Choreo has been run so far in this sketch
int calls = 0;

int inputPin = 2;
int outputPin = 6;

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

  Serial.println("Setup complete.\n");
}

void loop() {
  int sensorValue = digitalRead(inputPin);
  Serial.println("Sensor: " + String(sensorValue));

  if (sensorValue == HIGH) {
    if (calls < maxCalls) {
      Serial.println("\nTriggered! Calling AppendRow Choreo...");
      runAppendRow(sensorValue);
      calls++;
    } else {
      Serial.println("\nTriggered! Skipping to save Temboo calls. Adjust maxCalls as required.");
    }
  }
  delay(250);
}

void runAppendRow(int sensorValue) {
  TembooChoreo AppendRowChoreo(client);

  // Set Temboo account credentials
  AppendRowChoreo.setAccountName(TEMBOO_ACCOUNT);
  AppendRowChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
  AppendRowChoreo.setAppKey(TEMBOO_APP_KEY);

  // Set profile to use for execution
  AppendRowChoreo.setProfile("ArduinoUnoButtonLED");
  // Identify the Choreo to run
  AppendRowChoreo.setChoreo("/Library/Google/Spreadsheets/AppendRow");
    String analogSensorValue = (String)analogRead(A0);
    analogSensorValue  += ",";
    analogSensorValue  += (String)analogRead(A1);
    AppendRowChoreo.addInput("RowData", analogSensorValue );
    runSendEmail(analogSensorValue);


  // Run the Choreo
  unsigned int returnCode = AppendRowChoreo.run();

  // A return code of zero means everything worked
  if (returnCode == 0) {
    digitalWrite(outputPin, HIGH);
    delay(1000);
    digitalWrite(outputPin, LOW);
  } else {
        digitalWrite(outputPin, HIGH);
    delay(500);
    digitalWrite(outputPin, LOW);
  delay(500);
    digitalWrite(outputPin, HIGH);
    delay(500);
    digitalWrite(outputPin, LOW);
    while (AppendRowChoreo.available()) {
        char c = AppendRowChoreo.read();
        Serial.print(c);
      }
      
  }
  Serial.print("Return code: ");
  Serial.println(returnCode);

  AppendRowChoreo.close();
}

void runSendEmail(String message) {
  TembooChoreo SendEmailChoreo(client);

  // Set Temboo account credentials
  SendEmailChoreo.setAccountName(TEMBOO_ACCOUNT);
  SendEmailChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
  SendEmailChoreo.setAppKey(TEMBOO_APP_KEY);

  // Set profile to use for execution
  SendEmailChoreo.setProfile("Gmail");
  // Identify the Choreo to run
  SendEmailChoreo.setChoreo("/Library/Google/Gmail/SendEmail");
  SendEmailChoreo.addInput("MessageBody", message);
  // Run the Choreo
  unsigned int returnCode = SendEmailChoreo.run();

  // A return code of zero means everything worked
  if (returnCode == 0) {
    digitalWrite(outputPin, HIGH);
  }

  SendEmailChoreo.close();
}

