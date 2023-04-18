

void sfcodeON(int c ,int lenx , int protx){
Serial.print("sfcodeON running on             Core#");
    Serial.println(xPortGetCoreID());


for (size_t i = 0; i < len(codeON); ++i) {


  if(c == codeON[i]){
   if(lenx == lenr[i] && protx == protr[i]){ 
    String state = getState(i);
  if(state == "1"){   
  turnON( i , protx , lenx);
   break;

 }
  }
  }

}
}








void sfcodeOFF(int c ,int lenx , int protx){
Serial.print("sfcodeOFF OFF:" );
Serial.print("usernum:" );
Serial.print(currentUserNum);

  if(c == codeOFF[currentUserNum]){
    if(lenx == lenr[currentUserNum] && protx == protr[currentUserNum]){ 

   turnOFF();


    }
  }
  

}









void turnON(int i , int protx , int lenx){
  Serial.print("code matched user number: ");
  Serial.println(i);

   Serial.print("with the same protocol: ");
   Serial.println(protx);

   Serial.println("and the modulation: FSK");

   Serial.print("and the same bit length: ");
   Serial.println(lenx);


   Serial.print("Accumulating Engry consumption to user number:" );
   Serial.println(i);
   currentUser = usernames[i] ;
   currentSdId = SdIds[i];
   currentUserNum = i;
   state = 1;
   energyBalance = 0;
   istimer = 1;
   timerStartp = millis();

   
}

void turnOFF(){
  
    Serial.print("turned OFF  2.1" );

    char path[65] = "/d/d.1/";


    char path2[100] = "/d/d.1/logs/" ;
   // Serial.print("turned OFF  2.2" );
    strcat(path,currentSdId);
    //Serial.print("turned OFF  2.3" );
    strcat(path,"/a/");


     now = rtc.now();
    String yearString = String(now.year(), DEC);
      int lenee = yearString.length()+1;
  char yearChars[lenee];
   yearString.toCharArray(yearChars, lenee);

    String monthString = String(now.month(), DEC);
      int lenww = monthString.length()+1;
  char monthChars[lenww];
   monthString.toCharArray(monthChars, lenww);


    String dayString = String(now.day(), DEC);
      int lenww1 = dayString.length()+1;
  char dayChars[lenww1];
   dayString.toCharArray(dayChars, lenww1);


    String hourString = String(now.hour(), DEC);
      int lenww4 = hourString.length()+1;
  char hourChars[lenww4];
   hourString.toCharArray(hourChars, lenww4);
  

      String minuteString = String(now.minute(), DEC);
      int lenww2 = minuteString.length()+1;
  char minuteChars[lenww2];
   minuteString.toCharArray(minuteChars, lenww2);

   
      String secondString = String(now.second(), DEC);
      int lenww3 = secondString.length()+1;
  char secondChars[lenww3];
   secondString.toCharArray(secondChars, lenww3);


    char temp[35] = "";
    strcat(temp,yearChars);
    strcat(temp,"-");
    strcat(temp,monthChars);
    strcat(temp,".txt");
    encryptChars(temp);

        char temp2[45] = "";
    strcat(temp2,yearChars);
    strcat(temp2,"-");
    strcat(temp2,monthChars);
    strcat(temp2,"-");
    strcat(temp2,dayChars);
    strcat(temp2,".txt");
    encryptChars(temp2);
        strcat(path2,temp2);


    char timeStamp[45] = "";
    strcat(timeStamp,hourChars);
    strcat(timeStamp,"-");
    strcat(timeStamp,minuteChars);
    strcat(timeStamp,"-");
    strcat(timeStamp,secondChars);
   
   
    strcat(path,temp);
   float balance = 0 ;
  String balanceString ="p";
   if(!SD.exists(path)){
     if(!SD.exists(path)){
         writeFile(SD,path,"0");

     /*if(SD.mkdir(path)){
         writeFile(SD,path,"0");
     }else{
        if(SD.mkdir(path)){
         writeFile(SD,path,"0");
     }else{
        if(SD.mkdir(path)){
         writeFile(SD,path,"0");
     }else{
       
     }
     }
     }*/



     }else{
          balanceString = readFileToString(SD,path);
   balanceString = decrypt(balanceString);
  balance = balanceString.toFloat();
     }
   }else{
   balanceString = readFileToString(SD,path);
   balanceString = decrypt(balanceString);
  balance = balanceString.toFloat();
   }

  // balance+=30;
  balance +=energyBalance ;
     Serial.print("Accumulated energy balance:" );
   Serial.println(energyBalance);

   balanceString = String(balance);
  balanceString = encrypt(balanceString);

    /*   STRING TO CHAR*   */ 

  int lenqq = balanceString.length()+1;
  char userBalanceChars[lenqq];
   balanceString.toCharArray(userBalanceChars, lenqq);

   



   
  writeFile(SD,path,userBalanceChars);




 char message[150] ="";
  strcat(message , " ");
 strcat(message , timeStamp);
 strcat(message , " ");
 int lenqq2 = currentUser.length()+1;
char currentUserChars[lenqq2];
currentUser.toCharArray(currentUserChars, lenqq2);
strcat(message , currentUserChars);


char xx2[6];
itoa(energyBalance, xx2, 10);
strcat(message , xx2);
 strcat(message , " \n");


  energyBalance = 0;
   
   if(!SD.exists(path2)){ 
           writeFile(SD,path2,message);

         }else{
           appendFile(SD,path2,message);

         }




  




   //Serial.println(i);
   currentSdId = "0";
   currentUser = "none" ;
   currentUserNum = -1;
   istimer = 0 ;
   state = 0;
}

String getState(int i){
  
      char path[65] = "/d/d.1/";
      //Serial.print("turned OFF  2.2" );
      strcat(path,SdIds[i]);
      //Serial.print("turned OFF  2.3" );
      strcat(path,"/c/s.txt");
      String state = readFileToString(SD,path);




      if(state != "1" && state != "0" ){
        state = "0";
  char* stateChars = "0";
writeFile(SD,path,stateChars);
        } 




      return state ;

}



String getPrepaidState(int i){
  
      char path[65] = "/d/d.2/";
      //Serial.print("turned OFF  2.2" );
      strcat(path,SdIdsPrepaid[i]);
      //Serial.print("turned OFF  2.3" );
      strcat(path,"/c/s.txt");
      String state = readFileToString(SD,path);




      if(state != "1" && state != "0" ){
        state = "0";
  char* stateChars = "0";
writeFile(SD,path,stateChars);
        } 




      return state ;

}



String getPrepaidBalance(int i){
  
      char path[65] = "/d/d.2/";
      //Serial.print("turned OFF  2.2" );
      strcat(path,SdIdsPrepaid[i]);
      //Serial.print("turned OFF  2.3" );
      strcat(path,"/a/b.txt");
      String balance = readFileToString(SD,path);


      return balance ;

}



void writeState(int id,int state){
            char path[65] = "/d/d.1/";
      //Serial.print("turned OFF  2.2" );
      strcat(path,SdIds[id]);
      //Serial.print("turned OFF  2.3" );
      strcat(path,"/c/s.txt");
      char* stateChars = "0";


      if(state == 0){
      stateChars = "0";
      }else if(state == 1){
       stateChars = "1";
      }else{
        stateChars = "0";
      }


      writeFile(SD,path,stateChars);    
}




String writePrepaidBalance(int i,int balanceInt){
  
      char path[65] = "/d/d.2/";
      //Serial.print("turned OFF  2.2" );
      strcat(path,SdIdsPrepaid[i]);
      //Serial.print("turned OFF  2.3" );
      strcat(path,"/a/b.txt");


  String balance = String(balanceInt);
  balance =encrypt(balance);
          /*   STRING TO CHAR*   */ 
  int lenqq = balance.length()+1;
  char balanceChars[lenqq];
   balance.toCharArray(balanceChars, lenqq);



      writeFile(SD,path,balanceChars); 

      return balance ;

}


void writePrepaidState(int id,int state){
            char path[65] = "/d/d.2/";
      //Serial.print("turned OFF  2.2" );
      strcat(path,SdIdsPrepaid[id]);
      //Serial.print("turned OFF  2.3" );
      strcat(path,"/c/s.txt");
      char* stateChars = "0";


      if(state == 0){
      stateChars = "0";
      }else if(state == 1){
       stateChars = "1";
      }else{
        stateChars = "0";
      }


      writeFile(SD,path,stateChars);    
}



void reqCT(){
  
  // put your main code here, to run repeatedly:

  Serial.print("reqCT running on             Core#");
    Serial.println(xPortGetCoreID());
  Serial2.print("x\n");
  Serial.println("sent request: ");
  res = true;
  restime = millis();
  




   while(res) {
     if (Serial2.available())
  {
    /*int number1 = SerialPort.parseFloat();
    int number2 = SerialPort.parseFloat();
    int number3 = SerialPort.parseInt();

    Serial.println("redceived the following:");

    Serial.print(number1);
        Serial.println(",");
    Serial.print(number2);
     Serial.println(",");
    Serial.print(number3);
     Serial.println(",");*/

  String str = Serial2.readStringUntil('\n');
   
   Serial.print("\nreceived: ");
   Serial.println(str);
  

     char Buf[50];
    str.toCharArray(Buf, 50);

   bool good = checkstr(Buf);
  if(good){
char *strings[3]; 


    byte index = 0;
   char *ptr = strtok(Buf, ",");  // delimiter
   while (ptr != NULL && index<3)
   {
      strings[index] = ptr;
      index++;
      ptr = strtok(NULL, ",");
   }

   float CTvals[]= {atof(strings[0]) , atof(strings[1]) , atof(strings[2])} ;



 ctval1 = CTvals[0] ;
  ctval2 = CTvals[1] ;
   ctval3 = CTvals[2] ; 
   
   res = false;
   continouesEmpRes = 0 ;
     atmegaErr= false;


  }else{
     res = false;
     continouesEmpRes++ ;
     atmegaErr= false;
    Serial.print("Failed Receiving an elegible response from atmega: ");
    Serial.println(Buf);
  }



  
    
  
    

 

  }
  
    if (millis() - restime > 110){
     res = false;
     continouesEmpRes++;
     atmegaErr= true;

     Serial.println("Failed Receiving a response from atmega");

   }
  
  }
}





bool checkstr(char Buf[50]){
 

      int y = 0;
      for(int i = 0 ; i<500 ; i++){
       
        
        if(Buf[i] == ','){
          y++; if(y ==3){
          break;
         }
          }
      if(!((Buf[i] >='0' && Buf[i] <='9') || Buf[i] == ',' || Buf[i] =='.')){
        
        return false;
      }
      }
      
      return true;
    

}
