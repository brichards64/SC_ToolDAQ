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


int Canbus::GetTriggerDac0()
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
		//
	}else
	{
		fprintf(stderr, "No response from LVHV after DAC0 check\n");
		return 5;		
	}
}

int Canbus::GetTriggerDac1()
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
		//
	}else
	{
		fprintf(stderr, "No response from LVHV after DAC1 check\n");
		return 5;		
	}
}

int Canbus::SetTriggerDac0()
{
	unsigned int id = 0x0AB;
	unsigned long long msg = 0x0000000000000000;
	int retval;

	msg = msg;

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
		//
	}else
	{
		fprintf(stderr, "No response from LVHV after DAC0 check\n");
		return 5;		
	}

	return retval;
}

int Canbus::SetTriggerDac1()
{
	unsigned int id = 0x0DE;
	unsigned long long msg = 0x0000000000000000;
	int retval;

	msg = msg;

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
		//
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
		temp_hex = (t_temp << 16) >> 50;
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
		msg = 0x0000000000000000;
		retval = 1;
	}else{
		id = 0x030;
		msg = 0x0000000000000000;
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
	unsigned int id = 0x050;
	unsigned long long msg = 0x0000000000000000;
	int retval;
	float vset;

	if(volts > HV_MAX)
  	{
    	vset = HV_MAX;
  	}else
  	{
  		vset = volts;
  	}

	float vpct = vset / C40N_MAX;
	printf("  fraction of max HV output (4kV) = %f\n", vpct);
	float dac_vout = vpct * DAC_VMAX;
	printf("  DAC output voltage = %f\n", dac_vout);

	// convert into DAC input code
	int k = 0;
	k = (int)(pow(2,12) * dac_vout / DAC_VREF);
	//printf("DEBUG:  k = %d,  k = %X (hex),  k << 3 = %X (hex)\n", k, k, (k<<3));

  	unsigned long long tmp;
  	stringstream ss;
  	ss << std::hex << (k<<3);
  	tmp = std::stoull(ss.str(),nullptr,16);

	msg = msg | (tmp<<48);
	printf("0x%016llx\n", msg);

	//Ask for sensor data
	if(createCanFrame(id,msg,&frame)){
		fprintf(stderr, "HV: Wrong format!\n\n");
		return 2;
	}
	if ((nbytes = write(s, &frame, sizeof(frame))) != sizeof(frame)) {
		fprintf(stderr, "HV: Write error!\n\n");
		return 3;
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
	unsigned long long msg = 0x0000000000000000;
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
		msg = 0x0000000000000000;
		retval = 1;
	}else{
		id = 0x010;
		msg = 0x0000000000000000;
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
	unsigned long long msg = 0x0000000000000000;
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



