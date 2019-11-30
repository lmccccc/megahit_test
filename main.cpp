#include <iostream>
#include"main_functions.h"
#include "succinctDBG.h"
#include "rank_list.h"
#include "select_list.h"


int main() {
    //while(true){
        string order;
        //cin >> order;
        order = "1";
        const char* path1;
        const char* path2;
        //读取数据 构建kmer 排序 删除虚边
        if(order == "load_and_sort" || order == "0"){
            path1 = "/home/lmc/r3_1.fa";
            path2 = "/home/lmc/sorted.txt";
            load_and_sort(path1, path2);
        }
        //根据第一步构建的kmer 压缩构建succinctDBG
        //测试fwd和bwd的正确性
        else if(order == "succinct" || order == "1"){
            path1 = "/home/lmc/sorted.txt";

            kmer_list_t list = load_data(path1, false);
            succinctDBG dbg(list);

            //构建rank
            rank_list rl(dbg);//rank_list.h中include"succDBG"，不可存在include循环

            //构建select
            select_list sl(dbg);

            //验证正确
            //fwd bwd
            //int temp = 35;
            //int _f = fwd(sl, rl, dbg, temp);
            //int _b = bwd(sl, rl, dbg, temp);
            //cout << _f << endl << _b << endl;

        }

        //else if(order == "exit" || order == "quit" || order == "9"){
        //    break;
        //}
    //}

    return 0;
}