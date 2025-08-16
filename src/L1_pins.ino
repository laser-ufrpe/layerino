class PIN {
public:
  usize_t pin;
  PIN(usize_t arg) : pin(arg) {}
};
//==========================================================
template<usize_t N>
class PINS {
public:
  arr<PIN, N> pins;

  gents_t PINS(Ts... args) : pins{ PIN(args)... } {}

  constexpr usize_t size() const           { return pins.size(); }
  PIN& operator[](usize_t idx)             { return pins[idx]; }
  const PIN& operator[](usize_t idx) const { return pins[idx]; }
};
//==========================================================
gents_t PINS(Ts... args) -> PINS<sizeof...(Ts)>;
