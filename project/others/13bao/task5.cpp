#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <sstream>
#include <limits>
#include <stack>
#define N 50
int g1[N][N];
int dist1[N];
bool st1[N];
int pre1[N];
int g2[N][N];
int dist2[N];
bool st2[N];
int pre2[N];
int chengdu, jiangda;
int inter;
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
        iss >> from >> to >> dist >> speed;
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
    memset(g1, 0x3f, sizeof g1);
    memset(g2, 0x3f, sizeof g2);
    while (getline(f, line)) {
        istringstream iss(line);
        string from, to;
        int dist, speed;
        iss >> from >> to >> dist >> speed;
        g1[idx[from]][idx[to]] = g1[idx[to]][idx[from]] = dist;
        g2[idx[to]][idx[from]] = g2[idx[from]][idx[to]] = dist;  // 添加g2图的边
    }
    int n = places.size();

    // dijkstra
    memset(dist1, 0x3f, sizeof dist1);
    memset(dist2, 0x3f, sizeof dist2);
    dist1[chengdu] = 0;
    dist2[jiangda] = 0;
    for (int i = 0; i < n - 1; i++) {
        int t1 = -1;
        for (int j = 0; j < n; j++) {
            int index = idx[places[j]];
            if (!st1[index] && (t1 == -1 || dist1[t1] > dist1[index]))
                t1 = index;
        }
        int t2 = -1;
        for (int j = 0; j < n; j++) {
            int index = idx[places[j]];
            if (!st2[index] && (t2 == -1 || dist2[t2] > dist2[index]))
                t2 = index;
        }

        st1[t1] = true;
        st2[t2] = true;

        if (st1[t2] || st2[t1]) {
            inter = st1[t2] ? t2 : t1;
            break;
        }

        // 用1-t t-j的距离去更新 1-j
        for (int j = 0; j < n; j++) {
            int index = idx[places[j]];
            if (!st1[index] && dist1[index] > dist1[t1] + g1[t1][index]) {
                dist1[index] = dist1[t1] + g1[t1][index];
                pre1[index] = t1;
            }
        }
        for (int j = 0; j < n; j++) {
            int index = idx[places[j]];
            if (!st2[index] && dist2[index] > dist2[t2] + g2[t2][index]) {
                dist2[index] = dist2[t2] + g2[t2][index];
                pre2[index] = t2;
            }
        }
    }
    cout <<"总长度为："<< dist1[inter] + dist2[inter] << endl;
    stack<string> path;
    int t = inter;
    path.push(places[t]);
    while (t != jiangda) {
        path.push(places[pre2[t]]);
        t = pre2[t];
    }
    while (path.size()) {
        cout<<path.top()<<' ';
        path.pop();
    }
    t = inter;
    while (t != chengdu) {
        cout<< places[pre1[t]] << ' ';
        t = pre1[t];
    }
    return 0;
}
