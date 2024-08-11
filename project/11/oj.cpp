#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <algorithm>
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

Node* Build(vector<pair<char, int>>& charset) {
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
bool cmp2(pair<char, string> a,pair<char, string> b){
    if (a.second.size() == b.second.size()) return a.second < b.second;
	return a.second.size() < b.second.size();
}
int main() {
    int n;
    char ch;int freq;
    cin>>n;
    vector<pair<char,int>>charset;
    unordered_map<char,string>Huffman;
    while (n--) {
        cin>>ch>>freq;
        charset.push_back({ch,freq});
    }
    Node *root=Build(charset);
    gethuff(root, "", Huffman);

    vector<pair<char,string>> tmp;
	for (auto& pair:Huffman)tmp.push_back({pair.first,pair.second});
	sort(tmp.begin(),tmp.end(),cmp2);

    for (auto& pair:tmp)cout<<pair.first<<":"<<pair.second<<endl;
}