//
// Created by lmc on 2019/11/25.
//

#include "select_list.h"

select_list::select_list(succinctDBG dbg) {
    len = dbg.len;
    for(int i = 0; i < 5; ++i){
        wList[i] = new uint8_t[len+1];
    }
    for(int i = 0; i < 2; ++i){//初始化
        lastList[i] = new uint8_t[len+1];
    }
    lastItr[0] = lastItr[1] = 1;
    for (int i = 0; i < 5; ++i) wItr[i] = 1;

    form_W(dbg);
    form_Last(dbg);


    cout << "select W list ";
    cout  << endl;
    for (int k = 0; k < len; ++k) {
        cout << left << setw(3) << k << ' ';
    }
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < wItr[i]; ++j) {
            cout << left << setw(3) << (int)wList[i][j] << ' ';
        }
        cout << endl;
    }

    cout << "select last list ";
    cout << endl;
    for (int j = 0; j < lastItr[1]; ++j) {
        cout << left << setw(3) << (int)lastList[1][j] << ' ';
    }
    cout << endl;
}

void select_list::form_W(succinctDBG dbg){
    for (int i = 0; i < len; ++i) {
        int loc = i / 2;
        int shift = ((i+1) % 2)*4;
        uint8_t t = mole_map((dbg.W[loc]<<shift)&0b11110000);
        wList[t][wItr[t]] = i;
        wItr[t]++;
    }
}

void select_list::form_Last(succinctDBG dbg) {
    for (int i = 0; i < len; ++i) {
        int loc = i / 8;
        int shift = i % 8;
        uint8_t t = (dbg.Last[loc] >> shift)&0b00000001;
        lastList[t][lastItr[t]] = i;
        lastItr[t]++;
    }
}

uint8_t select_list::select_w(int loc, int c) const{
    return wList[c][loc];
}

uint8_t select_list::select_last(int loc, uint8_t c) const {
    return lastList[c][loc];
}

int fwd(const select_list& sel, const rank_list& rnk, const succinctDBG& dbg, const int i){
    //fwd(i)=select(Last,rank(w,i,abs(w[i])) + rank(last,F[abs(w[i])],1),1)
    //不可用于$后缀
    uint8_t w = mole_map(dbg.get_W(i));//abs(w[i]))
    if(w==0) return -1;
    uint8_t a = rnk.rank_w(i, w);//rank(w,i,abs(w[i]))
    uint8_t f = dbg.get_F(w-1);//F[abs(W[i])]
    int b = rnk.rank_last(f-1, 1);//rank(last,F[abs(w[i])],1),1)
    return sel.select_last(a+b, 1);
}

int bwd(const select_list& sel, const rank_list& rnk, const succinctDBG& dbg, const int i){
    //bwd(i)=select(W,rank(Last,i-1,1) - rank(Last,F[c]-1,1),c)
    //不可用于tip=1
    if(dbg.get_Tip(i)==1) return -1;
    int f = dbg.get_F_by_order(i);//分子在F中的index
    int a = rnk.rank_last(i, 1);
    int b = rnk.rank_last(dbg.get_F(f)-1, 1);
    int t= sel.select_w(a-b, f+1);
    return sel.select_w(a-b, f+1);
}