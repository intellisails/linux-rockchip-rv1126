/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Rockchip CIF Driver
 *
 * Copyright (C) 2020 Rockchip Electronics Co., Ltd.
 */

#ifndef _RKCIF_HW_H
#define _RKCIF_HW_H

#include <linux/mutex.h>
#include <media/media-device.h>
#include <media/media-entity.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/videobuf2-v4l2.h>
#include <media/v4l2-mc.h>
#include <linux/rk-camera-module.h>
#include "regs.h"
#include "version.h"

#define RKCIF_DEV_MAX		2
#define RKCIF_HW_DRIVER_NAME	"rkcifhw"
#define RKCIF_MAX_BUS_CLK	8
#define RKCIF_MAX_RESET		15

#define write_cif_reg(base, addr, val) \
	writel(val, (addr) + (base))
#define read_cif_reg(base, addr) \
	readl((addr) + (base))
#define write_cif_reg_or(base, addr, val) \
	writel(readl((addr) + (base)) | (val), (addr) + (base))
#define write_cif_reg_and(base, addr, val) \
	writel(readl((addr) + (base)) & (val), (addr) + (base))

/*
 * add new chip id in tail in time order
 * by increasing to distinguish cif version
 */
enum rkcif_chip_id {
	CHIP_PX30_CIF,
	CHIP_RK3128_CIF,
	CHIP_RK3288_CIF,
	CHIP_RK3328_CIF,
	CHIP_RK3368_CIF,
	CHIP_RK1808_CIF,
	CHIP_RV1126_CIF,
	CHIP_RV1126_CIF_LITE,
	CHIP_RK3568_CIF,
};

struct rkcif_hw_match_data {
	int chip_id;
	const char * const *clks;
	const char * const *rsts;
	int clks_num;
	int rsts_num;
	const struct cif_reg *cif_regs;
};

/*
 * the detecting mode of cif reset timer
 * related with dts property:rockchip,cif-monitor
 */
enum rkcif_monitor_mode {
	RKCIF_MONITOR_MODE_IDLE = 0x0,
	RKCIF_MONITOR_MODE_CONTINUE,
	RKCIF_MONITOR_MODE_TRIGGER,
	RKCIF_MONITOR_MODE_HOTPLUG,
};

struct rkcif_hw_timer {
	struct timer_list	timer;
	spinlock_t		timer_lock;
	unsigned long		cycle_jif;
	/* unit: us */
	unsigned int		run_cnt;
	unsigned int		max_run_cnt;
	unsigned int		stop_index_of_run_cnt;
	unsigned int		monitor_cycle;
	unsigned int		err_ref_cnt;
	unsigned int		err_time_interval;
	unsigned int		is_reset_by_user;
	bool			is_running;
	bool			has_been_init;
	enum rkcif_monitor_mode	monitor_mode;
	enum rkmodule_reset_src	reset_src;
};

/*
 * struct rkcif_device - ISP platform device
 * @base_addr: base register address
 * @active_sensor: sensor in-use, set when streaming on
 * @stream: capture video device
 */
struct rkcif_hw {
	struct device			*dev;
	int				irq;
	void __iomem			*base_addr;
	void __iomem			*csi_base;
	struct regmap			*grf;
	struct clk			*clks[RKCIF_MAX_BUS_CLK];
	int				clk_size;
	bool				iommu_en;
	struct iommu_domain		*domain;
	struct reset_control		*cif_rst[RKCIF_MAX_RESET];
	int				chip_id;
	const struct cif_reg		*cif_regs;
	bool				can_be_reset;

	struct rkcif_device *cif_dev[RKCIF_DEV_MAX];
	int dev_num;

	atomic_t power_cnt;
	const struct rkcif_hw_match_data *match_data;
	struct mutex			dev_lock;
	struct rkcif_hw_timer		hw_timer;
	struct rkcif_reset_info		reset_info;
	spinlock_t			spin_lock;
	bool				reset_work_cancel;
};

void rkcif_hw_soft_reset(struct rkcif_hw *cif_hw, bool is_rst_iommu);
void rkcif_disable_sys_clk(struct rkcif_hw *cif_hw);
int rkcif_enable_sys_clk(struct rkcif_hw *cif_hw);

#endif
