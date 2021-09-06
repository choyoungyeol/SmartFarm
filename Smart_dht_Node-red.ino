//Arduino Program

#include <dht.h>
#define DHT11_PIN 12

dht DHT;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float chk = DHT.read11(DHT11_PIN);
  Serial.print(DHT.temperature);
  Serial.print(",");
  Serial.println(DHT.humidity);
  delay(5000);
}

//Node-red Program
//https://github.com/choyoungyeol/SmartFarm/issues/1#issue-973231282
[
    {
        "id": "10b3b103db8c94fc",
        "type": "tab",
        "label": "Temp_RH",
        "disabled": false,
        "info": ""
    },
    {
        "id": "e79e6cf424357108",
        "type": "serial in",
        "z": "10b3b103db8c94fc",
        "name": "",
        "serial": "c1103d13aef36fa3",
        "x": 230,
        "y": 180,
        "wires": [
            [
                "0a14594f07f60451",
                "2bd0190d82f2b049"
            ]
        ]
    },
    {
        "id": "0a14594f07f60451",
        "type": "function",
        "z": "10b3b103db8c94fc",
        "name": "",
        "func": "var output = msg.payload.split(\",\");\nvar temperature = parseFloat(output[0]);\nvar msg = {payload:temperature};\nreturn [msg];\n",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 420,
        "y": 140,
        "wires": [
            [
                "af753656bb7ea8e1",
                "523c88c101037419"
            ]
        ]
    },
    {
        "id": "af753656bb7ea8e1",
        "type": "ui_gauge",
        "z": "10b3b103db8c94fc",
        "name": "",
        "group": "d55947fd14c91720",
        "order": 1,
        "width": 9,
        "height": 6,
        "gtype": "gage",
        "title": "Temperature",
        "label": "oC",
        "format": "{{value}}",
        "min": 0,
        "max": "60",
        "colors": [
            "#00b500",
            "#e6e600",
            "#ca3838"
        ],
        "seg1": "",
        "seg2": "",
        "x": 630,
        "y": 100,
        "wires": []
    },
    {
        "id": "523c88c101037419",
        "type": "ui_chart",
        "z": "10b3b103db8c94fc",
        "name": "",
        "group": "d55947fd14c91720",
        "order": 3,
        "width": 9,
        "height": 7,
        "label": "Temperature",
        "chartType": "line",
        "legend": "false",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "",
        "dot": false,
        "ymin": "0",
        "ymax": "60",
        "removeOlder": 1,
        "removeOlderPoints": "",
        "removeOlderUnit": "3600",
        "cutout": 0,
        "useOneColor": false,
        "useUTC": false,
        "colors": [
            "#1f77b4",
            "#aec7e8",
            "#ff7f0e",
            "#2ca02c",
            "#98df8a",
            "#d62728",
            "#ff9896",
            "#9467bd",
            "#c5b0d5"
        ],
        "outputs": 1,
        "useDifferentColor": false,
        "x": 630,
        "y": 160,
        "wires": [
            []
        ]
    },
    {
        "id": "2bd0190d82f2b049",
        "type": "function",
        "z": "10b3b103db8c94fc",
        "name": "",
        "func": "var output = msg.payload.split(\",\");\nvar humidity = parseFloat(output[1]);\nvar msg = {payload:humidity};\nreturn [msg];\n",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 420,
        "y": 240,
        "wires": [
            [
                "7c7fecd1a292cb90",
                "06fe77b3aada4138"
            ]
        ]
    },
    {
        "id": "7c7fecd1a292cb90",
        "type": "ui_gauge",
        "z": "10b3b103db8c94fc",
        "name": "",
        "group": "d55947fd14c91720",
        "order": 2,
        "width": 9,
        "height": 6,
        "gtype": "wave",
        "title": "Humidity",
        "label": "%",
        "format": "{{value}}",
        "min": 0,
        "max": "100",
        "colors": [
            "#00b500",
            "#e6e600",
            "#ca3838"
        ],
        "seg1": "",
        "seg2": "",
        "x": 620,
        "y": 220,
        "wires": []
    },
    {
        "id": "06fe77b3aada4138",
        "type": "ui_chart",
        "z": "10b3b103db8c94fc",
        "name": "",
        "group": "d55947fd14c91720",
        "order": 4,
        "width": 9,
        "height": 7,
        "label": "Humidity",
        "chartType": "line",
        "legend": "false",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "",
        "dot": false,
        "ymin": "0",
        "ymax": "100",
        "removeOlder": 1,
        "removeOlderPoints": "",
        "removeOlderUnit": "3600",
        "cutout": 0,
        "useOneColor": false,
        "useUTC": false,
        "colors": [
            "#1f77b4",
            "#aec7e8",
            "#ff7f0e",
            "#2ca02c",
            "#98df8a",
            "#d62728",
            "#ff9896",
            "#9467bd",
            "#c5b0d5"
        ],
        "outputs": 1,
        "useDifferentColor": false,
        "x": 620,
        "y": 280,
        "wires": [
            []
        ]
    },
    {
        "id": "c1103d13aef36fa3",
        "type": "serial-port",
        "serialport": "COM5",
        "serialbaud": "9600",
        "databits": "8",
        "parity": "none",
        "stopbits": "1",
        "waitfor": "",
        "dtr": "none",
        "rts": "none",
        "cts": "none",
        "dsr": "none",
        "newline": "\\n",
        "bin": "false",
        "out": "char",
        "addchar": "",
        "responsetimeout": "10000"
    },
    {
        "id": "d55947fd14c91720",
        "type": "ui_group",
        "name": "Default",
        "tab": "c80bcc7f33cc7eec",
        "order": 1,
        "disp": true,
        "width": 18,
        "collapse": false
    },
    {
        "id": "c80bcc7f33cc7eec",
        "type": "ui_tab",
        "name": "Temp_RH",
        "icon": "dashboard",
        "order": 3,
        "disabled": false,
        "hidden": false
    }
]
