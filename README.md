# raspberry-pi-ledmatrix

Driving an LED matrix display using a raspberry pi. Exposing a web API to write custom messages to the display.

## Prerequisites
- Python 3 (I use Python 3.7 but any version should work)
- gcc compiler

## Python app


```bash
cd python
virtualenv venv --python=python3.7
source venv/bin/activate
pip install -m requirements.txt
python app.py
```