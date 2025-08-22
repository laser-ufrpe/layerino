class PIN {
public:
  int gpio;
  PIN(int arg) : gpio(arg) {}

  int adc() const { return analogRead(gpio); }
  int get() const { return digitalRead(gpio); }

//  void  dac(int val)           const { dacWrite(gpio, val); }
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
  std::array<PIN, N> pins;

  template<typename... Ts>
  PINS(Ts... args) : pins{ PIN(args)... } {}

  constexpr int size()           const { return pins.size(); }
  PIN& operator[](int idx)             { return pins[idx]; }
  const PIN& operator[](int idx) const { return pins[idx]; }

  void set(int val) const { for (auto& p : pins) p.set(val); }
  void pwm(int val) const { for (auto& p : pins) p.pwm(val); }

  void input()      const { for (auto& p : pins) p.input(); }
  void output()     const { for (auto& p : pins) p.output(); }
  void pullup()     const { for (auto& p : pins) p.pullup(); }
  void pulldown()   const { for (auto& p : pins) p.pulldown(); }
  void opendrain()  const { for (auto& p : pins) p.opendrain(); }

  void pwmio(int res, int freq)               const { for (auto& p : pins) p.pwmio(res, freq); }
  void adcio(int res, adc_attenuation_t attn) const { for (auto& p : pins) p.adcio(res, attn); }
};
//==========================================================
template<typename... Ts>
PINS(Ts... args) -> PINS<sizeof...(Ts)>; // auto-detect args number
