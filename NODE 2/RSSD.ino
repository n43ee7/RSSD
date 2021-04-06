/*
Nabeel Nayyar |             Rover Mavs-2021 |           NODE 2 (Arduino Mega 2560)
github.com/n43ee7/RSSD/
===========================================================================================================
                                            Communication Model
===========================================================================================================

               
F)         X        Y        Z    GripperPitchDegrees GripperRotationDegrees FingerDegrees SolenoidState
V)     [double]  [double]  [double]      [double]                [int]              [int]          [bool]

E)      "0.0000@0.0000@0.0000@0.0000@00000@00000@T"
        > Tokenisation with '@' character
        Functions:
                0

==========================================================================================================

Notes:
[ ] Migrate to Char arrays for preserving SRAM
SET -> RESET_PIN to LOW for [LOCAL RESET]

*/
#include "Arduino.h"
#include "stringer.h"

#if defined(__AVR_ATmega2560__)

#define BOARD_NAME "RSD-MEGA 2560"

#endif

#define STATUS_LED 13       
#define RESET_PIN  12

// SDV
#define APPROVAL_CAST "UTA"
#define SERIAL_SUCESS_FLICK 10
#define SERIAL_FAIL_FLICK 5
#define BUFFER 32
#define RX_FLICK 5

// Arm instance
typedef struct ArmInstance {
    double X;
    double Y;
    double Z;
    double GripperPitchDeg;
    int GripperRotationDeg;
    int FingerDeg;
    bool SolenoidState;
};

void StatusAction(int sequence);
void connectionInit();
String SerialListener();
ArmInstance CastReader(String inStr);

void setup() {
      
    digitalWrite(RESET_PIN, HIGH); // Firmware action
    delay(200);    
    
    pinMode(RESET_PIN, OUTPUT);
    pinMode(STATUS_LED, OUTPUT);
    Serial.begin(115200);   // Best reliable buadrate tested
    
    Serial.println("[!]" + (String)BOARD_NAME + " Armed");
    StatusAction(SERIAL_SUCESS_FLICK);
    connectionInit();   // Starts establishing connection with peer

}

void loop() {
    // Pending latency test for optimization of a robust code.
    String L; 
    ArmInstance Arm1;
    L = SerialListener();
    delay(500);
    
    //Arm1 = CastReader(L); // By now the struct has all the instant Arm Parrameters
}

void StatusAction(int sequence) {

    // Conrtols the Status LED (D-13) of the controller for status action
    // REL-A (WORKING)

    for (size_t i = 0; i < sequence; i++) {

        digitalWrite(STATUS_LED, HIGH);
        delay(30);
        digitalWrite(STATUS_LED, LOW);
        delay(30);
    }
}

void connectionInit() {

    bool ApprovalFlag = false;
    char incomingByte[BUFFER];

    while (ApprovalFlag != true){
        while (!Serial) {
            ; 
        }

        if (Serial.available() > 0) {

            int size = Serial.readBytesUntil('\n', incomingByte, BUFFER);

            if ((String)incomingByte == APPROVAL_CAST) {
                // Approval Cast is sucessful
                Serial.println("[+] Connection APPROVED.");
                ApprovalFlag = true;
                StatusAction(SERIAL_SUCESS_FLICK);
            }
            else {
                // Declined and reset
                StatusAction(SERIAL_FAIL_FLICK);
                Serial.println("[!] Connection was declined, RESTTING.");
                digitalWrite(RESET_PIN, LOW);
            }
        }
        memset(incomingByte, 0, sizeof incomingByte);
    }
}

String SerialListener() {
    char incomingByte[BUFFER] = "";

    if (Serial.available() > 0) {

        int size = Serial.readBytesUntil('\n', incomingByte, BUFFER);
    }
    return (String)incomingByte;
}

ArmInstance CastReader(String inStr) { // 00000@00000@0000@0000
    ArmInstance temp;
    

    return temp;
}