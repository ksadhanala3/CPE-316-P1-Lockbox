/*
 * LCD_funcs.c
 *
 *  Created on: Oct 7, 2025
 *      Author: sean1
 */
#include <LCD.h>
#include<stdio.h>
#include "main.h"

	void E_latch(){
		GPIOC->ODR |= E;
		HAL_Delay(10);
		GPIOC->BRR = E;
		HAL_Delay(10);
	}


	void LCD_Clear(){
		GPIOC->BRR = (RS | RW | DB0 | DB1 | DB2 | DB3 | DB4 | DB5 | DB6 | DB7);
	}

	void write_lcd(uint8_t letter, uint8_t mode){
		LCD_Clear();
		GPIOC->BRR = (RS | RW);
		//write_lcd char
		if(mode) {
			GPIOC->ODR |= RS;
		}
		GPIOC->ODR |= (letter << 5);
		HAL_Delay(11);
		E_latch();
	}

	void LCD_init(){ //Need to latch to E for each command, ask Prof
		//wake up
		write_lcd(0x30, 0);
		HAL_Delay(101);

		write_lcd(0x30, 0);
		HAL_Delay(11);

		write_lcd(0x30, 0);
		HAL_Delay(11);

		//Function Set
		write_lcd(0x38, 0);
		HAL_Delay(11);



		//Display on/off
		write_lcd(0x10, 0);
		HAL_Delay(11);

		//Entry Set Mode
		write_lcd(0x0C, 0);
		HAL_Delay(11);

		write_lcd(0x06, 0);
		HAL_Delay(11);

		write_lcd(0x80, 0);
		HAL_Delay(11);

		LCD_Clear();

	}




	void write_lcd_string(char *str){
		while (*str != '\0'){
			write_lcd((int)*str, 1);
			str++;
		}
	}


