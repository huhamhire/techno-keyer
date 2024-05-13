#include <KeyerMorse.h>

struct t_mtab morsetab[] = {
    {'.', 106},
    {',', 115},
    {'?', 76},
    {'/', 41},
    {'A', 6},
    {'B', 17},
    {'C', 21},
    {'D', 9},
    {'E', 2},
    {'F', 20},
    {'G', 11},
    {'H', 16},
    {'I', 4},
    {'J', 30},
    {'K', 13},
    {'L', 18},
    {'M', 7},
    {'N', 5},
    {'O', 15},
    {'P', 22},
    {'Q', 27},
    {'R', 10},
    {'S', 8},
    {'T', 3},
    {'U', 12},
    {'V', 24},
    {'W', 14},
    {'X', 25},
    {'Y', 29},
    {'Z', 19},
    {'1', 62},
    {'2', 60},
    {'3', 56},
    {'4', 48},
    {'5', 32},
    {'6', 33},
    {'7', 35},
    {'8', 39},
    {'9', 47},
    {'0', 63}
};

#define N_MORSE (sizeof(morsetab)/sizeof(morsetab[0]))

int dotlen;
int dashlen;
int speed = 20;

String str = "";

void beginCWOutput() {
    pinMode(CW_PIN, OUTPUT);
    digitalWrite(CW_PIN, 0);

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, 0);

    updateCWSpeed();
}

void updateCWSpeed() {
    dotlen = (1200 / speed);
    dashlen = (3 * (1200 / speed));
}

void setCWSpeed(int s) {
    speed = s;
    updateCWSpeed();
}

void SetCWString(char *s) {
    str = s;
}

void appendCWString(char *s) {
    str += s;
} 

void sendDit() {
    digitalWrite(LED_PIN, 1);
    digitalWrite(CW_PIN, 1);
    vTaskDelay(dotlen / portTICK_PERIOD_MS);

    digitalWrite(LED_PIN, 0);
    digitalWrite(CW_PIN, 0);
    vTaskDelay(dotlen / portTICK_PERIOD_MS);
}

void SendDash() {
    digitalWrite(LED_PIN, 1);
    digitalWrite(CW_PIN, 1);
    vTaskDelay(dashlen / portTICK_PERIOD_MS);

    digitalWrite(LED_PIN, 0);
    digitalWrite(CW_PIN, 0);
    vTaskDelay(dotlen / portTICK_PERIOD_MS);
}

void sendChar(char c) {
    Serial.printf("Sending %c\n", c);
    if (c == ' ') {
        vTaskDelay(7 * dotlen / portTICK_PERIOD_MS);
    } else {
        for (int i = 0; i < N_MORSE; i++) {
            if (morsetab[i].c == c) {
                unsigned char p = morsetab[i].pat;
                while (p != 1) {
                    if (p & 1) {
                        SendDash();
                    } else {
                        sendDit();
                    }
                    p = p / 2;
                }
                break;
            }
        }
        vTaskDelay(2 * dotlen / portTICK_PERIOD_MS); ;
    }
}

// Task to send morse code
void vSendMorse(void *pvParameters) {
    for ( ;; ) {
        while(str.length() != 0) {
            sendChar(str[0]);
            str.remove(0, 1);
        }
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
}