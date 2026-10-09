/*
 * A3_Header.h
 *
 *  Created on: Oct 7, 2025
 *      Author: sean1
 */
#include "main.h"
#include<stdio.h>

#ifndef SRC_A3_HEADER_H_
#define SRC_A3_HEADER_H_

#define RS       	 GPIO_PIN_2
#define RW       	 GPIO_PIN_3
#define E        	 GPIO_PIN_4
#define DB0          GPIO_PIN_5
#define DB1          GPIO_PIN_6
#define DB2          GPIO_PIN_7
#define DB3          GPIO_PIN_8
#define DB4          GPIO_PIN_9
#define DB5          GPIO_PIN_10
#define DB6          GPIO_PIN_11
#define DB7          GPIO_PIN_12

void E_latch();
void LCD_Clear();
void write_lcd(uint8_t letter, uint8_t mode);
void LCD_init();
void write_lcd_string(char *str);

#endif /* SRC_A3_HEADER_H_ */
