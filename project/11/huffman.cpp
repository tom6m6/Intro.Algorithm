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

struct Node{
    char ch; 
    int freq;   
    Node* left;
    Node* right;

    Node(char ch,int freq){
        this->ch=ch;
        this->freq=freq;
        this->left=nullptr;
        this->right=nullptr;
    }
};

struct cmp1 {
    bool operator()(Node *left, Node *right) {
		if (left->freq == right->freq) {
            return left->ch > right->ch; 
        }
        return left->freq > right->freq;
    }
};

Node* Build(unordered_map<char, int>& charset) {
    priority_queue<Node*, vector<Node*>,cmp1> pq;
    for (auto& pair : charset)pq.push(new Node(pair.first, pair.second));

    while (pq.size()>1) {
        Node* left=pq.top();pq.pop();

        Node* right=pq.top();pq.pop();

        Node* merged = new Node('+', left->freq + right->freq);
        merged->left = left;merged->right = right;
        pq.push(merged);
    }
    return pq.top();
}

void gethuff(Node* root, string code, unordered_map<char, string>& Huffman) {
    if (root == nullptr)return;

    if (root->left == nullptr && root->right == nullptr) {
        Huffman[root->ch]=code;
		return;
    }

    gethuff(root->left,code+"0", Huffman);
    gethuff(root->right,code+"1", Huffman);
}

char Filepath[][100]={"Book 1 - The Philosopher's Stone.txt",
                "Book 2 - The Chamber of Secrets.txt",
                "Book 3 - The Prisoner of Azkaban.txt",
                "Book 4 - The Goblet of Fire.txt",
                "Book 5 - The Order of the Phoenix.txt",
                "Book 6 - The Half Blood Prince.txt",
                "Book 7 - The Deathly Hallows.txt"
};
int main() {
    double startTime,endTime;
for(int num=0;num<7;num++){
    //char filepath[]="test.txt";
    ifstream fin(Filepath[num]);
    char ch;string encode="";
    unordered_map<char, int>charset;
    unordered_map<char,string>Huffman;
    while(fin.get(ch))charset[ch]+=1;
    fin.clear();fin.seekg(0,ios::beg);

    startTime=clock();
    Node *root=Build(charset);
    gethuff(root,"",Huffman);
    while (fin.get(ch))encode+=Huffman[ch];
    endTime=clock();

    cout<<"Title: "<<Filepath[num]<<endl;
    cout<<"After Huffman algorithm, it's length: "<<encode.size()<<endl;
    cout<<"It takes "<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;

    string decode="";
    Node* cur=root;
    startTime=clock();
    for(char bit :encode) {
        if (bit=='0')cur=cur->left;
        else cur=cur->right;

        if(cur->left==nullptr && cur->right==nullptr){
            decode+= cur->ch;
            cur=root;
        }
    }
    endTime=clock();
    cout<<"Decoding takes "<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;
    cout<<"After decoding length: "<<decode.size()<<endl;
    fin.close();
}
    return 0;
}