#include <iostream>
#include <fstream>
#include <cctype> // ���� tolower ����
#include <unordered_set>
#include <vector>
#include "naive.cpp"
#include "huffman.cpp"
#include <ctime>
using namespace std;

int test1(string decodestr1, const char *filepath) {
    cout<<"naive"<<endl;
    ifstream f(filepath); 
    unordered_set<char> t;
    vector<char> charset;

    //Ԥ�������ı��е��ַ�
    char ch;
    while (f.get(ch)) { 
        t.emplace(ch);
    }
    //���ļ�ָ��ָ��ͷ������֮�����
    f.clear();
    f.seekg(0, ios::beg);
    charset.assign(t.begin(), t.end());
    //set -> vector ��ΪgenerateCode��������Ҫ������������ ����vector ��set����ȥ�ع���

    //���Ա���ʱ��
    string encodestr="";
    double st = clock();
    unordered_map<char, string> codeTable = generateCode(charset);
    while (f.get(ch)) { 
        encodestr += codeTable[ch];
    }
    double ed = clock();
    double result = (ed - st) / CLOCKS_PER_SEC;
    cout<<"encoding takes:"<<result<<"s"<<endl;
    //��������ʱ��
    unordered_map<string, char> decodeTable;
    for (const auto& pair : codeTable) {
        decodeTable.emplace(pair.second, pair.first);
    }
    int n = charset.size(), len = encodestr.size();
    int codeLength = ceil(log(n) / log(2));
    string decodestr;
    st = clock();
    for (int i = 0; i < len; i += codeLength) {
        decodestr += decodeTable[encodestr.substr(i, codeLength)];
    }
    ed = clock();
    result = (ed -st) / CLOCKS_PER_SEC;
    cout<<"decoding takes:"<<result<<"s"<<endl;
    f.close();
    
    decodestr1 = decodestr;
    return encodestr.size();
}

int test2(string decodestr2, const char *filepath) {
    cout<<"huffman"<<endl;
    ifstream f(filepath); 
    char ch;
    unordered_map<char, int> charset;
    unordered_map<char, string> huffmanCode;

    //Ԥ�������ı��е��ַ��Լ�Ƶ��
    while (f.get(ch)) {
        charset[ch] += 1;
    }
    //���ļ�ָ��ָ��ͷ������֮�����
    f.clear();
    f.seekg(0, ios::beg);

    //���Ա���ʱ��
    string encodestr;
    double st = clock();
    Node *root = buildHuffmanTree(charset);
    generateHuffmanCodes(root, "", huffmanCode);
    while (f.get(ch)) { 
        encodestr += huffmanCode[ch];
    }
    double ed = clock();
    double result = (ed - st) / CLOCKS_PER_SEC;
    cout<<"encoding takes:"<<result<<"s"<<endl;

    //��������ʱ��
    string decodestr;
    st = clock();
    Node* cur = root;
    for (char bit : encodestr) {
        if (bit == '0') {
            cur = cur->left;
        } else {
            cur = cur->right;
        }

        if (cur->left == nullptr && cur->right == nullptr) {
            decodestr += cur->ch;
            cur = root;
        }
    }
    ed = clock();
    result = (ed - st) / CLOCKS_PER_SEC;
    cout<<"decoding takes:"<<result<<"s"<<endl;
    f.close();
    
    decodestr2 = decodestr;
    return encodestr.size();
}
int main() {
    const char *filepath[] = {"test.txt","a tale of two cities.txt", "in search of lost time.txt", "war and peace.txt"};
    for (int i = 0; i < 1; i++) {
        cout<<filepath[i]<<":"<<endl;
        string decodestr1, decodestr2;
        int naive = test1(decodestr1, filepath[i]);
        int huffman = test2(decodestr2, filepath[i]);
        cout<<"the length after naive:"<<naive<<endl;
        cout<<"the length after huffman:"<<huffman<<endl;
        if (decodestr1 == decodestr2) cout<<"True"<<endl;
        else cout<<"False"<<endl;
        cout<<"compression rate:"<<(double) huffman / naive<<endl;
        cout<<endl;
    }
}