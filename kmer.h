#ifndef KMERDEF
#define KMERDEF

#include<cstdint>
#include<vector>
#include<string>
#include<fstream>
#include<cmath>
#include<algorithm>
#include"common_functions.h"

using namespace std;

class kmer {
private:
	uint8_t data[KMER_MAX_SIZE/NUM_PER_BYTE];//一个byt{}e存储4个信息，[0]为高位，即read顺序读取的左端，一个byte的高位为实际的低位（读取时先前数据<<移位到高位）
    // [0] 0001 0000 代表 $A
    // [1] 0011 0010 代表 CG 总共代表$ACG
public:
	kmer();

	explicit kmer(string);

	string to_string();

	const uint8_t* get_data();

    static int len;

    const uint8_t get_tail();
};

typedef vector<kmer> kmer_list_t;

void kmer_sort(kmer_list_t&);

void kmer_save(kmer_list_t&, string);

void kmer_delete_dummy(kmer_list_t&);

#endif

/*
对acgt编码，有$ A C G T -A -C -G -T 9种， 对应 0000 0001 0010 0011 0100 0101 0110 0111 1000 占用4bit
*/