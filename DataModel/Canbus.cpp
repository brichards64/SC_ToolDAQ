#include <Canbus.h>

Canbus::Canbus(){};

bool Canbus::Connect(){ 
	s = socket(PF_CAN,SOCK_RAW,CAN_RAW);
	memset(&addr, 0, sizeof(addr));
	
	strcpy(ifr.ifr_name, "can0");
	ioctl(s, SIOCGIFINDEX, &ifr);
	
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	
	bind(s,(struct sockaddr *)&addr, sizeof(addr));
	
	return true;
}

bool Canbus::Disconnect(){ 
	close(s);
	return true;
}

bool Canbus::GetLeak(){ 

	return true;
}

float Canbus::GetLight(){ 

	return true;
}


float Canbus::GetTriggerDac0(float VREF)
{
	unsigned int id = 0x0BC;
	unsigned long long msg = 0x0000000000000000;

	//Ask for sensor data
	if(createCanFrame(id,msg,&frame)!=0){
		fprintf(stderr, "DAC0: Wrong format!\n\n");
		return 2;
	}
	if ((nbytes = write(s, &frame, sizeof(frame))) != sizeof(frame)) {
		fprintf(stderr, "DAC0: Write error!\n\n");
		return 3;
	}

	//Recieve sensor data 
	char rec_id[5];
	char rec_temp[3];
	char *rec_message; rec_message = (char*) malloc(64);
	nbytes=0;
	while(nbytes<=0){
		if((nbytes = read(s, &frame, sizeof(struct can_frame)))<0){
			fprintf(stderr, "DAC0: Read error!\n\n");	
			return 4;
		}
		sprintf(rec_id,"%03X%c",frame.can_id,'#');
		rec_id[5] = '\0';
		strcpy(rec_message,rec_id);
		unsigned int num =  frame.can_dlc;
		for (int i = 0; i < num; i++){
			sprintf(rec_temp,"%02X",frame.data[i]);
			strcat(rec_message,rec_temp);
		}		
	}

	//back parse message to state
	unsigned int retID = parseResponseID(rec_message);
	unsigned long long retMSG = parseResponseMSG(rec_message);	

	if(retID == 0x0CB)
	{
		if((retMSG>>56)==0xC0)
		{
			unsigned int value = (retMSG & 0x00FFF00000000000) >> 44;
			float result = value*VREF/4095;

			return result;
		}
	}else
	{
		fprintf(stderr, "No response from LVHV after DAC0 check\n");
		return 5;		
	}
}

float Canbus::GetTriggerDac1(float VREF)
{
	unsigned int id = 0x0EF;
	unsigned long long msg = 0x0000000000000000;

	//Ask for sensor data
	if(createCanFrame(id,msg,&frame)!=0){
		fprintf(stderr, "DAC1: Wrong format!\n\n");
		return 2;
	}
	if ((nbytes = write(s, &frame, sizeof(frame))) != sizeof(frame)) {
		fprintf(stderr, "DAC1: Write error!\n\n");
		return 3;
	}

	//Recieve sensor data 
	char rec_id[5];
	char rec_temp[3];
	char *rec_message; rec_message = (char*) malloc(64);
	nbytes=0;
	while(nbytes<=0){
		if((nbytes = read(s, &frame, sizeof(struct can_frame)))<0){
			fprintf(stderr, "DAC1: Read error!\n\n");	
			return 4;
		}
		sprintf(rec_id,"%03X%c",frame.can_id,'#');
		rec_id[5] = '\0';
		strcpy(rec_message,rec_id);
		unsigned int num =  frame.can_dlc;
		for (int i = 0; i < num; i++){
			sprintf(rec_temp,"%02X",frame.data[i]);
			strcat(rec_message,rec_temp);
		}		
	}

	//back parse message to state
	unsigned int retID = parseResponseID(rec_message);
	unsigned long long retMSG = parseResponseMSG(rec_message);	

	if(retID == 0x0FE)
	{
		if((retMSG>>56)==0xC0)
		{
			unsigned int value = (retMSG & 0x00FFF00000000000) >> 44;
			float result = value*VREF/4095;

			return result;
		}
	}else
	{
		fprintf(stderr, "No response from LVHV after DAC1 check\n");
		return 5;		
	}
}

int Canbus::SetTriggerDac0(float threshold, float VREF)
{
	unsigned int id = 0x0AB;
	unsigned long long msg = 0x0000000000000000;
	int retval;

	if(threshold>VREF)
	{
		threshold = VREF;
	}

  	int k = 0;
  	k = (int)(threshold * 4095. / VREF);

	stringstream ss;
	ss << std::hex << (k);
	unsigned long long tmp = 0x0000000000000000;
	tmp = std::stoull(ss.str(),nullptr,16);

	msg = msg | (tmp<<48);

	//Ask for sensor data
	if(createCanFrame(id,msg,&frame)!=0){
		fprintf(stderr, "DAC0: Wrong format!\n\n");
		return 2;
	}
	if ((nbytes = write(s, &frame, sizeof(frame))) != sizeof(frame)) {
		fprintf(stderr, "DAC0: Write error!\n\n");
		return 3;
	}

	//Recieve sensor data 
	char rec_id[5];
	char rec_temp[3];
	char *rec_message; rec_message = (char*) malloc(64);
	nbytes=0;
	while(nbytes<=0){
		if((nbytes = read(s, &frame, sizeof(struct can_frame)))<0){
			fprintf(stderr, "DAC0: Read error!\n\n");	
			return 4;
		}
		sprintf(rec_id,"%03X%c",frame.can_id,'#');
		rec_id[5] = '\0';
		strcpy(rec_message,rec_id);
		unsigned int num =  frame.can_dlc;
		for (int i = 0; i < num; i++){
			sprintf(rec_temp,"%02X",frame.data[i]);
			strcat(rec_message,rec_temp);
		}		
	}

	//back parse message to state
	unsigned int retID = parseResponseID(rec_message);
	unsigned long long retMSG = parseResponseMSG(rec_message);	

	//Analize response
	if(retID == 0x0BA)
	{
		if((retMSG>>56)==0xC0)
		{
			unsigned int value = (retMSG & 0x00FFF00000000000) >> 44;
			float result = value*VREF/4095;
			if(result == threshold)
			{
				return 0;
			}else
			{
				std::cout << "Result was " << result << std::endl;
				return 6;
			}
		}
	}else
	{
		fprintf(stderr, "No response from LVHV after DAC0 check\n");
		return 5;		
	}

	return retval;
}

int Canbus::SetTriggerDac1(float threshold, float VREF)
{
	unsigned int id = 0x0DE;
	unsigned long long msg = 0x0000000000000000;
	int retval;

	if(threshold>VREF)
	{
		threshold = VREF;
	}

  	int k = 0;
  	k = (int)(threshold * 4095. / VREF);

	stringstream ss;
	ss << std::hex << (k);
	unsigned long long tmp = 0x0000000000000000;
	tmp = std::stoull(ss.str(),nullptr,16);

	msg = msg | (tmp<<48);

	//Ask for sensor data
	if(createCanFrame(id,msg,&frame)!=0){
		fprintf(stderr, "DAC1: Wrong format!\n\n");
		return 2;
	}
	if ((nbytes = write(s, &frame, sizeof(frame))) != sizeof(frame)) {
		fprintf(stderr, "DAC1: Write error!\n\n");
		return 3;
	}

	//Recieve sensor data 
	char rec_id[5];
	char rec_temp[3];
	char *rec_message; rec_message = (char*) malloc(64);
	nbytes=0;
	while(nbytes<=0){
		if((nbytes = read(s, &frame, sizeof(struct can_frame)))<0){
			fprintf(stderr, "DAC1: Read error!\n\n");	
			return 4;
		}
		sprintf(rec_id,"%03X%c",frame.can_id,'#');
		rec_id[5] = '\0';
		strcpy(rec_message,rec_id);
		unsigned int num =  frame.can_dlc;
		for (int i = 0; i < num; i++){
			sprintf(rec_temp,"%02X",frame.data[i]);
			strcat(rec_message,rec_temp);
		}		
	}

	//back parse message to state
	unsigned int retID = parseResponseID(rec_message);
	unsigned long long retMSG = parseResponseMSG(rec_message);	

	//Analize response
	if(retID == 0x0ED)
	{
		if((retMSG>>56)==0xC0)
		{
			unsigned int value = (retMSG & 0x00FFF00000000000) >> 44;
			float result = value*VREF/4095;
			if(result == threshold)
			{
				return 0;
			}else
			{
				std::cout << "Result was " << result << std::endl;
				return 6;
			}
		}
	}else
	{
		fprintf(stderr, "No response from LVHV after DAC1 check\n");
		return 5;		
	}

	return retval;
}

vector<float> Canbus::GetTemp()
{ 	
	vector<float> RHT;
	unsigned int id = 0x123;
	unsigned long long msg = 0x0000000000000000;

	//Ask for sensor data
	if(createCanFrame(id,msg,&frame)!=0){
		fprintf(stderr, "RHT: Wrong format!\n\n");
		return {2};
	}
	if ((nbytes = write(s, &frame, sizeof(frame))) != sizeof(frame)) {
		fprintf(stderr, "RHT: Write error!\n\n");
		return {3};
	}

	//Recieve sensor data 
	char rec_id[5];
	char rec_temp[3];
	char *rec_message; rec_message = (char*) malloc(64);
	nbytes=0;
	while(nbytes<=0){
		if((nbytes = read(s, &frame, sizeof(struct can_frame)))<0){
			fprintf(stderr, "HV: Read error!\n\n");	
			return {4};
		}
		sprintf(rec_id,"%03X%c",frame.can_id,'#');
		rec_id[5] = '\0';
		strcpy(rec_message,rec_id);
		unsigned int num =  frame.can_dlc;
		for (int i = 0; i < num; i++){
			sprintf(rec_temp,"%02X",frame.data[i]);
			strcat(rec_message,rec_temp);
		}		
	}

	//back parse message to state
	unsigned int retID = parseResponseID(rec_message);
	unsigned long long retMSG = parseResponseMSG(rec_message);
	unsigned long long t_temp;
	unsigned int temp_hex;
	unsigned long long t_hum;
	unsigned int hum_hex;

	if(retID == 0x321)
	{
		t_temp = retMSG & 0x0000FFFC00000000;
		temp_hex = t_temp >> 32;
		t_hum = retMSG & 0x3FFF000000000000;
		hum_hex = t_hum >> 48;

		float T = (temp_hex/(pow(2,14)-2))*165-40;
		float H = (hum_hex/(pow(2,14)-2))*100;

		RHT.push_back(T);
		RHT.push_back(H);

		cout << "H=" << H << " T=" << T << endl; 
	}else
	{
		fprintf(stderr, "No response from LVHV after RHT check\n");
		return {5};
	}

	return RHT;
}

//sends a can message to turn on/off the HV
//returns:
//0: false = off
//1: true = on
//2: error on create message
//3: error on write
int Canbus::SetHV_ONOFF(bool state){ 
	unsigned int id;
	unsigned long long msg;
	int retval;
	
	if(state==true){
		id = 0x040;
		msg = 0xBEEFDEAD00000000;
		retval = 1;
	}else{
		id = 0x030;
		msg = 0x00000000BEEFDEAD;
		retval = 0;
	}

	//Ask for sensor data
	if(createCanFrame(id,msg,&frame)!=0){
		fprintf(stderr, "HV: Wrong format!\n\n");
		return 2;
	}
	if ((nbytes = write(s, &frame, sizeof(frame))) != sizeof(frame)) {
		fprintf(stderr, "HV: Write error!\n\n");
		return 3;
	}

	//Recieve sensor data 
	char rec_id[5];
	char rec_temp[3];
	char *rec_message; rec_message = (char*) malloc(64);
	nbytes=0;
	while(nbytes<=0){
		if((nbytes = read(s, &frame, sizeof(struct can_frame)))<0){
			fprintf(stderr, "HV: Read error!\n\n");	
			return 4;
		}
		sprintf(rec_id,"%03X%c",frame.can_id,'#');
		rec_id[5] = '\0';
		strcpy(rec_message,rec_id);
		unsigned int num =  frame.can_dlc;
		for (int i = 0; i < num; i++){
			sprintf(rec_temp,"%02X",frame.data[i]);
			strcat(rec_message,rec_temp);
		}		
	}

	//back parse message to state
	unsigned int retID = parseResponseID(rec_message);
	unsigned long long retMSG = parseResponseMSG(rec_message);

	if(retID == 0x041)
	{	
		if(retMSG == 0x0001000100010001)
		{
			return 1;
		}else
		{
			fprintf(stderr, "Response doesn't make sense!\n");
			return 5;	
		}
	}else if(retID == 0x031)
	{
		if(retMSG == 0x0000000000000000)
		{
			return 0;
		}else
		{
			fprintf(stderr, "Response doesn't make sense!\n");
			return 5;	
		}
	}else
	{
		fprintf(stderr, "No response from LVHV after HV check\n");
		return 5;
	}

	return retval;
}

//sends a can message to set the HV voltage
//returns:
//0: false = done with fail
//1: true = done successfully
//2: error on create message
//3: error on write
int Canbus::SetHV_voltage(float volts){ 

	int retval=1;
	float sign = -1.0;
	float v_pre, v_tmp, v_diff, vset, vpct, dac_vout;
	unsigned int id;
	unsigned long long msg;
	int k;
	unsigned long long tmp;
	

	if(volts > HV_MAX)
	{
		volts = HV_MAX;
		std::cout << "Max voltage set" << std::endl;
	}

	//take volts from input and 
	v_pre = get_HV_volts;
    if (volts > v_pre)
    {
      sign = 1.0;
    }	
    v_tmp = v_pre;
    v_diff = abs(volts-v_tmp);
    
	while(v_tmp != volts)
	{
		//std::cout << volts << "!=" << v_tmp << std::endl;
		if(v_diff < 50) // check if close to final voltage
		{
			v_tmp += sign*v_diff;
		}
		else // increment by DV volts
		{
			v_tmp += sign*50;
		}
		v_diff = fabs(volts - v_tmp);

		id = 0x050;
		msg = 0x0000000000000000;
	
		vset = v_tmp;

		vpct = vset / C40N_MAX;
		//printf("  fraction of max HV output (4kV) = %f\n", vpct);
		dac_vout = vpct * DAC_VMAX;
		//printf("  DAC output voltage = %f\n", dac_vout);

		// convert into DAC input code
		k = 0;
		k = (int)(pow(2,12) * dac_vout / DAC_VREF);
		//printf("DEBUG:  k = %d,  k = %X (hex),  k << 3 = %X (hex)\n", k, k, (k<<3));
		stringstream ss;
		ss << std::hex << (k<<3);
		tmp = 0x0000000000000000;
		tmp = std::stoull(ss.str(),nullptr,16);
		
		msg = msg | (tmp<<48);

		//Ask for sensor data
		if(createCanFrame(id,msg,&frame)!=0)
		{
			fprintf(stderr, "HV: Wrong format!\n\n");
			return 2;
		}
		if ((nbytes = write(s, &frame, sizeof(frame))) != sizeof(frame)) 
		{
			fprintf(stderr, "HV: Write error!\n\n");
			return 3;
		}
		usleep(1000);
	}

	return retval;
}




//sends a can message to get the HV state
//returns:
//0: false = off
//1: true = on
//2: error on create message
//3: error on write
//4: error on read
//5: error on message interprete
//6: Why?
int Canbus::GetHV_ONOFF(){ 
	unsigned int id = 0x042;
	unsigned long long msg = 0x0000BEEFDEAD0000;
	int HV_state=6;
	
	//Ask for sensor data
	if(createCanFrame(id,msg,&frame)!=0){
		fprintf(stderr, "HV: Wrong format!\n\n");
		return 2;
	}
	if ((nbytes = write(s, &frame, sizeof(frame))) != sizeof(frame)) {
		fprintf(stderr, "HV: Write error!\n\n");
		return 3;
	}
		
	//Recieve sensor data 
	char rec_id[5];
	char rec_temp[3];
	char *rec_message; rec_message = (char*) malloc(64);
	nbytes=0;
	while(nbytes<=0){
		if((nbytes = read(s, &frame, sizeof(struct can_frame)))<0){
			fprintf(stderr, "HV: Read error!\n\n");	
			return 4;
		}

		sprintf(rec_id,"%03X%c",frame.can_id,'#');
		rec_id[5] = '\0';
		strcpy(rec_message,rec_id);
		unsigned int num =  frame.can_dlc;
		for (int i = 0; i < num; i++){
			sprintf(rec_temp,"%02X",frame.data[i]);
			strcat(rec_message,rec_temp);
		}		
	}
	
	//back parse message to state
	unsigned int retID = parseResponseID(rec_message);
	unsigned long long retMSG = parseResponseMSG(rec_message);

	if(retID == 0x420)
	{	
		if(retMSG == 0x0000000000000000)
		{
			return 0;
		}else if(retMSG == 0x0001000100010001)
		{
			return 1;
		}else
		{
			fprintf(stderr, "Response doesn't make sense!\n");
			return 5;	
		}
	}else
	{
		fprintf(stderr, "No response from LVHV after HV check\n");
		return 5;
	}

	return HV_state;
}

//sends a can message to turn on/off the LV
//returns:
//0: false = off
//1: true = on
//2: error on create message
//3: error on write
//4: error on read
//5: error on message interprete
//6: Why?
int Canbus::SetLV(bool state){ 
	unsigned int id;
	unsigned long long msg;
	int retval;
	
	if(state==true){
		id = 0x020;
		msg = 0xDEADBEEF00000000;
		retval = 1;
	}else{
		id = 0x010;
		msg = 0x00000000DEADBEEF;
		retval = 0;
	}

	//Ask for sensor data
	if(createCanFrame(id,msg,&frame)!=0){
		fprintf(stderr, "LV: Wrong format!\n\n");
		return 2;
	}
	if ((nbytes = write(s, &frame, sizeof(frame))) != sizeof(frame)) {
		fprintf(stderr, "LV: Write error!\n\n");
		return 3;
	}

	//Recieve sensor data 
	char rec_id[5];
	char rec_temp[3];
	char *rec_message; rec_message = (char*) malloc(64);
	nbytes=0;
	while(nbytes<=0){
		if((nbytes = read(s, &frame, sizeof(struct can_frame)))<0){
			fprintf(stderr, "LV: Read error!\n\n");	
			return 4;
		}

		sprintf(rec_id,"%03X%c",frame.can_id,'#');
		rec_id[5] = '\0';
		strcpy(rec_message,rec_id);
		unsigned int num =  frame.can_dlc;
		for (int i = 0; i < num; i++){
			sprintf(rec_temp,"%02X",frame.data[i]);
			strcat(rec_message,rec_temp);
		}		
	}

	//back parse message to state
	unsigned int retID = parseResponseID(rec_message);
	unsigned long long retMSG = parseResponseMSG(rec_message);

	if(retID == 0x021)
	{	
		if(retMSG == 0x0001000100010001)
		{
			return 1;
		}else
		{
			fprintf(stderr, "Response doesn't make sense!\n");
			return 5;	
		}
	}else if(retID == 0x011)
	{
		if(retMSG == 0x0000000000000000)
		{
			return 0;
		}else
		{
			fprintf(stderr, "Response doesn't make sense!\n");
			return 5;	
		}
	}else
	{
		fprintf(stderr, "No response from LVHV after LV check\n");
		return 5;
	}

	return retval;
}

//sends a can message to get the LV state
//returns:
//0: false = off
//1: true = on
//2: error on create message
//3: error on write
//4: error on read
//5: error on message interprete
//6: Why?
int Canbus::GetLV(){ 
	unsigned int id = 0x022;
	unsigned long long msg = 0x0000DEADBEEF0000;
	int LV_state=6;
	
	//Ask for sensor data
	if(createCanFrame(id,msg,&frame)!=0){
		fprintf(stderr, "LV: Wrong format!\n\n");
		return 2;
	}
	if ((nbytes = write(s, &frame, sizeof(frame))) != sizeof(frame)) {
		fprintf(stderr, "LV: Write error!\n\n");
		return 3;
	}
		
	//Recieve sensor data 
	char rec_id[5];
	char rec_temp[3];
	char *rec_message; rec_message = (char*) malloc(64);
	nbytes=0;
	while(nbytes<=0){
		if((nbytes = read(s, &frame, sizeof(struct can_frame)))<0){
			fprintf(stderr, "LV: Read error!\n\n");	
			return 4;
		}

		sprintf(rec_id,"%03X%c",frame.can_id,'#');
		rec_id[5] = '\0';
		strcpy(rec_message,rec_id);
		unsigned int num =  frame.can_dlc;
		for (int i = 0; i < num; i++){
			sprintf(rec_temp,"%02X",frame.data[i]);
			strcat(rec_message,rec_temp);
		}		
	}
	
	//back parse message to state
	unsigned int retID = parseResponseID(rec_message);
	unsigned long long retMSG = parseResponseMSG(rec_message);

	if(retID == 0x220)
	{	
		if(retMSG == 0x0000000000000000)
		{
			return 0;
		}else if(retMSG == 0x0001000100010001)
		{
			return 1;
		}else
		{
			fprintf(stderr, "Response doesn't make sense!\n");
			return 5;	
		}
	}else
	{
		fprintf(stderr, "No response from LVHV after LV check\n");
		return 5;
	}

	return LV_state;
}

int Canbus::SetRelay(int idx, bool state){
	wiringPiSetup();
	pinMode(RLY1, OUTPUT);
	pinMode(RLY2, OUTPUT);
	pinMode(RLY3, OUTPUT);
	int ch;
	int status = 0;

	switch(idx){
		case 1:
			ch = RLY1;
			break;
		case 2:
			ch = RLY2;
			break;
		case 3:
			ch = RLY3;
			break;
		default :
			printf(" Invalid relay channel! \n");
			return status;
	}
	
	digitalWrite(ch, state);
	if((digitalRead(ch)) == state)
	{
		if(state==true){
			status = 1;
		}else{
			status = 0;
		}
		printf("Relay %d\n", idx);
	}

	return status;
}

int Canbus::GetRelay(int idx){
	wiringPiSetup();
	pinMode(RLY1, OUTPUT);
	pinMode(RLY2, OUTPUT);
	pinMode(RLY3, OUTPUT);
	int ch;
	int status = 0;

	switch(idx){
		case 1:
			ch = RLY1;
			break;
		case 2:
			ch = RLY2;
			break;
		case 3:
			ch = RLY3;
			break;
		default :
			printf(" Invalid relay channel! \n");
			return status;
	}
	bool retval = digitalRead(ch);
	if(retval == true)
	{
		status = 1;
		printf("Relay %d\n", idx);
	}else if(retval == false){
		status = 0;
	}

	return status;
}



