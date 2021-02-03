/*
Nabeel Nayyar | Rover Mavs-2021
============================================
    Communication Model
============================================
SET -> RESET_PIN to LOW for [LOCAL RESET]
*/

#include <SoftwareSerial.h>

#define STATUS_LED 13       
#define RESET_PIN  12

// SDV
#define APPROVAL_CAST "1"
#define SERIAL_SUCESS_FLICK 10
#define SERIAL_FAIL_FLICK 100
#define BUFFER 16

void StatusAction(int sequence);
void writeString(String stringData);
void connectionInit();

void setup() {
    
    digitalWrite(RESET_PIN, HIGH);
    delay(200);    

    pinMode(RESET_PIN, OUTPUT);
    pinMode(STATUS_LED, OUTPUT);
    Serial.begin(38400);
    
    Serial.println("[!] RSD-Mega Armed");

}

void loop() {
  // Starting a Serial Channel and confirming peer.
    connectionInit();
    
  // Confirming serial delivery 
   // Attaching main routine to the serial.
}

void StatusAction(int sequence) {
    for (size_t i = 0; i < sequence; i++) {

        digitalWrite(STATUS_LED, HIGH);
        delay(50);
        digitalWrite(STATUS_LED, LOW);
        delay(50);
    }
}

void writeString(String stringData) { // Used to serially push out a String with Serial.write()

    for (int i = 0; i < stringData.length(); i++)
    {
        Serial.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
    }

}// end writeString

void readSerial() {
    char parram[BUFFER];
    // if we get a command, turn the LED on or off:
    if (Serial.available() > 0) {
        int size = Serial.readBytesUntil('\n', parram, BUFFER);
        if (parram[0] == 'Y') {
            digitalWrite(LED_BUILTIN, HIGH);
        }
        if (parram[0] == 'N') {
            digitalWrite(LED_BUILTIN, LOW);
        }
    }
}

void connectionInit() {
    bool ApprovalFlag = false;
    char incomingByte[BUFFER];

    while (ApprovalFlag != true){
        if (Serial.available() > 0) {
            StatusAction(SERIAL_SUCESS_FLICK);
            Serial.println("[+] Connection ESTABLISHED, awaiting approval.");

            int size = Serial.readBytesUntil('\n', incomingByte, BUFFER);

            if (incomingByte[0] == APPROVAL_CAST[0]) {

                // Approval Cast is sucessful
                Serial.println("[+] Connection APPROVED.");

            }
            else
            {
                // Declined and reset
                StatusAction(SERIAL_FAIL_FLICK);
                Serial.println("[!] Connection was NOT established, RESTTING.");
     

            }
        }
    }
}