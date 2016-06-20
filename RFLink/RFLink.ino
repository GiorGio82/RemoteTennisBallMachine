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
#define RX_PIN  12

// Button hardware is setup so the button goes LOW when pressed
#define BUTTON_PRESSED LOW
#define BUTTON_NOT_PRESSED HIGH

void setup()
{
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  pinMode(RX_PIN,OUTPUT);
  digitalWrite(RX_PIN,LOW);
 
  
  digitalWrite(LED_PIN, LOW);

  Serial.begin(1200);  // Hardware supports up to 2400, but 1200 gives longer range
  //Serial.println("Start");
}

#ifdef TRANSMITTER
void loop()
{
  static int prev_button = BUTTON_NOT_PRESSED;  // Previous button press value
  int        cur_button;                        // Current button press value

  cur_button = digitalRead(BUTTON_PIN);
  
  if ((prev_button == BUTTON_NOT_PRESSED) && (cur_button == BUTTON_PRESSED))
  {
   
    
  }

  delay(500);
  writeUInt(158); // Put any number you want to send here (71 is just a test)
  //delay(50); // Debounce button
  //prev_button = cur_button;
  delay(500);
  
}
#endif //TRANSMITTER

#ifdef RECEIVER
void loop()
{
  boolean light_led = false;

  
  if (readUInt(true) == 158) // Check to see if we got the 71 test number
  {
    light_led = true;
    digitalWrite(LED_PIN, HIGH);
    //Serial.println("rx");
  }
  digitalWrite(LED_PIN, LOW);

  
  if (light_led)
  {
    light_led = false;
    digitalWrite(LED_PIN, LOW);
    digitalWrite(RX_PIN, HIGH);
    delay(50);
    digitalWrite(RX_PIN, LOW);
  }
  
}
#endif //RECEIVER


