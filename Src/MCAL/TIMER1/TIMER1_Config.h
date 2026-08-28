/**
 * @file TIMER1_Config.h
 * @brief Timer1 
 *        Timer1 driver was developed by Team 4
 *        as part of the Timer1 assignment.
 * @author Team 4
 * @date 2026
 * @target ATmega32
 */
#ifndef TIMER1_CONFIG_H_
#define TIMER1_CONFIG_H_

/*
 * CPU Frequency = 8 MHz
 * Prescaler      = 64
 *
 * Timer Tick = 64 / 8000000
 *            = 8 microseconds
 *
 * Required Time = 1 millisecond
 *
 * Number Of Counts = 1000 / 8
 *                  = 125 Counts
 *
 * OCR1A = 125 - 1
 *       = 124
 */

#define TIMER1_COMPARE_MATCH_VALUE    124U

#endif /* TIMER1_CONFIG_H_ */