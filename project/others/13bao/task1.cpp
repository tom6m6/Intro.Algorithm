#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <sstream>
#include <limits>
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
        if (places[i] == "成都") chengdu = i;
        if (places[i] == "江达") jiangda = i;
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
    memset(dist, 0x3f, sizeof dist);
    dist[chengdu] = 0;
    for (int i = 0; i < n - 1; i++) {
        int t = -1;
        for (int j = 0; j < n; j++) {
            int index = idx[places[j]];
            if (!st[index] && (t == -1 || dist[t] > dist[index]))
                t = index;
        }
        //用1-t t-j的距离去更新 1-j
        for (int j = 0; j < n; j++) {
            int index = idx[places[j]];
            if (!st[index] && dist[index] > dist[t] + g[t][index]) {
                dist[index] = dist[t] + g[t][index];
                pre[index] = t;
            }
        }
        st[t] = true;
    }
    cout<<"总长度为："<<dist[idx[places[jiangda]]]<<endl;
    int t = jiangda;
    cout<<places[t]<<' ';
    while (t != chengdu) {
        cout<<places[pre[t]]<<' ';
        t = pre[t];
    }
}