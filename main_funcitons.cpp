#include"main_functions.h"

void load_and_sort(const char *path1, const char *path2){
    std::cout << "Testing!" << std::endl;
    //直接转为kmer保存
    kmer_list_t res = load_data(path1, true);
    //排序
    kmer_sort(res);
    //去除多余虚边
    kmer_delete_dummy(res);

    kmer_list_t::iterator itr;
    itr = res.begin();
    int cnt = 0;
    while(itr!=res.end()) {
        cout << itr->to_string() << endl;
        itr++;
        cnt++;
    }
    cout << "size = " << cnt << " * " << K << endl;
    kmer_save(res, path2);
}
