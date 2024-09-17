#include <Keyer.h>


void Keyer::begin() {
    _initSPI();
    initDisplay();

    // welcome message
    char msg[] = "    CW KEYER    ";
    _display->setMode(0);
    _display->setTitleLine(msg);

    delay(2000);

    initTransmitter();
    initConfig();

    initDecoder();

    // Wifi & Clock
    // wifiClient.connect();
    // initClock();

    // Bind buffer to display
    _display->setTransmitLines(
            _transmitter->getOutputBuffer()->getContent(),
            _transmitter->getInputBuffer()->getContent());
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

    xTaskCreate(vRefreshDisplay,
                "vRefreshDisplay",
                2048,
                &observer,
                1,
                NULL);

    _display = &ctx;
}

void Keyer::initTransmitter() {
    using namespace KeyboardKeyer;
    static Transmitter trans;
    trans.begin();
    _transmitter = &trans;
}

// Initialize Configurations
void Keyer::initConfig() {
    static KeyerConfig config(_display, _morse);
    config.init();

    xTaskCreate(vEncoderCheck,
                "vEncoderCheck",
                2048,
                &config,
                1,
                NULL);

    _config = &config;
}


// Initialize Keyer Decoder
void Keyer::initDecoder() {
    static KeyerDecoder decoder;
    decoder.init(_spi);

    xTaskCreate(vCheckAuxSignal,
                "vCheckAuxSignal",
                2048,
                &decoder,
                1,
                NULL);
    _decoder = &decoder;
}

void Keyer::initClock() {
    static NTPClock clk;
    clk.begin();

    xTaskCreate(vUpdateTime,
                "vUpdateTime",
                2048,
                &clk,
                1,
                NULL);

    _clock = &clk;
}

