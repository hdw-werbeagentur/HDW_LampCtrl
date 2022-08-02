import requests
import sched
import time
import os
from urllib.request import urlopen
from urllib.error import URLError

# the first scheduler for calling the function
s = sched.scheduler(time.time, time.sleep)


def callLamp(light_value):
    # calling the C++ script from the shell
    cmd = 'sudo /home/pi/Documents/Cleware_USB/LampCtrl/lampCtrl ' + \
        light_value
    stream = os.popen(cmd)


def untilConnection():
    while True:
        try:
            request = urlopen("http://www.google.com/", timeout=1)
            return
        except URLError:
            callLamp("3")
            pass


def request(sc):
    # get the global status value in the json using cURL
    response = requests.get('http://192.168.1.116/status.json').json()

    callLamp(str(response['status']))

    # calling the function again for infinite loop
    sc.enter(5, 1, request, (sc,))


untilConnection()

# 5s schedule calling the function for the 1st time
s.enter(5, 1, request, (s,))
s.run()
