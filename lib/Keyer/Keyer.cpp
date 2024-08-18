#include <Keyer.h>


void Keyer::begin() {
    _initSPI();
    initDisplay();

    // welcome message
    char msg[] = "    CW KEYER    ";
    _display->setMode(0);
    _display->setTitleLine(msg);

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
    _display->setTransmitLines(buffer.getSending(), buffer.getInput());
    _display->setMode(1);
}


void Keyer::_initSPI() {
    _spi = new SPIClass(FSPI);
    _spi->begin(SPI_CLK_PIN, -1, SPI_MOSI_PIN, SPI_CS_PIN);
}


/**
 * Initialize VFD Display
 */
void Keyer::initDisplay() {
    using namespace KeyboardKeyer;

    static VFD_1605N vfd;
    vfd.init(_spi);

    static DisplayContext ctx;
    static DisplayObserver observer(&ctx, &vfd);

    xTaskCreate(vRefreshDisplay, "vRefreshDisplay", 2048, &observer, 1, NULL);

    _display = &ctx;
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
//    static KeyerDecoder decoder;
//    decoder.init(_spi);
//
//    xTaskCreate(vCheckAuxSignal, "vCheckAuxSignal", 2048, &decoder, 1, NULL);
//    _decoder = &decoder;
}

void Keyer::initClock() {
    static NTPClock clk;
    clk.begin();

    xTaskCreate(vUpdateTime, "vUpdateTime", 2048, &clk, 1, NULL);

    _clock = &clk;
}

