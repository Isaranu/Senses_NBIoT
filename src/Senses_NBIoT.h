
#ifndef Senses_NBIoT_h
#define Senses_NBIoT_h

#include "Arduino.h"
#include "AIS_NB_BC95.h"

class Senses_NBIoT {

public:

  bool init();
  String send(String userid, String key, int slotnum, float data);
  String receiveResponse();
  String readRSSI();
  String readCSQ();
  //String pushLineNotify(String linetoken, String linemsg);
  String getNetworkTime();
  String getRespFromServer();
  //String getControlbySwitch(String userid, String key, int swnum);
  String getUDPip();

private:
  String _packet, _rssi, _csq;
  int _mode;
  String _userid, _key;
  int _slotnum;
  float _data;
  String _str, _response;
  bool _conn;
  String _linetoken, _linemsg;
  String _ntp;
  String _swnum;
  String _udpip;

};

#endif
