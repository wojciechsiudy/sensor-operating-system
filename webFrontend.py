#!/usr/bin/python3
from json import load
from flask import Flask
from os import listdir
from time import sleep

OUTPUT_CATALOG = "output/"
REFRESH_TIME = 2

class Sensor:
    def __init__(self, topic):
        self.topic = topic

    def get_last_value(self):
        try:
            file = self._read_last_file()
            return file.readlines()[-1]
        except IndexError:
            return "No data yet"

    def _read_last_file(self):
        catalog = self._find_output_catalog()
        files = listdir(catalog)
        files = [file for file in files if file.startswith(self.topic)]
        files.sort()
        return open(catalog + files[-1], "r")

    def _find_output_catalog(self):
        list = listdir(OUTPUT_CATALOG)
        list.sort()
        return OUTPUT_CATALOG + list[-1] + '/'

configuration = load(open('sos_config.json'))
sensors = []
for sensor in configuration['sensors']:
    sensors.append(Sensor(sensor['name']))



app = Flask(__name__)

@app.route('/')
def index():
    page = "<meta http-equiv=\"refresh\" content=\"2\">\n"
    page += "<h1>Current data from sensors</h1>\n"
    for sensor in sensors:
        page += "<h5>" + sensor.topic + "</h5>\n"
        page += "<p>" + sensor.get_last_value() + "</p>\n"
    return page

if __name__ == '__main__':
    app.run(host="127.0.0.1", port=5000, debug=True)