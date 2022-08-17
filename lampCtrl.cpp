#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "USBaccess.h"

const int MAXSWITCH = 3;

enum tl_enum
{
	TL_none = 1,
	TL_red = 2,
	TL_green = 4,
	TL_yellow = 8,
	TL_green_blink = 16,
	TL_red_blink = 32
};

int SetSwitch(int devID, enum CUSBaccess::SWITCH_IDs switchID, int turnSwitch, CUSBaccess *CWusb);
int CheckSwitch(int traffic, CUSBaccess *CWusb);

int main(int argc, char *argv[])
{
	int switchID[MAXSWITCH] = {CUSBaccess::SWITCH_0, 0, 0}; // represent the three lights
	CUSBaccess *CWusb = 0;
	int ok = 1;
	int USBcount = 1;
	int state = -1;
	int traffic = TL_none; // represent the lamps colors

	// check if the lamp is plugged to the USB port
	CWusb = new CUSBaccess;
	if (CWusb == NULL)
	{
		fprintf(stderr, "Can't open USBaccess!\n");
	}
	else
	{
		USBcount = CWusb->OpenCleware(); // open the device
	}

	/* get the input value and modify the traffic value
	0 = green
	1 = yellow
	2 = red
	3 = off */
	switch (argv[1][0])
	{
	case '0':
		traffic &= ~TL_none;
		traffic |= TL_red;
		break;
	case '1':
		traffic &= ~TL_none;
		traffic |= TL_yellow;
		break;
	case '2':
		traffic &= ~TL_none;
		traffic |= TL_green;
		break;
	case '3':
		traffic &= ~TL_none;
		break;
	default:
		printf("Illegal Argument");
	}

	if (CheckSwitch(traffic, CWusb))
	{
		exit(0);
	}

	// turn the lamp Off
	if (traffic == TL_none)
	{
		for (int i = 0; i < MAXSWITCH; i++)
		{
			if (switchID[i] == 0)
				break;
			ok = SetSwitch(0, (enum CUSBaccess::SWITCH_IDs)switchID[i], 0, CWusb);
		}
	}
	else // switch the lamps light using the SetSwitch Method
	{
		if (traffic & TL_red)
			ok = SetSwitch(0, CUSBaccess::SWITCH_0, 1, CWusb);
		else
			ok = SetSwitch(0, CUSBaccess::SWITCH_0, 0, CWusb);

		if (traffic & TL_green)
			ok = SetSwitch(0, CUSBaccess::SWITCH_2, 1, CWusb);
		else
			ok = SetSwitch(0, CUSBaccess::SWITCH_2, 0, CWusb);

		if (traffic & TL_yellow)
			ok = SetSwitch(0, CUSBaccess::SWITCH_1, 1, CWusb);
		else
			ok = SetSwitch(0, CUSBaccess::SWITCH_1, 0, CWusb);
	}

	// close then delete the device
	if (CWusb != NULL)
	{
		CWusb->CloseCleware();
		delete CWusb;
	}

	if (!ok)
		state = -1;

	return state;
}

/**
 *turn one of the switchs On or Off
 *
 * @param devID the devices name (here only the lamp)
 * @param switchID the switch that will be turned On or Off
 * @param turnSwitch 1 = On and 0 = Off
 */
int SetSwitch(int devID, enum CUSBaccess::SWITCH_IDs switchID, int turnSwitch, CUSBaccess *CWusb)
{
	int ok = 0;
	if (CWusb != NULL)
		ok = CWusb->SetSwitch(devID, switchID, turnSwitch);
	return ok;
}

int CheckSwitch(int traffic, CUSBaccess *CWusb)
{
	if (traffic & TL_red)
		return CWusb->GetSwitch(0, CUSBaccess::SWITCH_0);
	if (traffic & TL_yellow)
		return CWusb->GetSwitch(0, CUSBaccess::SWITCH_1);
	if (traffic & TL_green)
		return CWusb->GetSwitch(0, CUSBaccess::SWITCH_2);
	return 0;
}
