#include "main.h"
#include<stdio.h>
#include "string.h"

/* USER CODE BEGIN PD */
#define Slave_Addr 0x7C
/* USER CODE END PD */

I2C_HandleTypeDef hi2c1;
HCD_HandleTypeDef hhcd_USB_DRD_FS;

void SystemClock_Config(void);
static void SystemPower_Config(void);
static void MX_GPIO_Init(void);
static void MX_ICACHE_Init(void);
static void MX_USB_DRD_FS_HCD_Init(void);
static void MX_I2C1_Init(void);

/* USER CODE BEGIN PFP */
void lcd_Init(void);
void lcd_send_cmd(char data);
void lcd_send_data(char data);
void lcd_print_string(char *str);
void lcd_print_moving_word(char *str);
void lcd_set_cursor(int row, int col); // To put cursor at the entered position: row(0-1) and column(0-14)
void lcd_clear(void);
/* USER CODE END PFP */

int main(void)
{
  /* USER CODE BEGIN 1 */
	lcd_Init();
	lcd_print_moving_word("Hi Arjun");
  /* USER CODE END 1 */
  HAL_Init();
  SystemClock_Config();
  SystemPower_Config();

  MX_GPIO_Init();
  MX_ICACHE_Init();
  MX_USB_DRD_FS_HCD_Init();
  MX_I2C1_Init();

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE3) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_4;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

static void SystemPower_Config(void)
{
  if (HAL_PWREx_ConfigSupply(PWR_SMPS_SUPPLY) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_I2C1_Init(void)
{
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00000E14;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_ICACHE_Init(void)
{
  if (HAL_ICACHE_ConfigAssociativityMode(ICACHE_1WAY) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_ICACHE_Enable() != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ICACHE_Init 2 */

  /* USER CODE END ICACHE_Init 2 */

}

static void MX_USB_DRD_FS_HCD_Init(void)
{
  hhcd_USB_DRD_FS.Instance = USB_DRD_FS;
  hhcd_USB_DRD_FS.Init.dev_endpoints = 8;
  hhcd_USB_DRD_FS.Init.Host_channels = 8;
  hhcd_USB_DRD_FS.Init.speed = HCD_SPEED_FULL;
  hhcd_USB_DRD_FS.Init.phy_itface = HCD_PHY_EMBEDDED;
  hhcd_USB_DRD_FS.Init.Sof_enable = DISABLE;
  hhcd_USB_DRD_FS.Init.low_power_enable = DISABLE;
  hhcd_USB_DRD_FS.Init.vbus_sensing_enable = DISABLE;
  hhcd_USB_DRD_FS.Init.bulk_doublebuffer_enable = DISABLE;
  hhcd_USB_DRD_FS.Init.iso_singlebuffer_enable = DISABLE;
  if (HAL_HCD_Init(&hhcd_USB_DRD_FS) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_BUTTON_Pin */
  GPIO_InitStruct.Pin = USER_BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_BUTTON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_GREEN_Pin */
  GPIO_InitStruct.Pin = LED_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LED_GREEN_GPIO_Port, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */

void lcd_send_cmd(char data) {
	uint8_t cmd[2];
	/* LCD differentiates instruction commands and data by the RS bit, where when RS=0, its sending a command
	 * and when RS bit is 1, its sending data
	 * For sending commands, control byte set to 0x00
	 */
	cmd[0] &= 0x00; // Control byte
	cmd[1] &= 0x00; // Data byte
	cmd[1] |= data;
	HAL_I2C_Master_Transmit(&hi2c1, Slave_Addr, cmd, 2, 100);
}

void lcd_send_data(char data) {
	uint8_t cmd[2];
	cmd[0] &= 0x00;
	// For sending data, control byte set to 0x40
	cmd[0] |= 0x40;
	cmd[1] &= 0x00;
	cmd[1] |= data;
	HAL_I2C_Master_Transmit(&hi2c1, Slave_Addr, cmd, 2, 100);
}

void lcd_print_string(char *str) {
	while (*str)lcd_send_data(*str++); // loop iterates over each character in string, until it encounters null char
}

void lcd_print_moving_word(char *str) {
	int c = 0;
	lcd_set_cursor(1,15); // Sending cursor at end of column limit
	while(1) {
		char pos = *(str+c);
		lcd_send_data(pos); // Sending string, char by char
		HAL_Delay(200);
		lcd_send_cmd(0x18); // Shifts all display to left
		c++;
		if (c>=strlen(str)) {
			lcd_print_string("  ");
			c = 0;
		}
	}
}

void lcd_set_cursor(int row, int col) {
    switch(row) {
        case 1:
            col |= 0x80; // Sets cursor position to 1st row
            break;
        case 2:
            col |= 0xC0; // Sets cursor position to 2nd row
            break;
    }
    lcd_send_cmd(col); // Command for cursor position
}

void lcd_Init(void) {
	HAL_Delay(20);
	lcd_send_cmd(0x20); // Function Set
	HAL_Delay(1);
	lcd_send_cmd(0x0C); // Display ON/OFF
	HAL_Delay(1);
	lcd_send_cmd(0x01); // Display clear
	HAL_Delay(1);
	lcd_send_cmd(0x06); // Sets Entry mode, determining how cursor moves after writing the characters to the display
	HAL_Delay(1);
}

void lcd_clear(void) {
	lcd_send_cmd(0x01);
}

/* USER CODE END 4 */

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

void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif /* USE_FULL_ASSERT */
