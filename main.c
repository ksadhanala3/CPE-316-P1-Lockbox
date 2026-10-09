/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include<LCD.h>
#include<stdio.h>
#include<keypad.h>
#include <string.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

	RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN); //Init Clock

	//Reset LCD pins
	GPIOC->MODER &= ~(GPIO_MODER_MODE2 | GPIO_MODER_MODE3 | GPIO_MODER_MODE4 | GPIO_MODER_MODE5 |
			  	  	  GPIO_MODER_MODE6 | GPIO_MODER_MODE7 | GPIO_MODER_MODE8 | GPIO_MODER_MODE9 |
					  GPIO_MODER_MODE10 | GPIO_MODER_MODE11 | GPIO_MODER_MODE12);
	//Set LCD Pins to output
	GPIOC->MODER |= (GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0 | GPIO_MODER_MODE4_0 | GPIO_MODER_MODE5_0 |
			  	  	  GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0 | GPIO_MODER_MODE8_0 | GPIO_MODER_MODE9_0 |
					  GPIO_MODER_MODE10_0 | GPIO_MODER_MODE11_0 | GPIO_MODER_MODE12_0);

	//Set Keypad column pins as outputs
	  GPIOA->MODER &= ~(GPIO_MODER_MODE4 | GPIO_MODER_MODE1 | GPIO_MODER_MODE0);
	  GPIOA->MODER |= (GPIO_MODER_MODE4_0 | GPIO_MODER_MODE1_0 | GPIO_MODER_MODE0_0);
	  GPIOA->OTYPER &= ~(GPIO_OTYPER_OT4 | GPIO_OTYPER_OT1 | GPIO_OTYPER_OT0); //Push-Pull
	  GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEED4 | GPIO_OSPEEDR_OSPEED1 | GPIO_OSPEEDR_OSPEED0);


	    //Setting PA8, PC0, PC1, PB0 as keypad input pins
	    GPIOA->MODER &= ~(GPIO_MODER_MODE8);
	    GPIOB->MODER &= ~(GPIO_MODER_MODE0);
	    GPIOC->MODER &= ~(GPIO_MODER_MODE1 | GPIO_MODER_MODE0);
	    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD8);
	    GPIOA->PUPDR |= (GPIO_PUPDR_PUPD8_1);
	    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD0);
	    GPIOB->PUPDR |= (GPIO_PUPDR_PUPD0_1);
	    GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD1 | GPIO_PUPDR_PUPD0);
	    GPIOC->PUPDR |= (GPIO_PUPDR_PUPD1_1 | GPIO_PUPDR_PUPD0_1);

	    //PA5 set up as onboard LED
	    GPIOA->MODER &= ~(GPIO_MODER_MODE5);
	    GPIOA->MODER |= (GPIO_MODER_MODE5_0);
	    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT5);
	    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD5);
	    GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED5);


	    LCD_init();
	    write_lcd_string("Locked");
	    write_lcd(0xC0, 0);
	    write_lcd_string("ENTER KEY: ");

	    char code_array[] = "1234";

	    void unlocked(){
	    	write_lcd(0x01, 0);
	    	write_lcd_string("Unlocked");
	    	write_lcd(0xC0, 0);
	    	write_lcd_string("Lock: # Reset: *");

	    	GPIOA->BRR = GPIO_PIN_5;
	    	int pressed_key = check_press(0);
			  while(pressed_key != 11 && pressed_key != 10){
				  pressed_key = check_press(0);
				  }
			  if (pressed_key == 10){
				write_lcd(0x01, 0);
				write_lcd_string("New Key: ");
				 while(pressed_key == 10){
					 pressed_key = check_press(0);
				 }
				for (int i = 0; i < 4;){
					int pressed_key = check_press(0);
					if (pressed_key >= 0){
						char buffer[50];
						snprintf(buffer, sizeof(buffer), "%d", pressed_key);
						write_lcd_string(buffer);
						code_array[i++] = *buffer;
						HAL_Delay(200);
					}
				}

			  }
	    }

	    void locked(){
	    	write_lcd(0x01, 0);
	    	write_lcd_string("Locked");
	    	write_lcd(0xC0, 0);
	    	write_lcd_string("ENTER KEY: ");

	    	GPIOA->ODR = GPIO_PIN_5;

	    	while(1){
				char input_array[] = "fuck";
				for (int i = 0; i < 4;){
					int pressed_key = check_press(0);
					if(pressed_key >= 0){
						char buffer[50];
						snprintf(buffer, sizeof(buffer), "%d", pressed_key);
						write_lcd_string(buffer);
						input_array[i++] = *buffer;
						HAL_Delay(200);
					}
				}


				if(strcmp(input_array, code_array) == 0){
					break;
				} else {
					write_lcd(0x01, 0);
					write_lcd_string("Locked");
					write_lcd(0xC0, 0);
					write_lcd_string("ENTER KEY: ");
				}
	    	}
	    }

  while (1)
  {
	  locked();
	  unlocked();

	  }

  }
  /* USER CODE END 3 */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
