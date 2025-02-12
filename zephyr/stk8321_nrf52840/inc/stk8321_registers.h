/**
 * @file stk8321_registers.h
 * @brief STK8321 register definitions
 * @date 2025-02-07
 */

#ifndef STK8321_REGISTERS_H
#define STK8321_REGISTERS_H

/* The register contains the chip identification code. */
#define REG_CHIP_ID 0x00
#define REG_CHIP_ID_VALUE 0x21

/* XOUT1/XOUT2 register contain the x-axis acceleration data and the new data flag for the x-axis. */
#define REG_DATA_X_LSB 0x02 // XOUT1
#define REG_DATA_X_MSB 0x03 // XOUT2

/* YOUT1/YOUT2 register contain the y-axis acceleration data and the new data flag for the y-axis. */
#define REG_DATA_Y_LSB 0x04 // YOUT1
#define REG_DATA_Y_MSB 0x05 // YOUT2

/* ZOUT1/ZOUT2 register contain the z-axis acceleration data and the new data flag for the z-axis. */
#define REG_DATA_Z_LSB 0x06 // ZOUT1
#define REG_DATA_Z_MSB 0x07 // ZOUT2

/* This register contains the motion interrupts status in STK8321. */
#define REG_MOT_INT_STS 0x09
/* Values for interrupts status*/
#define SIG_MOT_STS_BIT 0x00 // 1: Motion detected, 0: No motion detected
#define ANY_MOT_STS_BIT 0x02 // 1: Any motion detected, 0: No motion detected

/* This register contains the new data interrupt status in STK8321.*/
#define REG_DAT_INT_STS 0x0A
/* Values for interrupts status*/
#define FIFO_FULL_STS_BIT 0x10   // 1: FIFO full, 0: FIFO not full
#define FIFO_WTRMRK_STS_BIT 0x20 // 1: FIFO watermark reached, 0: FIFO watermark not reached
#define DATA_RDY_STS_BIT 0x40    // 1: New data ready, 0: No new data

/* ============*/

// still some regs here that I dont define yet
// propably not needed for now

/* ================*/

/* This register contains the acceleration sensing range. It is recommended that set the suspend mode before changing
the register RANGESEL(0x0F) to ensure correct output data*/
#define REG_RANGESEL 0x0F
#define RANGE_2G 0x03 // +-2G
#define RANGE_4G 0x05 // +-4G
#define RANGE_8G 0x08 // +-8G

/* This register contains the output data bandwidth selection. It is recommended that set the suspend mode before
changing the register BWSEL(0x10) to ensure correct output data. */
#define REG_BANDWIDTHSEL 0x10

#define BW_7_81_HZ 0x08
#define BW_15_63_HZ 0x09
#define BW_31_25_HZ 0x0A
#define BW_62_5_HZ 0x0B
#define BW_125_HZ 0x0C
#define BW_250_HZ 0x0D
#define BW_500_HZ 0x0E
#define BW_1000_HZ 0x0F

/* This register contains the power mode selection and the sleep time duration setting. It is recommended that set the
suspend mode before changing the register POWMODE(0x11) to ensure correct output data. */
#define REG_POWMODE 0x11 // Power mode register

#define POWMODE_ACTIVE 0x00                // Normal mode: Continuous data acquisition
#define POWMODE_LOW_PWR 0x40               // Low power mode: Alternates between wake-up and sleep
#define POWMODE_LOW_PWR_WAKE_ON_EVENT 0x00 // Low power mode: Wake-up on event
#define POWMODE_LOW_PWR_WAKE_ON_TIMER 0x20 // Low power mode: Wake-up on timer
#define POWMODE_SUSPEND 0x80               // Suspend mode: Entire analog and oscillator powered down

// Sleep duration settings (SLEEP_DUR[3:0] in REG_POWMODE)
#define POWMODE_SLEEP_0_5MS 0x00  // Sleep duration: 0.5ms
#define POWMODE_SLEEP_1MS 0x06    // Sleep duration: 1ms
#define POWMODE_SLEEP_2MS 0x07    // Sleep duration: 2ms
#define POWMODE_SLEEP_4MS 0x08    // Sleep duration: 4ms
#define POWMODE_SLEEP_6MS 0x09    // Sleep duration: 6ms
#define POWMODE_SLEEP_10MS 0x0A   // Sleep duration: 10ms
#define POWMODE_SLEEP_25MS 0x0B   // Sleep duration: 25ms
#define POWMODE_SLEEP_50MS 0x0C   // Sleep duration: 50ms
#define POWMODE_SLEEP_100MS 0x0D  // Sleep duration: 100ms
#define POWMODE_SLEEP_500MS 0x0E  // Sleep duration: 500ms
#define POWMODE_SLEEP_1000MS 0x0F // Sleep duration: 1000ms

/* This register is used to select if the output data is filtered or unfiltered and how the output data contained in the
register XOUT1/XOUT2, YOUT1/YOUT2, ZOUT1/ZOUT2 are updated. */
#define REG_DAT_SETUP 0x13
#define DAT_PROT_BIT 0x20 // 1: Data protected, 0: Data not protected
#define DAT_FILT_BIT 0x40 // 1: Data unfiltered, 0: Data filtered

/* This register contains the X, Y, Z slope interrupt enable bit. */
#define REG_INT_EN_1 0x16
#define SLP_EN_X_BIT 0x01 // 1: X slope interrupt enabled, 0: X slope interrupt disabled
#define SLP_EN_Y_BIT 0x02 // 1: Y slope interrupt enabled, 0: Y slope interrupt disabled
#define SLP_EN_Z_BIT 0x04 // 1: Z slope interrupt enabled, 0: Z slope interrupt disabled

/* This register contains new data, fifo full, fifo watermark interrupt enable bit. */
#define REG_INT_EN_2 0x17
#define DATA_RDY_EN_BIT 0x10    // 1: New data ready interrupt enabled, 0: New data ready interrupt disabled
#define FIFO_FULL_EN_BIT 0x20   // 1: FIFO full interrupt enabled, 0: FIFO full interrupt disabled
#define FIFO_WTRMRK_EN_BIT 0x40 // 1: FIFO watermark interrupt enabled, 0: FIFO watermark interrupt disabled

/*This register is used to map the related interrupt to the desired INT pin. */
#define REG_INT_MAP_1 0x19
#define SIG_MOT_2_INT1_BIT 0x01 // 1: Motion interrupt mapped to INT1, 0: Motion interrupt not mapped to INT1
#define ANY_MOT_2_INT1_BIT 0x04 // 1: Any motion interrupt mapped to INT1, 0: Any motion interrupt not mapped to INT1
#define ANY_MOT_2_INT2_BIT 0x20 // 1: Any motion interrupt mapped to INT2, 0: Any motion interrupt not mapped to INT2
#define SIG_MOT_2_INT2_BIT 0x80 // 1: Motion interrupt mapped to INT2, 0: Motion interrupt not mapped to INT2

/* This register is used to map the related interrupt to the desired INT pin. */
#define REG_INT_MAP_2 0x1A
#define DATA_2_INT1_BIT 0x01      // 1: Map new data interrupt to INT1, 0: Do not map new data interrupt to INT1
#define FIFO_WM_2_INT1_BIT 0x02   // 1: Map FIFO watermark interrupt to INT1, 0: Do not map FIFO watermark interrupt to INT1
#define FIFO_FULL_2_INT1_BIT 0x04 // 1: Map FIFO full interrupt to INT1, 0: Do not map FIFO full interrupt to INT1
#define FIFO_FULL_2_INT2_BIT 0x20 // 1: Map FIFO full interrupt to INT2, 0: Do not map FIFO full interrupt to INT2
#define FIFO_WM_2_INT2_BIT 0x40   // 1: Map FIFO watermark interrupt to INT2, 0: Do not map FIFO watermark interrupt to INT2
#define DATA_2_INT2_BIT 0x80      // 1: Map new data interrupt to INT2, 0: Do not map new data interrupt to INT2

/* This register is used to define the INT1 and INT2 pins output type and active level. Open-drain or Push-pull output
type and active high or active low can be selected. */
#define REG_INT_CFG_1 0x20
#define INT1_LV_BIT 0x01 // 1: INT1 active low, 0: INT1 active high
#define INT1_OD_BIT 0x02 // 1: INT1 open-drain, 0: INT1 push-pull
#define INT2_LV_BIT 0x04 // 1: INT2 active low, 0: INT2 active high
#define INT2_OD_BIT 0x08 // 1: INT2 open-drain, 0: INT2 push-pull

/* This register is used to reset latched interrupt pin and select the interrupt mode. */
#define REG_INT_CFG_2 0x21

/* This register is used to set the number of samples needed in slope detection. The actual number of samples will be
equal to SLP_DUR[1:0] + 1.*/
#define REG_SLOPE_DUR 0x27

/* This register is used to set the threshold value for the slope detection. The actual slope threshold will depend on
sensing range = SLP_THD[7:0] * (3.91/7.81/15.63) (mg) cor. to 2/4/8g. The default value of SLP_THD[7:0] is 0x14. */
#define REG_SLOPE_THD 0x28







/* This register is used to set the skip time for the significant motion. Holding the duration for skip, for which the motion is
checked for re-detection. 1 LSB=20 ms. Range is 0 to 10sec. The default value of SKIP_TIME[8:0] is 0x96 correspond
to 3 seconds. */
#define REG_SIG_MOT_1 0x29
/* This register contains MSB of SKIP_TIME[8:0] for the significant motion, and significant motion interrupt enable bit.*/
#define REG_SIG_MOT_2 0x2A
#define SIG_MOT_EN_BIT 0x02
/* This register is used to set the proof time for the significant motion. Holding the duration for proof, for which the motion
is re-checked after. 1 LSB=20 ms. Range is 0 to 2.5sec. The default value of PROOF_TIME[8:0] is 0x32 correspond to
1 seconds. */
#define REG_SIG_MOT_3 0x2B

/* This register is used to reset the setting to zero for the offset compensation. */
#define REG_OFST_RESET 0x36 // 1: Reset the offset compensation setting to zero

/* This register contains the offset compensation value for the x,y,z-axis data output. */
#define REG_OFST_X 0x38 // 8-BIT, 7.81mg per LSB
#define REG_OFST_Y 0x39 // 8-BIT, 7.81mg per LSB
#define REG_OFST_Z 0x3A // 8-BIT, 7.81mg per LSB

#endif // STK8321_REGISTERS_H