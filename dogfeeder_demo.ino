/*
# disgard sms from no number
 
*/

// include the GSM library
#include <GSM.h>

// PIN Number for the SIM = None
#define PINNUMBER ""

// initialize the library instances
GSM gsmAccess;
GSM_SMS sms;

// Array to hold the number a SMS is retreived from
char senderNumber[20];  

int gsm_connected = 8;
int gsm_receive = 9;
int feeding = 11;
int relay = 6;

void setup() 
{
 
  // setup LED controls
  pinMode( gsm_connected, OUTPUT);
  pinMode( gsm_receive, OUTPUT );
  pinMode( feeding, OUTPUT);
  pinMode( relay, OUTPUT );
  
  // setup initial LED config
  digitalWrite( gsm_connected, LOW);
  digitalWrite( gsm_receive, HIGH );
  digitalWrite( feeding, LOW);
  
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // good practice to wait for it.
  } 
  
  // say hallo
  Serial.println();
  Serial.println();
  Serial.println("Trevor Inc Dog Feeder Version : Demo");
  Serial.println("====================================");
  Serial.println("Remember not to use pin 7");
  Serial.println("Waiting to connect to GSM network");
  
  
  // connection state
  boolean notConnected = true;
  
  // Start GSM connection
  // Wait for GSM connection
  while(notConnected)
  {
    if(gsmAccess.begin(PINNUMBER)==GSM_READY)
      notConnected = false;
    else
    {
      Serial.println("Not connected to GSM network");
      delay(1000);
    }
  }
  
  // We are connected to GSM now
  Serial.println("GSM initialized and connected");
  Serial.println("Feeder activated and ready");
  digitalWrite( gsm_receive, LOW );
  digitalWrite( feeding, LOW);
  digitalWrite( gsm_connected, HIGH);
  
  // Tell the numbers below we are online now
  sms.beginSMS("0823020106");
  sms.print("Trevor Inc, Dogfeeder now online. Send SMS with  # as start to activate feeding. Dog feeder available at 0813607553");
  sms.endSMS(); 
  Serial.println("Welcome SMS sent to Tobie");
  Serial.println("READY");
  Serial.println("==============================="); 
 
 sms.beginSMS("0798979035");
 sms.print("Trevor Inc, Dogfeeder now online. Send SMS with  # as start to activate feeding. Dog feeder available at 0813607553");
 sms.endSMS(); 
 Serial.println("Welcome SMS sent to Tobie");
 Serial.println("READY");
 Serial.println("===============================");   
  
 
}

void loop() 
{
  char c;
  
  // If there are any SMSs available()  
  if (sms.available())
  {
    Serial.println("Message received from:");
    
    // Get remote number
    sms.remoteNumber(senderNumber, 20);
    Serial.println(senderNumber);

    // An example of message disposal    
    // Any messages starting with # wil activate feeder
    if(sms.peek()=='#')
    {
      Serial.println("Activating feeding mechanism");
      sms.flush();
      digitalWrite( feeding, HIGH);
        digitalWrite( relay, HIGH);
        delay(300);
        digitalWrite( relay, LOW);
      delay( 5000 );
      digitalWrite( feeding, LOW );
      
      Serial.println("Feeding complete");
      
      sms.beginSMS(senderNumber);
      sms.print("Woof! Woof!, Thanks for the food master. SMS soon again please!");
      sms.endSMS(); 
      Serial.println("Master informed");
      
      
    }
    
    // Read message bytes and print them
    while(c=sms.read())
      Serial.print(c);
      Serial.println(); //Print new line
      
    // Delete message from modem memory
    sms.flush();
    Serial.println("Deleted last SMS from memory");
    Serial.println("============================");
    Serial.println();
    
  }



}


