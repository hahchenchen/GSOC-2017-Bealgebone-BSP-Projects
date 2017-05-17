/**
 * @file
 * @ingroup stm32f4_io
 * @brief IO support.
 */

/*
 * Copyright (c) 2012 Sebastian Huber.  All rights reserved.
 *
 *  embedded brains GmbH
 *  Obere Lagerstr. 30
 *  82178 Puchheim
 *  Germany
 *  <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#ifndef LIBBSP_ARM_STM32F4_IO_H
#define LIBBSP_ARM_STM32F4_IO_H

#include <stdbool.h>
#include <stdint.h>
#include <bspopts.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup stm32f4_io IO Support
 * @ingroup arm_stm32f4
 * @brief IO Support
 * @{
 */

#define STM32F4_GPIO_PIN(port, index) ((((port) << 4) | (index)) & 0xff)

#define STM32F4_GPIO_PORT_OF_PIN(pin) (((pin) >> 4) & 0xf)

#define STM32F4_GPIO_INDEX_OF_PIN(pin) ((pin) & 0xf)

#ifdef STM32F4_FAMILY_F4XXXX

/**
 * @name Family F4XXXX
 * @{
 */

typedef enum {
  STM32F4_GPIO_MODE_INPUT,
  STM32F4_GPIO_MODE_OUTPUT,
  STM32F4_GPIO_MODE_AF,
  STM32F4_GPIO_MODE_ANALOG
} stm32f4_gpio_mode;

typedef enum {
  STM32F4_GPIO_OTYPE_PUSH_PULL,
  STM32F4_GPIO_OTYPE_OPEN_DRAIN
} stm32f4_gpio_otype;

typedef enum {
  STM32F4_GPIO_OSPEED_2_MHZ,
  STM32F4_GPIO_OSPEED_25_MHZ,
  STM32F4_GPIO_OSPEED_50_MHZ,
  STM32F4_GPIO_OSPEED_100_MHZ
} stm32f4_gpio_ospeed;

typedef enum {
  STM32F4_GPIO_NO_PULL,
  STM32F4_GPIO_PULL_UP,
  STM32F4_GPIO_PULL_DOWN
} stm32f4_gpio_pull;

typedef enum {
  STM32F4_GPIO_AF_SYSTEM = 0,
  STM32F4_GPIO_AF_TIM1 = 1,
  STM32F4_GPIO_AF_TIM2 = 1,
  STM32F4_GPIO_AF_TIM3 = 2,
  STM32F4_GPIO_AF_TIM4 = 2,
  STM32F4_GPIO_AF_TIM5 = 2,
  STM32F4_GPIO_AF_TIM8 = 3,
  STM32F4_GPIO_AF_TIM9 = 3,
  STM32F4_GPIO_AF_TIM10 = 3,
  STM32F4_GPIO_AF_TIM11 = 3,
  STM32F4_GPIO_AF_I2C1 = 4,
  STM32F4_GPIO_AF_I2C2 = 4,
  STM32F4_GPIO_AF_I2C3 = 4,
  STM32F4_GPIO_AF_SPI1 = 5,
  STM32F4_GPIO_AF_SPI2 = 5,
  STM32F4_GPIO_AF_SPI3 = 6,
  STM32F4_GPIO_AF_USART1 = 7,
  STM32F4_GPIO_AF_USART2 = 7,
  STM32F4_GPIO_AF_USART3 = 7,
  STM32F4_GPIO_AF_UART4 = 8,
  STM32F4_GPIO_AF_UART5 = 8,
  STM32F4_GPIO_AF_USART6 = 8,
  STM32F4_GPIO_AF_CAN1 = 9,
  STM32F4_GPIO_AF_CAN2 = 9,
  STM32F4_GPIO_AF_TIM12 = 9,
  STM32F4_GPIO_AF_TIM13 = 9,
  STM32F4_GPIO_AF_TIM14 = 9,
  STM32F4_GPIO_AF_OTG_FS = 10,
  STM32F4_GPIO_AF_OTG_HS = 10,
  STM32F4_GPIO_AF_ETH = 11,
  STM32F4_GPIO_AF_FSMC = 12,
  STM32F4_GPIO_AF_OTG_HS_FS = 12,
  STM32F4_GPIO_AF_SDIO = 12,
  STM32F4_GPIO_AF_DCMI = 13,
  STM32F4_GPIO_AF_EVENTOUT = 15
} stm32f4_gpio_af;

typedef union {
  struct {
    uint32_t pin_first : 8;
    uint32_t pin_last : 8;
    uint32_t mode : 2;
    uint32_t otype : 1;
    uint32_t ospeed : 2;
    uint32_t pupd : 2;
    uint32_t output : 1;
    uint32_t af : 4;
    uint32_t reserved : 4;
  } fields;

  uint32_t value;
} stm32f4_gpio_config;

#define STM32F4_GPIO_CONFIG_TERMINAL \
  { { 0xff, 0xff, 0x3, 0x1, 0x3, 0x3, 0x1, 0xf, 0xf } }

/** @} */

#endif /* STM32F4_FAMILY_F4XXXX */
#ifdef STM32F4_FAMILY_F10XXX

/**
 * @name Family F10XXX
 * @{
 */

typedef enum {
  STM32F4_GPIO_MODE_INPUT,
  STM32F4_GPIO_MODE_OUTPUT_10MHz,
  STM32F4_GPIO_MODE_OUTPUT_2MHz,
  STM32F4_GPIO_MODE_OUTPUT_50MHz
} stm32f4_gpio_mode;

typedef enum {
  STM32F4_GPIO_CNF_IN_ANALOG = 0,
  STM32F4_GPIO_CNF_IN_FLOATING = 1,
  STM32F4_GPIO_CNF_IN_PULL_UPDOWN = 2,

  STM32F4_GPIO_CNF_OUT_GPIO_PP = 0,
  STM32F4_GPIO_CNF_OUT_GPIO_OD = 1,
  STM32F4_GPIO_CNF_OUT_AF_PP = 2,
  STM32F4_GPIO_CNF_OUT_AF_OD = 3,
} stm32f4_gpio_cnf;

typedef enum {
  STM32F4_GPIO_REMAP_DONT_CHANGE,
  STM32F4_GPIO_REMAP_SPI1_0,
  STM32F4_GPIO_REMAP_SPI1_1,
  STM32F4_GPIO_REMAP_I2C1_0,
  STM32F4_GPIO_REMAP_I2C1_1,
  STM32F4_GPIO_REMAP_USART1_0,
  STM32F4_GPIO_REMAP_USART1_1,
  STM32F4_GPIO_REMAP_USART2_0,
  STM32F4_GPIO_REMAP_USART2_1,
  STM32F4_GPIO_REMAP_USART3_0,
  STM32F4_GPIO_REMAP_USART3_1,
  STM32F4_GPIO_REMAP_USART3_3,
  STM32F4_GPIO_REMAP_TIM1_0,
  STM32F4_GPIO_REMAP_TIM1_1,
  STM32F4_GPIO_REMAP_TIM1_3,
  STM32F4_GPIO_REMAP_TIM2_0,
  STM32F4_GPIO_REMAP_TIM2_1,
  STM32F4_GPIO_REMAP_TIM2_2,
  STM32F4_GPIO_REMAP_TIM2_3,
  STM32F4_GPIO_REMAP_TIM3_0,
  STM32F4_GPIO_REMAP_TIM3_2,
  STM32F4_GPIO_REMAP_TIM3_3,
  STM32F4_GPIO_REMAP_TIM4_0,
  STM32F4_GPIO_REMAP_TIM4_1,
  STM32F4_GPIO_REMAP_CAN1_0,
  STM32F4_GPIO_REMAP_CAN1_2,
  STM32F4_GPIO_REMAP_CAN1_3,
  STM32F4_GPIO_REMAP_PD01_0,
  STM32F4_GPIO_REMAP_PD01_1,
  STM32F4_GPIO_REMAP_TIM5CH4_0,
  STM32F4_GPIO_REMAP_TIM5CH4_1,
  STM32F4_GPIO_REMAP_ADC1_ETRGINJ_0,
  STM32F4_GPIO_REMAP_ADC1_ETRGINJ_1,
  STM32F4_GPIO_REMAP_ADC1_ETRGREG_0,
  STM32F4_GPIO_REMAP_ADC1_ETRGREG_1,
  STM32F4_GPIO_REMAP_ADC2_ETRGINJ_0,
  STM32F4_GPIO_REMAP_ADC2_ETRGINJ_1,
  STM32F4_GPIO_REMAP_ADC2_ETRGREG_0,
  STM32F4_GPIO_REMAP_ADC2_ETRGREG_1,
  STM32F4_GPIO_REMAP_ETH_0,
  STM32F4_GPIO_REMAP_ETH_1,
  STM32F4_GPIO_REMAP_CAN2_0,
  STM32F4_GPIO_REMAP_CAN2_1,
  STM32F4_GPIO_REMAP_MII_RMII_0,
  STM32F4_GPIO_REMAP_MII_RMII_1,
  STM32F4_GPIO_REMAP_SWJ_0,
  STM32F4_GPIO_REMAP_SWJ_1,
  STM32F4_GPIO_REMAP_SWJ_2,
  STM32F4_GPIO_REMAP_SWJ_4,
  STM32F4_GPIO_REMAP_SPI3_0,
  STM32F4_GPIO_REMAP_SPI3_1,
  STM32F4_GPIO_REMAP_TIM2ITR1_0,
  STM32F4_GPIO_REMAP_TIM2ITR1_1,
  STM32F4_GPIO_REMAP_PTP_PPS_0,
  STM32F4_GPIO_REMAP_PTP_PPS_1,
  STM32F4_GPIO_REMAP_TIM15_0,
  STM32F4_GPIO_REMAP_TIM15_1,
  STM32F4_GPIO_REMAP_TIM16_0,
  STM32F4_GPIO_REMAP_TIM16_1,
  STM32F4_GPIO_REMAP_TIM17_0,
  STM32F4_GPIO_REMAP_TIM17_1,
  STM32F4_GPIO_REMAP_CEC_0,
  STM32F4_GPIO_REMAP_CEC_1,
  STM32F4_GPIO_REMAP_TIM1_DMA_0,
  STM32F4_GPIO_REMAP_TIM1_DMA_1,
  STM32F4_GPIO_REMAP_TIM9_0,
  STM32F4_GPIO_REMAP_TIM9_1,
  STM32F4_GPIO_REMAP_TIM10_0,
  STM32F4_GPIO_REMAP_TIM10_1,
  STM32F4_GPIO_REMAP_TIM11_0,
  STM32F4_GPIO_REMAP_TIM11_1,
  STM32F4_GPIO_REMAP_TIM13_0,
  STM32F4_GPIO_REMAP_TIM13_1,
  STM32F4_GPIO_REMAP_TIM14_0,
  STM32F4_GPIO_REMAP_TIM14_1,
  STM32F4_GPIO_REMAP_FSMC_0,
  STM32F4_GPIO_REMAP_FSMC_1,
  STM32F4_GPIO_REMAP_TIM67_DAC_DMA_0,
  STM32F4_GPIO_REMAP_TIM67_DAC_DMA_1,
  STM32F4_GPIO_REMAP_TIM12_0,
  STM32F4_GPIO_REMAP_TIM12_1,
  STM32F4_GPIO_REMAP_MISC_0,
  STM32F4_GPIO_REMAP_MISC_1,
} stm32f4_gpio_remap;

typedef union {
  struct {
    uint32_t pin_first : 8;
    uint32_t pin_last : 8;
    uint32_t mode : 2;
    uint32_t cnf : 2;
    uint32_t output : 1;
    uint32_t remap : 8;
    uint32_t reserved : 3;
  } fields;

  uint32_t value;
} stm32f4_gpio_config;

#define STM32F4_GPIO_CONFIG_TERMINAL \
  { { 0xff, 0xff, 0x3, 0x3, 0x1, 0xff, 0x7 } }

/** @} */

#endif /* STM32F4_FAMILY_F10XXX */

extern const stm32f4_gpio_config stm32f4_start_config_gpio [];

void stm32f4_gpio_set_clock(int pin, bool set);

void stm32f4_gpio_set_config(const stm32f4_gpio_config *config);

/**
 * @brief Sets the GPIO configuration of an array terminated by
 * STM32F4_GPIO_CONFIG_TERMINAL.
 */
void stm32f4_gpio_set_config_array(const stm32f4_gpio_config *configs);

void stm32f4_gpio_set_output(int pin, bool set);

bool stm32f4_gpio_get_input(int pin);

#ifdef STM32F4_FAMILY_F4XXXX

/**
 * @name Family F4XXXX
 * @{
 */

#define STM32F4_PIN_USART(port, idx, altfunc) \
  { \
    { \
      .pin_first = STM32F4_GPIO_PIN(port, idx), \
      .pin_last = STM32F4_GPIO_PIN(port, idx), \
      .mode = STM32F4_GPIO_MODE_AF, \
      .otype = STM32F4_GPIO_OTYPE_PUSH_PULL, \
      .ospeed = STM32F4_GPIO_OSPEED_2_MHZ, \
      .pupd = STM32F4_GPIO_PULL_UP, \
      .af = altfunc \
    } \
  }

#define STM32F4_PIN_USART1_TX_PA9 STM32F4_PIN_USART(0, 9, STM32F4_GPIO_AF_USART1)
#define STM32F4_PIN_USART1_TX_PB6 STM32F4_PIN_USART(1, 6, STM32F4_GPIO_AF_USART1)
#define STM32F4_PIN_USART1_RX_PA10 STM32F4_PIN_USART(0, 10, STM32F4_GPIO_AF_USART1)
#define STM32F4_PIN_USART1_RX_PB7 STM32F4_PIN_USART(1, 7, STM32F4_GPIO_AF_USART1)

#define STM32F4_PIN_USART2_TX_PA2 STM32F4_PIN_USART(0, 2, STM32F4_GPIO_AF_USART2)
#define STM32F4_PIN_USART2_TX_PD5 STM32F4_PIN_USART(3, 5, STM32F4_GPIO_AF_USART2)
#define STM32F4_PIN_USART2_RX_PA3 STM32F4_PIN_USART(0, 3, STM32F4_GPIO_AF_USART2)
#define STM32F4_PIN_USART2_RX_PD6 STM32F4_PIN_USART(3, 6, STM32F4_GPIO_AF_USART2)

#define STM32F4_PIN_USART3_TX_PC10 STM32F4_PIN_USART(2, 10, STM32F4_GPIO_AF_USART3)
#define STM32F4_PIN_USART3_TX_PD8 STM32F4_PIN_USART(3, 8, STM32F4_GPIO_AF_USART3)
#define STM32F4_PIN_USART3_RX_PC11 STM32F4_PIN_USART(2, 11, STM32F4_GPIO_AF_USART3)
#define STM32F4_PIN_USART3_RX_PD9 STM32F4_PIN_USART(3, 9, STM32F4_GPIO_AF_USART3)

#define STM32F4_PIN_UART4_TX_PA0 STM32F4_PIN_USART(0, 0, STM32F4_GPIO_AF_UART4)
#define STM32F4_PIN_UART4_TX_PC10 STM32F4_PIN_USART(2, 10, STM32F4_GPIO_AF_UART4)
#define STM32F4_PIN_UART4_RX_PA1 STM32F4_PIN_USART(0, 1, STM32F4_GPIO_AF_UART4)
#define STM32F4_PIN_UART4_RX_PC11 STM32F4_PIN_USART(2, 11, STM32F4_GPIO_AF_UART4)

#define STM32F4_PIN_UART5_TX_PC12 STM32F4_PIN_USART(2, 12, STM32F4_GPIO_AF_UART5)
#define STM32F4_PIN_UART5_RX_PD2 STM32F4_PIN_USART(3, 2, STM32F4_GPIO_AF_UART5)

#define STM32F4_PIN_USART6_TX_PC6 STM32F4_PIN_USART(2, 6, STM32F4_GPIO_AF_USART6)
#define STM32F4_PIN_USART6_RX_PC7 STM32F4_PIN_USART(2, 7, STM32F4_GPIO_AF_USART6)

/** @} */

#endif /* STM32F4_FAMILY_F4XXXX */
#ifdef STM32F4_FAMILY_F10XXX

/**
 * @name Family F10XXX
 * @{
 */

#define STM32F4_PIN_USART_TX(port, idx, remapvalue) \
  { \
    { \
      .pin_first = STM32F4_GPIO_PIN(port, idx), \
      .pin_last = STM32F4_GPIO_PIN(port, idx), \
      .mode = STM32F4_GPIO_MODE_OUTPUT_2MHz, \
      .cnf = STM32F4_GPIO_CNF_OUT_AF_PP, \
      .output = 0, \
      .remap = remapvalue \
    } \
  }

#define STM32F4_PIN_USART_RX(port, idx, remapvalue) \
  { \
    { \
      .pin_first = STM32F4_GPIO_PIN(port, idx), \
      .pin_last = STM32F4_GPIO_PIN(port, idx), \
      .mode = STM32F4_GPIO_MODE_INPUT, \
      .cnf = STM32F4_GPIO_CNF_IN_FLOATING, \
      .output = 0, \
      .remap = remapvalue \
    } \
  }

#define STM32F4_PIN_USART1_TX_MAP_0 STM32F4_PIN_USART_TX(0,  9, STM32F4_GPIO_REMAP_USART1_0)
#define STM32F4_PIN_USART1_RX_MAP_0 STM32F4_PIN_USART_RX(0, 10, STM32F4_GPIO_REMAP_USART1_0)
#define STM32F4_PIN_USART1_TX_MAP_1 STM32F4_PIN_USART_TX(1,  6, STM32F4_GPIO_REMAP_USART1_1)
#define STM32F4_PIN_USART1_RX_MAP_1 STM32F4_PIN_USART_RX(1,  7, STM32F4_GPIO_REMAP_USART1_1)

#define STM32F4_PIN_USART2_TX_MAP_0 STM32F4_PIN_USART_TX(0,  2, STM32F4_GPIO_REMAP_USART2_0)
#define STM32F4_PIN_USART2_RX_MAP_0 STM32F4_PIN_USART_RX(0,  3, STM32F4_GPIO_REMAP_USART2_0)
#define STM32F4_PIN_USART2_TX_MAP_1 STM32F4_PIN_USART_TX(3,  5, STM32F4_GPIO_REMAP_USART2_1)
#define STM32F4_PIN_USART2_RX_MAP_1 STM32F4_PIN_USART_RX(3,  6, STM32F4_GPIO_REMAP_USART2_1)

#define STM32F4_PIN_USART3_TX_MAP_0 STM32F4_PIN_USART_TX(1, 10, STM32F4_GPIO_REMAP_USART3_0)
#define STM32F4_PIN_USART3_RX_MAP_0 STM32F4_PIN_USART_RX(1, 11, STM32F4_GPIO_REMAP_USART3_0)
#define STM32F4_PIN_USART3_TX_MAP_1 STM32F4_PIN_USART_TX(2, 10, STM32F4_GPIO_REMAP_USART3_1)
#define STM32F4_PIN_USART3_RX_MAP_1 STM32F4_PIN_USART_RX(2, 11, STM32F4_GPIO_REMAP_USART3_1)
#define STM32F4_PIN_USART3_TX_MAP_3 STM32F4_PIN_USART_TX(3,  8, STM32F4_GPIO_REMAP_USART3_3)
#define STM32F4_PIN_USART3_RX_MAP_3 STM32F4_PIN_USART_RX(3,  9, STM32F4_GPIO_REMAP_USART3_3)

#define STM32F4_PIN_UART4_TX        STM32F4_PIN_USART_TX(2, 10, STM32F4_GPIO_REMAP_DONT_CHANGE)
#define STM32F4_PIN_UART4_RX        STM32F4_PIN_USART_RX(2, 11, STM32F4_GPIO_REMAP_DONT_CHANGE)

#define STM32F4_PIN_UART5_TX        STM32F4_PIN_USART_TX(2, 12, STM32F4_GPIO_REMAP_DONT_CHANGE)
#define STM32F4_PIN_UART5_RX        STM32F4_PIN_USART_RX(3,  2, STM32F4_GPIO_REMAP_DONT_CHANGE)

#define STM32F4_PIN_I2C(port, idx, remapvalue) \
  { \
    { \
      .pin_first = STM32F4_GPIO_PIN(port, idx), \
      .pin_last = STM32F4_GPIO_PIN(port, idx), \
      .mode = STM32F4_GPIO_MODE_OUTPUT_2MHz, \
      .cnf = STM32F4_GPIO_CNF_OUT_AF_OD, \
      .output = 0, \
      .remap = remapvalue \
    } \
  }

#define STM32F4_PIN_I2C1_SCL_MAP0 STM32F4_PIN_I2C(1, 6, STM32F4_GPIO_REMAP_I2C1_0)
#define STM32F4_PIN_I2C1_SDA_MAP0 STM32F4_PIN_I2C(1, 7, STM32F4_GPIO_REMAP_I2C1_0)
#define STM32F4_PIN_I2C1_SCL_MAP1 STM32F4_PIN_I2C(1, 8, STM32F4_GPIO_REMAP_I2C1_1)
#define STM32F4_PIN_I2C1_SDA_MAP1 STM32F4_PIN_I2C(1, 9, STM32F4_GPIO_REMAP_I2C1_1)

#define STM32F4_PIN_I2C2_SCL      STM32F4_PIN_I2C(1, 10, STM32F4_GPIO_REMAP_DONT_CHANGE)
#define STM32F4_PIN_I2C2_SDA      STM32F4_PIN_I2C(1, 11, STM32F4_GPIO_REMAP_DONT_CHANGE)

/** @} */

#endif /* STM32F4_FAMILY_F10XXX */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBSP_ARM_STM32F4_IO_H */
