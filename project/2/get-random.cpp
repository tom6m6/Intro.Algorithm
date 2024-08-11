#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
int n,s,t;
int main() {
    srand(time(NULL));
    ofstream fout("data.txt");
    cin>>n>>s>>t;
    fout<<n<<endl;
    for(int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            fout<< s+rand()%(t-s+1)<<" ";
            fout<< s+rand()%(t-s+1)<<" ";
        }
        fout<<endl;
    }
    for(int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            fout<< s+rand()%(t-s+1)<<" ";
        }
        fout<<endl;
    }
    fout.close();
    return 0;
}
