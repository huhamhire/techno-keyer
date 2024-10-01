#include <Keyer.h>

namespace TechnoKeyer {
    SPIBus *Keyer::_spi = new SPIBus();

    void Keyer::begin() {
        _spi->begin();

        initDisplay();

        // welcome message
        char msg[] = "    CW KEYER     ";
        _display->setMode(0);
        _display->setTitleLine(msg);

        delay(2000);

        initTransmitter();
        initReceiver();
        initConfig();

        // Bind buffer to display
        _display->setTransmitLines(
                _transmitter->getOutputBuffer()->getContent(),
                _transmitter->getInputBuffer()->getContent());
        _display->setReceiveLines(
                _receiver->getMorseLine()->getContent(),
                _receiver->getCharLine()->getContent());
        _mode = TX_MODE;
        _display->setMode(1);
        _transmitter->activate();
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
                    nullptr);

        _display = &ctx;
    }


    /**
     * Initialize Config Manager
     */
    void Keyer::initConfig() {
        static ConfigManager config(_display);
        config.begin();
        config.setOnConfig([&](Config *config) {
            // Update display brightness
            _display->setBrightness(config->bright);
            // Update transmitter
            _transmitter->setSpeed(config->tx_wpm);
            _transmitter->setTone(config->tx_tone);
            // Update receiver
            _receiver->setTone(config->rx_tone);
        });
        // Setup config event callback
        config.setOnConfigStart([&]() {
            _mode = CONFIG_MODE;
            _transmitter->deactivate();
            _receiver->deactivate();
            _display->setMode(0);
        });
        config.setOnConfigFinish([&]() {
            _mode = TX_MODE;
            _transmitter->activate();
            _display->setMode(1);
        });
    }


    /**
     * Initialize Morse Transmitter
     */
    void Keyer::initTransmitter() {
        static Transmitter trans;
        trans.begin();
        trans.deactivate();
        trans.setOnCheckMode([&](KeyerMode mode) {
            return setMode(mode);
        });
        _transmitter = &trans;
    }


    /**
     * Initialize Morse Receiver
     */
    void Keyer::initReceiver() {
        static Receiver recv;
        recv.begin();
        recv.deactivate();
        recv.setOnCheckMode([&](KeyerMode mode) {
            return setMode(mode);
        });
        _receiver = &recv;
    }

    /**
     * Switch keyer mode
     * @return
     */
    bool Keyer::setMode(KeyerMode mode) {
        if (_mode == mode) {
            // No change
            return true;
        }
        if (_mode == CONFIG_MODE) {
            // Block mode switch while config
            return false;
        }
        if (_mode == TX_MODE && mode == RX_MODE) {
            // Switch to RX mode
            if (_transmitter->isBusy()) {
                // Block mode switch while transmitting
                return false;
            } else {
                _mode = RX_MODE;
                _transmitter->deactivate();
                _receiver->activate();
                _display->setMode(2);
                return true;
            }
        } else if (_mode == RX_MODE && mode == TX_MODE) {
            // Switch to TX mode
            if (_receiver->isBusy()) {
                // Block mode switch while receiving
                return false;
            } else {
                _mode = TX_MODE;
                _receiver->deactivate();
                _transmitter->activate();
                _display->setMode(1);
                return true;
            }
        }
        return false;
    }
}