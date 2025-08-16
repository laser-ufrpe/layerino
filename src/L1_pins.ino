class PIN {
public:
  usize_t gpio;
  usize_t ledc;
  PIN(usize_t arg) : gpio(arg) {}

  void input()     const { pinMode(gpio, INPUT); }
  void output()    const { pinMode(gpio, OUTPUT); }
  void pullup()    const { pinMode(gpio, INPUT_PULLUP); }
  void pulldown()  const { pinMode(gpio, INPUT_PULLDOWN); }
  void opendrain() const { pinMode(gpio, OUTPUT_OPEN_DRAIN); }

  void low()             const { digitalWrite(gpio, LOW); }
  void high()            const { digitalWrite(gpio, HIGH); }
  void dac(usize_t val)  const { dacWrite(gpio, val); }
  void dig(usize_t val)  const { digitalWrite(gpio, val); }

  i32_t adc() const { return analogRead(gpio); }
};
//==========================================================
template<usize_t N>
class PINS {
public:
  arr<PIN, N> gpios;

  gents_t PINS(Ts... args) : gpios{ PIN(args)... } {}

  constexpr usize_t size() const           { return gpios.size(); }
  PIN& operator[](usize_t idx)             { return gpios[idx]; }
  const PIN& operator[](usize_t idx) const { return gpios[idx]; }
};
//==========================================================
gents_t PINS(Ts... args) -> PINS<sizeof...(Ts)>;
