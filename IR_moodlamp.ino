//By ASpace:https://www.youtube.com/channel/UC9i2-Fy9IOo8yzypeB7Xpow

#include <IRremote.h>

float RGB[3];
int redLed = 3; 
int greenLed = 5; 
int blueLed = 6;
int RECV_PIN = 11;
int delaymood = 100;
int before;
float sinVal; 
int ledVal; 

IRrecv irrecv(RECV_PIN);

decode_results results;

 
void setup()
{
Serial.begin(9600);
irrecv.enableIRIn(); // Start the receiver
pinMode(redLed,OUTPUT); 
pinMode(greenLed,OUTPUT);
pinMode(blueLed,OUTPUT); 
digitalWrite(redLed,HIGH);       //It is HIGH because I used a common anode RGB led,for common cathode it will be LOW.
digitalWrite(greenLed,HIGH);
digitalWrite(blueLed,HIGH);
before=0;
}

void loop()
{
  if (irrecv.decode(&results)) 
  {
      if (results.value==0xE01F906F)     //When this is true,all function will be called.
       { 
         if(before==0)
         {
         all();
         before=1;
        Serial.println(results.value, HEX);
         }

         else                               //When the same button is pressed again it will go off.           
         {
          alloff();
          Serial.println(results.value, HEX);
          before=0;
         }
       }

       
      if (results.value==0xE01F50AF)                  //When this is true,red led will glow.
       { 
        if(before==0)
         {
         digitalWrite(redLed,LOW); //Since I used a common anode.For common cathode it will be HIGH.
         before=1;
         Serial.println(results.value, HEX);
         }

         else                                         //When the same button is pressed again it will go off.
         {
          digitalWrite(redLed,HIGH);
          Serial.println(results.value, HEX);
          before=0;
         }      
        Serial.println(results.value, HEX);
       }

       
      if (results.value==0xE01FD02F)                       //When this is true,pulse function will be called.
       { 
        if(before==0)
         {
         pulse();
         before=1;
         Serial.println(results.value, HEX);
         }

         else                                            //When the same button is pressed again it will go off.
         {
          alloff();
          Serial.println(results.value, HEX);
          before=0;
         }      
        Serial.println(results.value, HEX);
       }
        
      irrecv.resume();
  }
}



void all()                  //Function for all the spectrum
{
for (int y=0; y<=3; y++) 
{
if (y=1)
{
 for (int x=0;x<=255;x++)
   {
    RGB[0]=220-x; 
    RGB[1]=0; 
    RGB[2]=0+x;
    analogWrite(redLed,RGB[0]);
    analogWrite(greenLed,RGB[1]);
    analogWrite(blueLed,RGB[2]); 
    delay(delaymood);
    }
}

if (y=2)
{
   for (int x=0;x<=255;x++)
   {
    RGB[0]=0; 
    RGB[1]=0+x; 
    RGB[2]=220-x;
    analogWrite(redLed,RGB[0]);
    analogWrite(greenLed,RGB[1]);
    analogWrite(blueLed,RGB[2]); 
    delay(delaymood);
    }
}

if (y=3)
{
      for (int x=0;x<=255;x++)
      {
       RGB[0]=0+x; 
       RGB[1]=220-x; 
       RGB[2]=0;
       analogWrite(redLed,RGB[0]);
       analogWrite(greenLed,RGB[1]);
       analogWrite(blueLed,RGB[2]); 
       delay(delaymood);
      } 
}

}
}


void alloff()                          //Function for turning all the lights off
{
digitalWrite(redLed,HIGH);
digitalWrite(greenLed,HIGH);
digitalWrite(blueLed,HIGH);  
}

void pulse()                           //Function for creating a pulse of light
{   
  for(int y=0; y<5; y++)
  {
    for (int x=0; x<180; x++) 
    {
      sinVal = (sin(x*(3.1412/180)));     
      ledVal = int(sinVal*255);     
      analogWrite(blueLed, ledVal);       
      delay(25);  
     }
  } 
}

