class LED_control{
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
    void FLASH(byte GPIO_pin, int FLASHSPD, int FLASHES){
      for (int i=0; i<FLASHES; i=i+1){
        ON(GPIO_pin);
        delay(FLASHSPD);
        OFF(GPIO_pin);
        delay(FLASHSPD);
      }
    }
};
