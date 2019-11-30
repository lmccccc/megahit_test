#include"kmer.h"

kmer::kmer(){
    for (int i = 0; i < KMER_MAX_SIZE/NUM_PER_BYTE; ++i) {
        data[i] = 0;
    }
}

int kmer::len = K;

kmer::kmer(string s) {//�ַ���ӳ�䵽kmer��
    // [0] 0001 0000 ���� $A
    // [1] 0011 0010 ���� CG �ܹ�����$ACG
    int i;
    int loc;
	for (i = 0; i < K; ++i) {
		loc = i / NUM_PER_BYTE;

		//��������
		data[loc] >>= WORD_WIDTH;
		data[loc] |= mole_encode(s[i]);
	}
	//����
	while(i%NUM_PER_BYTE != 0){
        data[loc] >>= WORD_WIDTH;
        ++i;
	}
}

string kmer::to_string() {//����ת�ַ�����-A -C -G -T ��Ӧa c g t����ת��
    // [0] 0001 0000 ���� $A
    // [1] 0011 0010 ���� CG �ܹ�����$ACG
    string res;
    static unsigned int saved = (int)(255-(pow(2, WORD_WIDTH)-1));//0b11110000
    for (int i = 0; i < len; ++i) {
        int pos = i / NUM_PER_BYTE;
        int shift = NUM_PER_BYTE-1-(i % NUM_PER_BYTE);
        uint8_t d = data[pos];
        d = (d<<shift*WORD_WIDTH)&saved;//��ȡҪ����Ĳ���
        res.append(1, mole_decode(d));//���벢�����ַ���
    }
    return res;
}

const uint8_t* kmer::get_data(){
    return data;
}

const uint8_t kmer::get_tail() {//��ȡ���һ��Ԫ��
    int pos = ceil(K/NUM_PER_BYTE)-1;
    int shift = (K % NUM_PER_BYTE)*4;
    return (data[pos]<<shift)&0b11110000;
}

bool kmer_compare_dec(kmer k1, kmer k2){//ǰ׺����������
    //ֻ��Ҫ�Ӻ���ǰ���αȴ�С
    int i;
    if(K%NUM_PER_BYTE == 0){
        //�����Ҫ������ĩλ
        uint8_t t1 = k1.get_data()[K/NUM_PER_BYTE-1] << WORD_WIDTH;
        uint8_t t2 = k2.get_data()[K/NUM_PER_BYTE-1] << WORD_WIDTH;
        if(t1 < t2) return true;
        else if(t1 > t2) return false;
        i = K/NUM_PER_BYTE-2;
    }
    else{
        i = K/2;
    }
    for (; i >= 0 ; --i) {
        if(k1.get_data()[i] < k2.get_data()[i]) return true;
        else if(k1.get_data()[i] > k2.get_data()[i]) return false;
    }

    //����ǰ׺������У�����ĩλ���򣬷����ظ��Ĳ��ҡ�
    if(K%NUM_PER_BYTE == 0){
        uint8_t t1 = k1.get_data()[K/NUM_PER_BYTE-1] & 0b11110000;
        uint8_t t2 = k2.get_data()[K/NUM_PER_BYTE-1] & 0b11110000;
        return t1 < t2;
    }
    return false;
}

void kmer_sort(kmer_list_t& list){
    sort(list.begin(), list.end(), kmer_compare_dec);
}

void kmer_save(kmer_list_t& list, string path){
    ofstream ofs;
    ofs.open(path);
    assert(ofs.is_open());
    kmer_list_t::iterator itr;
    itr = list.begin();
    while(itr!=list.end()) {
        ofs << itr->to_string() << endl;
        itr++;
    }
    ofs.close();
    return;
}

//-----------��������ɾ����Ч���---------
bool is_pre_dummy(kmer_list_t::iterator itr){//��ͷΪ$
    return itr->get_data()[0] << WORD_WIDTH == DUMMY;
}
bool pre_equal(kmer_list_t::iterator itr, kmer_list_t::iterator end){
    kmer_list_t::iterator itr2 = itr+1;
    if(itr2 == end) return false;
    for(int i = 1; i < K/NUM_PER_BYTE; ++i){
        if(itr->get_data()[i] != itr2->get_data()[i]) return false;
    }
    return true;
}

bool is_fix_dummy(kmer_list_t::iterator itr){//��βΪ$
    return (itr->get_data()[K/NUM_PER_BYTE-1] & 0b11110000) == DUMMY;
}
bool fix_equal(kmer_list_t::iterator itr, kmer_list_t::iterator end){
    kmer_list_t::iterator itr2 = itr+1;
    if(itr2 == end) return false;
    for(int i = 1; i < K/NUM_PER_BYTE; ++i){
        if(itr->get_data()[i] != itr2->get_data()[i]) return false;
    }
    return true;
}

void kmer_delete_dummy(kmer_list_t& list){
    kmer_list_t::iterator itr;
    itr = list.begin();
    while(itr!=list.end()) {
        if(is_pre_dummy(itr)){
            //����Ѱ����ȵ� $��С ��ȵ�ֻ�����·� �ҵ�ɾ��
            if(pre_equal(itr, list.end())) itr = list.erase(itr);
            else itr++;
        }
        else if(is_fix_dummy(itr)){
            //ͬ�� ����Ѱ�� �ҵ�ɾ��
            if(fix_equal(itr, list.end())) itr = list.erase(itr);
            else itr++;
        }
        else itr++;
    }
}

