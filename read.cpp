#include"read.h"
using namespace std;

read::read(){}

read::read(string& s, bool ini){//初始化
    if(ini) s = '$'+s+'$';//若是初始化，前后加上$
    data = s;
}

void read::to_kmer(kmer_list_t& kmer_list){
    if(data.size() < K) return;
    for (int i = 0; i < data.size()-K+1; ++i) {
        kmer_list.push_back(kmer(data.substr(i, i+K)));
    }
}

kmer_list_t load_data(const char *filepath, bool ini) {//载入文件（暂时普通文件流处理，后期可改成并行读取
    //读文件
    ifstream ifs;
    ifs.open(filepath, ios::in|ios::out|ios::binary);
    assert(ifs.is_open());

    string read_str;
    kmer_list_t kmer_list;
    int cnt = 0;
    while (getline(ifs, read_str)) {//成功读取
        cnt++;
        if (read_str[0] == '>') continue;//假定fasta格式

        //string转read
        read one_read(read_str, ini);

        //read转kmer存入list
        one_read.to_kmer(kmer_list);
    }
    ifs.close();
    cout << "size = " << cnt << " * " << K << endl;
    return kmer_list;
}