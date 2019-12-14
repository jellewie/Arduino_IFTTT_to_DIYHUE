# Arduino_IFTTT_to_DIYHUE
 A web url request (from IFTTT) to the DIYHUE Raspberry pi

hub: [diyHue](https://github.com/diyhue/diyHue)

# What you need
(opt)[IFTTTMaker](https://github.com/witnessmenow/arduino-ifttt-maker) (optional to send to IFTTT)

[ESP32](https://dl.espressif.com/dl/package_esp32_index.json)

[Arduino-WiFiManager](https://github.com/jellewie/Arduino-WiFiManager) 

[Arduino-DIYHUE]https://github.com/jellewie/Arduino_DIYHUE_switch

# How it works
Set-up your wifi/connection stuff (I use my own [Arduino-WiFiManager](https://github.com/jellewie/Arduino-WiFiManager) for it)

(opt)fill-in the "KEYIFTTT" with the IFTTT key

fill-in the "DIYHUE_bridgeIp" with your DIYHUE ip (see [Arduino-DIYHUE]https://github.com/jellewie/Arduino_DIYHUE_switch)) (Sitenote: must be reachable for the ESP ofc.)

Call "IFTTT_setup()" to start, this will set the webser stuff up.

Call "IFTTT_loop()" to handle the IFTTT web trafic

you can now do webrequest like "<IP>/Register?mac=<value>" and "<IP>/set?mac=<value>&id=<value2>", you cna uses {34, 16, 17, 18} for the ID's (to simulate buttons 1-4)

If you want the outside (no not only local) to be able to acces this ESP. you NEED to open a port in your router, and port forward that to the <IESPIP>(with an optional gate of 80)!
