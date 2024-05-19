#ifndef _KEYER_BUFFER_
#define _KEYER_BUFFER_

#include <Arduino.h>

#define INPUT_BUFFER_SIZE 32
#define SENDING_BUFFER_SIZE 128


class KeyerBuffer {
    public:
        char* getInput();
        char* getSending();

        bool isInputEmpty();
        bool isSendingEmpty();

        void appendInput(char* c);
        void backspaceInput();
        void commitToSending();
        void revertCommitted();
        char getFirstSendingChar();
        void unshiftSending();
        
        void clearInput();
        void clearSending();
    
    private:
        char _input[INPUT_BUFFER_SIZE] = "";
        char _sending[SENDING_BUFFER_SIZE] = "";
};

#endif  // _KEYER_BUFFER_
