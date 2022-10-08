#include <bitset>
#include <cstdint>
#include <iostream>

uint32_t EncodeInt(int32_t number) {
  return number < 0 ? (((uint32_t)(-number)) * 2 - 1) : number * 2;
}

int32_t DecodeInt(uint32_t number) { return (number >> 1) ^ -(number & 1); }

int main(int argc, char const *argv[]) {
  int      number  = -23;
  uint32_t encoded = EncodeInt(number);
  int      decoded = DecodeInt(encoded);

  std::cout << "number:  " << std::bitset<32>(number) << std::endl;
  std::cout << "encoded: " << std::bitset<32>(encoded) << std::endl;
  std::cout << "decoded: " << std::bitset<32>(decoded) << std::endl;
  return 0;
}
