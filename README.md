# How to install and configure HDW_LampCtrl

 1. Prepare USB traffic light driver:
     - Check if driver in: `ls /dev/usb` exists: **hiddev0** or **hiddev1**
	 - **OPTIONAL** Install drive if not existing:
		 - Move to your user directory: `cd ~`
		 - Download driver: `wget http://www.cleware.info/downloads/german/Ubuntu_V4.3.3.zip`
		 - Unzip the drivers:  `unzip Ubuntu_V4.3.3.zip`
		 - Move to driver directory `cd ~/USBaccess`
		 - Install driver: `sudo -s` & `source make_hid`

2. Install the required dependencies
	- Update RasperryPi OS: `sudo apt-get update` and `sudo apt-get upgrade`
	- Install Python3: `sudo apt install python3`
	- Install PIP Requests: `sudo pip3 install requests` or `sudo pip install requests`
	- Install PIP Os: `sudo pip3 install os` or `sudo pip install os`
	- Install PIP Urllib: `sudo pip3 install urllib` or `sudo pip install urllib`
	- Install PIP dotenv: `sudo pip3 install dotenv` or `sudo pip install dotenv`
	- Install Cleware Lib: `sudo apt-get install libusb-dev`
	
	*If installation errors happens on these **PIP3** commands, try the **PIP** command. If this is still not working, ignore it and continue*
	
3. Clone this [Git Repository](https://github.com/hdw-werbeagentur/HDW_LampCtrl) on your Raspberry Pi 
	- Move to your user directory: `cd ~`
	- `git clone git@github.com:hdw-werbeagentur/HDW_LampCtrl.git`

4. Build the C++ script in local repository
	- Move in project directory: `cd ~/HDW_LampCtrl/`
	- Compile the C++ Script: `make CLampCtrl`

5. Define the environment variables:
	- Create `.env` file: `cp .env.example .env`
	- Edit the `.env `file:
		- `REMOTE_PSM_URL='[your_remote_psm_url]'` 
		   (Example: `REMOTE_PSM_URL='https://monitor.hdw.agency/status.json'`)
		- `SCRIPT_CMD_PATH='sudo [path_to_your_lampCtrl_file]/CLampCtrl '` 
		   (Example: `SCRIPT_CMD_PATH='sudo /home/hdw/HDW_LampCtrl/CLampCtrl '`)
		   **don't forget to leave a space at the end**
6. Try if the usb traffic light is working
	- Run script: `sudo /bin/python3 ~/HDW_LampCtrl/statusManager.py `
	- The traffic light should now be lighten in green, yellow or red

7. Build cronjob to run the script automatically within an certain rhytmn
	- Add new cronjob:  `crontab -e` as current user or `sudo crontab -e` as root
	- Choose **nano** and add the following line to the end of the file: 
	- `3,8,13,18,23,28,33,38,43,48,53,58 * * * * sudo /bin/python3 ~/HDW_LampCtrl/statusManager.py`
	*This wil run the script every 3 minutes after the 5 minutes rhytm from the **php server monitor** cronjob*
