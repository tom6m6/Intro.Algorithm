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
double dist[N];//�����ڵ㵽�������ľ���
bool st[N];//�ڵ��Ƿ�������������
int pre[N];//��¼·��

double toRad(double angle) {
    return angle * M_PI / 180;
}

int main() {
    for (int i = 0; i < N; i++) pre[i] = -1;
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

    dist[0] = 0;//��0��ʼ����

    double res = 0;
    for (int i = 0; i < N; i++) {
        int t = -1;
        for(int j = 0; j < N; j++)
            if(!st[j] && (t == -1 || dist[t] > dist[j]))
                t = j;
        res += dist[t];
        st[t] = true;
        for(int j = 0; j < N; j++) { //������������ĵ㵽���ľ���
            if (!st[j] && dist[j] > g[t][j]) {
                dist[j] = g[t][j];
                pre[j] = t;
            }
        }
    }
    double testans=0;
    cout<<"�ܳ���Ϊ��"<<res<<endl;    
    for(int i = 33; i >= 0; i--) {
        if (pre[i] == -1) continue;
        testans+=g[pre[i]][i];
        cout << "('"<<names[i]<<"','"<<names[pre[i]]<<"',"<<g[pre[i]][i]<<"),"<< endl;// 
    } 
    cout<<testans;
}

