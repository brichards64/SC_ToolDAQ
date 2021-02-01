#include "Set.h"

Set::Set():Tool(){}


bool Set::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;
  m_log= m_data->Log;
 
  m_data->CB= new Canbus();
  m_data->CB->Connect(); 

  if(!m_variables.Get("verbose",m_verbose)) m_verbose=1;

	if(m_data->LAPPDdata.recieveFlag==0)
	{
		bool temp_HVS;
		m_variables.Get("HV_state_set",temp_HVS);
		m_data->LAPPDdata.HV_state_set = temp_HVS;

		bool temp_LVS;
		m_variables.Get("LV_state_set",temp_LVS);
		m_data->LAPPDdata.LV_state_set = temp_LVS;

		float temp_HVV;
		m_variables.Get("HV_volts",temp_HVV);
		m_data->LAPPDdata.HV_volts = temp_HVV;
		m_data->CB->get_HV_volts= temp_HVV;
	}

  int retval;
  retval = m_data->CB->SetLV(m_data->LAPPDdata.LV_state_set);
  if(retval == 0)
  {
  	std::cout << " LV should be turned off " << std::endl;
  }else if(retval ==1)
  {
  	std::cout << " LV should be turned on " << std::endl;
  }else
  {
	std::cout << " There was an error with retval: " << retval << std::endl;
  }

  retval = m_data->CB->SetHV_voltage(m_data->LAPPDdata.HV_volts);
  if(retval == 1)
  {
  	std::cout << " HV voltage value set on LVHV " << std::endl;
  	m_data->CB->get_HV_volts= m_data->LAPPDdata.HV_volts;
  }else
  {
	std::cout << " There was an error with retval: " << retval << std::endl;
  }

  retval = m_data->CB->SetHV_ONOFF(m_data->LAPPDdata.HV_state_set);
  if(retval == 0)
  {
  	std::cout << " HV should be turned off " << std::endl;
  }else if(retval ==1)
  {
  	std::cout << " HV should be turned on " << std::endl;
  }else
  {
	std::cout << " There was an error with retval: " << retval << std::endl;
  }

  return true;
}


bool Set::Execute(){

	//check LV/HV state_set 
  if(m_data->LAPPDdata.recieveFlag==0)
  {

		bool temp_HVS;
		m_variables.Get("HV_state_set",temp_HVS);
		m_data->LAPPDdata.HV_state_set = temp_HVS;

		bool temp_LVS;
		m_variables.Get("LV_state_set",temp_LVS);
		m_data->LAPPDdata.LV_state_set = temp_LVS;

		float temp_HVV;
		m_variables.Get("HV_volts",temp_HVV);
		m_data->LAPPDdata.HV_volts = temp_HVV;
		m_data->CB->get_HV_volts= temp_HVV;
	


	  int retval;
	  retval = m_data->CB->SetLV(m_data->LAPPDdata.LV_state_set);
	  if(retval == 0)
	  {
	  	std::cout << " LV should be turned off " << std::endl;
	  }else if(retval ==1)
	  {
	  	std::cout << " LV should be turned on " << std::endl;
	  }else
	  {
		std::cout << " There was an error with retval: " << retval << std::endl;
	  }

	  retval = m_data->CB->SetHV_voltage(m_data->LAPPDdata.HV_volts);
	  if(retval == 1)
	  {
	  	std::cout << " HV voltage value set on LVHV " << std::endl;
	  	m_data->CB->get_HV_volts = m_data->LAPPDdata.HV_volts;
	  }else
	  {
		std::cout << " There was an error with retval: " << retval << std::endl;
	  }

	  retval = m_data->CB->SetHV_ONOFF(m_data->LAPPDdata.HV_state_set);
	  if(retval == 0)
	  {
	  	std::cout << " HV should be turned off " << std::endl;
	  }else if(retval ==1)
	  {
	  	std::cout << " HV should be turned on " << std::endl;
	  }else
	  {
		std::cout << " There was an error with retval: " << retval << std::endl;
	  }
  }	

  return true;
}


bool Set::Finalise(){

  return true;
}
