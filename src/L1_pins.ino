class PIN {
public:
  int gpio;
  PIN(int arg) : gpio(arg) {}

  int adc() const { return analogRead(gpio); }
  int get() const { return digitalRead(gpio); }

  void  dac(int val)           const { dacWrite(gpio, val); }
  void  pwm(int val)           const { ledcWrite(gpio, val); }
  void  set(int val)           const { digitalWrite(gpio, val); }
  void freq(int val, int time) const { ledcWriteTone(gpio, val); delay(time); }

  void input()      const { pinMode(gpio, INPUT); }
  void output()     const { pinMode(gpio, OUTPUT); }
  void pullup()     const { pinMode(gpio, INPUT_PULLUP); }
  void pulldown()   const { pinMode(gpio, INPUT_PULLDOWN); }
  void opendrain()  const { pinMode(gpio, OUTPUT_OPEN_DRAIN); }

  void pwmio(int res, int freq) const {
    pinMode(gpio, OUTPUT);
    ledcAttach(gpio, freq, res);
  }

  void adcio(int res, adc_attenuation_t attn) const {
    pinMode(gpio, INPUT);
    analogReadResolution(res);
    analogSetAttenuation(attn);
  }
};

//==========================================================
template<int N>
class PINS {
public:
  arr<PIN, N> gpios;

  gents_t PINS(Ts... args) : gpios{ PIN(args)... } {}

  constexpr int size()           const { return gpios.size(); }
  PIN& operator[](int idx)             { return gpios[idx]; }
  const PIN& operator[](int idx) const { return gpios[idx]; }
};
//==========================================================
gents_t PINS(Ts... args) -> PINS<sizeof...(Ts)>; // auto-detect args number
