/*
 * This file contains the configuration parameters for the dbau1x00 board.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <configs/ar7100.h>

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#define CFG_MAX_FLASH_BANKS     1	    /* max number of memory banks */
//#define CFG_MAX_FLASH_SECT      128    /* max number of sectors on one chip */
#define CFG_MAX_FLASH_SECT      256    /* max number of sectors on one chip */
#define CFG_FLASH_SECTOR_SIZE   (64*1024)
#define CFG_FLASH_SIZE          0x00800000 /* Total flash size */

#define CFG_FLASH_WORD_SIZE     unsigned short 
#define CFG_FLASH_ADDR0         (0x5555)  		
#define CFG_FLASH_ADDR1         (0x2AAA)

//#define CFG_HOWL_1_2 1


/* 
 * We boot from this flash
 */
#define CFG_FLASH_BASE		    0xbf000000
#ifdef COMPRESSED_UBOOT
	#define BOOTSTRAP_TEXT_BASE			CFG_FLASH_BASE
	#define BOOTSTRAP_CFG_MONITOR_BASE 	BOOTSTRAP_TEXT_BASE
#endif

#undef CONFIG_ROOTFS_RD
#undef CONFIG_ROOTFS_FLASH
#undef CONFIG_BOOTARGS_FL
#undef CONFIG_BOOTARGS_RD
#undef CONFIG_BOOTARGS
#undef  MTDPARTS_DEFAULT
#undef  MTDIDS_DEFAULT

#define CONFIG_ROOTFS_FLASH
#define CONFIG_BOOTARGS CONFIG_BOOTARGS_FL

#define CONFIG_BOOTARGS_RD     "console=ttyS0,115200 root=01:00 rd_start=0x80600000 rd_size=5242880 init=/sbin/init mtdparts=ar9100-nor0:256k(u-boot),64k(u-boot-env),4096k(rootfs),2048k(uImage)"
#define CONFIG_BOOTARGS_FL     "console=ttyS0,115200 root=31:00 rootfstype=jffs2 init=/sbin/init mtdparts=ar9100-nor0:128k(u-boot),1024k(kernel),4096k(rootfs),64k(art)"

#define MTDPARTS_DEFAULT    "mtdparts=ar9100-nor0:mtdparts=ar9100-nor0:128k(u-boot),1024k(kernel),4096k(rootfs),64k(art)"
#define MTDIDS_DEFAULT      "nor0=ar9100-nor0"

/*
 * Other env default values
 */
#undef CONFIG_BOOTFILE
#define CONFIG_BOOTFILE			"firmware.bin"

#undef CONFIG_LOADADDR
#define CONFIG_LOADADDR			0x80800000

#define UPDATE_SCRIPT_FW_ADDR	"0xBF020000"
#define CONFIG_BOOTCOMMAND "bootm 0xBF020000"

//#define CFG_FLASH_BASE		    0xbfc00000 /* Temp WAR as remap is not on by default */

/* 
 * The following #defines are needed to get flash environment right 
 */
#define	CFG_MONITOR_BASE	TEXT_BASE
#define	CFG_MONITOR_LEN		(192 << 10)

#undef CFG_HZ
/*
 * MIPS32 24K Processor Core Family Software User's Manual
 *
 * 6.2.9 Count Register (CP0 Register 9, Select 0)
 * The Count register acts as a timer, incrementing at a constant
 * rate, whether or not an instruction is executed, retired, or
 * any forward progress is made through the pipeline.  The counter
 * increments every other clock, if the DC bit in the Cause register
 * is 0.
 */
/* Since the count is incremented every other tick, divide by 2 */
/* XXX derive this from CFG_PLL_FREQ */
#if (CFG_PLL_FREQ == CFG_PLL_200_200_100)
#	define CFG_HZ          (200000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_300_300_150)
#	define CFG_HZ          (200000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_333_333_166)
#	define CFG_HZ          (333000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_266_266_133)
#	define CFG_HZ          (266000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_266_266_66)
#	define CFG_HZ          (266000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_400_400_200)
#	define CFG_HZ          (400000000/2)
#elif (CFG_PLL_FREQ == CFG_PLL_360_360_180)
#	define CFG_HZ          (360000000/2)
#endif
#define CFG_HZ_FALLBACK CFG_HZ

#define AR7240_SPI_CONTROL_DEFAULT	0x43
#define AR7240_SPI_CONTROL	AR7240_SPI_CONTROL_DEFAULT


/* 
 * timeout values are in ticks 
 */
#define CFG_FLASH_ERASE_TOUT	(2 * CFG_HZ) /* Timeout for Flash Erase */
#define CFG_FLASH_WRITE_TOUT	(2 * CFG_HZ) /* Timeout for Flash Write */

/*
 * Cache lock for stack
 */
#define CFG_INIT_SP_OFFSET	0x1000


/* changed by lqm, 17Jan08
#define	CFG_ENV_IS_IN_FLASH    1
#undef CFG_ENV_IS_NOWHERE  
*/
#undef	CFG_ENV_IS_IN_FLASH   
#define CFG_ENV_IS_NOWHERE  	1
 

/* Address and size of Primary Environment Sector	*/
#define CFG_ENV_ADDR		0xbf040000
#define CFG_ENV_SIZE		0x20000

//#define CONFIG_BOOTCOMMAND "bootm 0xbf020000" // by lsz 17Nov08 "bootm 0xbf460000"
//#define CONFIG_FLASH_16BIT

#define CONFIG_NR_DRAM_BANKS	2

#if (CFG_PLL_FREQ == CFG_PLL_200_200_100)
#define CFG_DDR_REFRESH_VAL     0x4c00
#define CFG_DDR_CONFIG_VAL      0x67bc8cd0
#define CFG_DDR_MODE_VAL_INIT   0x161
#define CFG_DDR_EXT_MODE_VAL    0x2
#define CFG_DDR_MODE_VAL        0x61
#elif (CFG_PLL_FREQ == CFG_PLL_400_400_200) || (CFG_PLL_FREQ == CFG_PLL_360_360_180)
#define CFG_DDR_REFRESH_VAL     0x5f00
#define CFG_DDR_CONFIG_VAL      0x77bc8cd0
#define CFG_DDR_MODE_VAL_INIT   0x131
#define CFG_DDR_EXT_MODE_VAL    0x0
#define CFG_DDR_MODE_VAL        0x31
#endif

#define CFG_DDR_TRTW_VAL        0x1f
#define CFG_DDR_TWTR_VAL        0x1e

#define CFG_DDR_CONFIG2_VAL			    0x83d1f6a2
#define CFG_DDR_RD_DATA_THIS_CYCLE_VAL  0xffff


#define CONFIG_NET_MULTI

#define CONFIG_MEMSIZE_IN_BYTES


/*-----------------------------------------------------------------------
 * Cache Configuration
 */
#define CFG_CMD_EXCLUDE_BY_TP_LINK ((CFG_CMD_BDI | \
			CFG_CMD_LOADS | \
			CFG_CMD_CONSOLE | \
			CFG_CMD_ECHO | \
			CFG_CMD_SETGETDCR | \
			CFG_CMD_MISC | \
			CFG_CMD_ITEST | \
			CFG_CMD_NFS | \
			CFG_CMD_ENV | \
			CFG_CMD_XIMG | \
			CFG_CMD_AUTOSCRIPT | \
			CFG_CMD_IMI | \
			CFG_CMD_BOOTD | \
			CFG_CMD_IMLS | \
			CFG_CMD_MII \
		))

#define CONFIG_COMMANDS	( (CONFIG_CMD_DFL & ~CFG_CMD_EXCLUDE_BY_TP_LINK) | \
				CFG_CMD_NET | CFG_CMD_FLASH | CFG_CMD_LOADB )	
   
#if 0
#define CONFIG_COMMANDS	(( CONFIG_CMD_DFL | CFG_CMD_DHCP | CFG_CMD_ELF | \
            CFG_CMD_MII | CFG_CMD_PING | CFG_CMD_NET | CFG_CMD_JFFS2 |\
   CFG_CMD_ENV | CFG_CMD_FLASH | CFG_CMD_LOADS | CFG_CMD_RUN | CFG_CMD_LOADB \
   | CFG_CMD_ELF ))		/* del CFG_CMD_NET, lsz 080827 */
#endif

#define CONFIG_IPADDR		192.168.0.2
#define CONFIG_SERVERIP		192.168.0.5
#define CONFIG_ETHADDR		00:1D:0F:11:22:33 //00:00:00:00:00:00
#define CFG_FAULT_ECHO_LINK_DOWN    1
#define CONFIG_PHY_GIGE       1              /* GbE speed/duplex detect */

//#define CFG_VSC8601_PHY
//#define CFG_VITESSE_8601_7395_PHY 1
#define CFG_AG7100_NMACS 1 // 2 /* changed by lsz 14Nov08 */
#define CONFIG_AR9100 1
//#define CFG_PHY_ADDR 0x14  /* Port 4 */
#define CFG_PHY_ADDR 0  /* Port 4 */
#define CFG_GMII     0
#define CFG_MII0_RGMII             1

#define CFG_BOOTM_LEN	(16 << 20) /* 16 MB */
#undef DEBUG	/* del by lsz 14Nov08 */
#undef CFG_HUSH_PARSER
#undef CFG_PROMPT_HUSH_PS2


/*
 * Web Failsafe configuration
 */
#define WEBFAILSAFE_UPLOAD_RAM_ADDRESS					CONFIG_LOADADDR

// U-Boot partition size and offset
#if defined(CONFIG_FOR_TPLINK_WR1043ND)
	#ifndef CONFIG_MAX_UBOOT_SIZE_KB
	#define CONFIG_MAX_UBOOT_SIZE_KB 127  // MAC Address @0x1FC00
	#endif
#endif
#define WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS				CFG_FLASH_BASE
#define WEBFAILSAFE_UPLOAD_UBOOT_SIZE_IN_BYTES			(CONFIG_MAX_UBOOT_SIZE_KB * 1024)

#if defined(CONFIG_FOR_TPLINK_WR1043ND)
	// MAC Address @0x1FC00
	// Model & Version @0x1FD00 (e.g. 10 43 00 01  00 00 00 01)
	// WPS Pin @0x1FE00 (e.g. 31 32 33 34  35 36 37 38)
	#define UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES		"0x1FC00"
	#define UPDATE_SCRIPT_UBOOT_BACKUP_SIZE_IN_BYTES	UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES
#else
	// TODO: should be == CONFIG_MAX_UBOOT_SIZE_KB
	#define UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES		"0x1EC00"
	#define UPDATE_SCRIPT_UBOOT_BACKUP_SIZE_IN_BYTES	"0x20000"
#endif

// Firmware partition offset
#if defined(CONFIG_FOR_TPLINK_WR1043ND)
	#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS			WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS + 0x20000
#else
	#define WEBFAILSAFE_UPLOAD_KERNEL_ADDRESS			WEBFAILSAFE_UPLOAD_UBOOT_ADDRESS + 0x20000
#endif

#define WEBFAILSAFE_UPLOAD_ART_SIZE_IN_BYTES			(64 * 1024)

// max. firmware size <= (FLASH_SIZE -  WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES)
#if defined(CONFIG_FOR_TPLINK_WR1043ND)
	// TP-Link WR-1043ND v1: 128k(U-Boot + MAC),64k(ART)
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(192 * 1024)
#else
	// TP-Link: 64k(U-Boot),64k(MAC/model/WPS pin block),64k(ART)
	#define WEBFAILSAFE_UPLOAD_LIMITED_AREA_IN_BYTES	(192 * 1024)
#endif

// progress state info
#define WEBFAILSAFE_PROGRESS_START				0
#define WEBFAILSAFE_PROGRESS_TIMEOUT			1
#define WEBFAILSAFE_PROGRESS_UPLOAD_READY		2
#define WEBFAILSAFE_PROGRESS_UPGRADE_READY		3
#define WEBFAILSAFE_PROGRESS_UPGRADE_FAILED		4

// update type
#define WEBFAILSAFE_UPGRADE_TYPE_FIRMWARE		0
#define WEBFAILSAFE_UPGRADE_TYPE_UBOOT			1
#define WEBFAILSAFE_UPGRADE_TYPE_ART			2

/*-----------------------------------------------------------------------*/

/*
 * Additional environment variables for simple upgrades
 */
#define CONFIG_EXTRA_ENV_SETTINGS	"uboot_addr=0xBF000000\0" \
					"uboot_name=uboot.bin\0" \
					"uboot_size=" UPDATE_SCRIPT_UBOOT_SIZE_IN_BYTES "\0" \
					"uboot_backup_size=" UPDATE_SCRIPT_UBOOT_BACKUP_SIZE_IN_BYTES "\0" \
					"uboot_upg=" \
						"if ping $serverip; then " \
							"mw.b $loadaddr 0xFF $uboot_backup_size && " \
							"cp.b $uboot_addr $loadaddr $uboot_backup_size && " \
							"tftp $loadaddr $uboot_name && " \
							"if itest.l $filesize <= $uboot_size; then " \
								"erase $uboot_addr +$uboot_backup_size && " \
								"cp.b $loadaddr $uboot_addr $uboot_backup_size && " \
								"echo OK!; " \
							"else " \
								"echo ERROR! Wrong file size!; " \
							"fi; " \
						"else " \
							"echo ERROR! Server not reachable!; " \
						"fi\0" \
					"firmware_addr=" UPDATE_SCRIPT_FW_ADDR "\0" \
					"firmware_name=firmware.bin\0" \
					"firmware_upg=" \
						"if ping $serverip; then " \
							"tftp $loadaddr $firmware_name && " \
							"erase $firmware_addr +$filesize && " \
							"cp.b $loadaddr $firmware_addr $filesize && " \
							"echo OK!; " \
						"else " \
							"echo ERROR! Server not reachable!; " \
						"fi\0" \
					SILENT_ENV_VARIABLE


#include <cmd_confdefs.h>

#endif	/* __CONFIG_H */
