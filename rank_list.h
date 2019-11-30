#ifndef UNTITLED_RANK_LIST_H
#define UNTITLED_RANK_LIST_H


#include <stdint.h>
#include <cmath>
#include <cassert>
#include "defination.h"
#include "common_functions.h"
#include "succinctDBG.h"

class rank_list {
private:
    uint8_t* wList[5];
    uint8_t* lastList[2];
    int len;

    void form_W(succinctDBG);

    void form_Last(succinctDBG);

public:

    explicit rank_list(succinctDBG);



    uint8_t rank_w(int loc, uint8_t c) const;

    uint8_t rank_last(int loc, uint8_t c) const;

};


#endif //UNTITLED_RANK_LIST_H
