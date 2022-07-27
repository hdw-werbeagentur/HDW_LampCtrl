import paho.mqtt.client as mqtt
import os

def on_connect(client, userdata, flags, rc):
    print(f"connected with code {rc}")
    client.subscribe("raspberry/topic", 2)
    
def on_message(client, userdata, msg):
    cmd = 'sudo ./lampCtrl ' + str(msg.payload, 'UTF-8')
    stream = os.popen(cmd)
        
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.will_set('raspberry/status', b'{"status": "Off"}')

client.connect("192.168.1.103")
client.loop_forever()