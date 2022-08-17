# How to install and configure HDW_LampCtrl

 1. In the Raspberry Directory, check in *dev/usb* if **hiddev0** or **hiddev1** exist.

	CASE NOT:
	 - Download http://www.cleware.info/downloads/german/Ubuntu_V4.3.3.zip
	 - Unzip the file in your preferred location
	 - Open a console and go inside */USBaccess*
	 - run `source make_hid` (or `sudo source make_hid` if permission denied)

2. Install the following dependencies: (run `sudo apt-get update` and `sudo apt-get upgrade`before installing the dependencies)
	- Python3: `sudo apt install python3`
	- Requests: `sudo pip3 install requests`
	- os: `sudo pip3 install os`
	- urllib: `sudo pip3 install urllib`
	- dotenv: `sudo pip3 install dotenv`
	- Cleware Lib: `sudo apt-get install libusb-dev`
	
3. Clone the Git Repository on your Pi: https://github.com/hdw-werbeagentur/HDW_LampCtrl
4. Open a console, go to the repository, and run `make lampCtrl` (compile the C++ script)
5. Edit *.env.development*:
	- `REMOTE_PSM_URL='[your_remote_psm_url]'`
	- `SCRIPT_CMD_PATH='sudo [path_to_your_lampCtrl_file]/lampCtrl '` **<- don't forget to leave a space at the 																		                           end**
6. Open a console and run `sudo crontab -e` | it will first ask you to choose an editor, you can choose **nano**. You will then need to write the following task: 
	- `*/5 * * * * sudo /bin/python3 [path_to_your_statusManager_file]/statusManager.py`

Everything is now setup ! The cronjob will now run the python script every **5min** (e.g. 12h00 / 12h05 / 12h10)
 
