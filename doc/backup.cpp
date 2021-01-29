  //translates hex to dec
  float parse_data(char *message){
    int len_short = strlen(message);
    int i,j,m,n,k,p,q,number;
    int len_long;
    char *ident; ident = (char *)malloc(4);
    char *msg_short; msg_short=(char *)malloc(8);
    char *msg; msg=(char *)malloc(33);
    char *e; e=(char *)malloc(9);
    char *M; M=(char *)malloc(25);
    char *tem;
    char temp[5];
    int sign;
    int exp;
    float Mantisse = 1;
    float result;

    for(i=0; i<3; i++){
      ident[i] = message[i];
    }
    ident[i] = {'\0'};
    
    for(j=4; j<len_short; j++){
      msg_short[j-4] = message[j];
    }
    msg_short[j]={'\0'}; //std::cout << msg_short << std::endl;

    for(p=0,q=0; p<=(len_short-4)*4-4; p+=4){ 
      int t_num = msg_short[q];
      if(msg_short[q] >= '0' && msg_short[q] <= '9'){ 
        number = t_num - 48;
      }else if(msg_short[q] >= 'a' && msg_short[q] <= 'j'){
        number = t_num - 87;
      }else{
        number = t_num - 55;
      }
      tem = dec2bin(number);
      msg[p+0] = tem[0];
      msg[p+1] = tem[1];
      msg[p+2] = tem[2];
      msg[p+3] = tem[3];
      q++; 
    }
    msg[p+3] = {'\0'};	
    //std::cout << msg << std::endl;
    
    len_long = strlen(msg);	
    if(msg[0]=='0'){
      sign = 0;
    }else if(msg[0] == '1'){
      sign = 1;
    }
    
    for(n=1; n<9; n++){
      e[n-1] = msg[n];
    }
    e[n-1] = {'\0'};
    
    exp = bin2dec(e)-127;
    //std::cout << exp << std::endl;
    for(m=9; m<(len_long); m++){
      M[m-9] = msg[m];
    }
    M[m-9] = '0';
    M[m-8] = {'\0'};
    for(k=0; k<24; k+=4){
      temp[0] = M[k+0]; 
      temp[1] = M[k+1];	
      temp[2] = M[k+2]; 
      temp[3] = M[k+3]; 
      temp[4] = {'\0'};
      Mantisse += bin2dec(temp)*(1/pow(16,k/4+1));	
    }
    //std::cout << Mantisse << std::endl;
    result = pow(-1,sign)*Mantisse*pow(2,exp);		
    //std::cout << result << std::endl;
    return result;	
  }

    //converts binary to decimal
  int bin2dec(char* number){
    int len = strlen(number);
    int dec = 0;
    int exp;
    
    for(int i=0; i<len; i++){
      exp = number[i];
      dec += pow(2,(len-1)-i)*(exp-48);
    }
    return dec;
  }
  
    
  //converts int-hex to bin
  char* hex2bin(char* msg){
    int p,q,number;
    int len = strlen(message);
    char *msg_bin; msg_bin=(char *)malloc(16);
    char *temp;
    for(p=0,q=0; p<=len*4-4; p+=4){ 
      int t_num = msg[q];
      if(msg[q] >= '0' && msg[q] <= '9'){ 
        number = t_num - 48;
      }else if(msg[q] >= 'a' && msg[q] <= 'j'){
        number = t_num - 87;
      }else{
        number = t_num - 55;
      }
      temp = dec2bin(number);
      msg_bin[p+0] = temp[0];
      msg_bin[p+1] = temp[1];
      msg_bin[p+2] = temp[2];
      msg_bin[p+3] = temp[3];
      q++; 
    }
    msg_bin[p+3] = {'\0'};  
    
    return msg_bin;
  }

  //converts integer to binary
  char* dec2bin(int number){
    int i, j, c, temp_div;
    char t_bin_div[32];

    i=0;
    temp_div = number;
    while(temp_div!=0){
      if(temp_div%2==0){
        t_bin_div[i] = '0';
      }else{
        t_bin_div[i] = '1';
      } 
      temp_div = temp_div/2;
      i++;
    }
    
    if(i<4){
      for(int k=i; k<4; k++){
        t_bin_div[k] = '0';
        i++;
      }
    }
    if(i>4 && i<8){
        for(int k=i; k<8; k++){
        t_bin_div[k] = '0';
        i++;
      }
    }    
    
    char bin_div[i]; 
    for(j=i-1, c=0; j>=0; j--){
      bin_div[c] = t_bin_div[j];
      c++;
    }
    bin_div[c] = '\0';
    char *buff_msg = new char[c];
    strcpy(buff_msg,bin_div);
    //std::cout << "bin_div " << buff_msg << std::endl;
    return buff_msg;  
  }

  //converts decimal to binary
  char* pdec2bin(float number){
    int i; 
    char t_bin_dec[32];
    float temp_dec;
    if(number<0){
      number=-number;
    }
    i = 0;
    temp_dec = 2*number;
    while(i<32){
      if(temp_dec>=1 && temp_dec<2){
        t_bin_dec[i]='1';
        temp_dec = 2*(temp_dec-1);
      }else if(temp_dec<1 && temp_dec>0){
        t_bin_dec[i]='0';
        temp_dec = temp_dec*2;
      }
      i++;  
      if (temp_dec==0){break;} 
    } 
    t_bin_dec[i] = {'\0'}; 
    char * bin_dec = new char[i];
    strcpy(bin_dec,t_bin_dec);  
    //std::cout << "bin_dec " << bin_dec << std::endl;
    return bin_dec;
  }