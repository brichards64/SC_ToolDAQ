#include "Set.h"

Set::Set():Tool(){}


bool Set::Initialise(std::string configfile, DataModel &data){

  if(configfile!="")  m_variables.Initialise(configfile);
  //m_variables.Print();

  m_data= &data;
  m_log= m_data->Log;

  if(!m_variables.Get("verbose",m_verbose)) m_verbose=1;


	//set here

  return true;
}


bool Set::Execute(){

  return true;
}


bool Set::Finalise(){

  return true;
}
