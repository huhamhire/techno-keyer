#include <VFD_1605N.h>

void VFD_1605N::sendByte(uint8_t data) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(CLK_PIN, LOW);

        if ( data & 0x01 ) {
            digitalWrite(MOSI_PIN, HIGH);
        } else {
            digitalWrite(MOSI_PIN, LOW);
        }
        data = data >> 1;
        delayMicroseconds(_delay);

        digitalWrite(CLK_PIN, HIGH);
        delayMicroseconds(_delay);
    }
}

void VFD_1605N::clear(void) {
    digitalWrite(CS_PIN, LOW);
    // 第一行
    sendByte(0x90);
    sendByte(0x00);
    for (int i = 0; i < 16; i++) {
        sendByte(0xff);
    }
    digitalWrite(CS_PIN, HIGH);
    delayMicroseconds(_delay);

    digitalWrite(CS_PIN, LOW);
    // 第二行
    sendByte(0x10);
    sendByte(0x00);
    for (int i = 0; i < 16; i++) {
        sendByte(0xff);
    }
    digitalWrite(CS_PIN, HIGH);
    delayMicroseconds(_delay);
}


void VFD_1605N::setBrightness(unsigned short brightness) {
    unsigned char bl, bh;
    
    bl = brightness % 4;
    bh = brightness / 4;
    
    digitalWrite(CS_PIN, LOW);
    sendByte(0x50 | bl);
    sendByte(bh);
    digitalWrite(CS_PIN, HIGH);
    
    delayMicroseconds(_delay);
}


void VFD_1605N::init(void) {
    pinMode(EN_PIN, OUTPUT);
    pinMode(RST_PIN, OUTPUT);
    pinMode(CS_PIN, OUTPUT);
    pinMode(CLK_PIN, OUTPUT);
    pinMode(MOSI_PIN, OUTPUT);

    // 初始化 VFD
    digitalWrite(EN_PIN, HIGH);
    digitalWrite(CS_PIN, HIGH);

    delayMicroseconds(100);
    digitalWrite(RST_PIN, LOW);
    delayMicroseconds(_delay);
    digitalWrite(RST_PIN, HIGH);

    //
    digitalWrite(CS_PIN, LOW);
    sendByte(0x70);      //normal display
    digitalWrite(CS_PIN, HIGH);
    delayMicroseconds(_delay);

    digitalWrite(CS_PIN, LOW);
    sendByte(0x6C);      //set com1-com16
    digitalWrite(CS_PIN, HIGH);
    delayMicroseconds(_delay);

    setBrightness(500);  //set brightness(duty)
    clear();             // 清除显示屏内容
}


void VFD_1605N::displayChar(unsigned char row, unsigned char col, unsigned char data) {
    digitalWrite(CS_PIN, LOW);
    
    // 选择行
    if (row == 0) {
        // 第二行
        sendByte(0x10);
    } else if (row == 1) {
        // 第一行
        sendByte(0x90);
    } else {
        // 安全中断
        digitalWrite(CS_PIN, HIGH);
        delayMicroseconds(_delay);
        return;
    }
    
    if (col > 15) {
        // 安全中断
        digitalWrite(CS_PIN, HIGH);
        delayMicroseconds(_delay);
        return;
    }
    
    sendByte(15 - col);
    sendByte(data);
    
    digitalWrite(CS_PIN, HIGH);
    delayMicroseconds(_delay);
    return;
}
