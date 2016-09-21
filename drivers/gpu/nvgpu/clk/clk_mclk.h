/*
* Copyright (c) 2016, NVIDIA CORPORATION.  All rights reserved.
*
* This program is free software; you can redistribute it and/or modify it
* under the terms and conditions of the GNU General Public License,
* version 2, as published by the Free Software Foundation.
*
* This program is distributed in the hope it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
* more details.
*/

#ifndef _CLKMCLK_H_
#define _CLKMCLK_H_

#include <linux/mutex.h>

enum gk20a_mclk_speed {
	gk20a_mclk_low_speed,
	gk20a_mclk_mid_speed,
	gk20a_mclk_high_speed,
};

#define DEFAULT_BOOT_MCLK_SPEED gk20a_mclk_high_speed
#define MCLK_LOW_SPEED_LIMIT 405
#define MCLK_MID_SPEED_LIMIT 810
struct clk_mclk_state {
	enum gk20a_mclk_speed speed;
	struct mutex mclk_mutex;
	void *vreg_buf;
	bool init;

	/* function pointers */
	int (*change)(struct gk20a *g, enum gk20a_mclk_speed speed);

#ifdef CONFIG_DEBUG_FS
	s64 switch_max;
	s64 switch_min;
	u64 switch_num;
	s64 switch_avg;
	s64 switch_std;
	bool debugfs_set;
#endif
};

int clk_mclkseq_init_mclk_gddr5(struct gk20a *g);
int clk_mclkseq_change_mclk_gddr5(struct gk20a *g,
	enum gk20a_mclk_speed speed);

#endif
