#include <iostream>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <limits>
#define N 35
#define EARTH_RADIUS 6371.004
using namespace std;

int p[N];
double g[N][N];
unordered_map<string, pair<double, double>> city;
vector<string> names;
struct Edge
{
    int a, b;
    double w;

    bool operator< (const Edge &W)const//运算符重载 方便sort排序
    {
        return w < W.w;
    }
};
vector<Edge> edges;
vector<Edge> ans;
int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

double toRad(double angle) {
    return angle * M_PI / 180;
}

int main() {
    names.push_back("eren");
    ifstream f("cities.txt");
    string line;
    while (getline(f, line)) {
        istringstream iss(line);
        string name;
        double longitude, latitude;
        getline(iss, name, ',');
        names.push_back(name);
        iss >> longitude;
        iss.ignore();
        iss>> latitude;
        city[name] = {longitude, latitude};
    }
    f.close();
    
    for (int i = 1; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            double lon1 = toRad(city[names[i]].first), lat1 = toRad(city[names[i]].second);
            double lon2 = toRad(city[names[j]].first), lat2 = toRad(city[names[j]].second);
            double c = sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon1 - lon2);
            edges.push_back({i, j, EARTH_RADIUS * acos(c)});
        }
    }

    sort(edges.begin(), edges.end());
    for (int i = 1; i < N; i ++ ) p[i] = i;    // 初始化并查集

    double res = 0;
    int cnt = 0;
    int n = edges.size();
    for (int i = 0; i < n; i ++ ) {
        int a = edges[i].a, b = edges[i].b;
        double w = edges[i].w;

        a = find(a), b = find(b);
        if (a != b)
        {
            ans.push_back(edges[i]);
            p[a] = b;
            res += w;
            cnt ++ ;
        }
    }
    cout<<res;
}