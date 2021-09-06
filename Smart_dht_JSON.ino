#include <dht.h>
#define DHT22_PIN 7

dht DHT;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float chk = DHT.read22(DHT22_PIN);
  Serial.print("{\"temp\":");
  Serial.print(DHT.temperature, 1);
  Serial.print(",\"humidity\":");
  Serial.print(DHT.humidity, 1);
  Serial.println("}");
  delay(5000);
}


//Node-red code
[
    {
        "id": "77ca4fd5313dd382",
        "type": "tab",
        "label": "Temp_RH_JSON",
        "disabled": false,
        "info": ""
    },
    {
        "id": "772cf1ba0f6ca15e",
        "type": "serial in",
        "z": "77ca4fd5313dd382",
        "name": "",
        "serial": "c1103d13aef36fa3",
        "x": 130,
        "y": 200,
        "wires": [
            [
                "e7f2d634de0592d9"
            ]
        ]
    },
    {
        "id": "e7f2d634de0592d9",
        "type": "json",
        "z": "77ca4fd5313dd382",
        "name": "",
        "property": "payload",
        "action": "",
        "pretty": true,
        "x": 250,
        "y": 140,
        "wires": [
            [
                "031c8d131b0ce52f"
            ]
        ]
    },
    {
        "id": "031c8d131b0ce52f",
        "type": "function",
        "z": "77ca4fd5313dd382",
        "name": "",
        "func": "var b = JSON.parse(JSON.stringify(msg.payload)); \nb=msg;\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 360,
        "y": 240,
        "wires": [
            [
                "dcfd4c0c585ac933",
                "12e81b60d60cd367"
            ]
        ]
    },
    {
        "id": "dcfd4c0c585ac933",
        "type": "function",
        "z": "77ca4fd5313dd382",
        "name": "",
        "func": "msg.payload=msg.payload.temp;\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 560,
        "y": 180,
        "wires": [
            [
                "59f40d70b33c17ed",
                "b7271b7f18f6b0ec"
            ]
        ]
    },
    {
        "id": "59f40d70b33c17ed",
        "type": "ui_gauge",
        "z": "77ca4fd5313dd382",
        "name": "",
        "group": "ddb9acc26e9bbb3f",
        "order": 1,
        "width": 6,
        "height": 6,
        "gtype": "gage",
        "title": "Temperature",
        "label": "oC",
        "format": "{{value}}",
        "min": 0,
        "max": "50",
        "colors": [
            "#00b500",
            "#e6e600",
            "#ca3838"
        ],
        "seg1": "25",
        "seg2": "30",
        "x": 730,
        "y": 180,
        "wires": []
    },
    {
        "id": "12e81b60d60cd367",
        "type": "function",
        "z": "77ca4fd5313dd382",
        "name": "",
        "func": "msg.payload=msg.payload.humidity;\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 560,
        "y": 280,
        "wires": [
            [
                "af6c65b5f2514453",
                "43c90d98d8bcbe63"
            ]
        ]
    },
    {
        "id": "af6c65b5f2514453",
        "type": "ui_gauge",
        "z": "77ca4fd5313dd382",
        "name": "",
        "group": "ddb9acc26e9bbb3f",
        "order": 2,
        "width": 6,
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
        "seg1": "30",
        "seg2": "50",
        "x": 760,
        "y": 300,
        "wires": []
    },
    {
        "id": "b7271b7f18f6b0ec",
        "type": "ui_chart",
        "z": "77ca4fd5313dd382",
        "name": "",
        "group": "ddb9acc26e9bbb3f",
        "order": 9,
        "width": 6,
        "height": 7,
        "label": "Temperature",
        "chartType": "line",
        "legend": "false",
        "xformat": "HH:mm:ss",
        "interpolate": "linear",
        "nodata": "",
        "dot": false,
        "ymin": "0",
        "ymax": "50",
        "removeOlder": 1,
        "removeOlderPoints": "",
        "removeOlderUnit": "60",
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
        "x": 740,
        "y": 240,
        "wires": [
            []
        ]
    },
    {
        "id": "43c90d98d8bcbe63",
        "type": "ui_chart",
        "z": "77ca4fd5313dd382",
        "name": "",
        "group": "ddb9acc26e9bbb3f",
        "order": 10,
        "width": 6,
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
        "x": 750,
        "y": 360,
        "wires": [
            []
        ]
    },
    {
        "id": "c774582264110e2e",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 5,
        "width": 18,
        "height": 1
    },
    {
        "id": "27037b872eda6b07",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 6,
        "width": 18,
        "height": 1
    },
    {
        "id": "d61411d4df3b541d",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 8,
        "width": 12,
        "height": 1
    },
    {
        "id": "5d01fb1993732598",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 9,
        "width": 12,
        "height": 1
    },
    {
        "id": "42239c29f1e8a6c7",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 10,
        "width": 12,
        "height": 1
    },
    {
        "id": "7524e7f628b8942a",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 11,
        "width": 12,
        "height": 1
    },
    {
        "id": "6781d2443fd8b0b6",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 12,
        "width": 3,
        "height": 1
    },
    {
        "id": "19b4447f0b0cecda",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 14,
        "width": 3,
        "height": 1
    },
    {
        "id": "cedf158c06493395",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 15,
        "width": 9,
        "height": 1
    },
    {
        "id": "63ed7423956da88f",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 16,
        "width": 9,
        "height": 1
    },
    {
        "id": "6aa2a86b9b9dec08",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 17,
        "width": 9,
        "height": 1
    },
    {
        "id": "28a2e86a9349998d",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 18,
        "width": 9,
        "height": 1
    },
    {
        "id": "74451076762069ad",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 19,
        "width": 9,
        "height": 1
    },
    {
        "id": "7c8c310e1ccdd071",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 21,
        "width": 1,
        "height": 1
    },
    {
        "id": "7d816d768bd4d895",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 23,
        "width": 2,
        "height": 1
    },
    {
        "id": "00325dbd9a3ea3ee",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 24,
        "width": 1,
        "height": 1
    },
    {
        "id": "88c7423cf63f4ac1",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 25,
        "width": 2,
        "height": 1
    },
    {
        "id": "5db7b1d8b35da7d0",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 26,
        "width": 1,
        "height": 1
    },
    {
        "id": "2b5b73c50f6318dd",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 27,
        "width": 2,
        "height": 1
    },
    {
        "id": "916c920cd2c4607a",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 28,
        "width": 1,
        "height": 1
    },
    {
        "id": "3a0cc1973f0bae22",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 29,
        "width": 2,
        "height": 1
    },
    {
        "id": "90a2ea71319be2b9",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 30,
        "width": 1,
        "height": 1
    },
    {
        "id": "ea9ec1798b924480",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 31,
        "width": 2,
        "height": 1
    },
    {
        "id": "fda3321f79d8d10c",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 32,
        "width": 1,
        "height": 1
    },
    {
        "id": "5ac7aec104ba8703",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 33,
        "width": 2,
        "height": 1
    },
    {
        "id": "7293e53c6891500d",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "d55947fd14c91720",
        "order": 34,
        "width": 9,
        "height": 1
    },
    {
        "id": "2ceb143a32188944",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "ddb9acc26e9bbb3f",
        "order": 3,
        "width": 2,
        "height": 1
    },
    {
        "id": "6e49d690c8e32c90",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "ddb9acc26e9bbb3f",
        "order": 4,
        "width": 2,
        "height": 1
    },
    {
        "id": "9c3c4f7bf249bc39",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "ddb9acc26e9bbb3f",
        "order": 5,
        "width": 2,
        "height": 1
    },
    {
        "id": "d54869d729e51b5f",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "ddb9acc26e9bbb3f",
        "order": 6,
        "width": 2,
        "height": 1
    },
    {
        "id": "3ee0fbcdd4998e14",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "ddb9acc26e9bbb3f",
        "order": 7,
        "width": 2,
        "height": 1
    },
    {
        "id": "af05752a55f79785",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "ddb9acc26e9bbb3f",
        "order": 8,
        "width": 2,
        "height": 1
    },
    {
        "id": "9df5c259660d85cc",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "ddb9acc26e9bbb3f",
        "order": 11,
        "width": 2,
        "height": 1
    },
    {
        "id": "9be3a2cd5e0f902b",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "ddb9acc26e9bbb3f",
        "order": 12,
        "width": 2,
        "height": 1
    },
    {
        "id": "ec48a3955ae2ac3a",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "ddb9acc26e9bbb3f",
        "order": 13,
        "width": 2,
        "height": 1
    },
    {
        "id": "6507199a6c09fea7",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "ddb9acc26e9bbb3f",
        "order": 14,
        "width": 2,
        "height": 1
    },
    {
        "id": "579c1f7bc974c02d",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "ddb9acc26e9bbb3f",
        "order": 15,
        "width": 2,
        "height": 1
    },
    {
        "id": "8b83d3ceab43bb98",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "ddb9acc26e9bbb3f",
        "order": 16,
        "width": 2,
        "height": 1
    },
    {
        "id": "3b0463a978689a08",
        "type": "ui_spacer",
        "z": "77ca4fd5313dd382",
        "name": "spacer",
        "group": "ddb9acc26e9bbb3f",
        "order": 17,
        "width": 2,
        "height": 1
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
        "id": "ddb9acc26e9bbb3f",
        "type": "ui_group",
        "name": "Group 1",
        "tab": "fa77f82c0a076646",
        "order": 1,
        "disp": true,
        "width": 14
    },
    {
        "id": "fa77f82c0a076646",
        "type": "ui_tab",
        "name": "Temp_RH_JSON",
        "icon": "dashboard",
        "order": 5,
        "disabled": false,
        "hidden": false
    }
]
