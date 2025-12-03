#include <ti/devices/msp/msp.h> 
#include "../LP_MSPM0G3507_SW/LP_MSPM0G3507/bsp.h" 
#include "../LP_MSPM0G3507_SW/LP_MSPM0G3507/timer.h" 
#include "../LP_MSPM0G3507_SW/LP_MSPM0G3507/tone_pitch.h" 
#include "../LP_MSPM0G3507_SW/LP_MSPM0G3507/MKII.h" 
#include <stdint.h> 
#include <stdbool.h>

#define FALSE 0 #define TRUE 1

#define PROJECT_CLOCK_FREQUENCY 4000000u #define TIMERA1_AS_GPT ((GPTIMER_Regs *)TIMA1)

// BPM and
#define BPM 140u 
#define QUARTER_MS (60000u / BPM) 
#define EIGHTH_MS (QUARTER_MS / 2) 
#define SIXTEENTH_MS (EIGHTH_MS/2) 
#define HALF_MS (QUARTER_MS * 2)

// dance of the sugar plum fairy
// creating array for melody 
uint32_t melody_freq[] = { 
// ==== MEASURE 1 ==== 
NOTE_E3, // quarter 
NOTE_B3, // quarter 
NOTE_E3, // quarter 
NOTE_C4, // quarter

// ==== MEASURE 2 ====
NOTE_E3,   // quarter
NOTE_CS4,   // quarter
NOTE_E3,   // quarter
NOTE_C4,   // quarter

// MEASURE 3
NOTE_E3,   // quarter
NOTE_B3,   // quarter
NOTE_E3,   // quarter
NOTE_C4,   // quarter

// MEASURE 4
NOTE_E3,   // quarter
NOTE_CS4,   // quarter
NOTE_E3,   // quarter
NOTE_C4,   // quarter

 // MEASURE 5
NOTE_G5,   // eighth
NOTE_E5,   // eighth
NOTE_G5,   // quarter
NOTE_FS5,   // quarter

 // MEASURE 6
NOTE_DS5,   //quarter //E FLAT
NOTE_E5,   // quarter
NOTE_D5,   //eighth
NOTE_D5,   // eighth
NOTE_D5,   // quarter

// MEASURE 7
NOTE_CS5,   // eighth 
NOTE_CS5,   // eighth
NOTE_CS5,   // quarter


// MEASURE 8
NOTE_C5,   // eighth 
NOTE_C5,   // eighth
NOTE_C5,   // quarter


// MEASURE 9
NOTE_B4,   // eighth 
NOTE_E5,   // eighth
NOTE_C5,   // eighth
NOTE_E5,   // eighth
NOTE_B4,    // quarter

// CLEFT measure 1
NOTE_E4,    //sixteenth
NOTE_D4,    //sixteenth
NOTE_C3,    //sixteenth
NOTE_B3,    //sixteenth
NOTE_AS3,   // half

// MEASURE 10
NOTE_G5,    //eighth 
NOTE_FS5,   // eighth
NOTE_G5,   // quarter
NOTE_FS5,    // quarter

// MEASURE 11
NOTE_C6,   // quarter 
NOTE_B5,   // quarter
NOTE_G5,   // eighth
NOTE_G5,   // eighth
NOTE_G5,   // quarter 
   
// MEASURE 12
NOTE_FS5,   // eighth 
NOTE_FS5,   // eighth
NOTE_FS5,   // quarter

// MEASURE 13
NOTE_E5,   // eighth 
NOTE_E5,   // eighth
NOTE_E5,   // quarter

// MEASURE 14
NOTE_DS5,   // eighth
NOTE_FS5,   // eighth
NOTE_E5,    // eighth
NOTE_FS5,   // eighth
NOTE_DS5,   // quarter 

//MEASURE 15
NOTE_G5,    // eighth
NOTE_E5,    // eighth
NOTE_G5,    // quarter 
NOTE_FS5,   // quarter 

// MEASURE 16
NOTE_DS5,   // quarter 
NOTE_E5,    // quarter 
NOTE_D5,    // eighth
NOTE_D5,    // eighth
NOTE_D5,    // quarter

//  MEASURE 17
NOTE_CS5,   // eighth
NOTE_CS5,   // eighth
NOTE_CS5,   // quarter

//  MEASURE 18
NOTE_C5,   // eighth
NOTE_C5,   // eighth
NOTE_C5,   // quarter

// MEASURE 19
NOTE_B4,   // eighth
NOTE_E5,   // eighth
NOTE_C5,    // eighth
NOTE_E5,   // eighth
NOTE_B4,    //quarter

// CLEFT MEASURE 2
NOTE_G3,    //sixteenth
NOTE_FS3,   //sixteenth
NOTE_E3,    //sixteenth
NOTE_D3,    //sixteenth
NOTE_CS3,   //half

// MEASURE 20
NOTE_E5,    //eightH
NOTE_CS5,   //eighth
NOTE_E5,      //quarter
NOTE_DS5,    //quarter

//MEASURE 21
NOTE_D5,    //eighth
NOTE_B4,    //eighth
NOTE_D5,    //quarter
NOTE_CS5,   //quarter

//MEASURE22
NOTE_C5,    //eighth
NOTE_A4,    //eighth
NOTE_C5,    //quarter
NOTE_B4,    //quarter

// MEASURE 23
NOTE_B5,    //quarter
NOTE_E6,    //quarter
};

uint16_t melody_dur_ms[] = { // ==== MEASURE 1 ==== QUARTER_MS, QUARTER_MS, QUARTER_MS, QUARTER_MS,

// ==== MEASURE 2 ====
QUARTER_MS,
QUARTER_MS,
QUARTER_MS,
QUARTER_MS,

// ==== MEASURE 3 ====
QUARTER_MS,
QUARTER_MS,
QUARTER_MS,
QUARTER_MS,

// ==== MEASURE 4 ====
QUARTER_MS,
QUARTER_MS,
QUARTER_MS,
QUARTER_MS,

// ==== MEASURE 5 ====
EIGHTH_MS,
EIGHTH_MS,
QUARTER_MS,
QUARTER_MS,

// ==== MEASURE 6 ====
QUARTER_MS,
QUARTER_MS,
EIGHTH_MS,
EIGHTH_MS,
QUARTER_MS,

// ==== MEASURE 7 ====
EIGHTH_MS,
EIGHTH_MS,
QUARTER_MS,

// ==== MEASURE 8 ====
EIGHTH_MS,
EIGHTH_MS,
QUARTER_MS,

// ==== MEASURE 9 ====
EIGHTH_MS,
EIGHTH_MS,
EIGHTH_MS,
EIGHTH_MS,
QUARTER_MS,


// cleft measure 1
SIXTEENTH_MS,
SIXTEENTH_MS,
SIXTEENTH_MS,
SIXTEENTH_MS,
HALF_MS,


// ==== MEASURE 10 ====
EIGHTH_MS,
EIGHTH_MS,
QUARTER_MS,
QUARTER_MS,

// ==== MEASURE 11 ====
QUARTER_MS,
QUARTER_MS,
EIGHTH_MS,
EIGHTH_MS,
QUARTER_MS,

// ==== MEASURE 12 ====
EIGHTH_MS,
EIGHTH_MS,
QUARTER_MS,

// ==== MEASURE 13 ====
EIGHTH_MS,
EIGHTH_MS,
QUARTER_MS,

// ==== MEASURE 14 ====
EIGHTH_MS,
EIGHTH_MS,
EIGHTH_MS,
EIGHTH_MS,
QUARTER_MS,

// ==== MEASURE 15 ====
EIGHTH_MS,
EIGHTH_MS,
QUARTER_MS,
QUARTER_MS,

// ==== MEASURE 16 ====
QUARTER_MS,
QUARTER_MS,
EIGHTH_MS,
EIGHTH_MS,
QUARTER_MS,

// ==== MEASURE 17 ====
EIGHTH_MS,
EIGHTH_MS,
QUARTER_MS,

// ==== MEASURE 18 ====
EIGHTH_MS,
EIGHTH_MS,
QUARTER_MS,

// ==== MEASURE 19 ====
EIGHTH_MS,
EIGHTH_MS,
EIGHTH_MS,
EIGHTH_MS,
QUARTER_MS,

// CLEFT MEASURE 2
SIXTEENTH_MS,
SIXTEENTH_MS,
SIXTEENTH_MS,
SIXTEENTH_MS,
HALF_MS,

// ==== MEASURE 20 ====
EIGHTH_MS,
EIGHTH_MS,
QUARTER_MS,
QUARTER_MS,

// ==== MEASURE 21 ====
EIGHTH_MS,
EIGHTH_MS,
QUARTER_MS,
QUARTER_MS,

// ==== MEASURE 22 ====
EIGHTH_MS,
EIGHTH_MS,
QUARTER_MS,
QUARTER_MS,

// ==== MEASURE 23 ====
QUARTER_MS,
QUARTER_MS,
};

#define MELODY_LENGTH (sizeof(melody_freq) / sizeof(melody_freq[0]))

// delay
void delay_ms(uint32_t ms) { 
    for (uint32_t i = 0; i < ms * 4000; i++) 
        { __NOP(); } 
        }

// timer config 
static Timer_ClockConfig TimerA1ClockConfig = { .clockSel = GPTIMER_CLKSEL_BUSCLK_SEL_ENABLE, .divideRatio = GPTIMER_CLKDIV_RATIO_DIV_BY_4, .prescale = 0 };

static Timer_TimerConfig TimerA1TimerConfig = { .period = 1000, .timerMode = (GPTIMER_CTRCTL_CM_DOWN | GPTIMER_CTRCTL_REPEAT_REPEAT_1) };

static Timer_PWMConfig TimerA1PWMConfig = { .index = PB4INDEX, .iomuxMode = (IOMUX_PINCM_PC_CONNECTED | IOMUX_MODE4), .ccr = 0, .ccpd = GPTIMER_CCPD_C0CCP0_OUTPUT, .ccctl = GPTIMER_CCCTL_01_COC_COMPARE, .octl = GPTIMER_OCTL_01_CCPO_FUNCVAL, .ccact = (GPTIMER_CCACT_01_CDACT_CCP_LOW | GPTIMER_CCACT_01_LACT_CCP_HIGH), .duty = 500 };

int main(void) { InitializeBoosterpack(PROJECT_CLOCK_FREQUENCY); // for S1/S2 InitializeTimerClock(TIMERA1_AS_GPT, &TimerA1ClockConfig); InitializeTimerPWM(TIMERA1_AS_GPT, &TimerA1PWMConfig);

const uint32_t bus_div = 4u;
const uint32_t tick_hz = PROJECT_CLOCK_FREQUENCY / bus_div;

bool playing = false;        // start with song NOT playing
uint8_t S1_Pressed = FALSE;  // edge-detect flags
uint8_t S2_Pressed = FALSE;

uint32_t note_index = 0;     // which note we are on
uint32_t remaining_ms = 0;   // time left on current note
uint32_t current_period = 0; // last used period (for resume)

while (1)
{
    // Switch 1, Pause 
    if (BP_ReadS1()) {
        S1_Pressed = TRUE;
    }
    if (!BP_ReadS1() && S1_Pressed) {
        S1_Pressed = FALSE;

        if (playing) {
            // pause: freeze song and mute buzzer
            playing = false;
            TimerA1PWMConfig.duty = 0;
            UpdateDutyCycle(TIMERA1_AS_GPT, &TimerA1PWMConfig);
        }
        // if already paused, S1 does nothing
    }

    //Switch 2 resume or start 
    if (BP_ReadS2()) {
        S2_Pressed = TRUE;
    }
    if (!BP_ReadS2() && S2_Pressed) {
        S2_Pressed = FALSE;

        // S2 always means "play" (start or resume)
        playing = true;

        // If we already finished the whole song, restart from beginning
        if (note_index >= MELODY_LENGTH) {
            note_index = 0;
            remaining_ms = 0;
        }

        // If we were paused in the middle of a note, just restore duty
        if (remaining_ms > 0 && current_period > 0) {
            TimerA1PWMConfig.duty = current_period >> 1;
            UpdateDutyCycle(TIMERA1_AS_GPT, &TimerA1PWMConfig);
            EnableTimer(TIMERA1_AS_GPT);
        }
    }

    // playback 
    if (playing) {
        // Need to (re)start a note?
        if (remaining_ms == 0 && note_index < MELODY_LENGTH) {
            uint32_t freq = melody_freq[note_index];
            uint32_t dur  = melody_dur_ms[note_index];

            uint32_t period = tick_hz / freq;
            if (period < 2) period = 2;
            current_period = period;   // remember for resume

            // Configure timer for this note
            TimerA1TimerConfig.period = period;
            InitializeTimerCompare(TIMERA1_AS_GPT, &TimerA1TimerConfig);

            TimerA1PWMConfig.duty = period >> 1;  // 50% duty
            UpdateDutyCycle(TIMERA1_AS_GPT, &TimerA1PWMConfig);
            EnableTimer(TIMERA1_AS_GPT);

            remaining_ms = dur;
        }

        if (remaining_ms > 0) {
            delay_ms(1);
            remaining_ms--;

            // Finished this note?
            if (remaining_ms == 0) {
                note_index++;

                // Finished the whole song → stop and mute
                if (note_index >= MELODY_LENGTH) {
                    playing = false;
                    TimerA1PWMConfig.duty = 0;
                    UpdateDutyCycle(TIMERA1_AS_GPT, &TimerA1PWMConfig);
                }
            }
        }
    } else {
        // paused or not started: just idle but still poll buttons
        delay_ms(1);
    }
}
// add led configuration 
}
