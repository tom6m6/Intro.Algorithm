#include <string>
#include <bitset>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <fstream>
#include <cctype>
#include <ctime>
using namespace std;
unordered_map<char, string> getcode(vector<char> charset) {
    unordered_map<char, string> table;
    int n=charset.size();
    int codeLength=ceil(log(n)/log(2));
    for (int i=0;i<n;i++) {
        string code=bitset<32>(i).to_string().substr(32-codeLength);
        table[charset[i]]=code;
    }
    return table;
}
char Filepath[][100]={"Book 1 - The Philosopher's Stone.txt",
                "Book 2 - The Chamber of Secrets.txt",
                "Book 3 - The Prisoner of Azkaban.txt",
                "Book 4 - The Goblet of Fire.txt",
                "Book 5 - The Order of the Phoenix.txt",
                "Book 6 - The Half Blood Prince.txt",
                "Book 7 - The Deathly Hallows.txt"
};
int main(){
for(int num=0;num<7;num++){
    //char filepath[]="test.txt";
    ifstream fin(Filepath[num]);
    unordered_set<char> t;
    vector<char> charset;
    string encode="";
    char ch;while(fin.get(ch))t.emplace(ch);
    fin.clear();fin.seekg(0,ios::beg);
    charset.assign(t.begin(),t.end());

    double startTime,endTime;
    startTime=clock();
    unordered_map<char,string>table=getcode(charset);
    while(fin.get(ch))encode+=table[ch];
    endTime=clock();
    cout<<"Title: "<<Filepath[num]<<endl;
    cout<<"After normal algorithm, it's length: "<<encode.size()<<endl;
    cout<<"It takes "<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;
    
    string decode="";
    startTime=clock();
    unordered_map<string, char> table2; //用于解码
    for (auto& i:table)table2.emplace(i.second,i.first);
    int n=charset.size();
    int len=encode.size();
    int codeLength = ceil(log(n)/ log(2));
    for (int i=0;i<len;i+=codeLength)decode+=table2[encode.substr(i,codeLength)];
    endTime=clock();
    cout<<"Decoding takes "<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;
    cout<<"After decoding length: "<<decode.size()<<endl;
    fin.close();
}
    return 0;
}