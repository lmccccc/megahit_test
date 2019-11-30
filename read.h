#ifndef READDEF
#define READDEF

#include<string>
#include<fstream>
#include<iostream>
#include"common_functions.h"
#include"kmer.h"

using namespace std;

class read {
private:
    string data;

public:
	read();

	explicit read(string&, bool);

    void to_kmer(kmer_list_t&);
};

kmer_list_t load_data(const char *, bool);//读取文件

#endif