#include "succinctDBG.h"


succinctDBG::succinctDBG(kmer_list_t list) {
    int size = list.size();
    W = new uint8_t[(int)ceil(size/2)];
    Last = new uint8_t[(int)ceil(size/8)];
    Tip = new uint8_t[(int)ceil(size/8)];
    len = 0;
    for (int i = 0; i < 4; ++i) {
        F[i] = 0;
    }
    form(list);
    for(int i = 0; i < 4; ++i) cout << F[i] << endl;
}

void succinctDBG::pushInfo(int w, bool tip, bool last, uint8_t c) {
    int _pos = len/2;
    W[_pos] >>= 4;
    W[_pos] |= w;

    int pos = len / 8;
    Last[pos] >>= 1;
    Last[pos] |= last?0b10000000:0;

    Tip[pos] >>= 1;
    Tip[pos] |= tip?0b10000000:0;

    int k;
    if (c==A) k = 1;
    else if(c == C) k = 2;
    else if(c == G) k = 3;
    else if(c == T) k = 4;
    else assert(0);
    for(int i = k; i < 4; ++i){
        F[i]++;
    }

    cout << left << setw(10) << len << ' ';
    cout << mole_decode(w) << ' ';
    cout << tip << ' ';
    cout << last << ' ';
    cout << endl;

    len++;
}

//用于succinct 的函数
static bool suf_equal(kmer_list_t::iterator k1, kmer_list_t::iterator k2){
    //后缀是否相等
    if(k1->get_data()[0]>>4 != k2->get_data()[0]>>4) return false;
    for (int i = 1; i < ceil(K/NUM_PER_BYTE); ++i) {
        if(k1->get_data()[i] != k2->get_data()[i]) return false;
    }
    return true;
}

static bool pre_equal(kmer_list_t::iterator k1, kmer_list_t::iterator k2){
    //前缀是否相等
    for (int i = 0; i < ceil(K/NUM_PER_BYTE)-2; ++i) {
        if(k1->get_data()[i] != k2->get_data()[i]) return false;
    }
    uint8_t t1 = (k1->get_data()[(int)ceil(K/NUM_PER_BYTE)-1])<<4;
    uint8_t t2 = (k2->get_data()[(int)ceil(K/NUM_PER_BYTE)-1])<<4;
    return t1 == t2;
}

static bool mid_equal(kmer_list_t::iterator k1, kmer_list_t::iterator k2){
    //中间是否相等
    if(k1->get_data()[0]>>4 != k2->get_data()[0]>>4) return false;
    for (int i = 1; i < ceil(K/NUM_PER_BYTE)-2; ++i) {
        if(k1->get_data()[i] != k2->get_data()[i]) return false;
    }
    uint8_t t1 = (k1->get_data()[(int)ceil(K/NUM_PER_BYTE)-1])<<4;
    uint8_t t2 = (k2->get_data()[(int)ceil(K/NUM_PER_BYTE)-1])<<4;
    return t1 == t2;
}

void succinctDBG::form(kmer_list_t& list) {
    kmer_list_t::iterator itr1;
    kmer_list_t::iterator temp;

    int ind = 0;
    itr1 = list.begin();
    while (itr1 != list.end()) {

        //W
        uint8_t w = itr1->get_tail();
        if(itr1!= list.begin()){
            temp = itr1-1;
            while(mid_equal(temp, itr1)) {
                if (w == temp->get_tail()) {
                    w = convert(w);
                    break;
                }
                if(temp == list.begin()) break;
                --temp;
            }
        }
        //tip
        bool tip = ((uint8_t)(itr1->get_data()[0]<<4)) == DUMMY;//类型不匹配返回false
        //last
        temp = itr1+1;
        bool last;
        if(temp == list.end()) last = true;
        else {
            last = !pre_equal(temp, itr1) && !tip;
        }
        //c 即找出决定F的c，倒数第二个字符
        int loc = ceil(K/2)-1;
        int shift = ((K+1)%2)*4;
        uint8_t mask = 0b11110000;
        uint8_t c = (itr1->get_data()[loc]<<shift)&mask;
        if(c==0) assert(0);

        this->pushInfo(w, tip, last, c);
        itr1++;
        ind++;
    }

    //push之后最末尾的参数位置需要调整
    int shift = len % 8;
    int pos = len / 8;
    Tip[pos] >>= 8-shift;
    Last[pos] >>= 8-shift;
    W[(int)((len-1)*1.0/2)] >>= (len%2)*4;
}

uint8_t succinctDBG::get_W(const int i) const {
    int loc = i/2;
    int shift = ((i+1)%2)*4;
    return (W[loc]<<shift)&0b11110000;
}

int succinctDBG::get_F(const int t) const{
    if(t<0) return -1;
    return F[t];
}

bool succinctDBG::get_Tip(const int i) const{
    int loc = i / 8;
    int shift = i % 8;
    return (Tip[loc]>>shift)&0b00000001;
}

int succinctDBG::get_F_by_order(int t) const {
    for(int i = 1; i < 4; ++i){
        if(t < F[i]) return i-1;
    }
    return 3;
}

int succinctDBG::getlen() {
    return len;
}