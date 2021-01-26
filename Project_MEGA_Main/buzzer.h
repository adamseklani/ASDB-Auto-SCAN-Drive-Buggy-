class BUZ_control{
  public:

  void Begin(byte GPIO_pin){
    pinMode(GPIO_pin, OUTPUT);
  }

  void ON(byte GPIO_pin){
    for (int a = 0; a < 80; a++){
    //digitalWrite(GPIO_pin, HIGH);
    delay(1);
    //digitalWrite(GPIO_pin, LOW);
    delay(1);}
    delay(50);
    for (int b = 0; b < 100; b++) { 
    digitalWrite(GPIO_pin, HIGH);
    delay(2);
    digitalWrite(GPIO_pin, LOW);
    delay(2);}
    }
    void OFF(byte GPIO_pin){
   digitalWrite(GPIO_pin, LOW);
    }
    void sound(byte GPIO_pin, int flash_speed, int flashes){
      for (int i=0; i<flashes; i=i+1){
        ON(GPIO_pin);
        delay(flash_speed);
        OFF(GPIO_pin);
        delay(flash_speed);
      }
    }
};
