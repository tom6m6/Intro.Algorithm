#include<iostream>
#include<vector>
#include<algorithm>
#include <ctime>
using namespace std;

int partition(vector<int> &arr,int low,int high,int key);

bool cmp(int a,int b){
    return a > b;
}

vector<int> create(int N,int low ,int high,int T){
    vector<int> arr(N);
    srand((unsigned)time(NULL));
    for(int i=0;i<N;i++)
        arr[i] = rand() % (high - low + 1) + low;
    if(T == 1)
        sort(arr.begin(),arr.end());
    else if(T == 2)
        sort(arr.begin(),arr.end(),cmp);
    return arr;
}

void merge(vector<int> &arr,int low,int mid,int high){
    int i = low,j = mid + 1;
    int k = 0;
    vector<int> A(high - low + 1);
    while(i <= mid && j <= high)
        A[k++] = arr[i] <= arr[j] ? arr[i++] : arr[j++];
    while(i <= mid)
        A[k++] = arr[i++];
    while(j <= high)
        A[k++] = arr[j++];
    for(k=0,i=low;k<high-low+1;k++,i++)
        arr[i] = A[k];
}

void mergeSort(vector<int> &arr,int low,int high){
    if(low >= high)
        return;
    int mid = low + (high - low) / 2;
    mergeSort(arr,low,mid);
    mergeSort(arr,mid+1,high);
    merge(arr,low,mid,high);
}   

int getRamdom(int low,int high){
    return rand() % (high - low + 1) + low;
}

int randomizedSelect(vector<int> &arr,int low,int high,int k){
    if(low >= high)
        return low;
    int index = partition(arr,low,high,arr[getRamdom(low,high)]);
    if(index + 1 == k)
        return arr[index];
    else if(index + 1 > k)
        return randomizedSelect(arr,low,index,k);
    else
        return randomizedSelect(arr,index+1,high,k);
}

void InsertSort(vector<int> &arr,int low,int high){
    for(int i=low+1;i<=high;i++){
        int t = arr[i];
        int j;
        for(j=i-1;arr[j] > t && j >= low;j--)
            arr[j+1] = arr[j];
        arr[j+1] = t;
    }
}

int partition(vector<int> &arr,int low,int high,int key){
    int L = low;
    bool hasSwap = false;
    for(int i=low;i<=high;i++){
        if(arr[i] < key)
            swap(arr[i],arr[L++]);
        if(arr[i] == key && !hasSwap){
            swap(arr[i--],arr[high]);
            hasSwap = true;
        }
    }
    if(hasSwap)
        swap(arr[L],arr[high]);
    return L;
}

int findMidofMid(vector<int> &arr,int low,int high){
    int size = high - low + 1;
    if(size == 1)
        return arr[low];
    vector<int> child(size % 5 == 0 ? size / 5 : size / 5 + 1);
    int i = 0;
    for(int j=low,end=min(low+4,high);j <= high;j += 5,end = min(j+4,high)){
        InsertSort(arr,j,end);
        child[i++] = arr[(end + j) / 2];
    }
    return findMidofMid(child,0,i-1);
}

int select(vector<int> &arr,int low,int high,int k){
    if(low >= high)
        return low;
    
    int index = partition(arr,low,high,findMidofMid(arr,low,high));
    if(index + 1 == k)
        return arr[index];
    else if(index + 1 > k)
        return select(arr,low,index,k);
    else
        return select(arr,index+1,high,k);
}

/*int main(){
    vector<int> arr = {4,15,15,4,8,4,15,13,1,2,2,31,6,9,7}; //8 4 6
    cout << partition(arr,0,arr.size()-1,10) << endl;
    for(int i=0;i<arr.size();i++)
        cout << arr[i] << ' ';
    return 0;
}*/

int main(){
    srand((unsigned)time(NULL));
    for(int i=100;i<=1000000;i*=10){
        cout << "数据量为" << i << endl;
        //vector<int> arr = create(i,0,i,3);
        vector<int> arr = create(i,0,i,1);
        vector<int> arr2 = arr;
        vector<int> arr3 = arr;
        long time1 = clock();
        randomizedSelect(arr,0,arr.size()-1,arr.size()/2);
        long time2 = clock();
        cout << "randomizedSelect costs time : " << ((double)time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
        time1 = clock();
        select(arr,0,arr.size()-1,arr.size()/2);
        time2 = clock();
        cout << "select costs time : " << ((double)time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
        time1 = clock();
        mergeSort(arr,0,arr.size()-1);
        time2 = clock();
        cout << "mergeSort costs time : " << ((double)time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
    }
}

/*int main(){
    srand((unsigned)time(NULL));
    for(double i=0.2;i<1;i+=0.2){
        cout << i << "N" << endl;
        vector<int> arr = create(1000000,0,1000000,3);
        vector<int> arr2 = arr;
        long time1 = clock();
        randomizedSelect(arr,0,arr.size()-1,(int)i*1000000);
        long time2 = clock();
        cout << "randomizedSelect costs time : " << ((double)time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
        time1 = clock();
        select(arr,0,arr.size()-1,arr.size()/2);
        time2 = clock();
        cout << "select costs time : " << ((double)time2 - time1) / CLOCKS_PER_SEC << "s" << endl;
    }
}*/