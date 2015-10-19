#include "rtl_phy.h"
#include "rtl8366s_asicdrv.h"
#include "rtl8366s_api.h"


#if 0
void rtl_vlanSetup()
{
	/* initialize VLAN */
	rtl8366s_initVlan();

	/* all the ports are in the default VLAN 1 after VLAN initialized, 
	 * modify it as follows 
	 * VLAN1 member: port0, port5;
	 * VLAN2 member: port1, port2, port3, port4, port5 
	 */
	rtl8366s_setVlan(1, 0x21, 0x1f);
	rtl8366s_setVlan(2, 0x3E, 0x1f);

	/* set PVID for each port */
	rtl8366s_setVlanPVID(PORT0, 1, 0);
	rtl8366s_setVlanPVID(PORT1, 2, 0);
	rtl8366s_setVlanPVID(PORT2, 2, 0);
	rtl8366s_setVlanPVID(PORT3, 2, 0);
	rtl8366s_setVlanPVID(PORT4, 2, 0);
	//rtl8366s_setVlanPVID(PORT5, 2, 0);
	
}

#endif
/******************************************************************************
*
* rtl_phySetup - reset and setup the PHY associated with
* the specified MAC unit number.
*
* Resets the associated PHY port.
*
* RETURNS:
*    TRUE  --> associated PHY is alive
*    FALSE --> no LINKs on this ethernet unit
*/

BOOL
rtl_phySetup(int ethUnit)
{
	int phyNo = 0;

	rtl8366s_initChip();

	return 1;

#if 0
	int result = 0;
	int retry = 1;

	while ((retry--) > 0)
	{
		result = rtl8366s_initChip();
		printf("rtl8366s_initChip returns %d\n", result);
		if (result == 0)
			break;
	}
	
	udelay(1000*1000);


	
	//rtl_vlanSetup();

	/* configure phy ability */
	phyAbility_t pa, pb;
	memset(&pa, 0, sizeof(pa));
	memset(&pa, 0, sizeof(pb));
	
	//pa.AutoNegotiation = 1;
	//pa.Full_100	= 1;
	pa.Full_1000 = 1;
	//pa.FC		= 1;
	//pa.AsyFC	= 1;
	
	for (phyNo = 0; phyNo < PHY_NUM_MAX; phyNo++)
	{
		rtl8366s_setEthernetPHY(phyNo, pa);
		rtl8366s_getEthernetPHY(phyNo, &pb);
		printf("AutoNegotiation : %d Full_1000 : %d FC : %d AsyFC : %d\n",
			pb.AutoNegotiation, 
			pb.Full_1000, 
			pb.FC, 
			pb.AsyFC);
		
	}

	uint32_t phyData = 0;
	for (phyNo = 0; phyNo < PHY_NUM_MAX; phyNo++)
	{
		rtl8366s_getAsicPHYRegs(phyNo, 0, 0, &phyData);
		printf("0 0: %X\n", phyData);
		rtl8366s_getAsicPHYRegs(phyNo, 1, 22, &phyData);
		printf("1 22: %X\n", phyData);
		rtl8366s_getAsicPHYRegs(phyNo, 1, 23, &phyData);
		printf("1 23: %X\n", phyData);
		rtl8366s_getAsicReg(0x0005, &phyData);
		printf("0x0005: %X\n", phyData);
		rtl8366s_getAsicReg(0x0400, &phyData);
		printf("0x0400: %X\n", phyData);
	}

	
	return 1;

    int     phyNo;
    uint32_t  phyHwStatus;
    uint16_t  timeout;
    int     liveLinks = 0;

	//smi_init();
	
	#if 0
	uint32_t phyData = 0;
	do
	{
		rtl8366s_getAsicPHYRegs(0, 0, 0, &phyData);
	}while(phyData != 0x1140);
	#endif
	/* Init chip */
	//rtl8366s_initChip();
	//mdelay(5000);



	//uint32_t retVal = 0;
	//rtl8366s_getAsicReg(RTL8366S_CPU_CTRL_REG, &retVal);
	//printk("CPU port map:%x\n", retVal);
	
	/* Set Port 5 as cpu port */
	//rtl8366s_setCPUPort(PORT5, 0x1, 0x0);

	/* configure phy ability */
	phyAbility_t pa, pb;
	memset(&pa, 0, sizeof(pa));
	memset(&pa, 0, sizeof(pb));
	
	//pa.AutoNegotiation = 1;
	//pa.Full_100	= 1;
	pa.Full_1000 = 1;
	pa.FC		= 0;
	pa.AsyFC	= 0;
	
	for (phyNo = 0; phyNo < PHY_NUM_MAX; phyNo++)
	{
		rtl8366s_setEthernetPHY(phyNo, pa);
		//rtl8366s_getEthernetPHY(phyNo, &pb);
		//printk("AutoNegotiation : %d Full_1000 : %d FC : %d AsyFC : %d\n",
		//	pb.AutoNegotiation, pb.Full_1000, pb.FC, pb.AsyFC);
	}

	//rtl8366s_setMac5ForceLink(SPD_1000M, FULL_DUPLEX, 1, 1, 1);
	


	uint32_t phyData = 0;	
	int phy = 0, reg = 0;


	do
	{
		rtl8366s_getAsicPHYRegs(0, 0, 0, &phyData);
	}while(phyData != 0x1140);
	
//#else	
	for (phy = 0; phy < 5; phy ++)
	{
		for (reg = 0; reg < 8; reg++)
		{
			rtl8366s_getAsicPHYRegs(phy, 0, reg, &phyData);
			printk("%#X ", phyData);
		}
		printk("\n");
	}

	rtl8366s_getAsicReg(0x105, &phyData);
	printk("%#X ", phyData);
	
    /* Reset PHYs*/
    for (phyNo = 0; phyNo < PHY_NUM_MAX; phyNo++)
	{
        rtl8366s_setAsicPHYRegs(phyNo, 0, PHY_CONTROL_REG, PHY_CTRL_SOFTWARE_RESET);
    }
    /*
     * After the phy is reset, it takes a little while before
     * it can respond properly.
     */
    mdelay(300);

	//rtl8366s_setCPUPort(5, TRUE, FALSE);
	
    /* start auto negogiation on each phy */
	for (phyNo = 0; phyNo < PHY_NUM_MAX; phyNo++) 
	{
		rtl8366s_setAsicPHYRegs(phyNo, 0, PHY_AN_ADVERTISEMENT_REG, PHY_ADVERTISE_ALL);

        rtl8366s_setAsicPHYRegs(phyNo, 0, PHY_CONTROL_REG,
                    PHY_CTRL_AUTONEGOTIATION_ENABLE | PHY_CTRL_START_AUTONEGOTIATION);
    }

    /*
     * Wait up to .75 seconds for ALL associated PHYs to finish
     * autonegotiation.  The only way we get out of here sooner is
     * if ALL PHYs are connected AND finish autonegotiation.
     */
    timeout = 10;
	
	for (phyNo = 0; phyNo < PHY_NUM_MAX; phyNo++) 
	{
		for (;;)
		{
            rtl8366s_getAsicPHYRegs(phyNo, 0, PHY_STATUS_REG, &phyHwStatus);

			printk("Setup %d:%x\n", phyNo, phyHwStatus);
			
            if (PHY_AUTONEG_DONE(phyHwStatus)) {
                printk("Port %d, Neg Success\n", phyNo);
                break;
            }
            if (timeout == 0) {
                printk("Port %d, Negogiation timeout\n", phyNo);
                break;
            }
            if (--timeout == 0) {
                printk("Port %d, Negogiation timeout\n", phyNo);
                break;
            }

            mdelay(150);
        }
    }

    /*
     * All PHYs have had adequate time to autonegotiate.
     * Now initialize software status.
     *
     * It's possible that some ports may take a bit longer
     * to autonegotiate; but we can't wait forever.  They'll
     * get noticed by mv_phyCheckStatusChange during regular
     * polling activities.
     */
    for (phyNo=0; phyNo < PHY_NUM_MAX; phyNo++) 
	{
        if (rtl_phyIsLinkAlive(phyNo)) {
            liveLinks++;
        }
    }

	/* added by lsz 30Apri07 to configure port vlan registers */
	
/****************************************************************************
	Port VLan:
	
	 ---------------------------------------------------------------
	|		| Port6	| Port5	| Port4	| Port3	| Port2	| Port1	| Port0	|
	 ---------------------------------------------------------------
	| Port0	|	0	|	1	|	0	|	0	|	0	|	0	|	0	|
	 ---------------------------------------------------------------
	| Port1	|	0	|	1	|	1	|	1	|	1	|	0	|	0	|
	 ---------------------------------------------------------------
	| Port2	|	0	|	1	|	1	|	1	|	0	|	1	|	0	|
	 ---------------------------------------------------------------
	| Port3	|	0	|	1	|	1	|	0	|	1	|	1	|	0	|
	 ---------------------------------------------------------------
	| Port4	|	0	|	1	|	0	|	1	|	1	|	1	|	0	|
	 ---------------------------------------------------------------
	| Port5	|	0	|	0	|	1	|	1	|	1	|	1	|	1	|
	 ---------------------------------------------------------------
	| Port6	|	0	|	0	|	0	|	0	|	0	|	0	|	0	|
	 ---------------------------------------------------------------
	 
	Port 0:		Wan
	Port 1~4:	Lan

	e.g. Port 0 is 010 0000, i.e. 0x20.
****************************************************************************/
	#define PORT_VALN_MAP_REG	0x06

	#ifdef PHY_ADDR_LOW
	uint32_t portAddr[6] = {0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D};
	#else
	uint32_t portAddr[7] = {0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E};
	#endif
	
	phy_reg_write(0, portAddr[0], PORT_VALN_MAP_REG, 0x1020);
	phy_reg_write(0, portAddr[1], PORT_VALN_MAP_REG, 0x203c);
	phy_reg_write(0, portAddr[2], PORT_VALN_MAP_REG, 0x203A);
	phy_reg_write(0, portAddr[3], PORT_VALN_MAP_REG, 0x2036);
	phy_reg_write(0, portAddr[4], PORT_VALN_MAP_REG, 0x202E);
	phy_reg_write(0, portAddr[5], PORT_VALN_MAP_REG, 0x201F);
	//phy_reg_write(0, portAddr[6], PORT_VALN_MAP_REG, 0x0000);
	
	/* added by lsz to configure header mode registers */
	#define PORT_CONTROL_REG	0x04
	//uint16_t reg_data = 0x8803;	/* Flow Control | Header Mode | Forwarding */
	
	phy_reg_write(0, portAddr[0], PORT_CONTROL_REG, 0x8000);
	phy_reg_write(0, portAddr[1], PORT_CONTROL_REG, 0x8000);
	phy_reg_write(0, portAddr[2], PORT_CONTROL_REG, 0x8000);
	phy_reg_write(0, portAddr[3], PORT_CONTROL_REG, 0x8000);
	phy_reg_write(0, portAddr[4], PORT_CONTROL_REG, 0x8000);
	phy_reg_write(0, portAddr[5], PORT_CONTROL_REG, 0x8800);
	//phy_reg_write(0, portAddr[6], PORT_CONTROL_REG, reg_data);

#endif
		
}


