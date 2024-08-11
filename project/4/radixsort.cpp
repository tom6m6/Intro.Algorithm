#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
using namespace std;
int n;
void radixsort(vector<int>& arr);
int getdigit(int num, int digit);

int main(){
    clock_t startTime, endTime;
    ifstream fin("data.txt");
    ofstream fout("result.txt");
    fin>>n;
    vector<int> arr;
    int tmp;
    for(int i=0;i<n;i++){
        fin>>tmp;
        arr.push_back(tmp);
    }

    startTime=clock();
    radixsort(arr);
    endTime=clock();
    cout<<"Time: "<<(1000*( (double) (endTime - startTime) / CLOCKS_PER_SEC))<<"ms"<<endl;
    for (int i:arr)fout <<i<<" ";
    fin.close();
    fout.close();
    return 0;
}
void radixsort(vector<int>& arr) {
    if (arr.empty())return;

    int maxnum=arr[0];
    for (int num:arr) if (num>maxnum)maxnum=num;

    int maxdigit=0;
    while (maxnum>0) {
        maxnum/=10;maxdigit++;
    }

    vector<vector<int>> buckets(10);
    //毕竟是根据十进制来基数排序了，每一位的可能性也就是0-9，所以设置了十个大桶

    for (int i=1;i<=maxdigit;i++) {
        for (int j:arr){
            int idx=getdigit(j,i);
            buckets[idx].push_back(j);
        }
        //重新放回
        int tmp_idx=0;
        for (vector<int>& bucket : buckets) {
            for (int j: bucket) {
                arr[tmp_idx++] = j;
            }
            bucket.clear();
            //最后放好了之后一定别忘了把这个桶给清空了！
        }
    }
}

int getdigit(int num,int digit) {
    //获取数字的指定位数
    int tmp=1;
    for (int i=0;(i+1)<digit; i++)tmp *= 10;
    return (num/tmp)%10;
}