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
#define BUTTON_PIN  2
#define LED_PIN  13
#define RX_PIN  7


void setup()
{
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  pinMode(RX_PIN,OUTPUT);
  digitalWrite(RX_PIN,LOW);
 
  
  digitalWrite(LED_PIN, LOW);

  Serial.begin(1200);  // Hardware supports up to 2400, but 1200 gives longer range
}

#ifdef TRANSMITTER
void loop()
{

  writeUInt(158); // Put any number you want to send here
  digitalWrite(LED_PIN, HIGH);
  
}
#endif //TRANSMITTER

#ifdef RECEIVER
int cnt = 0;
int threshold = 20;
void loop()
{
  boolean light_led = false;

  
  if (readUInt(true) == 158) // Check to see if we got the test number
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
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(RX_PIN, HIGH);
    delay(50);
    digitalWrite(RX_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }
  
}
#endif //RECEIVER


