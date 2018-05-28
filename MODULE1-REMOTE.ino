/*
 THIS CODE IS FOR SAVING THE PATH TO BE FOLLOWED,
 AND CAN SAVE UP TO 100 INSTRUCTIONS IN IT. 
 SD CARD CAN BE USED BUT THE USER NEED TO ADD ITS CODE
 THAT IS EASLIY AVAILABLE ON THE ARDUINO.CC

 THE VALUES IN THE FORM OF X,Y VARIABLE IS SEND TO THE ANOTHER BOARD
 X0Y0-STOP
 X4Y0-FORWARD
 X0Y4-RIGHT
 X-4Y0-BACKWARD
 X0Y-4-LEFT
 
AN ARRAY IS USED TO STORE THE INSTRUCTIONS IN THE FORM LIKE
F-10 WHICH STANDS FOR 10 TIMES X4Y0.
B-5 FOR X-4Y0 FIVE TIMES.
*/

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

int joyPin1 = 0;                 // slider variable connecetd to analog pin 0     //    X
int joyPin2 = 2;                 // slider variable connecetd to analog pin 1     //    Y

int value1 = 0;                  // variable to read the value from the analog pin 0
int value2 = 0;                  // variable to read the value from the analog pin 1

int I1[400];
String path[100];
int J1[400];

int count=0;

int x1;

int q1=1;                        
int q2=1;
int q3=1;
int q4=1;
int q5=1;
int q6=1;
int q7=1;
int q8=1;
int q9=1;

int k=0;

int msg[1];

int c1=0;     
int c2=0;



RF24 radio(7,9);                    // nRF24L01(+) radio attached using Getting Started board 

RF24Network network(radio);          // Network uses that radio

const uint16_t this_node = 01;        // Address of our node in Octal format
const uint16_t other_node = 00;       // Address of the other node in Octal format

const unsigned long interval = 2000; //ms  // How often to send 'hello world to the other unit

unsigned long last_sent;             // When did we last send?
unsigned long packets_sent;          // How many have we sent already


struct payload_t {                  // Structure of our payload
  unsigned long ms;
  unsigned long counter;
};

void setup(void)
{
  Serial.begin(9600);
  delay(50);
  Serial.println("RF24Network/examples/helloworld_tx/");
 
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 60, /*node address*/ this_node);

}

  
  
int treatValue(int data) {
  return (data * 9 / 1024) ;

  pinMode(8, INPUT);
  pinMode(10, INPUT);


}

void upsteps(int x, int count1)           //UPDATES THE STEPS TO BE FOLLOW
{

switch (x)
  {
    case 1:
      path[k]=" F-"+String(count1+0);
      break; 
    case 2:
      path[k]=" B-"+String(count1+0);
      break;
    case 3:
      path[k]=" R-"+String(count1+0);    
      break;  
    case 4:
      path[k]=" L-"+String(count1+0);     
      break;
    case 5:
      path[k]=" FR-"+String(count1+0);   
      break;
    case 6:
      path[k]=" BR-"+String(count1+0);    
      break;
    case 7:
      path[k]=" FL-"+String(count1+0);    
      break;
    case 8:
      path[k]=" BL-"+String(count1+0);
      break;
    case 9:
      path[k]=" S-"+String(count1+0);
      break;
      
    }    
  k++;
}


    
int y1=0;
int y2=0;

void loop() {
  
  network.update();                          // Check the network regularly

  int reading = digitalRead(8);

  
  

  value1 = analogRead(joyPin1);
  
  value2 = analogRead(joyPin2);
  
  y1=treatValue(value1) - 4;
  y2=treatValue(value2) - 4+100;
  

  Serial.print('X');
  Serial.print(treatValue(value1) - 4);
  Serial.print('Y');
  Serial.print(treatValue(value2) - 4);
  Serial.println();

  
 if((treatValue(value1)-4)>0 && (treatValue(value2)-4)==0)             //FORWARD.................   CASE-1
  {
    if((treatValue(value1)-4)>0 && q1==1)
    {
      upsteps(x1,count);
      count=0;
      q1=0;
      q2=1;
      q3=1;
      q4=1;
      q5=1;
      q6=1;
      q7=1;
      q8=1;
      q9=1;
      Serial.println("Forward");
      }
      x1=1;     
      count++;      
    }
   else if((treatValue(value1)-4)<0 && (treatValue(value2)-4)==0)    //BACKWARD.................     CASE-2
   {
     if((treatValue(value1)-4)<0 && q2==1)
    {
      upsteps(x1,count);
      count=0;
      q1=1;
      q2=0;
      q3=1;
      q4=1;
      q5=1;
      q6=1;
      q7=1;
      q8=1;
      q9=1;
      Serial.println("Backward");
      }
    x1=2;
    count++;
    }


   else if((treatValue(value2)-4)>0 && (treatValue(value1)-4)==0)           //RIGHT.................      CASE-3
  {
    if((treatValue(value2)-4)>0 && q3==1)
    {
      upsteps(x1,count);
      count=0;
      q1=1;
      q2=1;
      q3=0;
      q4=1;
      q5=1;
      q6=1;
      q7=1;
      q8=1;
      q9=1;
      Serial.println("RIGHT");
      }
    x1=3;
    count++;
    }
    
   else if((treatValue(value2)-4)<0 && (treatValue(value1)-4)==0)   //LEFT.................       CASE-4
   {
    
    if((treatValue(value2)-4)<0 && q4==1)
    {
      upsteps(x1,count);
      count=0;
      q1=1;
      q2=1;
      q3=1;
      q4=0;
      q5=1;
      q6=1;
      q7=1;
      q8=1;
      q9=1;
      Serial.println("LEFT");
      }
      x1=4;
      count++;
    }

   else if((treatValue(value1)-4)>0 && (treatValue(value2)-4)>0)        //FORWARD-RIGHT.................   CASE-5              
  {
    if((treatValue(value1)-4)>0 && q5==1 && (treatValue(value2)-4)>0)
    {
      upsteps(x1,count);
      count=0;
      q1=1;
      q2=1;
      q3=1;
      q4=1;
      q5=0;
      q6=1;
      q7=1;
      q8=1;
      q9=1;
      Serial.println("Forward-RIGHT");
      }
    x1=5;
    count++;
    }
    
   else if((treatValue(value1)-4)<0 && (treatValue(value2)-4)>0)      //BACKWARD-RIGHT.................        CASE-6
   {
    
    if((treatValue(value1)-4)<0 && q6==1 && (treatValue(value2)-4)>0)
    {
      upsteps(x1,count);
      count=0;
      q1=1;
      q2=1;
      q3=1;
      q4=1;
      q5=1;
      q6=0;
      q7=1;
      q8=1;
      q9=1;
      Serial.println("Backward-RIGHT");
      }
      x1=6;
      count++;
    }
    
   else if((treatValue(value1)-4)>0 && (treatValue(value2)-4)<0)             //FORWARD-LEFT.................      CASE-7
  {
    if((treatValue(value1)-4)>0 && q7==1 && (treatValue(value2)-4)<0)
    {
      upsteps(x1,count);
      count=0;
      q1=1;
      q2=1;
      q3=1;
      q4=1;
      q5=1;
      q6=1;
      q7=0;
      q8=1;
      q9=1;
      Serial.println("FORWARD-LEFT");
      }
    x1=7;
    count++;
    }
    
   else if((treatValue(value1)-4)<0 && (treatValue(value2)-4)<0)          //BACKWARD-LEFT.................       CASE-8
   {
    
    if((treatValue(value1)-4)<0 && q8==1 && (treatValue(value2)-4)<0)
    {
      upsteps(x1,count);
      count=0;
      q1=1;
      q2=1;
      q3=1;
      q4=1;
      q5=1;
      q6=1;
      q7=1;
      q8=0;
      q9=1;
      Serial.println("Backward-LEFT");
      }
      x1=8;
      count++;
    }
     else if((treatValue(value1)-4)==0 && (treatValue(value2)-4)==0)          //STOP.................       CASE-0
   {
    
    if((treatValue(value1)-4)==0 && q9==1 && (treatValue(value2)-4)==0)
    {
      upsteps(x1,count);
      count=0;
      q1=1;
      q2=1;
      q3=1;
      q4=1;
      q5=1;
      q6=1;
      q7=1;
      q8=1;
      q9=0;
      Serial.println("STOP");
      }
      x1=9;
      count++;
    }
    


  while(digitalRead(3)==HIGH)          //WHEN THE BUTTON IS PRESSED THE ROBOT START FOLLOWING THE INSTRUCTION STORED IN THE ARRAY
   {   
      int x5;
      int y5;
      for(int y=0;y<50;y++)
   {
  
   int f1=path[y].indexOf('-',0);
   String f2=path[y].substring(f1+1,path[y].length());
   int Count1=f2.toInt();
   String drt=path[y].substring(1,f1);
   if(drt=="F")
  { 

    delay(100);
    Serial.print("F");
    Serial.println(Count1);
    x5=4;
    y5=0;

   
    
   for(int g=0;g<Count1;g++)
    {
      int y6=0;
      delay(100);
     Serial.print("x");
     Serial.print(x5);
     Serial.print("y");
     Serial.println(y5);
     y6=y5+100;
     RF24NetworkHeader header(/*to node*/ other_node);
     network.write(header,&x5,sizeof(x5));
     network.write(header,&y6,sizeof(y6));  
      }
  }
      else if(drt=="B")
      {
        delay(100);
        Serial.print("B");
        Serial.println(Count1);   
        x5=-4;
        y5=0;
        for(int g=0;g<Count1;g++)
        {
         int y6=0;
         delay(100);
         Serial.print("x");
         Serial.print(x5);
         Serial.print("y");
         Serial.println(y5);
         y6=y5+100;
         RF24NetworkHeader header(/*to node*/ other_node);
         network.write(header,&x5,sizeof(x5));
         network.write(header,&y6,sizeof(y6));      
         }
       }
      else if(drt=="S")
      {
        delay(100);
        Serial.print("S");
        Serial.println(Count1);
        x5=0;
        y5=0;
          for(int g=0;g<Count1;g++)
          {
           int y6=0;
           delay(100);
           Serial.print("x");
           Serial.print(x5);
           Serial.print("y");
           Serial.println(y5);
           y6=y5+100;
           RF24NetworkHeader header(/*to node*/ other_node);
           network.write(header,&x5,sizeof(x5));
           network.write(header,&y6,sizeof(y6));
          }
        }
      else if(drt=="L")
      {
        delay(100);
        Serial.print("L");
        Serial.println(Count1);
        x5=0;
        y5=-4;
          for(int g=0;g<Count1;g++)
          {
           int y6=0;
           delay(100);
           Serial.print("x");
           Serial.print(x5);
           Serial.print("y");
           Serial.println(y5);
           y6=y5+100;
           RF24NetworkHeader header(/*to node*/ other_node);
           network.write(header,&x5,sizeof(x5));
           network.write(header,&y6,sizeof(y6));
          }   
      }
        else if(drt=="R")
        {
          delay(100);
          Serial.print("R");
          Serial.println(Count1);
          x5=0;
          y5=4;
            for(int g=0;g<Count1;g++)
            {
             int y6=0;
             delay(100);
             Serial.print("x");
             Serial.print(x5);
             Serial.print("y");
             Serial.println(y5);
             y6=y5+100;
             RF24NetworkHeader header(/*to node*/ other_node);
             network.write(header,&x5,sizeof(x5));
             network.write(header,&y6,sizeof(y6));
            }   
        }
        else if(drt=="FR")
        {
          delay(100);
          Serial.print("FR");
          Serial.println(Count1);
          x5=4;
          y5=4;
            for(int g=0;g<Count1;g++)
            {
             int y6=0;
             delay(100);
             Serial.print("x");
             Serial.print(x5);
             Serial.print("y");
             Serial.println(y5);
             y6=y5+100;
             RF24NetworkHeader header(/*to node*/ other_node);
             network.write(header,&x5,sizeof(x5));
             network.write(header,&y6,sizeof(y6));
            } 
        }
        else if(drt=="FL")
        {
          delay(100);
          Serial.print("FL");
          Serial.println(Count1);
          x5=4;
          y5=-4;
            for(int g=0;g<Count1;g++)
            {
             int y6=0;
             delay(100);
             Serial.print("x");
             Serial.print(x5);
             Serial.print("y");
             Serial.println(y5);
             y6=y5+100;
             RF24NetworkHeader header(/*to node*/ other_node);
             network.write(header,&x5,sizeof(x5));
             network.write(header,&y6,sizeof(y6));
            }
         
          }
        else if(drt=="BR")
        {
          delay(100);
          Serial.print("BR");
          Serial.println(Count1);
          x5=-4;
          y5=4;
          for(int g=0;g<Count1;g++)
          {
           int y6=0;
           delay(100);
           Serial.print("x");
           Serial.print(x5);
           Serial.print("y");
           Serial.println(y5);
           y6=y5+100;
           RF24NetworkHeader header(/*to node*/ other_node);
           network.write(header,&x5,sizeof(x5));
           network.write(header,&y6,sizeof(y6));
             }   
       
          }
        else if(drt=="BL")
        {
          delay(100);
          Serial.print("BL");
          Serial.println(Count1);
          x5=-4;
          y5=-4;
          for(int g=0;g<Count1;g++)
          {
           int y6=0;
           delay(100);
           Serial.print("x");
           Serial.print(x5);
           Serial.print("y");
           Serial.println(y5);
           y6=y5+100;
           RF24NetworkHeader header(/*to node*/ other_node);
           network.write(header,&x5,sizeof(x5));
           network.write(header,&y6,sizeof(y6));
            }   
          } 
    
      }
      
 } 
    RF24NetworkHeader header(/*to node*/ other_node);
    network.write(header,&y1,sizeof(y1));
    network.write(header,&y2,sizeof(y2));
    delay(50);
}



