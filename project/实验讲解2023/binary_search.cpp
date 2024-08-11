#include <iostream>

using namespace std;

int binary_search(vector<int> &a, int len, int target){
    int l = 1, r = len, mid;
    while(l <= r) {
        mid = (l+r)/2;
        if(a[mid] < target){
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return l;
}

int main(){
    int K;
    cin >> K;
    for (int i = 0; i < K; ++i) {
        int N;
        cin >> N;
        int a[N];
        for (int j = 0; j < N; ++j) {
            cin >> a[j];
        }
        vector<int> b(N+1);
        b[N] = 0;
        b[1] = a[0];
        int index = 1;
        for (int j = 1; j < N; ++j) {
            if(a[j] > b[index]){
                b[++index] = a[j];
            } else {
                b[binary_search(b, index, a[j])] = a[j];
            }
        }
        cout<<index<<" ";
    }
}