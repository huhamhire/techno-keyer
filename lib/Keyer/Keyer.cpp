#include <Keyer.h>


void Keyer::begin() {
    static TechnoKeyer::SPIBus spi;
    spi.begin();

    initDisplay();

    // welcome message
    char msg[] = "    CW KEYER    ";
    _display->setMode(0);
    _display->setTitleLine(msg);

    delay(2000);

    initTransmitter();
    initConfig();

    initDecoder();

    // Bind buffer to display
    _display->setTransmitLines(
            _transmitter->getOutputBuffer()->getContent(),
            _transmitter->getInputBuffer()->getContent());
    _display->setMode(1);
}


/**
 * Initialize VFD Display
 */
void Keyer::initDisplay() {
    using namespace TechnoKeyer;

    static DisplayContext ctx;
    static DisplayObserver observer(&ctx);

    xTaskCreate(vRefreshDisplay,
                "vRefreshDisplay",
                2048,
                &observer,
                1,
                NULL);

    _display = &ctx;
}


void Keyer::initTransmitter() {
    using namespace TechnoKeyer;
    static Transmitter trans;
    trans.begin();
    _transmitter = &trans;
}


// Initialize Configurations
void Keyer::initConfig() {
    using namespace TechnoKeyer;
    static ConfigManager config(_display);
    config.init();
}


// Initialize Keyer Decoder
void Keyer::initDecoder() {
    using namespace TechnoKeyer;

}
