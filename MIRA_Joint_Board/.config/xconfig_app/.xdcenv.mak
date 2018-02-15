#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/bios_6_50_01_12/packages;C:/ti/ccsv7/ccs_base;C:/Users/Ben/Documents/MQP_Code/MIRA_Joint_Board_Code/MIRA_Joint_Board/.config
override XDCROOT = C:/ti/xdctools_3_50_03_33_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/bios_6_50_01_12/packages;C:/ti/ccsv7/ccs_base;C:/Users/Ben/Documents/MQP_Code/MIRA_Joint_Board_Code/MIRA_Joint_Board/.config;C:/ti/xdctools_3_50_03_33_core/packages;..
HOSTOS = Windows
endif
