#include <iostream>

using namespace std;
int main(){
    int K;
    cin >> K;
    for (int i = 0; i < K; ++i) {
        int N;
        cin >> N;
        int a[N];
        vector<int> b(N);
        for (int j = 0; j < N; ++j) {
            cin >> a[j];
            b[j] = 1;
        }
        int ret = 0;
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < j; ++k) {
                if (a[k] < a[j]) {
                    b[j] = max(b[j], b[k] + 1);
                }
            }
            ret = max(b[j],ret);
        }
        cout<<ret<<" ";
    }
}