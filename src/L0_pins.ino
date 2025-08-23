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
//                   MULTIPLE PINS CLASS
//==========================================================
template<int N>
class PINS {
public:
  arr< PIN, N >        pins;
  arr< int, 1<<(N-1) > muxseq;

  constexpr int size()           const { return pins.size(); }
  PIN& operator[](int idx)             { return pins[idx]; }
  const PIN& operator[](int idx) const { return pins[idx]; }

  gents_t PINS(Ts... args) : pins{ PIN(args)... } {}
  gents_t void pwm(Ts... vals) const {
    int values[] = { vals... };
    for (int i = 0; i < N; i++) {
      pins[i].pwm(values[i]);
    }
  }
//==========================================================
  gents_t void dmuxio(int res, adc_attenuation_t attn, Ts... order) {
    muxseq = { order... };
    pins[0].output();
    for (int i = 1; i < N; i++) pins[i].output();
  }
  gents_t void amuxio(int res, adc_attenuation_t attn, Ts... order) {
    muxseq = { order... };
    pins[0].adcio(res, attn);
    for (int i = 1; i < N; i++) pins[i].output();
  }
//==========================================================
  void input()      const { for (auto& p : pins) p.input(); }
  void output()     const { for (auto& p : pins) p.output(); }
  void pullup()     const { for (auto& p : pins) p.pullup(); }
  void pulldown()   const { for (auto& p : pins) p.pulldown(); }
  void opendrain()  const { for (auto& p : pins) p.opendrain(); }

  void pwmio(int res, int freq)               const { for (auto& p : pins) p.pwmio(res, freq); }
  void adcio(int res, adc_attenuation_t attn) const { for (auto& p : pins) p.adcio(res, attn); }
  
  void set(int bitmask) {
    for(int i = N-1; i > -1; i--) {
      pins[i].set(bitmask & 1);
      bitmask = bitmask>>1;
    }
  }
//==========================================================
  arr<int, N> get() const {
    arr<int, N> states{};
    for (int i = 0; i < N; i++) { states[i] = pins[i].get(); }
    return states;
  }

  arr<int, N> adc() const {
    arr<int, N> values{};
    for (int i = 0; i < N; i++) {
      values[i] = pins[i].adc();
    }
    return values;
  }
};
//==========================================================
gents_t PINS(Ts... args) -> PINS<sizeof...(Ts)>; // auto-detect args number
