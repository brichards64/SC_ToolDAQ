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

	  float temp_VREF;
	  m_variables.Get("TrigVref",temp_VREF);
	  m_data->LAPPDdata.TrigVref = temp_VREF;

	  float temp_Tr1;
	  m_variables.Get("Trig1_threshold",temp_Tr1);
	  m_data->LAPPDdata.Trig1_threshold = temp_Tr1;

	  float temp_Tr0;
	  m_variables.Get("Trig0_threshold",temp_Tr0);
	  m_data->LAPPDdata.Trig0_threshold = temp_Tr0;
	  
	  bool temp_r1, temp_r2,temp_r3;
	  m_variables.Get("relayCh1",temp_r1);
	  m_variables.Get("relayCh2",temp_r2);
	  m_variables.Get("relayCh3",temp_r3);
	  m_data->LAPPDdata.relayCh1 = temp_r1;
	  m_data->LAPPDdata.relayCh2 = temp_r2;
	  m_data->LAPPDdata.relayCh3 = temp_r3;
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

  retval = m_data->CB->SetTriggerDac0(m_data->LAPPDdata.Trig0_threshold, m_data->LAPPDdata.TrigVref);
  if(retval == 1)
  {
    std::cout << " Threshold on DAC 0 set on LVHV " << std::endl;
  }else
  {
    std::cout << " There was an error with retval: " << retval << std::endl;
  }

  retval = m_data->CB->SetTriggerDac1(m_data->LAPPDdata.Trig1_threshold, m_data->LAPPDdata.TrigVref);
  if(retval == 1)
  {
    std::cout << " Threshold on DAC 1 set on LVHV " << std::endl;
  }else
  {
    std::cout << " There was an error with retval: " << retval << std::endl;
  }
  
  retval = m_data->CB->SetRelay(1,m_data->LAPPDdata.relayCh1);
  if(retval == 0)
  {
  	std::cout << " Relay 1 should be turned off " << std::endl;
  }else if(retval ==1)
  {
  	std::cout << " Relay 1 should be turned on " << std::endl;
  }else
  {
	  std::cout << " There was an error with retval: " << retval << std::endl;
  }
  
  retval = m_data->CB->SetRelay(2,m_data->LAPPDdata.relayCh2);
  if(retval == 0)
  {
  	std::cout << " Relay 2 should be turned off " << std::endl;
  }else if(retval ==1)
  {
  	std::cout << " Relay 2 should be turned on " << std::endl;
  }else
  {
	  std::cout << " There was an error with retval: " << retval << std::endl;
  } 
   
  retval = m_data->CB->SetRelay(3,m_data->LAPPDdata.relayCh3);
  if(retval == 0)
  {
  	std::cout << " Relay 3 should be turned off " << std::endl;
  }else if(retval ==1)
  {
  	std::cout << " Relay 3 should be turned on " << std::endl;
  }else
  {
	  std::cout << " There was an error with retval: " << retval << std::endl;
  }
  
  return true;
}


bool Set::Execute(){
  int retval;
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

    float temp_Tr1;
    m_variables.Get("Trig1_threshold",temp_Tr1);
    m_data->LAPPDdata.Trig1_threshold = temp_Tr1;

    float temp_Tr0;
    m_variables.Get("Trig0_threshold",temp_Tr0);
    m_data->LAPPDdata.Trig0_threshold = temp_Tr0;
	  
	  float temp_VREF;
	  m_variables.Get("TrigVref",temp_VREF);
	  m_data->LAPPDdata.TrigVref = temp_VREF;
	  
	  bool temp_r1, temp_r2,temp_r3;
	  m_variables.Get("relayCh1",temp_r1);
	  m_variables.Get("relayCh2",temp_r2);
	  m_variables.Get("relayCh3",temp_r3);
	  m_data->LAPPDdata.relayCh1 = temp_r1;
	  m_data->LAPPDdata.relayCh2 = temp_r2;
	  m_data->LAPPDdata.relayCh3 = temp_r3;
	
	  
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

    retval = m_data->CB->SetTriggerDac0(m_data->LAPPDdata.Trig0_threshold, m_data->LAPPDdata.TrigVref);
    if(retval == 1)
    {
      std::cout << " Threshold on DAC 0 set on LVHV " << std::endl;
    }else
    {
      std::cout << " There was an error with retval: " << retval << std::endl;
    }

    retval = m_data->CB->SetTriggerDac1(m_data->LAPPDdata.Trig1_threshold, m_data->LAPPDdata.TrigVref);
    if(retval == 1)
    {
      std::cout << " Threshold on DAC 1 set on LVHV " << std::endl;
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
  
  retval = m_data->CB->SetRelay(1,m_data->LAPPDdata.relayCh1);
  if(retval == 0)
  {
  	std::cout << " Relay 1 should be turned off " << std::endl;
  }else if(retval ==1)
  {
  	std::cout << " Relay 1 should be turned on " << std::endl;
  }else
  {
	  std::cout << " There was an error with retval: " << retval << std::endl;
  }
  
  retval = m_data->CB->SetRelay(2,m_data->LAPPDdata.relayCh2);
  if(retval == 0)
  {
  	std::cout << " Relay 2 should be turned off " << std::endl;
  }else if(retval ==1)
  {
  	std::cout << " Relay 2 should be turned on " << std::endl;
  }else
  {
	  std::cout << " There was an error with retval: " << retval << std::endl;
  } 
   
  retval = m_data->CB->SetRelay(3,m_data->LAPPDdata.relayCh3);
  if(retval == 0)
  {
  	std::cout << " Relay 3 should be turned off " << std::endl;
  }else if(retval ==1)
  {
  	std::cout << " Relay 3 should be turned on " << std::endl;
  }else
  {
	  std::cout << " There was an error with retval: " << retval << std::endl;
  }

  return true;
}


bool Set::Finalise(){

  m_data->CB->get_HV_volts = 0;
  return true;
}
