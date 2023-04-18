
String encrypt(String str){

unsigned int i ;
  
      for(i = 0; (i < 100 && str[i] != '\0'); i++){
            str[i] = str[i] - 15; //the key for encryption is 3 that is added to ASCII value


      }

      return str;

}
void encryptChars(char str[35]){

unsigned int i ;
  
      for(i = 0; (i < 35 && str[i] != '\0'); i++){
        if( str[i] == '-'){
          str[i] = 'a';
        }else if( str[i] == '.' || str[i] == 't' || str[i] == 'x'){
          
        }else{
          // for the rest of numbers
            str[i] = str[i] +18; //the key for encryption is 18 that is added to ASCII value
            }

      }

     // return str;

}


String decrypt(String str){

unsigned int i ;
  
      for(i = 0; (i < 100 && str[i] != '\0'); i++){
            str[i] = str[i] + 15; //the key for encryption is 3 that is added to ASCII value


      }

      return str;

}

void decryptChars(char str[35]){

unsigned int i ;
  
     for(i = 0; (i < 35 && str[i] != '\0'); i++){
        if( str[i] == 'a'){
          str[i] ='-';
        }else if( str[i] == '.' || str[i] == 't' || str[i] == 'x'){
          
        }else{
          // for the rest of numbers
            str[i] = str[i] -18; //the key for encryption is 3 that is added to ASCII value
            }

      }

     // return str;

}







void addCurrMonthsToSD(){


String zero = encrypt("0");
      int lenoo = zero.length()+1;
  char zeroChars[lenoo];
   zero.toCharArray(zeroChars, lenoo);

     now = rtc.now();

for(int i = 0 ; i< len(SdIds) ; i++){


    String yearString = String(now.year(), DEC);
      int lenee = yearString.length()+1;
  char yearChars[lenee];
   yearString.toCharArray(yearChars, lenee);

    String monthString = String(now.month(), DEC);
      int lenww = monthString.length()+1;
  char monthChars[lenww];
   monthString.toCharArray(monthChars, lenww);

    char path[65] = "/d/d.1/";
    // Serial.print("turned OFF  2.2" );
    strcat(path,SdIds[i]);
    //Serial.print("turned OFF  2.3" );
    strcat(path,"/a/");
    char temp[35] = "";
    strcat(temp,yearChars);
    strcat(temp,"-");
    strcat(temp,monthChars);
    strcat(temp,".txt");
    encryptChars(temp);
   
   
    strcat(path,temp);

    if(!SD.exists(path)){
    writeFile(SD,path,zeroChars);}


}
}



void addPrevAndNextMonthsToSD(){
       now = rtc.now();
      int currMonth =  now.month();
      int prevMonth = 0;
      int nextMonth = 0;

      int currYear =  now.year();
      int prevYear = 0;
      int nextYear = 0;


      if(currMonth >1 && currMonth <12){
        prevMonth = currMonth - 1;
      prevYear =   currYear;
      nextMonth =  currMonth + 1;
      nextYear = currYear;
      }else if(currMonth ==1) {
        prevMonth = 12;
        prevYear =   currYear - 1;
        nextMonth =  currMonth + 1;
        nextYear = currYear;
      }else if (currMonth ==12){
        prevMonth = currMonth - 1;
        prevYear =   currYear;
        nextMonth =  1;
        nextYear = currYear+1;
      }

String zero = encrypt("0");
      int lenoo = zero.length()+1;
  char zeroChars[lenoo];
   zero.toCharArray(zeroChars, lenoo);



for(int i = 0 ; i< len(SdIds) ; i++){

     now = rtc.now();
    String yearString = String(prevYear, DEC);
      int lenee = yearString.length()+1;
  char yearChars[lenee];
   yearString.toCharArray(yearChars, lenee);

    String monthString = String(prevMonth, DEC);
      int lenww = monthString.length()+1;
  char monthChars[lenww];
   monthString.toCharArray(monthChars, lenww);

   
    String yearString2 = String(nextYear, DEC);
      int lenee2 = yearString2.length()+1;
  char yearChars2[lenee2];
   yearString2.toCharArray(yearChars2, lenee2);

    String monthString2 = String(nextMonth, DEC);
      int lenww2 = monthString2.length()+1;
  char monthChars2[lenww2];
   monthString2.toCharArray(monthChars2, lenww2);




    char path[65] = "/d/d.1/";
    // Serial.print("turned OFF  2.2" );
    strcat(path,SdIds[i]);
    //Serial.print("turned OFF  2.3" );
    strcat(path,"/a/");
    char temp[35] = "";
    strcat(temp,yearChars);
    strcat(temp,"-");
    strcat(temp,monthChars);
    strcat(temp,".txt");
    encryptChars(temp);
   
   
    strcat(path,temp);


        char path2[65] = "/d/d.1/";
    // Serial.print("turned OFF  2.2" );
    strcat(path2,SdIds[i]);
    //Serial.print("turned OFF  2.3" );
    strcat(path2,"/a/");
    char temp2[35] = "";
    strcat(temp2,yearChars2);
    strcat(temp2,"-");
    strcat(temp2,monthChars2);
    strcat(temp2,".txt");
    encryptChars(temp2);
   
   
    strcat(path2,temp2);

    if(!SD.exists(path)){
    writeFile(SD,path,zeroChars);}
    
    if(!SD.exists(path2)){
    writeFile(SD,path2,zeroChars);}





}
}
