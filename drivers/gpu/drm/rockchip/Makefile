# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the drm device driver.  This driver provides support for the
# Direct Rendering Infrastructure (DRI) in XFree86 4.1.0 and higher.

rockchipdrm-y := rockchip_drm_drv.o rockchip_drm_fb.o \
		rockchip_drm_gem.o

rockchipdrm-$(CONFIG_ROCKCHIP_PSR) += rockchip_drm_psr.o

rockchipdrm-$(CONFIG_ROCKCHIP_VOP) += rockchip_drm_vop.o rockchip_vop_reg.o

rockchipdrm-$(CONFIG_DRM_FBDEV_EMULATION) += rockchip_drm_fbdev.o

rockchipdrm-$(CONFIG_ROCKCHIP_ANALOGIX_DP) += analogix_dp-rockchip.o
rockchipdrm-$(CONFIG_ROCKCHIP_CDN_DP) += cdn-dp-core.o cdn-dp-reg.o \
					 cdn-dp-link-training.o
rockchipdrm-$(CONFIG_ROCKCHIP_DW_HDMI) += dw_hdmi-rockchip.o
rockchipdrm-$(CONFIG_ROCKCHIP_DW_MIPI_DSI) += dw-mipi-dsi.o
rockchipdrm-$(CONFIG_ROCKCHIP_INNO_HDMI) += inno_hdmi.o
rockchipdrm-$(CONFIG_ROCKCHIP_LVDS) += rockchip_lvds.o
rockchipdrm-$(CONFIG_ROCKCHIP_DRM_TVE) += rockchip_drm_tve.o
rockchipdrm-$(CONFIG_ROCKCHIP_RGB) += rockchip_rgb.o

obj-$(CONFIG_DRM_ROCKCHIP) += rockchipdrm.o

obj-$(CONFIG_DRM_ROCKCHIP_RK618) += rk618/
obj-$(CONFIG_DRM_ROCKCHIP_RK628) += rk628/
