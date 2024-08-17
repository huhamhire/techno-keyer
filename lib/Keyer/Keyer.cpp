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

    initConfig();

    initDecoder();

    // Wifi & Clock
    // wifiClient.connect();
    // initClock();
    
    // Bind buffer to display
    _display->setVFDLine(0, buffer.getSending());
    _display->setVFDLine(1, buffer.getInput());
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

// Initialize Configurations
void Keyer::initConfig() {
    static KeyerConfig config(_buffer, _display, _morse);
    config.init();

    xTaskCreate(vEncoderCheck, "vEncoderCheck", 2048, &config, 1, NULL);

    _config = &config;
}   

// Initialize Keyer Output
void Keyer::initOutput() {
    static KeyerMorse morse(_buffer);
    morse.begin();
    morse.setSpeed(20);

    xTaskCreate(vSendMorse, "vSendMorse", 2048, &morse, 1, NULL);

    _morse = &morse;
}


// Initialize Keyer Decoder
void Keyer::initDecoder() {
    static KeyerDecoder decoder;
    decoder.init();

    xTaskCreate(vCheckAuxSignal, "vCheckAuxSignal", 2048, &decoder, 1, NULL);
    _decoder = &decoder;
}

void Keyer::initClock() {
    static NTPClock clk;
    clk.begin();

    xTaskCreate(vUpdateTime, "vUpdateTime", 2048, &clk, 1, NULL);

    _clock = &clk;
}

