#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <limits>
#define EARTH_RADIUS 6371.004
#define N 34
using namespace std;
unordered_map<string, pair<double, double>> city;
vector<string> names;
double g[N][N];
double dist[N];//各个节点到生成树的距离
bool st[N];//节点是否已在生成树中
int pre[N];//记录路径
double res;

double toRad(double angle) {
    return angle * M_PI / 180;
}

void update(int t1, int t2) {
    st[t1] = st[t2] = true;
    pre[t2] = t1;
    res += g[t1][t2];
    
    for(int j = 0; j < N; j++) { //更新生成树外的点到树的距离
        if (!st[j] && dist[j] > g[t1][j]) {
            dist[j] = g[t1][j];
            pre[j] = t1;
        }
    }

    for(int j = 0; j < N; j++) { //更新生成树外的点到树的距离
        if (!st[j] && dist[j] > g[t2][j]) {
            dist[j] = g[t2][j];
            pre[j] = t2;
        }
    }
}
int main() {
    for (int i = 0; i < N; i++) pre[i] = -1;
    ifstream f("cities.txt");
    string line;
    int xining, zhengzhou, k = 0, hangzhou, changsha;
    while (getline(f, line)) {
        istringstream iss(line);
        string name;
        double longitude, latitude;
        getline(iss, name, ',');
        names.push_back(name);
        if (name == "西宁市") xining = k;
        if (name == "郑州市") zhengzhou = k;
        if (name == "杭州市") hangzhou = k;
        if (name == "长沙市") changsha = k;
        iss >> longitude;
        iss.ignore();
        iss>> latitude;
        city[name] = {longitude, latitude};
        k++;
    }
    f.close();

    for (int i = 0; i < N; i++) {
        dist[i] = numeric_limits<double>::infinity();
        for (int j = 0; j < N; j++)
            g[i][j] = numeric_limits<double>::infinity();
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) g[i][j] = 0;
            else {
                double lon1 = toRad(city[names[i]].first), lat1 = toRad(city[names[i]].second);
                double lon2 = toRad(city[names[j]].first), lat2 = toRad(city[names[j]].second);
                double c = sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon2 - lon1);
                g[j][i] = g[i][j] = min(g[i][j], EARTH_RADIUS * acos(c));
            }
        }
    }
    
    update(xining, zhengzhou);
    
    for (int i = 0; i < N - 2; i++) {
        int t;
        if (i == 0) t = zhengzhou;
        else {
            t = -1;
            for(int j = 0; j < N; j++)
                if(!st[j] && (t == -1 || dist[t] > dist[j]))
                    t = j;
            res += dist[t];
        }
        
        st[t] = true;
        if (t == hangzhou) {//不能是zhengzhou
            update(hangzhou, changsha);
        }
        else {
            for(int j = 0; j < N; j++) { //更新生成树外的点到树的距离
                if (!st[j] && dist[j] > g[t][j]) {
                    dist[j] = g[t][j];
                    pre[j] = t;
                }
            }
        }
    }
    cout<<"总长度为："<<res<<endl;    
    for(int i = 33; i >= 0; i--) {
        if (pre[i] == -1) continue;
        cout << "('"<<names[i]<<"','"<<names[pre[i]]<<"',"<<g[pre[i]][i]<<"),"<< endl;// 
    }   
}

