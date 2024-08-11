#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <limits>
#include <unordered_set>
#define EARTH_RADIUS 6371.004
#define N 34
using namespace std;
unordered_map<string, pair<double, double>> city;
unordered_map<string, int> idx;
vector<string> names;
double g[N][N];
double dist[N];//各个节点到生成树的距离
bool st[N];//节点是否已在生成树中
int pre[N];//记录路径

double toRad(double angle) {
    return angle * M_PI / 180;
}

int main() {
    for (int i = 0; i < N; i++) pre[i] = -1;
    string norPro[15] = {
        "济南市", "石家庄市", "天津市", "北京市", "沈阳市", 
        "长春市", "哈尔滨市", "郑州市", "太原市", "呼和浩特市", 
        "西安市", "兰州市", "银川市", "西宁市", "乌鲁木齐市"};
    string souPro[19] = {
        "南京市", "合肥市", "上海市", "长沙市", "南昌市",
        "杭州市", "福州市", "广州市", "台北市", "海口市",
        "南宁市", "重庆市", "昆明市", "贵阳市", "成都市",
        "拉萨市", "香港", "澳门", "武汉市"
    };
    ifstream f("cities.txt");
    string line;
    int hongkong, aomen, guangzhou, k = 0;
    while (getline(f, line)) {
        istringstream iss(line);
        string name;
        double longitude, latitude;
        getline(iss, name, ',');
        names.push_back(name);
        idx[name] = k;
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

    dist[idx[norPro[0]]] = 0;//从0开始生成

    double res = 0;
    for (int i = 0; i < 15; i++) {
        int t; 
        if (i == 0) {
            t = idx[norPro[0]];
        }
        else {
            t = -1;
            for(int j = 0; j < 15; j++) {
                int index = idx[norPro[j]];
                if (!st[index] && (t == -1 || dist[t] > dist[index]))
                    t = index;
            }
        }
        res += dist[t];
        st[t] = true;
        for(int j = 0; j < 15; j++) { //更新生成树外的点到树的距离
            int index = idx[norPro[j]];
            if (!st[index] && dist[index] > g[t][index]) {
                dist[index] = g[t][index];
                pre[index] = t;
            }
        }
    }
    double summ = 0;
    for(int j = 14; j >= 0; j--) {
        int i = idx[norPro[j]];
        if (pre[i] == -1) continue;
        cout << "('"<<names[i]<<"','"<<names[pre[i]]<<"',"<<g[pre[i]][i]<<"),"<< endl;
        summ += g[pre[i]][i];
    }
    
    dist[idx[souPro[0]]] = 0;
    for (int i = 0; i < 19; i++) {
        int t; 
        if (i == 0) {
            t = idx[souPro[0]];
        }
        else {
            t = -1;
            for(int j = 0; j < 19; j++) {
                int index = idx[souPro[j]];
                if (!st[index] && (t == -1 || dist[t] > dist[index]))
                    t = index;
            }
        }
        res += dist[t];
        st[t] = true;
        for(int j = 0; j < 19; j++) { //更新生成树外的点到树的距离
            int index = idx[souPro[j]];
            if (!st[index] && dist[index] > g[t][index]) {
                dist[index] = g[t][index];
                pre[index] = t;
            }
        }
    }
    for(int j = 18; j >= 0; j--) {
        int i = idx[souPro[j]];
        if (pre[i] == -1) continue;
        cout << "('"<<names[i]<<"','"<<names[pre[i]]<<"',"<<g[pre[i]][i]<<"),"<< endl;
        summ += g[pre[i]][i];
    }

    double minn = numeric_limits<double>::infinity();
    int t1, t2;
    for (int i = 0; i < 15; i++) {
        int i1 = idx[norPro[i]];
        for (int j = 0; j < 19; j++) {
            int i2 = idx[souPro[j]];
            if (g[i1][i2] < minn) {
                t1 = i1;
                t2 = i2;
                minn = g[i1][i2];
            }
        }
    }
    pre[t2] = t1;
    summ += g[t1][t2];
    cout << "('"<<names[t2]<<"','"<<names[pre[t2]]<<"',"<<g[pre[t2]][t2]<<"),"<< endl;
    cout<<"总长度为："<<summ<<endl;
}

