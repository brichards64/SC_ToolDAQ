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
  
  //RHT
  float hum_mon;
  float temp_mon;
  
  //HV
  bool HV_mon;
  bool HV_state_set = NULL;
  float HV_volts = NULL;

  //LV
  bool LV_mon;
  bool LV_state_set = NULL;

  //Emergency variables
  float LIMIT_temperature_low = NULL;
  float LIMIT_humidity_low = NULL;
  float LIMIT_temperature_high = NULL;
  float LIMIT_humidity_high = NULL;  
  bool FLAG_temperature;
  bool FLAG_humidity;



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
  
 }
 
};

#endif
