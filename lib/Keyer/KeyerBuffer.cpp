#include <KeyerBuffer.h>

// Get input buffer
char* KeyerBuffer::getInput() {
    return _input;
}


// Get sending buffer
char* KeyerBuffer::getSending() {
    return _sending;
}


// Check if input buffer is empty
bool KeyerBuffer::isInputEmpty() {
    return strlen(_input) == 0;
}


// Check if sending buffer is empty
bool KeyerBuffer::isSendingEmpty() {
    return strlen(_sending) == 0;
}


// Append character to input buffer
void KeyerBuffer::appendInput(char* c) {
    if (strlen(_input) < INPUT_BUFFER_SIZE) {
        strcat(_input, c);
    } else {
        // Buffer full
    }
}


// Remove last character from input buffer
void KeyerBuffer::backspaceInput() {
    if (strlen(_input) > 0) {
        _input[strlen(_input) - 1] = '\0';
    }
}


// Commit input buffer to sending buffer
void KeyerBuffer::commitToSending() {
    if (strlen(_input) == 0) {
        // Nothing to send
        return;
    } else if (strlen(_sending) + strlen(_input) + 1 > SENDING_BUFFER_SIZE) {
        // Sending buffer full
        return;
    }

    strcat(_sending, _input);
    strcat(_sending, " ");

    // clear input buffer
    clearInput();
}

// Get first character from sending buffer
char KeyerBuffer::getFirstSendingChar() {
    return _sending[0];
}


// Remove first character from sending buffer
void KeyerBuffer::unshiftSending() {
    uint8_t len = strlen(_sending);
    for (int i = 0; i < len - 1; i++) {
        _sending[i] = _sending[i + 1];
    }
    _sending[len - 1] = '\0';
}


// Clear input buffer
void KeyerBuffer::clearInput() {
    memset(_input, 0, INPUT_BUFFER_SIZE);
}


//  Clear sending buffer
void KeyerBuffer::clearSending() {
    memset(_sending, 0, SENDING_BUFFER_SIZE);
}
