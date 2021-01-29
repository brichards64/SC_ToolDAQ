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
  bool HV_state_set;
  float HV_volts;

  //LV
  bool LV_mon;
  bool LV_state_set;


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
  
 }
 
};

#endif
