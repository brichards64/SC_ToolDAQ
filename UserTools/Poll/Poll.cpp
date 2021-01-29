#include "Poll.h"

Poll::Poll():Tool(){}


bool Poll::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;
  m_log= m_data->Log;

  if(!m_variables.Get("verbose",m_verbose)) m_verbose=1;

  m_data->CB= new Canbus();
  m_data->CB->Connect(); 

  return true;
}


bool Poll::Execute(){

  //LV
  int LVstate = m_data->CB->GetLV();
  if(LVstate==0)
  {
  	m_data->LAPPDdata.LV_mon = false;
  }else if(LVstate==1)
  {
  	m_data->LAPPDdata.LV_mon == true;
  }else
  {
  	cout << "There has been an error!" << endl;
  }

  //HV
  int HVstate = m_data->CB->GetHV_ONOFF();
  if(HVstate==0)
  {
  	m_data->LAPPDdata.HV_mon = false;
  }else if(HVstate==1)
  {
  	m_data->LAPPDdata.HV_mon == true;
  }else
  {
  	cout << "There has been an error!" << endl;
  }

  //RHT
  vector<float> RHT = m_data->CB->GetTemp();
  m_data->LAPPDdata.temp_mon = RHT[0];
  m_data->LAPPDdata.hum_mon = RHT[1];

  //DAC0

  //DAC1

  return true;
}


bool Poll::Finalise(){

  m_data->CB->Disconnect();
  delete m_data->CB;
  m_data->CB=0;

  return true;
}
