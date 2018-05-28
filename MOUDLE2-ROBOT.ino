

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

int x=0;
int y=0;

int timer=0;

int k6=0;

RF24 radio(9,7);                // nRF24L01(+) radio attached using Getting Started board 

RF24Network network(radio);      // Network uses that radio
const uint16_t this_node = 00;    // Address of our node in Octal format ( 04,031, etc)
const uint16_t other_node = 01;   // Address of the other node in Octal format

struct payload_t {                 // Structure of our payload
  unsigned long ms;
  unsigned long counter;
};


void setup(void)
{
  pinMode(2,OUTPUT);    //ENABLE MOTOR 1km 
  pinMode(3,OUTPUT);     //LOGICS FOR 1
  pinMode(4,OUTPUT);
  

  
  pinMode(5,OUTPUT);     //LOGICS FOR 2
  pinMode(6,OUTPUT);
  
  pinMode(8,OUTPUT);    //ENABLE MOTOR 2
  Serial.begin(9600);
  Serial.println("RF24Network/examples/helloworld_rx/");

  pinMode(30,OUTPUT);
  pinMode(28,OUTPUT);
  pinMode(29,OUTPUT);
  pinMode(31,OUTPUT);
  pinMode(32,OUTPUT);
  pinMode(33,OUTPUT);

 

  digitalWrite(29,HIGH);
  digitalWrite(28,HIGH);
  digitalWrite(31,HIGH);
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 60, /*node address*/ this_node);
}
int H;


void loop(void){
  
  network.update();                  // Check the network regularly

  digitalWrite(2,HIGH);
  digitalWrite(8,HIGH);

  digitalWrite(30,LOW);
  

  
  while ( network.available() ) {     // Is there anything ready for us?
    
    RF24NetworkHeader header;        // If so, grab it and print it out
    payload_t payload;
    network.read(header,&H,sizeof(H));

    int theChar=H ;

    if(theChar==777)
    {
      
      Serial.println("                               -------ON------");
      k6=7;
     
      }
      else if(theChar==888)
      {
      Serial.println("                                -------OFF------");
      timer=0;
      k6=4;
       }

        if(k6==7)
        {
          digitalWrite(29,LOW);
          
          
        
          if(timer<=100) 
          { 
          digitalWrite(31,LOW);
         
          
          }
          else
          {
            digitalWrite(31,HIGH);
            
            }
            timer++;
          }
        else if(k6==4 || k6==0)
        {
           digitalWrite(29,HIGH);
          
          }

          
           digitalWrite(28,LOW);
        
    theChar = H-4;
    
    //Serial.print(H);
       if(theChar<=50)
      {
        x=theChar+4;
        
        }
        else if(theChar>50 && theChar<=200) 
        {
          y=theChar-100+4;
          
         }
Serial.print("x");
Serial.print(x);

Serial.print("   y");
Serial.println(y);

  if(x>0)
  {
  
  if(y>0)
  {
    Serial.println("FORWARD RIGHT"); 
   digitalWrite(3,HIGH);             //CLOCK
   digitalWrite(4,LOW);
   digitalWrite(5,LOW);             //ANTI CLOCK
   digitalWrite(6,HIGH);
    }

    else if(y<0)
    {
       Serial.println("FORWARD LEFT");
   digitalWrite(3,LOW);             //ANTI CLOCK
   digitalWrite(4,HIGH);
   digitalWrite(5,HIGH);             //CLOCK
   digitalWrite(6,LOW);
      }
      else
      {
         Serial.println("FORWARD");
          digitalWrite(3,HIGH);             //CLOCK
          digitalWrite(4,LOW);
          digitalWrite(5,HIGH);             //CLOCK
          digitalWrite(6,LOW);
        }
  }
  
  else if(x<0)
  {
  
    
if(y>0)
{
  Serial.println("BACKWARD RIGH");
  digitalWrite(3,LOW);             //ANTI CLOCK
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);             //CLOCK
  digitalWrite(6,LOW);
  }

  else if(y<0)
  {
    Serial.println("BACKWARD LEFT");
    digitalWrite(3,HIGH);             //CLOCK
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);             //ANTI CLOCK
    digitalWrite(6,HIGH);
    
    }
    else
    {
      Serial.println("BACKWARD");
        digitalWrite(3,LOW);             //ANTI CLOCK
        digitalWrite(4,HIGH);
        digitalWrite(5,LOW);             //ANTI CLOCK
        digitalWrite(6,HIGH);
      }
  }
   
   else
  {
  
    
if(y>0)
{
  Serial.println("RIGH");

  digitalWrite(3,HIGH);             //CLOCK
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);             //ANTI CLOCK
    digitalWrite(6,HIGH);
  }

  else if(y<0)
  {
    Serial.println("LEFT");
      digitalWrite(3,LOW);             //ANTI CLOCK
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);             //CLOCK
  digitalWrite(6,LOW);
    
    }
    else
    {
      Serial.println("=STOP");
        digitalWrite(3,HIGH);             //ANTI CLOCK
        digitalWrite(4,HIGH);
        digitalWrite(5,HIGH);             //ANTI CLOCK
        digitalWrite(6,HIGH);
      }
  }


   
     
  
  }
  delay(100);
}

