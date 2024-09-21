#include <Keyer.h>

namespace TechnoKeyer {
    SPIBus *Keyer::_spi = new SPIBus();

    void Keyer::begin() {
        _spi->begin();

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


    /**
     * Initialize Config Manager
     */
    void Keyer::initConfig() {
        static ConfigManager config(_display);
        config.init();
    }


    /**
     * Initialize Morse Transmitter
     */
    void Keyer::initTransmitter() {
        static Transmitter trans;
        trans.begin();
        _transmitter = &trans;
    }



    /**
     * Initialize Morse Decoder
     */
    void Keyer::initDecoder() {

    }
}