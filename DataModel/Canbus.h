#ifndef CANBUS_H
#define CANBUS_H

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <chrono>
#include <sstream>
#include <vector>

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>

#include <linux/can.h>
#include <linux/can/raw.h>
#include <linux/can/error.h>

#define CANID_DELIM '#'
#define DELIM "#"
#define DATA_SEPERATOR '.'
#define C40N_MAX 4000.0 // V
#define HV_MAX 3276.0
#define DAC_VMAX 5.0
#define DAC_VREF 2.048
#define DV 50.0 // V

using namespace std;

class Canbus{

public:

	Canbus();

	bool Connect(); //done 
	bool Disconnect(); //done

	//LV
	int SetLV(bool state); //done
	int GetLV(); //done

	//HV
	int SetHV_ONOFF(bool state); //done
	int SetHV_voltage(float volts); //done
	int GetHV_ONOFF(); //done

	//RHT
	vector<float> GetTemp(); //done

	//Trigger DAC
	int GetTriggerDac0();
	int GetTriggerDac1();
	int SetTriggerDac0();
	int SetTriggerDac1();

	//??
	bool GetLeak();
	float GetLight();
	



	int s;
	int nbytes;
	struct ifreq ifr;
	struct sockaddr_can addr;
	struct can_frame frame;

	unsigned char asc2nib(char c){
		if((c>='0') && (c<='9'))
		{
		  return c - '0';
		}
		if((c>='A') && (c <='F'))
		{
		  return c - 'A' + 10;
		}
		if((c>='a') && (c<='f'))
		{
		  return c - 'a' + 10;
		}
		return 16;
	}

	char* parseFrame(unsigned int id, unsigned long msg)
	{
		char* t_id = (char *)malloc(3);
		char* t_msg = (char *)malloc(8);
		char* r_frame = (char*)malloc(11);

		stringstream ss;
		ss << hex << id;

		stringstream ss2;
		ss2 << hex << msg;

		strcpy(r_frame,ss.str().c_str());
		strcat(r_frame,DELIM);
		strcat(r_frame,ss2.str().c_str());

		return r_frame;
	}


	int createCanFrame(unsigned int id, unsigned long msg, struct can_frame *cf)
	{
		char *t_frame = (char *)malloc(11);
		t_frame = parseFrame(id,msg);

		int i, idx, dlc, len;
		unsigned char temp;

		len = strlen(t_frame);
		memset(cf, 0, sizeof(*cf));

		if (len<4)
		{
			return 1;
		}
		if (t_frame[3] == CANID_DELIM)
		{
			idx = 4;
			for (i=0; i<3; i++)
			{
		  		if((temp = asc2nib(t_frame[i])) > 0x0F)
		  		{
		    		return 1;
		  		}
		  		cf->can_id |= (temp << (2-i)*4);
			}
		}else if (t_frame[8] == CANID_DELIM)
		{
			idx = 9;
			for (i=0; i<8; i++)
			{
		  		if((temp = asc2nib(t_frame[i])) > 0x0F)
		  		{
				    return 1;
				}
		  		cf->can_id |= (temp << (7-i)*4);
			}
			if(!(cf->can_id & CAN_ERR_FLAG))
			{
		  		cf->can_id |= CAN_EFF_FLAG;
			}
		} else 
		{
			return 1;
		}

		for (i=0, dlc=0; i<8; i++)
		{
			if(t_frame[idx] == DATA_SEPERATOR)
			{
		  		idx++;
			}
			if(idx >= len)
			{
		  		break;
			}
			if((temp = asc2nib(t_frame[idx++])) > 0x0F)
			{
		  		return 1;
			}
			cf->data[i] = (temp << 4);
			if((temp = asc2nib(t_frame[idx++])) > 0x0F)
			{
		  		return 1;
			}
			cf->data[i] |= temp;
			dlc++;
		}
		cf->can_dlc = dlc;

		return 0;
	}

	unsigned int parseResponseID(char* response)
	{
	  unsigned int retID;

	  char ch_id[4];
	  for(int i=0; i<3; i++)
	  {
	    ch_id[i] = response[i];
	  }
	  retID = strtoul(ch_id,nullptr,16);

	  return retID;

	}

	unsigned long long parseResponseMSG(char* response)
	{
	  unsigned long long retMSG;

	  char ch_msg[17];
	  for(int i=0; i<16; i++)
	  {
	    ch_msg[i] = response[i+4];
	  }
	  retMSG = strtoul(ch_msg,nullptr,16);

	  return retMSG;
	}
};

#endif