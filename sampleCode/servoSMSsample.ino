#include <Servo.h>
#include "SIM900.h"
#include <SoftwareSerial.h>
//If not used, is better to exclude the HTTP library,
//for RAM saving.
//If your sketch reboots itself proprably you have finished,
//your memory available.
//#include "inetGSM.h"
 
//If you want to use the Arduino functions to manage SMS, uncomment the lines below.
#include "sms.h"
SMSGSM sms;
 
 
//To change pins for Software Serial, use the two lines in GSM.cpp.
 
//GSM Shield for Arduino
//www.open-electronics.org
//this code is based on the example of Arduino Labs.
 
//Simple sketch to send and receive SMS.
 char usr[]="@usr";        
 char adm[]="@adm";
 char del[]="@del";
 char on[]="@on";
 char off[]="@off";
 
int numdata;
boolean started=false;
char position;  
char phone_number[20]; // array for the phone number string
char sms_text[13];
Servo s1;
 
 
void setup()
{
  //Serial connection.
 
  Serial.begin(9600);
  Serial.println("GSM Shield testing.");
 
  //Start configuration of shield with baudrate.
  //For http uses is raccomanded to use 4800 or slower.
  if (gsm.begin(2400)){
    Serial.println("\nstatus=READY");
    started=true;  
  }
  else Serial.println("\nstatus=IDLE");
 
  if(started){
     }
 
};
 
void loop()
{
 
  Serial.println("No new sms!");
  delay(1000);
  s1.attach(6);
  s1.detach();
  position = sms.IsSMSPresent(SMS_UNREAD);
 if (position) {
          // read new SMS
     sms.GetSMS(position, phone_number, sms_text, 15);
     Serial.println("SMS recieved");
     Serial.println(sms_text);
     
                       /* if(has_command(sms_text,usr,sizeof(usr))&& has_number(sms_text,usr,sizeof(usr)))
                                {
                                        Serial.println("Added user entry");
                                                       
                                }
                        if(has_command(sms_text,adm,sizeof(adm))&& has_number(sms_text,adm,sizeof(adm)))
                                {
                                        Serial.println("Added admin entry");
                                                       
                                }
                                               
                        if(has_command(sms_text,del,sizeof(del))&& has_number(sms_text,del,sizeof(del)))
                                {
                                        Serial.println("\nDeleted entry\n");
                                                                       
                                }*/
                        if(has_command(sms_text,on,sizeof(on)))
                                {
                                        Serial.println("On");
                                          s1.attach(6);
                                         s1.write(118);
                                         delay(1000);
                                         s1.detach();
                                        //log who opened       
                                }  
                              if(has_command(sms_text,off,sizeof(off)))
                                {
 
                                        Serial.println("Off");
                                           s1.attach(6);
                                         s1.write(80);
                                         delay(1000);
                                         s1.detach();
                                        //log who opened       
                                }
 
        }
}
 
bool has_command(char command[], char type[], int com_size)
{
 
for(int i=1;i<com_size-1;i++) //to determine the size of the commands
{
        if(type[i]!=command[i]) //if any of the commands are not acceptable, it returns false
                {
                return false;
                }
}
return true;
}
 
bool has_number(char command[],char type[], int com_size)
{
for(int i=com_size+1;i<com_size+7;i++) //determines the length of the command
        if(!isdigit(command[i]))
                {
                return false;
                }
}
return true;
}