#include <LAPPDMoniterData.h>

LAPPDMoniterData::LAPPDMoniterData(){};

bool LAPPDMoniterData::Send(zmq::socket_t* sock){

  zmq::message_t msg1(&hum_mon,sizeof hum_mon, NULL);
  zmq::message_t msg2(&temp_mon,sizeof temp_mon, NULL);
  zmq::message_t msg3(&HV_mon,sizeof HV_mon, NULL);
  zmq::message_t msg4(&LV_mon,sizeof LV_mon, NULL);
  zmq::message_t msg5(&FLAG_temperature,sizeof FLAG_temperature, NULL);
  zmq::message_t msg6(&FLAG_humidity,sizeof FLAG_humidity, NULL);
  zmq::message_t msg7(&relayCh1,sizeof relayCh1, NULL);
  zmq::message_t msg8(&relayCh2,sizeof relayCh2, NULL);
  zmq::message_t msg9(&relayCh3,sizeof relayCh3, NULL);

  sock->send(msg1,ZMQ_SNDMORE);
  sock->send(msg2,ZMQ_SNDMORE);
  sock->send(msg3,ZMQ_SNDMORE);
  sock->send(msg4,ZMQ_SNDMORE);
  sock->send(msg5,ZMQ_SNDMORE);
  sock->send(msg6,ZMQ_SNDMORE);
  sock->send(msg7,ZMQ_SNDMORE);
  sock->send(msg8,ZMQ_SNDMORE);
  sock->send(msg9);
  
  return true;

}

bool LAPPDMoniterData::Receive(zmq::socket_t* sock){

  zmq::message_t msg;
  
  //flag
  sock->recv(&msg);
  recieveFlag=*(reinterpret_cast<int*>(msg.data())); 

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

bool LAPPDMoniterData::RelayControl(zmq::socket_t* sock){
  
  zmq::message_t msg;
 //relay
  sock->recv(&msg);
  relayCh1=*(reinterpret_cast<bool*>(msg.data())); 
  sock->recv(&msg);
  relayCh2=*(reinterpret_cast<bool*>(msg.data()));  
  sock->recv(&msg);
  relayCh3=*(reinterpret_cast<bool*>(msg.data())); 
  
  return true;
}


bool LAPPDMoniterData::Print(){

  std::cout << "humidity = " << hum_mon << std::endl;
  std::cout << "temperature = " << temp_mon << std::endl;
  std::cout << "HV state should be " << HV_state_set << " and is " << HV_mon << " and is set to " << HV_volts << " V" << std::endl;
  std::cout << "LV state should be " << LV_state_set << " and is " << LV_mon << std::endl;
  std::cout << "Temperature warning flag is " << FLAG_temperature << std::endl;
  std::cout << "Humidity warning flag is " << FLAG_humidity << std::endl;
  std::cout << "Relay 1 is " << relayCh1 << std::endl;
  std::cout << "Relay 2 is " << relayCh2 << std::endl;
  std::cout << "Relay 3 is " << relayCh3 << std::endl;
  
  
  return true;
}
