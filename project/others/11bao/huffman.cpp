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

    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};

struct cmp {
    bool operator()(Node *left, Node *right) {
		if (left->freq == right->freq) {
            return left->ch > right->ch; 
        }
        return left->freq > right->freq;
    }
};

Node* buildHuffmanTree(const unordered_map<char, int>& charset) {
    priority_queue<Node*, vector<Node*>, cmp> pq;
    for (const auto& pair : charset) {
        pq.push(new Node(pair.first, pair.second));
    }


    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* merged = new Node(' ', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }

    return pq.top();
}

void generateHuffmanCodes(Node* root, string code, unordered_map<char, string>& huffmanCode) {
    if (root == nullptr) {
        return;
    }

    if (root->left == nullptr && root->right == nullptr) {
        huffmanCode[root->ch] = code;
		return;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCode);
    generateHuffmanCodes(root->right, code + "1", huffmanCode);
}
