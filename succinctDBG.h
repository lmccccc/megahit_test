#ifndef UNTITLED_SUCCINCTDBG_H
#define UNTITLED_SUCCINCTDBG_H

#include <iostream>
#include <iomanip>
#include <bitset>
#include"kmer.h"

class succinctDBG {
private:
    uint8_t *W;//4bit
    uint8_t *Last;//1bit
    int F[4];//固定长度 分别代表ACGT
    uint8_t *Tip;//1bit
    int len;

    void form(kmer_list_t&);

    void pushInfo(int, bool, bool, uint8_t);

public:

    explicit succinctDBG(kmer_list_t);

    uint8_t get_W(const int) const;

    int get_F(const int) const;

    bool get_Tip(const int) const;

    int get_F_by_order(int) const;

    int getlen();

    friend class rank_list;

    friend class select_list;
};


#endif
