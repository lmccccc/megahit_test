#include"read.h"
using namespace std;

read::read(){}

read::read(string& s, bool ini){//��ʼ��
    if(ini) s = '$'+s+'$';//���ǳ�ʼ����ǰ�����$
    data = s;
}

void read::to_kmer(kmer_list_t& kmer_list){
    if(data.size() < K) return;
    for (int i = 0; i < data.size()-K+1; ++i) {
        kmer_list.push_back(kmer(data.substr(i, i+K)));
    }
}

kmer_list_t load_data(const char *filepath, bool ini) {//�����ļ�����ʱ��ͨ�ļ����������ڿɸĳɲ��ж�ȡ
    //���ļ�
    ifstream ifs;
    ifs.open(filepath, ios::in|ios::out|ios::binary);
    assert(ifs.is_open());

    string read_str;
    kmer_list_t kmer_list;
    int cnt = 0;
    while (getline(ifs, read_str)) {//�ɹ���ȡ
        cnt++;
        if (read_str[0] == '>') continue;//�ٶ�fasta��ʽ

        //stringתread
        read one_read(read_str, ini);

        //readתkmer����list
        one_read.to_kmer(kmer_list);
    }
    ifs.close();
    cout << "size = " << cnt << " * " << K << endl;
    return kmer_list;
}