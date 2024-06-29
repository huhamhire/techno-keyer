#include <Keyer.h>


void Keyer::begin() {
    initDisplay();
    // welcome message
    char msg[] = "    CW KEYER    ";
    _display->setVFDLine(0, msg);

    delay(2000);
    
    // Start input/output
    static KeyerBuffer buffer;
    _buffer = &buffer;
    initInput();
    initOutput();

    initEncorder();
    
    // Bind buffer to display
    _display->setVFDLine(0, buffer.getSending());
    _display->setVFDLine(1, buffer.getInput());

    // TODO remove test
    buffer.appendInput("CQ CQ CQ");
    buffer.commitToSending();
}

// Initialize VFD Display
void Keyer::initDisplay() {
    static VFD_1605N VFD;
    VFD.init();

    static KeyerDisplay display(&VFD);
    xTaskCreate(vRefreshVFD, "vRefreshVFD", 2048, &display, 1, NULL);

    _display = &display;
}

// Initialize Keyer Input
void Keyer::initInput() {
    static KeyerInput input(_buffer);
    input.init();
    
    xTaskCreate(vGetKey, "vGetKey", 2048, &input, 1, NULL);

    _input = &input;
}

// Initialize Rotory Encorder
void Keyer::initEncorder() {
    static KeyerEncoder encorder;
    encorder.begin();

    xTaskCreate(vEncoderCheck, "vEncoderCheck", 2048, &encorder, 1, NULL);

    _encoder = &encorder;
}   

// Initialize Keyer Output
void Keyer::initOutput() {
    static KeyerMorse morse(_buffer);
    morse.begin();
    morse.setSpeed(20);

    xTaskCreate(vSendMorse, "vSendMorse", 2048, &morse, 1, NULL);

    _morse = &morse;
}