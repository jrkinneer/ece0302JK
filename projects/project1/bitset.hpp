#ifndef BITSET_HPP
#define BITSET_HPP
#include <string>

class Bitset{
public:

  // default constructor
  Bitset();

  // bitset constructor of size N
  Bitset(intmax_t size);

  // bitset constructor based on string value, has to contain
  // only zeros and ones
  Bitset(const std::string & value);

  // bitset destructor
  ~Bitset();

  Bitset(const Bitset & ) = delete;
  Bitset & operator=(const Bitset &) = delete;

  // returns the size of the bitset
  intmax_t size() const;

  // returns a true or false value after testing if the bitset is valid
  bool good() const;

  // sets the bit at "index" to one, and if index is not in the range of
  //0 to N-1 then the bitset becomes invalid
  void set(intmax_t index);

  // sets the bit at "index" to zero, and if index is not in the range of
  //0 to N-1 then the bitset becomes invalid
  void reset(intmax_t index);

  // toggles the bit at "index", and if index is not in the range of
  //0 to N-1 then the bitset becomes invalid
  void toggle(intmax_t index);

  // returns true if the bit at "index" is one and returns false if it is
  // zero or if index is not in the range of 0 to N-1
  bool test(intmax_t index);

  // returns the bitset as a string of zeros and ones
  std::string asString() const;

private:
  
  bool validity;

  intmax_t length = 0;
  
  intmax_t *bset;
  
};

#endif
