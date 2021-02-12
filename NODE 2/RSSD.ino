/*
Nabeel Nayyar |             Rover Mavs-2021 |           NODE 2 (Arduino Mega 2560)
github.com/n43ee7/RSSD/
========================================================================================
                                Communication Model
========================================================================================

      
                    [000]                    [000]                    [000]
                Component Identifier        Bit Order 1              Bit Order 2
      
         Functions:
                L13000xx    Sets LED 13 (Onboard or Pin 13) to flicker 'xx' times
                SI0MSG01    Casts a Serial Message echo of system name


=========================================================================================

Notes:
SET -> RESET_PIN to LOW for [LOCAL RESET]

*/

#if defined(__AVR_ATmega2560__)

#define BOARD_NAME "RSD-MEGA 2560"

#endif

#define STATUS_LED 13       
#define RESET_PIN  12

// SDV
#define APPROVAL_CAST "Z99999999" 
#define SERIAL_SUCESS_FLICK 10
#define SERIAL_FAIL_FLICK 100
#define BUFFER 9                    // 0-8 + /n = 9?

void StatusAction(int sequence);
void connectionInit();
bool CastComparter(char a[BUFFER], char b[BUFFER]);

void setup() {
    
    digitalWrite(RESET_PIN, HIGH); // Firmware action
    delay(200);    

    pinMode(RESET_PIN, OUTPUT);
    pinMode(STATUS_LED, OUTPUT);
    Serial.begin(115200);   // Best reliable buadrate tested
    
    Serial.println("[!]" + (String)BOARD_NAME + "Armed");
    connectionInit();   // Starts establishing connection with peer

    digitalWrite(STATUS_LED, LOW);
}

void loop() {
    // Communication test
    char parram[BUFFER];

    if (Serial.available() > 0) {
        int size = Serial.readBytesUntil('\n', parram, BUFFER);
        
        if (parram[0] == 'L') {         // Status Action to LED
            
        }
        if (parram[0] == 'S') {        // Serial echo
                    
        }
    }
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

bool CastComparter(char a[BUFFER], char b[BUFFER]) {

    // Compares two input character arrays and returns a flag
    // MOD-A (CHANGE)

    bool flag = false;
    
    for (int i = 0; i < BUFFER + 1; i++) {

        if (a[i] == b[i]) {
            flag = true;
        }
    
    }
    
    return flag;
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