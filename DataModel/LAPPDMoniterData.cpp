#include <LAPPDMoniterData.h>

LAPPDMoniterData::LAPPDMoniterData(){};

bool LAPPDMoniterData::Send(zmq::socket_t* sock){

  zmq::message_t msg1(&hum_mon,sizeof hum_mon, NULL);
  zmq::message_t msg2(&temp_mon,sizeof temp_mon, NULL);
  zmq::message_t msg3(&HV_mon,sizeof HV_mon, NULL);
  zmq::message_t msg4(&LV_mon,sizeof LV_mon, NULL);
  zmq::message_t msg5(&FLAG_temperature,sizeof FLAG_temperature, NULL);
  zmq::message_t msg6(&FLAG_humidity,sizeof FLAG_humidity, NULL);

  sock->send(msg1,ZMQ_SNDMORE);
  sock->send(msg2,ZMQ_SNDMORE);
  sock->send(msg3,ZMQ_SNDMORE);
  sock->send(msg4,ZMQ_SNDMORE);
  sock->send(msg5,ZMQ_SNDMORE);
  sock->send(msg6);
  
  return true;

}

bool LAPPDMoniterData::Receive(zmq::socket_t* sock){

  zmq::message_t msg;
  
  //HV
  sock->recv(&msg);   
  HV_state_set=*(reinterpret_cast<bool*>(msg.data()));
  sock->recv(&msg);   
  HV_volts=*(reinterpret_cast<float*>(msg.data())); 
  
  //LV
  sock->recv(&msg);  
  LV_state_set=*(reinterpret_cast<bool*>(msg.data()));

  //Emergency
  sock->recv(&msg);
  LIMIT_temperature_low=*(reinterpret_cast<float*>(msg.data())); 
  sock->recv(&msg);
  LIMIT_humidity_low=*(reinterpret_cast<float*>(msg.data())); 
  sock->recv(&msg);
  LIMIT_temperature_high=*(reinterpret_cast<float*>(msg.data())); 
  sock->recv(&msg);
  LIMIT_humidity_high=*(reinterpret_cast<float*>(msg.data())); 

  return true;

}


bool LAPPDMoniterData::Print(){

  std::cout<<"hum="<<hum_mon<<std::endl;
  std::cout<<"temp="<<temp_mon<<std::endl;
  std::cout<<"HV="<<HV_mon<<std::endl;
  std::cout<<"LV="<<LV_mon<<std::endl;

}
