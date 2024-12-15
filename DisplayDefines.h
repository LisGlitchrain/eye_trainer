#ifndef EYE_TRAINER_DISPLAYDEFINES
#define EYE_TRAINER_DISPLAYDEFINES 0

#include <TM1637Display.h>

//SEG_A - Up
//SEG_B..SEG_F - Clockwise
//SEG_G - middle

#define NONE 0
#define A SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G
#define B SEG_F | SEG_C | SEG_D | SEG_E | SEG_G
#define C SEG_A | SEG_F | SEG_E | SEG_D
#define D SEG_B | SEG_C | SEG_D | SEG_E | SEG_G
#define E SEG_A | SEG_D | SEG_E | SEG_F | SEG_G
#define F SEG_A | SEG_F | SEG_G | SEG_E
#define G SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G
#define H SEG_F | SEG_C | SEG_E | SEG_G
#define I SEG_B | SEG_C
#define J SEG_B | SEG_C | SEG_D
#define K SEG_A
#define L SEG_F | SEG_E | SEG_D
#define M SEG_C | SEG_G | SEG_E
#define N SEG_C | SEG_G | SEG_E
#define O SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F
#define P SEG_A | SEG_B | SEG_G | SEG_F | SEG_E
#define Q SEG_A | SEG_B | SEG_C | SEG_G | SEG_F
#define R SEG_E | SEG_G
#define S SEG_A | SEG_F | SEG_G | SEG_C | SEG_D
#define T SEG_F | SEG_E | SEG_D | SEG_G
#define U SEG_C | SEG_D | SEG_E
#define V SEG_C | SEG_D | SEG_E | SEG_F | SEG_B
#define W SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G
#define X SEG_B | SEG_C | SEG_E | SEG_F | SEG_G
#define Y SEG_F | SEG_G | SEG_B | SEG_C
#define Z SEG_A | SEG_B | SEG_G | SEG_E | SEG_D

#define WORD(a, b, c, d) (const uint8_t[]) {a, b, c, d}

#define WORD_DONE         WORD( D, O, N, E )
#define WORD_RUN          WORD( R, U, N, NONE )
#define WORD_MODE         WORD( R, M, O, D )
#define WORD_TIME_SWITCH  WORD( T, I, M, E )
#define WORD_TIME_MODE    WORD( T, M, O, D )
#define WORD_BRIGHTNESS   WORD( B, R, G, H )
#define WORD_TEST         WORD( T, E, S, T )
#define WORD_             WORD( SEG_G, SEG_G, SEG_G, SEG_G )


#endif