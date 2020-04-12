from flask import Flask
from ctypes import *

app = Flask(__name__)

so_file = "/home/pi/src/c/pin_management.so"
pin_management = CDLL(so_file)


@app.route('/')
def hello():
    return "Hello World!"

@app.route('/on')
def led_on():
    return str(pin_management.set_pin_high(4))

@app.route('/off')
def led_off():
    return str(pin_management.set_pin_low(4))

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)