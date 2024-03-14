#include <M5EPD.h>

M5EPD_Canvas canvas(&M5.EPD);

const int NUM_OPTIONS = 3;
const char *options[NUM_OPTIONS] = {"BT", "manuel", "Musique"};
const int optionX = 200;
const int optionY[NUM_OPTIONS] = {200, 400, 600};
const int optionWidth = 140;
const int optionHeight = 60;
const int backButtonX = 20;
const int backButtonY = 20;
const int backButtonWidth = 120;
const int backButtonHeight = 40;

bool optionSelected = false;

void drawMenu() {
    canvas.fillCanvas(0);
    canvas.setTextSize(3);
    for (int i = 0; i < NUM_OPTIONS; i++) {
        canvas.drawString(options[i], optionX, optionY[i]);
        canvas.drawRect(optionX - 10, optionY[i] - 10, optionWidth + 20, optionHeight + 20, 15);
    }
    canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
}

void drawBackButton() {
    canvas.drawRect(backButtonX, backButtonY, backButtonWidth, backButtonHeight, 15);
    canvas.setTextSize(2);
    canvas.drawString("Retour", backButtonX + 10, backButtonY + 10);
    canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
}

void performAction(const char *option) {
    canvas.fillCanvas(0);
    canvas.setTextSize(5);
    if (strcmp(option, "BT") == 0) {
        canvas.drawString("Thomas", 100, 400);
    } else if (strcmp(option, "manuel") == 0) {
        canvas.drawString("OK", 200, 400);
    } else if (strcmp(option, "Musique") == 0) {
        // Ajoutez ici le code pour l'action correspondant à "Musique"
    }
    drawBackButton();
}

void setup() {
    M5.begin();
    M5.EPD.SetRotation(90);
    M5.TP.SetRotation(90);
    M5.EPD.Clear(true);
    canvas.createCanvas(540, 960);
    drawMenu();
}

void loop() {
    if (M5.TP.available()) {
        if (!M5.TP.isFingerUp()) {
            M5.TP.update();
            for (int i = 0; i < 2; i++) {
                tp_finger_t FingerItem = M5.TP.readFinger(i);
                int touchX = FingerItem.x;
                int touchY = FingerItem.y;
                if (!optionSelected) {
                    for (int j = 0; j < NUM_OPTIONS; j++) {
                        if (touchX >= optionX && touchX <= optionX + optionWidth &&
                            touchY >= optionY[j] && touchY <= optionY[j] + optionHeight) {
                            // Action correspondant à l'option j
                            Serial.printf("Option sélectionnée: %s\n", options[j]);
                            performAction(options[j]);
                            optionSelected = true;
                        }
                    }
                } else {
                    if (touchX >= backButtonX && touchX <= backButtonX + backButtonWidth &&
                        touchY >= backButtonY && touchY <= backButtonY + backButtonHeight) {
                        // Bouton "retour" pressé, réafficher le menu
                        drawMenu();
                        optionSelected = false;
                    }
                }
            }
        }
    }
}
