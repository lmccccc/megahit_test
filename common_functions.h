#ifndef COMMONFUN
#define COMMONFUN

#include"defination.h"
#include<cassert>
#include <cstdint>
#include <cstdlib>
#include <cmath>
using namespace std;

unsigned char mole_encode(const char c);

char mole_decode(unsigned char c);

uint8_t convert(uint8_t val);

uint8_t mole_map(uint8_t c);



#endif


