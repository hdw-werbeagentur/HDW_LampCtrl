import paho.mqtt.client as mqtt
import os

host = "192.168.1.103"
port = 1883

#when connecting, the script subscribe to the global status topic
def on_connect(client, userdata, flags, rc):
    print(f"connected with code {rc}")
    client.subscribe("raspberry/global_status", 2)
    
def on_message(client, userdata, msg):
    cmd = 'sudo ./lampCtrl ' + str(msg.payload, 'UTF-8')
    stream = os.popen(cmd) #calling the c++ script from the shell
        
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

#message to send when the Raspberry is Off
client.will_set('raspberry/status', 'Raspberry Off')

client.connect(host, port)
client.loop_forever()