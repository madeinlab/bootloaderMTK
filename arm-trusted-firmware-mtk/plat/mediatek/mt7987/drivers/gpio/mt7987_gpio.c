// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright (c) 2024, MediaTek Inc. All rights reserved.
 */

#include <assert.h>
#include <common/debug.h>
#include <drivers/delay_timer.h>
#include <drivers/gpio.h>
#include <lib/mmio.h>
#include <mt7987_gpio.h>
#include <platform_def.h>

/******************************************************************************
 *Macro Definition
 ******************************************************************************/
#define GPIO_MODE_BITS	      4
#define MAX_GPIO_MODE_PER_REG 8
#define MAX_GPIO_REG_BITS     32
#define DIR_BASE	      (GPIO_BASE + 0x000)
#define DOUT_BASE	      (GPIO_BASE + 0x100)
#define DIN_BASE	      (GPIO_BASE + 0x200)
#define MODE_BASE	      (GPIO_BASE + 0x300)
#define SET		      0x4
#define CLR		      0x8

static void mt_set_pinmux_mode_chip(uint32_t pin, int mode)
{
	uint32_t pos, bit, val;
	uint32_t mask = (1L << GPIO_MODE_BITS) - 1;

	assert(pin < MAX_GPIO_PIN);

	pos = pin / MAX_GPIO_MODE_PER_REG;
	mode &= mask;
	bit = pin % MAX_GPIO_MODE_PER_REG;

	val = mmio_read_32(MODE_BASE + 0x10U * pos);

	if (((val >> (GPIO_MODE_BITS * bit)) & mask) == mode)
		return;

	val &= ~(mask << (GPIO_MODE_BITS * bit));
	val |= (mode << (GPIO_MODE_BITS * bit));

	mmio_write_32(MODE_BASE + 0x10U * pos, val);
}

static int mt_get_pinmux_mode_chip(uint32_t pin)
{
	uint32_t pos, bit;
	uint32_t val;
	uint32_t mask = (1L << GPIO_MODE_BITS) - 1;

	assert(pin < MAX_GPIO_PIN);

	pos = pin / MAX_GPIO_MODE_PER_REG;
	bit = pin % MAX_GPIO_MODE_PER_REG;

	val = mmio_read_32(MODE_BASE + 0x10U * pos);
	val >>= (GPIO_MODE_BITS * bit);
	val &= mask;

	return val;
}

static void mt_set_gpio_dir_chip(uint32_t pin, int dir)
{
	uint32_t pos, bit;

	assert(pin < MAX_GPIO_PIN);
	assert(dir < MT_GPIO_DIR_MAX);

	pos = pin / MAX_GPIO_REG_BITS;
	bit = pin % MAX_GPIO_REG_BITS;

	if (dir == MT_GPIO_DIR_IN) {
		mmio_write_32(DIR_BASE + 0x10U * pos + CLR, 1U << bit);
	} else {
		mmio_write_32(DIR_BASE + 0x10U * pos + SET, 1U << bit);
	}
}

static int mt_get_gpio_dir_chip(uint32_t pin)
{
	uint32_t pos, bit;
	uint32_t reg;

	assert(pin < MAX_GPIO_PIN);

	pos = pin / MAX_GPIO_REG_BITS;
	bit = pin % MAX_GPIO_REG_BITS;

	reg = mmio_read_32(DIR_BASE + 0x10U * pos);
	return (((reg & (1U << bit)) != 0U) ? MT_GPIO_DIR_OUT : MT_GPIO_DIR_IN);
}

static void mt_set_gpio_out_chip(uint32_t pin, int output)
{
	uint32_t pos, bit;

	assert(pin < MAX_GPIO_PIN);
	assert(output < MT_GPIO_OUT_MAX);

	pos = pin / MAX_GPIO_REG_BITS;
	bit = pin % MAX_GPIO_REG_BITS;

	if (output == MT_GPIO_OUT_ZERO) {
		mmio_write_32(DOUT_BASE + 0x10U * pos + CLR, 1U << bit);
	} else {
		mmio_write_32(DOUT_BASE + 0x10U * pos + SET, 1U << bit);
	}
}

static int mt_get_gpio_in_chip(uint32_t pin)
{
	uint32_t pos, bit;
	uint32_t reg;

	assert(pin < MAX_GPIO_PIN);

	pos = pin / MAX_GPIO_REG_BITS;
	bit = pin % MAX_GPIO_REG_BITS;

	reg = mmio_read_32(DIN_BASE + 0x10U * pos);
	return (((reg & (1U << bit)) != 0U) ? 1 : 0);
}

static uintptr_t mt_gpio_find_reg_addr(uint32_t pin)
{
	uintptr_t reg_addr = 0U;
	struct mt_pin_info gpio_info;

	gpio_info = mt7987_pin_infos[pin];

	switch (gpio_info.base & 0x0f) {
	case 0:
		reg_addr = GPIO_BASE;
		break;
	case 1:
		reg_addr = IOCFG_RB_BASE;
		break;
	case 2:
		reg_addr = IOCFG_LB_BASE;
		break;
	case 3:
		reg_addr = IOCFG_RT1_BASE;
		break;
	case 4:
		reg_addr = IOCFG_RT2_BASE;
		break;
	case 5:
		reg_addr = IOCFG_TL_BASE;
		break;
	default:
		break;
	}

	return reg_addr;
}

static void mt_gpio_set_spec_pull_pupd(uint32_t pin, int enable, int select)
{
	uintptr_t reg1;
	uintptr_t reg2;
	struct mt_pin_info gpio_info;

	gpio_info = mt7987_pin_infos[pin];
	uint32_t bit = gpio_info.bit;

	reg1 = mt_gpio_find_reg_addr(pin) + gpio_info.offset;
	reg2 = reg1 + (gpio_info.base & 0xf0);
	if (enable == MT_GPIO_PULL_ENABLE) {
		mmio_write_32(reg2 + SET, (1U << bit));
		if (select == MT_GPIO_PULL_DOWN) {
			mmio_write_32(reg1 + SET, (1U << bit));
		} else {
			mmio_write_32(reg1 + CLR, (1U << bit));
		}
	} else {
		mmio_write_32(reg2 + CLR, (1U << bit));
		mmio_write_32((reg2 + 0x010U) + CLR, (1U << bit));
	}
}

static void mt_gpio_set_pull_pu_pd(uint32_t pin, int enable, int select)
{
	uintptr_t reg1;
	uintptr_t reg2;
	struct mt_pin_info gpio_info;

	gpio_info = mt7987_pin_infos[pin];
	uint32_t bit = gpio_info.bit;

	reg1 = mt_gpio_find_reg_addr(pin) + gpio_info.offset;
	reg2 = reg1 - (gpio_info.base & 0xf0);

	if (enable == MT_GPIO_PULL_ENABLE) {
		if (select == MT_GPIO_PULL_DOWN) {
			mmio_write_32(reg1 + CLR, (1U << bit));
			mmio_write_32(reg2 + SET, (1U << bit));
		} else {
			mmio_write_32(reg2 + CLR, (1U << bit));
			mmio_write_32(reg1 + SET, (1U << bit));
		}
	} else {
		mmio_write_32(reg1 + CLR, (1U << bit));
		mmio_write_32(reg2 + CLR, (1U << bit));
	}
}

static void mt_gpio_set_pull_chip(uint32_t pin, int enable, int select)
{
	struct mt_pin_info gpio_info;
	uint32_t idx = 0;
	uint32_t pin_info_cnt = 0;

	pin_info_cnt = sizeof(mt7987_pin_infos) / sizeof(struct mt_pin_info);

	for (idx = 0; idx < pin_info_cnt; ++idx) {
		if (mt7987_pin_infos[idx].id == pin) {
			gpio_info = mt7987_pin_infos[idx];
			break;
		}
	}

	if (idx == pin_info_cnt) {
		INFO("Fail to find gpio_info from table\n");
		return;
	}

	if (gpio_info.flag) {
		mt_gpio_set_spec_pull_pupd(idx, enable, select);
	} else {
		mt_gpio_set_pull_pu_pd(idx, enable, select);
	}
}

static int mt_gpio_get_spec_pull_pupd(uint32_t pin)
{
	uintptr_t reg1;
	uintptr_t reg2;
	uint32_t r0;
	uint32_t r1;

	struct mt_pin_info gpio_info;

	gpio_info = mt7987_pin_infos[pin];
	uint32_t bit = gpio_info.bit;

	reg1 = mt_gpio_find_reg_addr(pin) + gpio_info.offset;
	reg2 = reg1 + (gpio_info.base & 0xf0);

	r0 = (mmio_read_32(reg2) >> bit) & 1U;
	r1 = (mmio_read_32(reg2 + 0x010) >> bit) & 1U;
	if (r0 == 0U && r1 == 0U) {
		return MT_GPIO_PULL_NONE;
	} else {
		if (mmio_read_32(reg1) & (1U << bit)) {
			return MT_GPIO_PULL_DOWN;
		} else {
			return MT_GPIO_PULL_UP;
		}
	}
}

static int mt_gpio_get_pull_pu_pd(uint32_t pin)
{
	uintptr_t reg1;
	uintptr_t reg2;
	uint32_t pu;
	uint32_t pd;

	struct mt_pin_info gpio_info;

	gpio_info = mt7987_pin_infos[pin];
	uint32_t bit = gpio_info.bit;

	reg1 = mt_gpio_find_reg_addr(pin) + gpio_info.offset;
	reg2 = reg1 - (gpio_info.base & 0xf0);
	pu = (mmio_read_32(reg1) >> bit) & 1U;
	pd = (mmio_read_32(reg2) >> bit) & 1U;
	if (pu == 1U) {
		return MT_GPIO_PULL_UP;
	} else if (pd == 1U) {
		return MT_GPIO_PULL_DOWN;
	} else {
		return MT_GPIO_PULL_NONE;
	}
}

static int mt_gpio_get_pull_chip(uint32_t pin)
{
	struct mt_pin_info gpio_info;

	gpio_info = mt7987_pin_infos[pin];
	if (gpio_info.flag) {
		return mt_gpio_get_spec_pull_pupd(pin);
	} else {
		return mt_gpio_get_pull_pu_pd(pin);
	}
}

static void mt_set_gpio_pull_select_chip(uint32_t pin, int sel)
{
	assert(pin < MAX_GPIO_PIN);

	if (sel == MT_GPIO_PULL_NONE) {
		mt_gpio_set_pull_chip(pin, MT_GPIO_PULL_DISABLE,
				      MT_GPIO_PULL_DOWN);
	} else if (sel == MT_GPIO_PULL_UP) {
		mt_gpio_set_pull_chip(pin, MT_GPIO_PULL_ENABLE,
				      MT_GPIO_PULL_UP);
	} else if (sel == MT_GPIO_PULL_DOWN) {
		mt_gpio_set_pull_chip(pin, MT_GPIO_PULL_ENABLE,
				      MT_GPIO_PULL_DOWN);
	}
}

/* get pull-up or pull-down, regardless of resistor value */
static int mt_get_gpio_pull_select_chip(uint32_t pin)
{
	assert(pin < MAX_GPIO_PIN);

	return mt_gpio_get_pull_chip(pin);
}

void mt_set_gpio_dir(int gpio, int direction)
{
	mt_set_gpio_dir_chip((uint32_t)gpio, direction);
}

int mt_get_gpio_dir(int gpio)
{
	uint32_t pin;

	pin = (uint32_t)gpio;
	return mt_get_gpio_dir_chip(pin);
}

void mt_set_gpio_pull(int gpio, int pull)
{
	uint32_t pin;

	pin = (uint32_t)gpio;
	mt_set_gpio_pull_select_chip(pin, pull);
}

int mt_get_gpio_pull(int gpio)
{
	uint32_t pin;

	pin = (uint32_t)gpio;
	return mt_get_gpio_pull_select_chip(pin);
}

void mt_set_gpio_out(int gpio, int value)
{
	uint32_t pin;

	pin = (uint32_t)gpio;
	mt_set_gpio_out_chip(pin, value);
}

int mt_get_gpio_in(int gpio)
{
	uint32_t pin;

	pin = (uint32_t)gpio;
	return mt_get_gpio_in_chip(pin);
}

void mt_set_pinmux_mode(int gpio, int mode)
{
	mt_set_pinmux_mode_chip((uint32_t)gpio, mode);
}

int mt_get_pinmux_mode(int gpio)
{
	uint32_t pin;

	pin = (uint32_t)gpio;
	return mt_get_pinmux_mode_chip(pin);
}

const gpio_ops_t mtgpio_ops = {
	.get_mode = mt_get_pinmux_mode,
	.set_mode = mt_set_pinmux_mode,
	.get_direction = mt_get_gpio_dir,
	.set_direction = mt_set_gpio_dir,
	.get_value = mt_get_gpio_in,
	.set_value = mt_set_gpio_out,
	.set_pull = mt_set_gpio_pull,
	.get_pull = mt_get_gpio_pull,
};

void mtk_pin_init(void)
{
	gpio_init(&mtgpio_ops);
}

void mt7987_set_default_pinmux(void)
{
#ifdef ENABLE_JTAG
	/* ENABLE JTAG */
	mt_set_pinmux_mode(3, GPIO_MODE_01);
	mt_set_pinmux_mode(4, GPIO_MODE_01);
	mt_set_pinmux_mode(5, GPIO_MODE_01);
	mt_set_pinmux_mode(6, GPIO_MODE_01);
	mt_set_pinmux_mode(7, GPIO_MODE_01);
#else
	/* DISABLE JTAG */
	mt_set_pinmux_mode(3, GPIO_MODE_00);
	mt_set_pinmux_mode(4, GPIO_MODE_00);
	mt_set_pinmux_mode(5, GPIO_MODE_00);
	mt_set_pinmux_mode(6, GPIO_MODE_00);
	mt_set_pinmux_mode(7, GPIO_MODE_00);
#endif
}
