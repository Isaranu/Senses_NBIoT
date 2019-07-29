
#include "Senses_NBIoT.h"

/* Senses iot configuration parameter */
#define Senses_NBIoT_HOST "34.87.38.20"
#define Senses_NBIoT_PORT "5683"

AIS_NB_BC95 AISnb;

bool Senses_NBIoT::init(){

  AISnb.debug = true;
  Serial.begin(9600);

  Serial.println("Waiting Initialize...");
  AISnb.setupDevice(Senses_NBIoT_PORT);

  String ip1 = AISnb.getDeviceIP();
  pingRESP pingR = AISnb.pingIP(Senses_NBIoT_HOST);
  Serial.println("Initialize completed !..");
  Serial.println("Ready for data sending to sensesiot.com");
  return true;

}

String Senses_NBIoT::send(String userid, String key, int slotnum, float data){

  _mode = 2;
  _userid = userid;
  _key = key;
  _slotnum = slotnum;
  _data = data;

  _packet = String(_mode);
  _packet += ":";
  _packet += _userid;
  _packet += ":";
  _packet += _key;
  _packet += ":";
  _packet += String(_slotnum);
  _packet += ":";
  _packet += String(_data);

  UDPSend udp = AISnb.sendUDPmsgStr(Senses_NBIoT_HOST, Senses_NBIoT_PORT, _packet);
  return "OK";

}

String Senses_NBIoT::readRSSI(){
  signal chksignal_rssi = AISnb.getSignal();
  _rssi = chksignal_rssi.rssi;
  return _rssi;
}

String Senses_NBIoT::readCSQ(){
  signal chksignal_csq = AISnb.getSignal();
  _csq = chksignal_csq.csq;
  return _csq;
}

String Senses_NBIoT::getNetworkTime(){

  String _ntpPacket = "NTP";
  Serial.println("Request network time from server (+7GMT)");

  UDPSend udpLineNoti = AISnb.sendUDPmsgStr(Senses_NBIoT_HOST, Senses_NBIoT_PORT, _ntpPacket);
  _ntp = getRespFromServer();

  return _ntp;
}

String Senses_NBIoT::getUDPip(){

    String _udpipPacket = "IP";
    Serial.println("Request UDP IP address");

    UDPSend udpIP = AISnb.sendUDPmsgStr(Senses_NBIoT_HOST, Senses_NBIoT_PORT, _udpipPacket);
    _udpip = getRespFromServer();

    return _udpip;
}

String Senses_NBIoT::getRespFromServer(){

  String respStr = "";
  unsigned long responseChkRetry = 50000;
  int retCnt = 0;

  while((respStr = "") && (retCnt < responseChkRetry)){
    UDPReceive resp = AISnb.waitResponse();
      if(resp.data != ""){
        Serial.println("resp.data = " + String(resp.data));
        //Serial.println("retry cnt = " + String(retCnt));
        respStr = AISnb.toString(resp.data);
        return respStr;
      }
    retCnt++;
  }

  if(retCnt >= responseChkRetry){
    Serial.println("Timeout at : " + String(retCnt));
    return "Request timeout";
  }

}

/*
String Senses_NBIoT::receiveResponse(){

  UDPReceive resp = AISnb.waitResponse();
  //_response = resp.data;
  //Serial.println("IoTtweet response : " + _response);

  return "received";
}

String Senses_NBIoT::pushLineNotify(String linetoken, String linemsg){

  _linetoken = linetoken;
  _linemsg = linemsg;

  String _lnfPacket = "LNF";
         _lnfPacket += ":";
         _lnfPacket += _linetoken;
         _lnfPacket += ":";
         _lnfPacket += _linemsg;
         _lnfPacket += ":";
         _lnfPacket += "eol";

  Serial.println("_lnfPacket = " + _lnfPacket);

  UDPSend udpLineNoti = AISnb.sendUDPmsgStr(Senses_NBIoT_HOST, Senses_NBIoT_PORT, _lnfPacket);
  return "Line Notify OK";
}

String Senses_NBIoT::getControlbySwitch(String userid, String key, int swnum){

  _userid = userid;
  _key = key;
  _swnum = String(swnum);

  String _getswctl = "SWC";
         _getswctl += ":";
         _getswctl += _userid;
         _getswctl += ":";
         _getswctl += _key;
         _getswctl += ":";
         _getswctl += _swnum;

  UDPSend udpGetcontrol = AISnb.sendUDPmsgStr(Senses_NBIoT_HOST, Senses_NBIoT_PORT, _getswctl);
  String _ctlstatus = getRespFromServer();
  return _ctlstatus;
}
*/
