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

void setup() {

  pinMode(A0, INPUT);
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

  Serial.println("Setup complete.\n");
}

void loop() {
  if (numRuns <= maxRuns) {
    Serial.println("Running AppendRow - Run #" + String(numRuns++));

    TembooChoreo AppendRowChoreo(client);

    // Invoke the Temboo client
    AppendRowChoreo.begin();

    // Set Temboo account credentials
    AppendRowChoreo.setAccountName(TEMBOO_ACCOUNT);
    AppendRowChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    AppendRowChoreo.setAppKey(TEMBOO_APP_KEY);

    // Set Choreo inputs
//    String RowDataValue = "12,13";
    String sensorValue = (String)analogRead(A0);
    sensorValue += ",";
    sensorValue += (String)analogRead(A1);
    AppendRowChoreo.addInput("RowData", sensorValue);
    String SpreadsheetTitleValue = "arduino_temboo";
    AppendRowChoreo.addInput("SpreadsheetTitle", SpreadsheetTitleValue);
    String RefreshTokenValue = "ya29.oAJ6eHxllGKSA0gDh6h2a6jO4v2eVLYBufoL7SISllbcr-2DHNLaM2Cq_HjXeDoUVw";
    AppendRowChoreo.addInput("RefreshToken", RefreshTokenValue);
    String ClientSecretValue = "ShtnI_es9QtEBnrOUudcCZBI";
    AppendRowChoreo.addInput("ClientSecret", ClientSecretValue);
    String ClientIDValue = "685352526328-02gepb81i0takdfjjnffm2thulrf9q6q.apps.googleusercontent.com";
    AppendRowChoreo.addInput("ClientID", ClientIDValue);

    // Identify the Choreo to run
    AppendRowChoreo.setChoreo("/Library/Google/Spreadsheets/AppendRow");

    // Run the Choreo; when results are available, print them to serial
    AppendRowChoreo.run();

    while(AppendRowChoreo.available()) {
      char c = AppendRowChoreo.read();
      Serial.print(c);
    }
    AppendRowChoreo.close();
  }

  Serial.println("\nWaiting...\n");
  delay(30000); // wait 30 seconds between AppendRow calls
}
