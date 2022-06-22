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
	TL_yellow = 8
};

int SetSwitch(int devID, enum CUSBaccess::SWITCH_IDs switchID, int turnSwitch, CUSBaccess *CWusb);

int main(int argc, char *argv[])
{
	int switchID[MAXSWITCH] = {CUSBaccess::SWITCH_0, 0, 0};
	CUSBaccess *CWusb = 0;
	int ok = 1;
	int USBcount = 1;
	int state = -1;

	CWusb = new CUSBaccess;
	if (CWusb == NULL)
	{
		fprintf(stderr, "Can't open USBaccess!\n");
	}
	else
	{
		USBcount = CWusb->OpenCleware();
	}

	int devID;
	int traffic = TL_red;
	for (devID = 0; ok && devID < USBcount; devID++)
	{
		if (traffic == TL_none)
		{
			for (int i = 0; i < MAXSWITCH; i++)
			{
				if (switchID[i] == 0)
					break;
				ok = SetSwitch(devID, (enum CUSBaccess::SWITCH_IDs)switchID[i], 0, CWusb);
			}
		}
		else
		{
			if (traffic & TL_red)
				ok = SetSwitch(devID, CUSBaccess::SWITCH_0, 1, CWusb);
			else
				ok = SetSwitch(devID, CUSBaccess::SWITCH_0, 0, CWusb);
			if (traffic & TL_green)
				ok = SetSwitch(devID, CUSBaccess::SWITCH_2, 1, CWusb);
			else
				ok = SetSwitch(devID, CUSBaccess::SWITCH_2, 0, CWusb);
			if (traffic & TL_yellow)
				ok = SetSwitch(devID, CUSBaccess::SWITCH_1, 1, CWusb);
			else
				ok = SetSwitch(devID, CUSBaccess::SWITCH_1, 0, CWusb);
		}
	}

	if (CWusb != NULL)
	{
		CWusb->CloseCleware();
		delete CWusb;
	}

	if (!ok)
		state = -1;

	return state;
}

int SetSwitch(int devID, enum CUSBaccess::SWITCH_IDs switchID, int turnSwitch, CUSBaccess *CWusb)
{
	int ok = 0;
	if (CWusb != NULL)
		ok = CWusb->SetSwitch(devID, switchID, turnSwitch);
	return ok;
}