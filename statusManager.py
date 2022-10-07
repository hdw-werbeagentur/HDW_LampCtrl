import requests
import os
from urllib.request import urlopen
from urllib.error import URLError
from dotenv import load_dotenv, find_dotenv


load_dotenv(find_dotenv('.env'))

SCRIPT_CMD_PATH = os.getenv('SCRIPT_CMD_PATH')
REMOTE_PSM_URL = os.getenv('REMOTE_PSM_URL')


def callLamp(light_value):
    # calling the C++ script from the shell
    cmd = SCRIPT_CMD_PATH + light_value
    stream = os.popen(cmd)


def untilConnection():
    while True:
        try:
            request = urlopen("http://www.google.com/", timeout=1)
            return
        except URLError:
            pass


def getJSON():
    # get the global status value in the json using cURL
    response = requests.get(REMOTE_PSM_URL).json()

    callLamp(str(response['status']))


untilConnection()
getJSON()
