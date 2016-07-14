// Maurice Ribble 
// 8-30-2009
// http://www.glacialwanderer.com/hobbyrobotics
// Used Arduino 0017
// This is a simple test app for some cheap RF transmitter and receiver hardware.
// RF Transmitter: http://www.sparkfun.com/commerce/product_info.php?products_id=8945
// RF Receiver: http://www.sparkfun.com/commerce/product_info.php?products_id=8948

// This says whether you are building the transmistor or reciever.
// Only one of these should be defined.
//#define TRANSMITTER
#define RECEIVER

// Arduino digital pins
#define LED_PIN  13
#define TRIGGER_PIN  7
#define TRIGGER_PERDIOD 1000
#define STOP_RX_PERIOD 5000
#define WAIT_B4_TRIGGER 5000

void setup()
{

  pinMode(LED_PIN, OUTPUT);
  pinMode(TRIGGER_PIN,OUTPUT);
  digitalWrite(TRIGGER_PIN,LOW);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(1200);  // Hardware supports up to 2400, but 1200 gives longer range
}

#ifdef TRANSMITTER
void loop()
{

  
  writeUInt(158); // byte to transmit
  delay(10);
  digitalWrite(LED_PIN, HIGH);
  
}
#endif //TRANSMITTER

#ifdef RECEIVER
int cnt = 0;
int threshold = 5;
void loop()
{
  boolean light_led = false;
  int whileLoopCnt;
  bool readyToReceive = true;

  
  if (readUInt(true) == 158 && readyToReceive) // Check to see if we got the test number
  {
    
    cnt++;
 
  }

  if(cnt >= threshold){
    
    cnt = 0;
    light_led = true;
    
  }
  
  if (light_led)
  {
    light_led = false;
    //wait a bit of time before triggerint the ball machine
    digitalWrite(LED_PIN, HIGH);
    delay(WAIT_B4_TRIGGER);
    digitalWrite(TRIGGER_PIN, HIGH);
    
    //stay in the while loop and discard other messages during this period
    delay(TRIGGER_PERDIOD);
    
    digitalWrite(TRIGGER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    
    
     //stay in the while loop and discard other messages during this period
     delay(STOP_RX_PERIOD);

    
  }
  
}
#endif //RECEIVER


