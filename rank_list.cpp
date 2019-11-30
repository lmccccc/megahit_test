#include "rank_list.h"


rank_list::rank_list(succinctDBG dbg) {
    len = dbg.len;
    for(int i = 0; i < 5; ++i){//初始化
        wList[i] = new uint8_t[len];
        wList[i][0] = 0;
    }
    form_W(dbg);


    for(int i = 0; i < 2; ++i){//初始化
        lastList[i] = new uint8_t[len];
        lastList[i][0] = 0;
    }
    form_Last(dbg);

    cout << "rank W list ";
    cout  << endl;
    for (int k = 0; k < len; ++k) {
        cout << left << setw(3) << k << ' ';
    }
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < len; ++j) {
            cout << left << setw(3) << (int)wList[i][j] << ' ';
        }
        cout << endl;
    }

    cout << "rank last list ";
    cout << endl;
    for (int j = 0; j < len; ++j) {
        cout << left << setw(3) << (int)lastList[1][j] << ' ';
    }
    cout << endl;
}

void rank_list::form_W(succinctDBG dbg){
    wList[mole_map(dbg.W[0]<<4)][0]=1;
    uint8_t mask = 0b11110000;

    for (int i = 1; i < len;) {//逐个取数
        for (int k = 0; k < 2 && i < len; ++k) {//从1byte中取数
            for (int j = 0; j < 5; ++j) {//对每个赋初值
                wList[j][i] = wList[j][i-1];
            }
            int loc = i / 2;
            int shift = ((i+1) % 2) * 4;
            uint8_t data = (dbg.W[loc]<<shift) & mask;
            if(data > mT) assert(0);
            int ind = mole_map(data);//找出对应的数
            wList[ind][i]++;//该数加一
            ++i;
        }
    }
}

void rank_list::form_Last(succinctDBG dbg){
    uint8_t mask = 0b00000001;
    lastList[dbg.Last[0]&mask][0] = 1;

    for (int i = 1; i <= len;) {//逐个取数
        for (int k = 0; k < 8 && i <= len; ++k) {//从1byte中取数
            for (int j = 0; j < 2; ++j) {//对每个赋初值
                lastList[j][i] = lastList[j][i-1];
            }
            int loc = i/8;
            int shift = i % 8;
            int ind = (dbg.Last[loc]>>shift) & mask;//找出对应的数
            lastList[ind][i]++;//该数加一
            ++i;
        }
    }
}

uint8_t rank_list::rank_w(int loc, uint8_t c) const {
    return wList[c][loc];
}

uint8_t rank_list::rank_last(int loc, uint8_t c) const {
    if(loc<0) return 0;
    return lastList[c][loc];
}
