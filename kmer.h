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
	uint8_t data[KMER_MAX_SIZE/NUM_PER_BYTE];//һ��byt{}e�洢4����Ϣ��[0]Ϊ��λ����read˳���ȡ����ˣ�һ��byte�ĸ�λΪʵ�ʵĵ�λ����ȡʱ��ǰ����<<��λ����λ��
    // [0] 0001 0000 ���� $A
    // [1] 0011 0010 ���� CG �ܹ�����$ACG
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
��acgt���룬��$ A C G T -A -C -G -T 9�֣� ��Ӧ 0000 0001 0010 0011 0100 0101 0110 0111 1000 ռ��4bit
*/