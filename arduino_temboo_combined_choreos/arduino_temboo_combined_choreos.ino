#include <SPI.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <Temboo.h>
#include "TembooAccount.h" // Contains Temboo account information

byte ethernetMACAddress[] = ETHERNET_SHIELD_MAC;
EthernetClient client;

int numRuns = 1;   // Execution count, so this doesn't run forever
int maxRuns = 10;   // Maximum number of times the Choreo should be executed
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
  Serial.println("Setup complete.\n");

}

void loop() {
  int sensorValue = digitalRead(inputPin);
  Serial.println("Sensor: " + String(sensorValue));

  if (sensorValue == HIGH) {
    if (numRuns <= maxRuns) {
      String analogValue = (String)analogRead(A0);
      analogValue  += ",";
      analogValue  += (String)analogRead(A1);
      runAppendRow(analogValue );
      runSendEmail(analogValue );
    }
  }

}

void runAppendRow(String message) {
TembooChoreo AppendRowChoreo(client);

    // Invoke the Temboo client
    AppendRowChoreo.begin();

    // Set Temboo account credentials
    AppendRowChoreo.setAccountName(TEMBOO_ACCOUNT);
    AppendRowChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    AppendRowChoreo.setAppKey(TEMBOO_APP_KEY);

    // Set profile to use for execution
    AppendRowChoreo.setProfile("arduinotemboo1");

    AppendRowChoreo.addInput("RowData", message);

    // Identify the Choreo to run
    AppendRowChoreo.setChoreo("/Library/Google/Spreadsheets/AppendRow");

    // Run the Choreo
  unsigned int returnCode = AppendRowChoreo.run();
  Serial.print("Return code: ");
  Serial.println(returnCode);
  // A return code of zero means everything worked
  if (returnCode == 0) {
    digitalWrite(outputPin, HIGH);
    delay(1000);
    digitalWrite(outputPin, LOW);
  } else
  {
     digitalWrite(outputPin, HIGH);
    delay(300);
    digitalWrite(outputPin, LOW);
  }

    while(AppendRowChoreo.available()) {
      char c = AppendRowChoreo.read();
      Serial.print(c);
    }
    
    AppendRowChoreo.close();

}

void runSendEmail(String message) {

  TembooChoreo SendEmailChoreo(client);

    // Invoke the Temboo client
    SendEmailChoreo.begin();

    // Set Temboo account credentials
    SendEmailChoreo.setAccountName(TEMBOO_ACCOUNT);
    SendEmailChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    SendEmailChoreo.setAppKey(TEMBOO_APP_KEY);

    // Set profile to use for execution
    SendEmailChoreo.setProfile("TembooEmail");
   
    SendEmailChoreo.addInput("MessageBody", message);


    // Identify the Choreo to run
    SendEmailChoreo.setChoreo("/Library/Google/Gmail/SendEmail");

     unsigned int returnCode = SendEmailChoreo.run();
    Serial.print("Return code: ");
    Serial.println(returnCode);
  // A return code of zero means everything worked
  if (returnCode == 0) {
    digitalWrite(outputPin, HIGH);
    delay(1500);
    digitalWrite(outputPin, LOW);
  } else
  {
     digitalWrite(outputPin, HIGH);
    delay(300);
    digitalWrite(outputPin, LOW);
  }
  

    while(SendEmailChoreo.available()) {
      char c = SendEmailChoreo.read();
      Serial.print(c);
    }
    SendEmailChoreo.close();
  }



