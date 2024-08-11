#include <bits/stdc++.h>
using namespace std;
int main() {
    default_random_engine e;
    e.seed(time(NULL));
    uniform_int_distribution<int> u(1,66666666);
    ofstream fout1("insert.txt");
    ofstream fout2("query.txt");
    for(int i=0;i<1000000;i++)fout1<<u(e)<<" ";
    for(int i=0;i<10000000;i++)fout2<<u(e)<<" ";
    fout1.close();fout2.close();
    return 0;
}