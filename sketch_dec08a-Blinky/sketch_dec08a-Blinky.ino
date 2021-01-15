//#include"classes.h"
class LED_Control{
  public:

  void Begin(byte GPIO_pin){
    pinMode(GPIO_pin, OUTPUT);
  }

  void ON(byte GPIO_pin){
    digitalWrite(GPIO_pin, HIGH);
  }
    void OFF(byte GPIO_pin){
    digitalWrite(GPIO_pin, LOW);
    }
    //void flash{byte GPIO_pin, int flash_speed, int flashes}{
      //for (int i=0; i<flashed; f=f+1){
        //ON(GPIO_pin);
        //delay(flash_speed);
        //OFF(GPIO_pin);
        //delay(flash_speed)
      //}
};
// Class      Object 
LED_Control   LED;

void setup() {
  // put your setup code here, to run once:
 //set up LED pin mode
 //const int red_led = 49;
//pinMode(red_led, OUTPUT);
LED.Begin(LED_BUILTIN);
}

void loop() {
  // put your main code here, to run repeatedly:
LED.ON(LED_BUILTIN);
delay(1000);
LED.OFF(LED_BUILTIN);
delay(1000);
//LED.Flash(LED_BUILTIN,100,10);


  //for (int i=0; i<5; i++){
//digitalWrite(red_led, HIGH);
///delay(1000);
//digitalWrite(red_led, LOW);
//delay(1000);
  }
