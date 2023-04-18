
//#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <RCSwitch.h>
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"




#include "FS.h"
#include "SD.h"
#include "SPI.h"


#define rf 4

#include "Wire.h"
#include "RTClib.h"

TaskHandle_t Task2;


bool test = 1;
int testIndex=0;



template <class T, size_t N> constexpr size_t len(const T(&)[N]) { return N; }


/* for reqCT  */

bool res = 0;
long unsigned int restime =0;


/*RTC*/
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char month[12][10]= {"January","February","March","April","May","June","July","August","September","October","November","December"};
 


/* Put your SSID & Password */
const char* ssid = "Elva";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

const char* ssid1 = "ProWay";  // Enter SSID here
const char* password1 = "ProwayTormos.6";



/*   errors   */
bool atmegaErr = false;
bool rtcErr = false;
bool sdErr = false;
unsigned int continouesEmpRes = 0 ;


  //Enter Password here
RCSwitch mySwitch = RCSwitch();


/* Put IP Address details */
IPAddress local_ip(192,168,0,1);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);


AsyncWebServer server(80);

uint8_t elvatorRelay = 26 ;





///////
/*
char* SdIds[16] = {"11042" , "11029" , "11023" , "11096" , "11076" , "11074" , "11078" , "11071" , "11001" , "11047" , "11100" , "11011" , "11052" , "11005" , "11045" , "11077"};
String usernames[16] = {"1-a" , "1-b" , "2-a" , "2-b" , "3-a" , "3-b" , "4-a" , "4-b" , "5-a" , "5-b" , "6-a" , "6-b" , "7-a" , "7-b" , "8-a" , "8-b"};



int codeON[16] =  {11042 , 11063 , 11038 , 11051 , 11039 , 11041 , 11020 , 11100 , 11003 , 11033 , 11054 , 11078 , 11005 , 11032 , 11034 , 11093};
int codeOFF[16] = {11023 , 11010 , 11058 , 11037 , 11085 , 11026 , 11025 , 11090 , 11056 , 11045 , 11053 , 11077 , 11095 , 11087 , 11081 , 11011};
int lenr[16]= {24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24};
int protr[16] = {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1};
*/


/*
char* SdIds[16] = {"7098" , "7583" , "8506" , "9966" , "8187" , "5130" , "7312" , "2107" , "1541" , "6305" , "1303" , "4069" , "1468" , "3610" , "3359" , "1050"};
c{"بدران ط9", "نذار ط9" , "حمادة ط8" , "أحمد عساف ط8","نور الدين ط7","ناصر الحاج ط7","أحمد كرنيب ط6","جوني ط6","بوب ط5","مهدي علوية ط5","حسن عسيلي ط4","أمين ط4","يوسف كرنيب ط3","حسين سليم ط3","منذر عسيلي ط2","حسين علوية ط2"};


int codeON[16] =  {39014 , 95883 , 40959 , 3678 , 86590 , 78681 , 73648 , 86205 , 17656 , 8132 , 29829 , 58777 , 9642 , 21232 , 2269 , 63154};
int codeOFF[16] = {70072 , 14012 , 76691 , 83223 , 59545 , 77986 , 46470 , 42645 , 91890 , 26553 , 45018 , 81047 , 97143 , 46507 , 91748 , 4748};
int lenr[16]= {24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24};
int protr[16] = {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1};

*/

/*
int codeON[18] =  {11149 , 11105 , 11107 , 11192 , 11108 , 11190 , 11111 , 11141 , 11200 , 11121 , 11193 , 11184 , 11133 , 11153 , 11134 , 11194 , 11162 , 11157};

int codeOFF[18] = {11100 , 11128 , 11172 , 11132 , 11167 , 11197 , 11160 , 11186 , 11198 , 11139 , 11104 , 11173 , 11135 , 11127 , 11138 , 11165 , 11191 , 11168};

char* SdIds[18] =  {"11168" , "11141" , "11161" , "11151" , "11125" , "11196" , "11178" , "11190" , "11102" , "11192" , "11122" , "11140" , "11132" , "11105" , "11131" , "11128" , "11194" , "11160"};
String usernames[18] = {"0-Ground" , "1-North" , "1-South" , "2-North" , "2-South" , "3-North" , "3-South" , "4-North" , "4-South" , "5-North" , "5-South" , "6-North" , "6-South" , "7-North" , "7-South" , "8-North" , "8-South" , "9-South"};
int lenr[18]= {24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24 , 24};
int protr[18] ={1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1};
*/

bool istimer = 0;
unsigned long int timerStartp= 0;

char* SdIdsPrepaid[3] = {"951623", "236951" , "784955"};
/////////





String currentUser = "none";
char* currentSdId = "0";
int  currentUserNum = -1;


float ctval1 = 0 ; 
float ctval2 = 0 ; 
float ctval3 = 0 ; 

float energyBalance = 0;
bool state = 0;

/*
void scanForCode(File dir/* the par for this is fs.open()*//*,int code) {



  while (true) {

    File entry =  dir.openNextFile();

    if (! entry) {
      // no more files
      break;
    }

    String str = "";
while (entry.available())
{
  str += (char)entry.read();
Serial.println( (char)entry.read());  
}

    


Serial.println(str);


   

    entry.close();

  
  }


}

*/

DateTime now ;





void setup() {




Serial2.begin(9600, SERIAL_8N1, 16, 17);
Serial.begin(115200);


if (! rtc.begin()) {
Serial.println("Couldn't find RTC");
rtcErr = true;
while (1);
}
 now = rtc.now();
Serial.print(now.year(), DEC);
 Serial.print('/');
Serial.print(now.month(), DEC);
 Serial.print('/');
  Serial.print(now.day(), DEC);
   Serial.print(" (");

Serial.print(") "); Serial.print(now. hour(), DEC); Serial.print(':');
Serial.print(now. minute(), DEC); Serial.print(':'); Serial.print(now.second() , DEC); 
Serial.println();







/*      rf      */  
  mySwitch.enableReceive(rf); 


/*    sd   */
    if(!SD.begin(5)){
        Serial.println("Card Mount Failed 1st time");
        if(!SD.begin(5)){
          Serial.println("Card Mount Failed 2nd time");

          if(!SD.begin(5)){
            Serial.println("Card Mount Failed 3rd time");
            sdErr = true ;
            return;
            }
        }
    }

addCurrMonthsToSD();
addPrevAndNextMonthsToSD();



  pinMode(elvatorRelay, OUTPUT);

  initWiFi_hotspot();
 // initWiFi_connection();

  listDir(SD,"/",0);










      ///   server routes    ///

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("HTTP request received");
       Serial.print("webserver running on core: ");
  Serial.println(xPortGetCoreID());

     request->send(SD, "/navbar.html", "text/html");
     
     
  });

  server.on("/currentUser", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("HTTP request received: currentUser");
      
     
     request->send(200, "text/plain", currentUser);
     
  });

   server.on("/date", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("HTTP request received: Date");
     char Datex[50] = "";

     char ychars[5];
     String ystr = String(now.year());
     ystr.toCharArray(ychars,5);
     
     strcat(Datex,ychars );
      strcat (Datex, "/");
      strcat (Datex, month[now.month()-1] );
      strcat (Datex,"/" );

       char dchars[3];
     String dstr = String(now.day());
     dstr.toCharArray(dchars,3);

      strcat (Datex,dchars);
      String strDatex= Datex ;
     
     request->send(200, "text/plain", strDatex);
     
  });


     server.on("/about", HTTP_GET, [](AsyncWebServerRequest *request){
            
      request->send(SD, "/About.html", "text/html");
     });

      server.on("/services", HTTP_GET, [](AsyncWebServerRequest *request){
            
      request->send(SD, "/About.html", "text/html");
     });


  server.on("/61465416", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("HTTP request received: perUser");
      
     
      request->send(SD, "/perUser.html", "text/html");
     
  });


  
  server.on("/030707", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("HTTP request received: perUserAdmin");
      
     
      request->send(SD, "/perUserAdmin.html", "text/html");
     
  });

    server.on("/61465417", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("HTTP request received: each user usage");
      now = rtc.now();
      int currMonth =  now.month();
      int prevMonth = 0;

      int currYear =  now.year();
      int prevYear = 0;


      if(currMonth >1){
        prevMonth = currMonth - 1;
      prevYear =   currYear;
      }else{
        prevMonth = 12;
        prevYear =   currYear - 1;
      }


          String currYearString = String(currYear, DEC);
      int lenee = currYearString.length()+1;
  char currYearChars[lenee];
   currYearString.toCharArray(currYearChars, lenee);

    String currMonthString = String(currMonth, DEC);
      int lenww = currMonthString.length()+1;
  char currMonthChars[lenww];
   currMonthString.toCharArray(currMonthChars, lenww);


       String prevYearString = String(prevYear, DEC);
      int lenee2 = prevYearString.length()+1;
  char prevYearChars[lenee2];
   prevYearString.toCharArray(prevYearChars, lenee2);

    String prevMonthString = String(prevMonth, DEC);
      int lenww2 = prevMonthString.length()+1;
  char prevMonthChars[lenww2];
   prevMonthString.toCharArray(prevMonthChars, lenww2);


      String names = "[[" ;
      String currBalances = "[" ;
      String prevBalances = "[" ;
      for(int i =0 ; i<len(usernames) ; i++){

        names+='\"';
        names+=usernames[i];
        names+='\"';
       


      char path[65] = "/d/d.1/";
      //Serial.print("turned OFF  2.2" );
      strcat(path,SdIds[i]);
      //Serial.print("turned OFF  2.3" );
      strcat(path,"/a/");

      char temp[35] = "";
    strcat(temp,currYearChars);
    strcat(temp,"-");
    strcat(temp,currMonthChars);
    strcat(temp,".txt");
    encryptChars(temp);
   
   
    strcat(path,temp);


 
      String currUserBalance = readFileToString(SD,path);
      currUserBalance = decrypt(currUserBalance);
      currBalances+= currUserBalance;

      
      char path2[65] = "/d/d.1/";
      //Serial.print("turned OFF  2.2" );
      strcat(path2,SdIds[i]);
      //Serial.print("turned OFF  2.3" );
      strcat(path2,"/a/");

      char temp2[35] = "";
    strcat(temp2,prevYearChars);
    strcat(temp2,"-");
    strcat(temp2,prevMonthChars);
    strcat(temp2,".txt");
    encryptChars(temp2);
   
   
    strcat(path2,temp2);


      String prevUserBalance = readFileToString(SD,path2);
      prevUserBalance = decrypt(prevUserBalance);
      prevBalances+= prevUserBalance;


      if (i!= len(usernames) - 1 ){
       names+=",";
      currBalances+=",";
      prevBalances+=",";
      }
      
      }
      names+="]";
      prevBalances+="]";
      currBalances+="]]";


      names+=',';
      names+=prevBalances;
      names+=',';
      names+=currBalances;

     
     request->send(200, "text/plain", names);
     
  });

  server.on("/61465430", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("HTTP request received: users_state_html");
      
     
      request->send(SD, "/admin1.html", "text/html");
     
  });

    server.on("/61465431", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("HTTP request received: users_state_post_ajax");
      

       String names = "[[" ;
      String states = "[" ;

      for(int i =0 ; i<len(usernames) ; i++){

        names+='\"';
        names+=usernames[i];
        names+='\"';
       


      String state =  getState(i);
     // state = decrypt(state);
      states += state;


      if (i!= len(usernames) - 1 ){
       names+=",";
      states+=",";
      }
      
      }
      names+="]  ";
      states+="]]";

      names+=',';
      names+=states;
     
      request->send(200, "text/plain", names);
     
  });

    server.on("/61465432", HTTP_POST, [](AsyncWebServerRequest *request){
      Serial.println("HTTP POST request received: edit_user_state");
       
     /*if(request->hasParam("userID", true)){
       AsyncWebParameter* id = request->getParam("userID", true);
          if(id->isFile()){ //id->isPost() is also true
    Serial.printf("FILE[%s]: %s, size: %u\n", id->name().c_str(), id->value().c_str(), id->size());
    Serial.println("1");
  } else if(id->isPost()){
    Serial.printf("POST[%s]: %s\n", id->name().c_str(), id->value().c_str());
    Serial.println("2");
  } else {
    Serial.printf("GET[%s]: %s\n", id->name().c_str(), id->value().c_str());
    Serial.println("3");
  }

     }else{
       Serial.println("No parameter as userID");
       return 0;
     }*/
    /*  AsyncWebParameter* state;
     if(request->hasParam("state", true)){
        state = request->getParam("state", true);

     }else{
       return 0;
     }
    


      char path[65] = "/d/d.1/";
      //Serial.print("turned OFF  2.2" );
      strcat(path,SdIds[id]);
      //Serial.print("turned OFF  2.3" );
      strcat(path,"/c/s.txt");
      
      if(state == 0){
       char* stateChars = "0";
      }else{
        char* stateChars = "1";
      }
      writeFile(SD,path,stateChars);      
*/ 



    int paramsNr = request->params();
    Serial.println(paramsNr);
    String id , state;
    for(int i=0;i<paramsNr;i++){
 
        AsyncWebParameter* p = request->getParam(i);
        Serial.print("Param name: ");
        Serial.println(p->name());
        Serial.print("Param value: ");
        Serial.println(p->value());
        Serial.println("------");

      if (p->name() == "userID"){
           id = p->value();        
      }
      if (p->name() == "state"){
           state = p->value();
      }
    }




    int idInt = id.toInt();
    int stateInt = state.toInt();     
writeState( idInt, stateInt);


 
    request->send(200, "text/plain", "message received");
     
  });











 server.on("/61465440", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("HTTP request received: users_state_html");
      
     
      request->send(SD, "/admin2.html", "text/html");
     
  });

    server.on("/61465441", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("HTTP request received: prepaid_remotes_post_ajax");
      

       String balances = "[[" ;
       String states = "[" ;

      for(int i =0 ; i<len(SdIdsPrepaid) ; i++){

        String val = getPrepaidBalance(i);

        balances+='\"';
        
        balances+=decrypt(val);
        balances+='\"';



        String state = getPrepaidState(i) ;

        states+='\"';
        states+=state;
        states+='\"';

       





      if (i!= len(usernames) - 1 ){

      balances+=",";
      states+=",";
      }
      
      }


      states+="]]";
      balances+="]";
      balances+=",";

    balances+=states ;


     
      request->send(200, "text/plain", balances);
     
  });

    server.on("/61465442", HTTP_POST, [](AsyncWebServerRequest *request){
      Serial.println("HTTP POST request received: edit_user_state");



    int paramsNr = request->params();
    Serial.println(paramsNr);
    String id , balance , state;
    for(int i=0;i<paramsNr;i++){
 
        AsyncWebParameter* p = request->getParam(i);
        Serial.print("Param name: ");
        Serial.println(p->name());
        Serial.print("Param value: ");
        Serial.println(p->value());
        Serial.println("------");

      if (p->name() == "userID"){
           id = p->value();        
      }
      if (p->name() == "balance"){
           balance = p->value();
      }
      if (p->name() == "state"){
           state = p->value();
      }



      
    }




    int idInt = id.toInt();
    int balanceInt = balance.toInt();
    int stateInt = state.toInt();     
writePrepaidBalance( idInt, balanceInt);
writePrepaidState(idInt  ,  stateInt);


 
    request->send(200, "text/plain", "message received");
     
  });






  


  server.serveStatic("/", SD, "/static/");
  






  
  server.begin();
  Serial.println("HTTP server started");

  //scanForCode(SD.open("/d/d.1/d.1.1"),202);


   delay(350); 

xTaskCreatePinnedToCore(loop2, "Task2", 10000, NULL, 0, &Task2,  0); 

    delay(350); 
}











void loop() {
  


  
  

}
















void loop2( void * parameter )
{

TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
TIMERG0.wdt_feed=1;
TIMERG0.wdt_wprotect=0;

  int lastMeasure = millis();
  for (;;) {






int timex = timerStartp - millis() ;
if (istimer && abs(timex) > 180000){
istimer = 0;
sfcodeOFF(codeOFF[currentUserNum] ,lenr[currentUserNum] , protr[currentUserNum]);
}      







  if (mySwitch.available()) {
  
       Serial.println("Received the following:");
    Serial.println(mySwitch.getReceivedValue());
    Serial.println(mySwitch.getReceivedBitlength());
    Serial.println(mySwitch.getReceivedProtocol());


    if(state == 0 ){

    sfcodeON(mySwitch.getReceivedValue()  , mySwitch.getReceivedBitlength() , mySwitch.getReceivedProtocol());

    }else if (state){

    sfcodeOFF(mySwitch.getReceivedValue()  , mySwitch.getReceivedBitlength() , mySwitch.getReceivedProtocol());

    }


    TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
    TIMERG0.wdt_feed=1;
    TIMERG0.wdt_wprotect=0;
    mySwitch.resetAvailable();
  }

  
  


  if(state){

    digitalWrite(elvatorRelay,HIGH);
    


  int timer = lastMeasure - millis();
  if(abs(timer) > 200){


  lastMeasure = millis() ;
  reqCT();
 energyBalance += ((ctval1 * 220 *0.2/3600000) + (ctval2 * 220 *0.2/3600000) + (ctval3 * 220 *0.2/3600000) );



 Serial.print(now.year(), DEC);
 Serial.print('/');
Serial.print(now.month(), DEC);
 Serial.print('/');
  Serial.print(now.day(), DEC);
   Serial.print(" (");

Serial.print(") "); Serial.print(now. hour(), DEC); Serial.print(':');
Serial.print(now. minute(), DEC); Serial.print(':'); Serial.print(now.second() , DEC); 





  }

  }else{


    
    digitalWrite(elvatorRelay,LOW);

  }
 



if(test){


  if(millis()  > 5000 && testIndex<1){
    sfcodeON(11149,24,1);
    testIndex++;
  }else if (millis() > 13000 && testIndex<2){
  sfcodeOFF(11100,24,1);
  testIndex++;
  test = 0;
  }

}








   
 
   
  }
}
