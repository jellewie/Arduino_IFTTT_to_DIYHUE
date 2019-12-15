/* Written by JelleWho https://github.com/jellewie

   TODO
   Polish it up, test it even more
   Get data back from Raspberry?

   DO NOT USE:
   Prefix 'IFTTT' for anything
*/

#include <WiFiClientSecure.h>
#include <WebServer.h>
//#include <IFTTTMaker.h>

//#define IFTTT_SerialEnabled

//#define IFTTT_KEYIFTTT "REPLACE THIS WITH YOU IFTTT KEY"
//IFTTTMaker ifttt(IFTTT_KEYIFTTT, client);

WebServer IFTTT_server(80);
WiFiClientSecure client;

void IFTTT_setup() {
  IFTTT_server.on("/set",       IFTTT_handle_Set);
  IFTTT_server.on("/register",  IFTTT_handle_Register);
  IFTTT_server.onNotFound(      IFTTT_HandleNotFound);
  IFTTT_server.begin();
}
void IFTTT_loop() {
  IFTTT_server.handleClient();
}
void IFTTT_handle_Register() {
  //URL argument names like "<IP>/register?mac=<value>"
  //Example                 "192.168.1.128/register?mac=00:0a:95:9d:68:16"

  for (int i = 0; i < IFTTT_server.args(); i++) {
    String IFTTT_ArguName = IFTTT_server.argName(i);
    IFTTT_ArguName.toLowerCase();
    String IFTTT_ArgValue = IFTTT_server.arg(i);
    IFTTT_ArgValue.toLowerCase();
    if (IFTTT_ArguName == "mac") {
      DIYHUE_Register(IFTTT_ArgValue);
      IFTTT_server.send(200, "text/plain", "Succesfull send register mac='" + IFTTT_ArgValue);
    } else {
      IFTTT_server.send(422, "text/plain", "'mac' missing mac='" + IFTTT_ArgValue + "'");
    }
  }
}
void IFTTT_handle_Set() {
  //URL argument names like "<IP>/set?mac=<value>&id=<value2>"
  //Example                 "192.168.1.128/set?mac=00:0a:95:9d:68:16&id=34"

  String IFTTT_ReturnMSG;
  int IFTTT_ReturnStatus;

  String IFTTT_mac;
  int IFTTT_ID = 0;
  for (int i = 0; i < IFTTT_server.args(); i++) {
    String IFTTT_ArguName = IFTTT_server.argName(i);
    IFTTT_ArguName.toLowerCase();
    String IFTTT_ArgValue = IFTTT_server.arg(i);
    IFTTT_ArgValue.toLowerCase();
    if (IFTTT_ArguName == "mac") {
      IFTTT_mac = IFTTT_ArgValue;
    } else if (IFTTT_ArguName == "id") {
      IFTTT_ID = IFTTT_ArgValue.toInt();
    }
  }
  if (IFTTT_mac != "" and IFTTT_ID != 0) {
    if (!DIYHUE_sendHttpRequest(IFTTT_mac, IFTTT_ID))
      IFTTT_ReturnMSG = "Could not connect to DIYHUE ip='" + String(DIYHUE_bridgeIp) + "' and send Http Request";
  } else
    IFTTT_ReturnMSG = "'mac' or 'id' missing";
  if (IFTTT_ReturnMSG == "") { //If no error MSG
    IFTTT_ReturnStatus = 200; //Return 'OK, succes' flag
    IFTTT_ReturnMSG = "Succesfull send";
  } else if (IFTTT_ReturnStatus == 0)
    IFTTT_ReturnStatus = 422;  //Return this error as default

  IFTTT_server.send(IFTTT_ReturnStatus, "text/plain", String(IFTTT_ReturnMSG) + " mac='" + IFTTT_mac + "' id='" + String(IFTTT_ID) + "'");
  return;
}
void IFTTT_HandleNotFound() {
#ifdef IFTTT_SerialEnabled
  Serial.println("Method: " + String(IFTTT_server.method()) + " URI: " + IFTTT_server.uri());
  for (int i = 0; i < IFTTT_server.args(); i++)
    Serial.println("arg '" + String(IFTTT_server.argName(i)) + "' = '" + String(IFTTT_server.arg(i)) + "'");
#endif //IFTTT_SerialEnabled
}
//void IFTTT_SendIFTTT() {
//  if (ifttt.triggerEvent("Test", "waarde 1", "waarde 2", "waarde 3")) {
//#ifdef IFTTT_SerialEnabled
//    Serial.println("IFTTT Successfully sent");
//#endif //IFTTT_SerialEnabled
//  } else {
//#ifdef IFTTT_SerialEnabled
//    Serial.println("IFTTTFailed");
//#endif //IFTTT_SerialEnabled
//  }
//}
