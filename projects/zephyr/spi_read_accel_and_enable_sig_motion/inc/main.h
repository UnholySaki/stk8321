#ifndef MAIN_H
#define MAIN_H

#define DELAY_REG 10
#define DELAY_PARAM 50
#define DELAY_VALUES 100

/* Significant motion detection parameters */
#define SIG_MOT_INT_PIN SIG_MOT_2_INT1_BIT
#define SIG_MOT_SKIP_TIME 0x0A  // 100ms - def: 0x96 (3 seconds)
#define SIG_MOT_PROOF_TIME 0x32 // def: 0x32 (1 second)
#define SLOPE_DUR 0x00          // def: 0x00 (1 sample)
#define SLOPE_THD 0x14          // def: 0x14 (20mg)
#define INT_LATCH_MODE NON_LATCHED_0

#endif // MAIN_H