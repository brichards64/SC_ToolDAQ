#ifndef LAPPDMONITERDATA_H
#define LAPPDMONITERDATA_H

#include "zmq.hpp"
#include <SerialisableObject.h>
#include <iostream>

class LAPPDMoniterData : public SerialisableObject{

 friend class boost::serialization::access;

 public:

  LAPPDMoniterData();
  
  //Comms
  bool Send(zmq::socket_t* sock);
  bool Receive(zmq::socket_t* sock);
  bool RelayControl(zmq::socket_t* sock);
  int recieveFlag = 0;
  
  //RHT
  float hum_mon;
  float temp_mon;
  
  //HV
  int HV_mon;
  bool HV_state_set;
  float HV_volts;

  //LV
  int LV_mon;
  bool LV_state_set;

  //Emergency variables
  float LIMIT_temperature_low = 0;
  float LIMIT_humidity_low = 0;
  float LIMIT_temperature_high = 0;
  float LIMIT_humidity_high = 0;  
  int FLAG_temperature = 0;
  int FLAG_humidity = 0;

  //relay
  bool relayCh1;
  bool relayCh2;
  bool relayCh3;

  //Triggerboard
  float TrigVref;
  float Trig1_threshold;
  float Trig1_mon;
  float Trig0_threshold;
  float Trig0_mon;

  bool Print();

 private:
 
 template <class Archive> void serialize(Archive& ar, const unsigned int version){

  ar & hum_mon;
  ar & temp_mon;
  ar & HV_mon;
  ar & HV_state_set;
  ar & HV_volts;
  ar & LV_mon;
  ar & LV_state_set;
  ar & LIMIT_temperature_low;
  ar & LIMIT_humidity_low;
  ar & LIMIT_temperature_high;
  ar & LIMIT_humidity_high;  
  ar & FLAG_temperature;
  ar & FLAG_humidity;
  ar & Trig1_threshold;
  ar & Trig1_mon;
  ar & Trig0_threshold;
  ar & Trig0_mon;
  ar & TrigVref;
  
 }
 
};

#endif
