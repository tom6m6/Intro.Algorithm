#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <sstream>
#include <limits>
#include <queue>
#define N 50
int g[N][N];
int dist[N];
bool st[N];
int pre[N];
int chengdu, jiangda;
using namespace std;
int main() {
    unordered_set<string> set;
    vector<string> places;
    unordered_map<string, int> idx;
    ifstream f("data.txt");
    string line;
    while (getline(f, line)) {
        istringstream iss(line);
        string from, to;
        int dist, speed;
        iss >> from>>to>>dist>>speed;
        set.emplace(from);
        set.emplace(to);
    }
    places.assign(set.begin(), set.end());
    for (int i = 0; i < places.size(); i++) {
        idx[places[i]] = i;
        if (places[i] == "�ɶ�") chengdu = i;
        if (places[i] == "����") jiangda = i;
    }
    f.clear();
    f.seekg(0, ios::beg);
    memset(g, 0x3f, sizeof g);
    while (getline(f, line)) {
        istringstream iss(line);
        string from, to;
        int dist, speed;
        iss >> from>>to>>dist>>speed;
        g[idx[from]][idx[to]] = g[idx[to]][idx[from]] = dist;
    }
    int n = places.size();

    //dijkstra
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;//С����
    memset(dist, 0x3f, sizeof dist);
    dist[chengdu] = 0;
    heap.emplace(0, chengdu);//Ĭ�ϰ��յ�һ��Ԫ������ ���Ծ������ǰ��
    while (heap.size()) {
        int t = heap.top().second;
        heap.pop();
        //��1-t t-j�ľ���ȥ���� 1-j
        for (int j = 0; j < n; j++) {
            int index = idx[places[j]];
            if (!st[index] && dist[index] > dist[t] + g[t][index]) {
                dist[index] = dist[t] + g[t][index];
                pre[index] = t;
                heap.emplace(dist[index], index);
            }
        }
        st[t] = true;
    }
    cout<<"�ܳ���Ϊ��"<<dist[idx[places[jiangda]]]<<endl;
    int t = jiangda;
    cout<<places[t]<<' ';
    while (t != chengdu) {
        cout<<places[pre[t]]<<' ';
        t = pre[t];
    }
}