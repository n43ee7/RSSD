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

#include <string.h>

#if defined(__AVR_ATmega2560__)

#define BOARD_NAME "RSD-MEGA 2560"

#endif

#define STATUS_LED 13       
#define RESET_PIN  12

// SDV
#define APPROVAL_CAST "Z"
#define SERIAL_SUCESS_FLICK 10
#define SERIAL_FAIL_FLICK 100
#define BUFFER 16
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
    connectionInit();   // Starts establishing connection with peer

    digitalWrite(STATUS_LED, LOW);
}

void loop() {
    // Pending latency test for optimization of a robust code.
    String L; 
    ArmInstance Arm1;
    do {
        L = SerialListener();
    } while (L == "0");
    StatusAction(RX_FLICK);
    Arm1 = CastReader(L); // By now the struct has all the instant Arm Parrameters
}

void StatusAction(int sequence) {

    // Conrtols the Status LED (D-13) of the controller for status action
    // REL-A (WORKING)

    for (size_t i = 0; i < sequence; i++) {

        digitalWrite(STATUS_LED, HIGH);
        delay(50);
        digitalWrite(STATUS_LED, LOW);
        delay(50);
    }
}

void connectionInit() {

    // Establishes and confirms a serial connection with peer or resets the controller
    // REL-A (WORKING)

    bool ApprovalFlag = false;
    char incomingByte[BUFFER];

    while (ApprovalFlag != true){
        while (!Serial) {
            ; // wait for native USB Serial port to activate
        }
        if (Serial.available() > 0) {
            StatusAction(SERIAL_SUCESS_FLICK);
            Serial.println("[+] Connection ESTABLISHED, awaiting approval.");

            int size = Serial.readBytesUntil('\n', incomingByte, BUFFER);

            if (incomingByte[0] == APPROVAL_CAST[0]) {

                // Approval Cast is sucessful
                Serial.println("[+] Connection APPROVED.");
                break;
            }
            else {
                // Declined and reset
                StatusAction(SERIAL_FAIL_FLICK);
                Serial.println("[!] Connection was NOT established, RESTTING.");
                digitalWrite(RESET_PIN, LOW);

            }
        }
    }
}

String SerialListener() {
    byte icbx;
    String sdata = "";

    if (Serial.available()) {
        icbx = Serial.read();

        sdata += (char)icbx; // Typecasting each byte recieved must be okay I bet

        if (icbx == '\r') {  // Command recevied and packed.
            sdata.trim(); // trimming \r upon serial success
        }
        return sdata; 
    }
    else
    {
        return sdata + "#"; // Exception handler
    }
}

ArmInstance CastReader(String inStr) { // 00000@00000@0000@0000
    ArmInstance temp;
    char c_inStr[]= "";
    inStr.toCharArray(c_inStr,inStr.length());
    
    char *strings[BUFFER];
    char *ptr = NULL;
    byte index = 0;

    ptr = strtok(c_inStr, "@");  // takes a list of delimiters
    while (ptr != NULL){

        strings[index] = ptr;
        index++;
        ptr = strtok(NULL, "@");  // takes a list of delimiters
    }
    return temp;
    
}