
const int BUZZER_PIN = 10;

const int BUTTON_DO = 2;
const int BUTTON_RE = 3;
const int BUTTON_MI = 4;
const int BUTTON_FA = 5;
const int BUTTON_SOL = 6;
const int BUTTON_LA = 7;
const int BUTTON_SI = 8;
const int BUTTON_DJ = 9;

const int NOTE_DO = 262;
const int NOTE_RE = 294;
const int NOTE_MI = 330;
const int NOTE_FA = 349;
const int NOTE_SOL = 392;
const int NOTE_LA = 440;
const int NOTE_SI = 494;

bool djMode = false;
bool previousDjButtonState = HIGH;
bool previousDoButtonState = HIGH;
bool previousReButtonState = HIGH;

const int marioMelody[] = {
    659, 659, 659, 0,
    523, 659, 784, 0,
    392, 0, 523, 0,
    392, 0, 330, 0,
    440, 494, 466, 440,
    392, 659, 784, 880,
    698, 784, 0, 659,
    523, 587, 494, 0
};

const int marioDurations[] = {
    150, 150, 300, 150,
    150, 300, 600, 200,
    400, 150, 300, 150,
    300, 150, 300, 150,
    300, 300, 150, 300,
    200, 200, 200, 300,
    150, 300, 150, 150,
    150, 150, 300, 300
};

const int marioMelodyLength =
    sizeof(marioMelody) / sizeof(marioMelody[0]);

const int sonicMelody[] = {
    784, 659, 523, 659,
    784, 880, 784, 659,
    587, 659, 784, 659,
    523, 440, 523, 0,

    659, 784, 880, 784,
    659, 587, 659, 784,
    880, 988, 880, 784,
    659, 523, 587, 0
};

const int sonicDurations[] = {
    200, 200, 200, 200,
    300, 200, 200, 300,
    200, 200, 300, 200,
    400, 200, 400, 150,

    200, 200, 300, 200,
    200, 200, 200, 300,
    300, 200, 200, 300,
    300, 200, 400, 200
};

const int sonicMelodyLength =
    sizeof(sonicMelody) / sizeof(sonicMelody[0]);

const int pacmanMelody[] = {
    784, 988, 1047, 988,
    784, 659, 784, 988,
    1047, 988, 784, 659,
    587, 659, 784, 0
};

const int pacmanDurations[] = {
    120, 120, 240, 120,
    120, 240, 120, 120,
    240, 120, 120, 240,
    120, 120, 350, 200
};

const int pacmanMelodyLength =
    sizeof(pacmanMelody) / sizeof(pacmanMelody[0]);

const int tetrisMelody[] = {
    659, 494, 523, 587,
    523, 494, 440, 440,
    523, 659, 587, 523,
    494, 523, 587, 659,
    523, 440, 440, 0,

    587, 698, 880, 784,
    698, 659, 523, 659,
    587, 523, 494, 494,
    523, 659, 587, 523,
    494, 523, 587, 659,
    523, 440, 440, 0
};

const int tetrisDurations[] = {
    300, 150, 150, 300,
    150, 150, 300, 150,
    150, 300, 300, 150,
    150, 150, 300, 300,
    300, 300, 300, 200,

    300, 150, 300, 150,
    150, 300, 150, 150,
    300, 150, 150, 300,
    150, 300, 300, 150,
    150, 150, 300, 300,
    300, 300, 300, 200
};

const int tetrisMelodyLength =
    sizeof(tetrisMelody) / sizeof(tetrisMelody[0]);


const int funk90Melody[] = {
    523, 659, 784, 659,
    523, 587, 659, 0,
    440, 523, 659, 523,
    440, 494, 523, 0,

    659, 784, 880, 784,
    659, 587, 523, 587,
    659, 784, 659, 523,
    587, 523, 440, 0,

    523, 659, 784, 659,
    523, 587, 659, 0,
    440, 523, 659, 784,
    659, 523, 440, 0
};

const int funk90Durations[] = {
    160, 160, 320, 160,
    160, 160, 320, 120,
    160, 160, 320, 160,
    160, 160, 320, 120,

    160, 160, 320, 160,
    160, 160, 320, 120,
    160, 160, 160, 160,
    320, 160, 400, 120,

    160, 160, 320, 160,
    160, 160, 320, 120,
    160, 160, 320, 160,
    160, 160, 400, 200
};

const int funk90MelodyLength =
    sizeof(funk90Melody) / sizeof(funk90Melody[0]);


void setup()
{
    pinMode(BUZZER_PIN, OUTPUT);

    pinMode(BUTTON_DO, INPUT_PULLUP);
    pinMode(BUTTON_RE, INPUT_PULLUP);
    pinMode(BUTTON_MI, INPUT_PULLUP);
    pinMode(BUTTON_FA, INPUT_PULLUP);
    pinMode(BUTTON_SOL, INPUT_PULLUP);
    pinMode(BUTTON_LA, INPUT_PULLUP);
    pinMode(BUTTON_SI, INPUT_PULLUP);
    pinMode(BUTTON_DJ, INPUT_PULLUP);

    Serial.begin(9600);

    Serial.println("Modo Piano: ON");
    Serial.println("Modo DJ: OFF");
}

void loop()
{
    handleModeButton();

    bool currentDoButtonState = digitalRead(BUTTON_DO);
    bool doButtonPressed =
        previousDoButtonState == HIGH &&
        currentDoButtonState == LOW;

    previousDoButtonState = currentDoButtonState;

    bool currentReButtonState = digitalRead(BUTTON_RE);
    bool reButtonPressed =
        previousReButtonState == HIGH &&
        currentReButtonState == LOW;

    previousReButtonState = currentReButtonState;

    if (djMode)
    {
        handleDjMode(doButtonPressed, reButtonPressed);
    }
    else
    {
        handlePianoMode();
    }
}

void handleModeButton()
{
    bool currentDjButtonState = digitalRead(BUTTON_DJ);

    if (previousDjButtonState == HIGH &&
        currentDjButtonState == LOW)
    {
        djMode = !djMode;

        noTone(BUZZER_PIN);

        if (djMode)
        {
            Serial.println("Modo DJ: ON");
        }
        else
        {
            Serial.println("Modo DJ: OFF");
        }
    }

    previousDjButtonState = currentDjButtonState;
}

void handlePianoMode()
{
    if (digitalRead(BUTTON_DO) == LOW)
    {
        tone(BUZZER_PIN, NOTE_DO);
    }
    else if (digitalRead(BUTTON_RE) == LOW)
    {
        tone(BUZZER_PIN, NOTE_RE);
    }
    else if (digitalRead(BUTTON_MI) == LOW)
    {
        tone(BUZZER_PIN, NOTE_MI);
    }
    else if (digitalRead(BUTTON_FA) == LOW)
    {
        tone(BUZZER_PIN, NOTE_FA);
    }
    else if (digitalRead(BUTTON_SOL) == LOW)
    {
        tone(BUZZER_PIN, NOTE_SOL);
    }
    else if (digitalRead(BUTTON_LA) == LOW)
    {
        tone(BUZZER_PIN, NOTE_LA);
    }
    else if (digitalRead(BUTTON_SI) == LOW)
    {
        tone(BUZZER_PIN, NOTE_SI);
    }
    else
    {
        noTone(BUZZER_PIN);
    }
}

void handleDjMode(bool doButtonPressed, bool reButtonPressed)
{
    if (doButtonPressed)
    {
        Serial.println("Reproduzindo tema do Mario...");
        playMelody(
            marioMelody,
            marioDurations,
            marioMelodyLength);
        Serial.println("Melodia finalizada.");
    }
    else if (reButtonPressed)
    {
        Serial.println("Reproduzindo tema do Sonic...");
        playMelody(
            sonicMelody,
            sonicDurations,
            sonicMelodyLength);
        Serial.println("Melodia finalizada.");
    }
    else if (digitalRead(BUTTON_MI) == LOW)
    {
        Serial.println("Reproduzindo tema do Pac-Man...");
        playMelody(
            pacmanMelody,
            pacmanDurations,
            pacmanMelodyLength);
        Serial.println("Melodia finalizada.");
    }
    else if (digitalRead(BUTTON_FA) == LOW)
    {
        Serial.println("Reproduzindo tema do Tetris...");
        playMelody(
            tetrisMelody,
            tetrisDurations,
            tetrisMelodyLength);
        Serial.println("Melodia finalizada.");
    }
    else if (digitalRead(BUTTON_SOL) == LOW)
    {
        Serial.println("Reproduzindo tema Funk 90...");
        playMelody(
            funk90Melody,
            funk90Durations,
            funk90MelodyLength);
        Serial.println("Melodia finalizada.");
    }
}

void playMelody(
    const int melody[],
    const int durations[],
    int length)
{
    for (int i = 0; i < length; i++)
    {
        if (melody[i] == 0)
        {
            noTone(BUZZER_PIN);
        }
        else
        {
            tone(BUZZER_PIN, melody[i]);
        }

        delay(durations[i]);
        noTone(BUZZER_PIN);
    }
}
