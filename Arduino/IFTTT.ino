/* Written by JelleWho https://github.com/jellewie
   
   DO NOT USE:
   Prefix 'IFTTT' for anything
*/
#ifdef IFTTT
void IFTTT_handle_Register() {
  //URL argument names like "<IP>/register?mac=<value>"
  //Example                 "192.168.1.128/register?mac=00:0a:95:9d:68:16"

  for (int i = 0; i < server.args(); i++) {
    String IFTTT_ArguName = server.argName(i);
    IFTTT_ArguName.toLowerCase();
    String IFTTT_ArgValue = server.arg(i);
    IFTTT_ArgValue.toLowerCase();
    if (IFTTT_ArguName == "mac") {
      DIYHUE_Register(IFTTT_ArgValue);    //Register this device at the DIYHUE hub (NOT INCLUDED!!, INCLUDE YOUR OWN OR INCLUDE IT YOURSELF)
      server.send(200, "text/plain", "Succesfull send register mac='" + IFTTT_ArgValue);
    } else {
      server.send(422, "text/plain", "'mac' missing mac='" + IFTTT_ArgValue + "'");
    }
  }
}
void IFTTT_handle_Set() {
  //URL argument names like "<IP>/set?mac=<value>&id=<value2>"
  //Example                 "192.168.1.128/set?mac=00:0a:95:9d:68:16&id=34"

  String IFTTT_ReturnMSG = "";
  int IFTTT_ReturnStatus = 0;

  String IFTTT_mac;
  int IFTTT_ID = 0;
  for (int i = 0; i < server.args(); i++) {
    String IFTTT_ArguName = server.argName(i);
    IFTTT_ArguName.toLowerCase();
    String IFTTT_ArgValue = server.arg(i);
    IFTTT_ArgValue.toLowerCase();
    if (IFTTT_ArguName == "mac") {
      IFTTT_mac = IFTTT_ArgValue;
    } else if (IFTTT_ArguName == "id") {
      IFTTT_ID = IFTTT_ArgValue.toInt();
    }
  }
  if (IFTTT_mac != "" and IFTTT_ID != 0) {
    if (!DIYHUE_sendHttpRequest(IFTTT_mac, IFTTT_ID))     //Send buttonstate to the DIYHUE hub (NOT INCLUDED!!, INCLUDE YOUR OWN OR INCLUDE IT YOURSELF)
      IFTTT_ReturnMSG = "Could not connect to DIYHUE ip='" + String(DIYHUE_bridgeIp) + "' and send Http Request";
  } else
    IFTTT_ReturnMSG = "'mac' or 'id' missing";
  if (IFTTT_ReturnMSG == "") { //If no error MSG
    IFTTT_ReturnStatus = 200; //Return 'OK, succes' flag
    IFTTT_ReturnMSG = "Succesfull send";
  } else if (IFTTT_ReturnStatus == 0)
    IFTTT_ReturnStatus = 422;  //Return this error as default

  server.send(IFTTT_ReturnStatus, "text/plain", String(IFTTT_ReturnMSG) + " mac='" + IFTTT_mac + "' id='" + String(IFTTT_ID) + "'");
  return;
}
//#include <IFTTTMaker.h>
//#define IFTTT_KEYIFTTT "REPLACE THIS WITH YOU IFTTT KEY"
//IFTTTMaker ifttt(IFTTT_KEYIFTTT, client);
//void IFTTT_SendIFTTT() {
//  if (ifttt.triggerEvent("Test", "value 1", "value 2", "value 3")) {
//    Serial.println("IFTTT Successfully sent");
//  } else {
//    Serial.println("IFTTTFailed");
//  }
//}
#endif //IFTTT
