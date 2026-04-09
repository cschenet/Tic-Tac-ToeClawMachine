#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>
#include "stm32f0xx.h"


// Pulse length, 5 us to be safe. Could be lowered if need be
#define MOTOR_PULSE_US      5

// 1ms delay between stepping, raise or lower to slow down or speed up.
#define MOTOR_STEP_DELAY_US 1000

// -----------------------------------------------------------------------------
// Axis definitions
// -----------------------------------------------------------------------------
typedef enum {
    AXIS_X = 0,
    AXIS_Y = 1,
    AXIS_Z = 2,
    AXIS_CLAW = 3,
    AXIS_COUNT = 4
} axis_t;

typedef enum {
    DIR_FORWARD  = 0,
    DIR_BACKWARD = 1
} motor_dir_t;

// -----------------------------------------------------------------------------
// Per-axis pin descriptor
// -----------------------------------------------------------------------------
typedef struct {
    GPIO_TypeDef *step_port;
    uint8_t       step_pin;
    GPIO_TypeDef *dir_port;
    uint8_t       dir_pin;
} motor_pins_t;

// -----------------------------------------------------------------------------
// Public API
// -----------------------------------------------------------------------------

// Call once during hardware init, after GPIO clocks are enabled
void Motor_Init(void);

// Enable / disable all drivers via shared EN pin (active LOW on DRV8825)
void Motor_Enable(void);
void Motor_Disable(void);

// Move a single axis a given number of steps in a given direction
void Motor_Step(axis_t axis, motor_dir_t dir, uint32_t steps);

// Convenience wrappers used by game.c / claw logic
void Motor_MoveX(motor_dir_t dir, uint32_t steps);
void Motor_MoveY(motor_dir_t dir, uint32_t steps);
void Motor_MoveZ(motor_dir_t dir, uint32_t steps);
void Motor_MoveClaw(motor_dir_t dir, uint32_t steps);
void Motor_MoveXZ(motor_dir_t dir, uint32_t steps);

#endif