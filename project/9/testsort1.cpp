#include <cstring>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <random>
using namespace std;
vector <int> a;
int main(){
    std::random_device rd;
    std::mt19937 rng(rd());
    for(int i=0;i<100;i++)a.push_back(i);
    shuffle(a.begin(),a.end(),rng);

    sort(a.begin(),a.begin()+10);

    for(int i=0;i<10;i++)cout<<a[i]<<" ";
    return 0;
}