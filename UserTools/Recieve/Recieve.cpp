#include "Recieve.h"

Recieve::Recieve():Tool(){}


bool Recieve::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;
  m_log= m_data->Log;

  if(!m_variables.Get("Port",m_port)) m_port=4444;

  sock=new zmq::socket_t(*(m_data->context), ZMQ_SUB);
  std::stringstream tmp;
  tmp<<"tcp://127.0.0.1:"<<m_port;
  sock->connect(tmp.str().c_str());
  sock->setsockopt(ZMQ_SUBSCRIBE, "", 0);
   
  items[0].socket = *sock;
  items[0].fd = 0;
  items[0].events = ZMQ_POLLIN;
  items[0].revents =0;

  zmq::poll(&items[0], 1, 100);

  if((items [0].revents & ZMQ_POLLIN)) 
  {
    m_data->LAPPDdata.Receive(sock);
    m_data->LAPPDdata.RelayControl(sock);
  }

  return true;
}


bool Recieve::Execute(){

    zmq::poll(&items[0], 1, 100);

    if((items [0].revents & ZMQ_POLLIN)) 
    {
      if(m_data->LAPPDdata.recieveFlag == 0) 
      {
        m_data->LAPPDdata.Receive(sock);
      }
      m_data->LAPPDdata.RelayControl(sock);  
    }
  
  return true;
}


bool Recieve::Finalise(){
  delete sock;

  return true;
}
