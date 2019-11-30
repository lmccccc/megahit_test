#include"common_functions.h"

unsigned char mole_encode(const char c){
    switch (c) {
        case'A': return A;
        case'C': return C;
        case'G': return G;
        case'T': return T;
        case'$': return DUMMY;
        case'a': return mA;
        case'c': return mC;
        case'g': return mG;
        case't': return mT;
        default: assert(0);
    }
}

char mole_decode(unsigned char c){
    switch(c){
        case A: return 'A';
        case C: return 'C';
        case G: return 'G';
        case T: return 'T';
        case DUMMY: return '$';
        case mA: return 'a';
        case mC: return 'c';
        case mG: return 'g';
        case mT: return 't';
        default: assert(0);
    }
}

uint8_t convert(uint8_t val){
    if(val==A||val==C||val==G||val==T) return val+64;
    else assert(0);
}

uint8_t mole_map(uint8_t c){//映射到对应数组的索引
    if(c==DUMMY) return 0;
    else if(c == A || c == mA) return 1;
    else if(c == C || c == mC) return 2;
    else if(c == G || c == mG) return 3;
    else if(c == T || c == mT) return 4;
    else assert(0);
}

uint8_t code_abs(uint8_t c){
    return c>T?c-64:c;
}