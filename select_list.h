//
// Created by lmc on 2019/11/25.
//

#ifndef UNTITLED_SELECT_LIST_H
#define UNTITLED_SELECT_LIST_H

#include<cstdint>
#include "rank_list.h"
#include "succinctDBG.h"

class select_list {
private:
    uint8_t* wList[5];
    uint8_t* lastList[2];
    int len;
    int wItr[5];
    int lastItr[2];

    void form_W(succinctDBG);

    void form_Last(succinctDBG);

public:
    select_list(succinctDBG);

    uint8_t select_w(int loc, int c) const;

    uint8_t select_last(int loc, uint8_t c) const;
};

int fwd(const select_list&, const rank_list&, const succinctDBG&, const int);

int bwd(const select_list&, const rank_list&, const succinctDBG&, const int);
#endif //UNTITLED_SELECT_LIST_H
