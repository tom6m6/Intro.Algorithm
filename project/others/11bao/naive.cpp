#include <iostream>
#include <string>
#include <unordered_map>
#include <bitset>
#include <vector>
#include <cmath>
using namespace std;
unordered_map<char, string> generateCode(vector<char> charset) {
    unordered_map<char, string> codeTable;
    int n = charset.size();
    int codeLength = ceil(log(n) / log(2));
    for (int i = 0; i < n; i++) {
        string code = bitset<32>(i).to_string().substr(32 - codeLength);
        codeTable[charset[i]] = code;
    }
    return codeTable;
}
