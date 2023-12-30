#!/usr/bin/python3
from json import load
from flask import Flask
from os import listdir
from time import sleep, time

OUTPUT_CATALOG = "output/"
REFRESH_TIME = 2


def get_time_stamp(data):
    return int(data.split("|")[0])

def get_T(data1, data2):
    tstmp1 = get_time_stamp(data1)
    tstmp2 = get_time_stamp(data2)
    return  tstmp2-tstmp1

def get_message_age(message):
    now = int(time() * 1e6)
    message_time = get_time_stamp(message)
    return now - message_time


class Sensor:
    def __init__(self, topic, extra_values=""):
        self.topic = topic
        self.extra_values = extra_values

    def get_last_value(self):
        try:
            file = self._read_last_file()
            lines = file.readlines()
            return (lines[-1], lines[-2])
        except IndexError:
            return "no data yet"

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
    name = sensor['name']

    extra_values = ""
    if sensor['type'] == "external":
        extra_values += "path: " + sensor["command"] + "<br>"

    if sensor['type'] == "serial":
        extra_values += "port: " + sensor["path"] + " baudrate: " + str(sensor["baudrate"]) + "<br>"
        parser = sensor.get("parser")
        if parser:
            extra_values += "parser: " + parser + "<br>"
        filter = sensor.get("regex_filter")
        if filter:
            extra_values += "regex filter: " + filter + "<br>"

    sensors.append(Sensor(sensor['name'], extra_values))



app = Flask(__name__)

@app.route('/')
def index():
    page = "<meta http-equiv=\"refresh\" content=\"2\">\n"
    page += "<style>\n\
            * {\n\
            font-family: sans-serif;\n\
            }\n\
            </style>\n"
    page += "<head>\n\
  	    <title>sensor operating system</title>\n\
            </head>\n"
    page += "<h1>sensor operating system</h1>\n"
    for sensor in sensors:
        page += "<h5>" + sensor.topic + "</h5>\n"
        page += "<p>" + sensor.extra_values + "</p>\n"
        try:
        	last_two_values = sensor.get_last_value()
            page += "<p> last value: " + str(last_two_values[0].split("|")[1]) + "<br>\n"
            page += "Δt [μs]: " + str(get_T(last_two_values[1], last_two_values[0])) + "<br>\n"
            page += "age [μs]: " + str(get_message_age(last_two_values[0])) + "</p>\n"
        except UnicodeDecodeError:
        	page += "<p>unicode error</p>\n"
        except IndexError:
                page += "<p>no data yet</p>\n"
    return page

if __name__ == '__main__':
    app.run(host="127.0.0.1", port=5000, debug=True)
