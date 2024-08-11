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
int g1[N][N];
int dist[N];
bool st[N];
int pre[N];
int chengdu, jiangda, daofu;
using namespace std;
int main() {
    unordered_set<string> set;
    vector<string> places;
    unordered_map<string, int> idx;

    //第一次读取 获取地点数组
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
        if (places[i] == "道孚") daofu = i;
    }

    //第二次读取前先重置文件指针
    f.clear();
    f.seekg(0, ios::beg);
    memset(g1, 0x3f, sizeof g1);
    while (getline(f, line)) {
        istringstream iss(line);
        string from, to;
        int dist, speed;
        iss >> from>>to>>dist>>speed;
        g1[idx[from]][idx[to]] = g1[idx[to]][idx[from]] = dist;
    }

    int n = places.size();

    //成都-道孚
    memset(dist, 0x3f, sizeof dist);
    dist[daofu] = 0;
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
            if (!st[index] && dist[index] > dist[t] + g1[t][index]) {
                dist[index] = dist[t] + g1[t][index];
                pre[index] = t;
            }
        }
        st[t] = true;
    }
    int res= 0;
    res += dist[idx[places[jiangda]]];
    int t = jiangda;
    cout<<places[t]<<' ';
    while (t != daofu) {
        cout<<places[pre[t]]<<' ';
        t = pre[t];
    }
    
    //道孚-江达
    for (int i = 0; i < n; i++) st[i] = false;
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
            if (!st[index] && dist[index] > dist[t] + g1[t][index]) {
                dist[index] = dist[t] + g1[t][index];
                pre[index] = t;
            }
        }
        st[t] = true;
    }
    res += dist[idx[places[daofu]]];
    t = daofu;
    while (t != chengdu) {
        cout<<places[pre[t]]<<' ';
        t = pre[t];
    }
    cout<<endl;
    cout<<"总长度为："<<res;
}