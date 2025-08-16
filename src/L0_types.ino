// GENERICS
#define gent_t template<typename T>
#define gents_t template<typename... Ts>
#define gentn_t template<typename T, usize_t N >
#define genkv_t template<typename K, typename V>

// UNSIGNED
using u8_t  = std::uint8_t;
using u16_t = std::uint16_t;
using u32_t = std::uint32_t;
using u64_t = std::uint64_t;

// SIGNED
using i8_t  = std::int8_t;
using i16_t = std::int16_t;
using i32_t = std::int32_t;
using i64_t = std::int64_t;

// FLOAT
using f32_t   = float;
using f64_t   = double;

// SPECIAL
using any_t   = std::any;
using str_t   = std::string;
using usize_t = std::size_t; 
