/* Copyright 2020 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef METAL__DRIVERS__SIFIVE_UART0_H
#define METAL__DRIVERS__SIFIVE_UART0_H

{% include 'template_comment.h' %}

#include <metal/clock.h>
#include <metal/generated/uart.h>
#include <metal/machine/platform.h>
#include <stddef.h>

static const struct dt_uart_data {
	uintptr_t base_addr;
	struct metal_clock *clock;
} dt_uart_data[__METAL_DT_NUM_UARTS] = {
	{% for uart in uarts %}
	{
	    .base_addr = METAL_SIFIVE_SIMUART0_{{ uart.id }}_BASE_ADDR,

	    {% if defined(uart.clocks) %}
		    .clock = (struct metal_clock *) {{ metal_clock(uart.clocks[0].id) }},
	    {% else %}
		    .clock = NULL,
	    {% endif %}
	},
	{% endfor %}
};

#endif
