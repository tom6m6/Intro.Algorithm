#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#define R 6371.004 //平均半径
#define SUP 100000000
using namespace std;
struct city{
    string name;
    double longitude,latitude;
};
struct edge{
    int from,to;
    double val;
};
double rad(double angle){return angle * M_PI / 180;}
double earth_dist(city *pos_a, city *pos_b){
    double long_a = rad(pos_a->longitude);double lat_a = rad(pos_a->latitude);
    double long_b = rad(pos_b->longitude);double lat_b = rad(pos_b->latitude);
    double c = sin(lat_a) * sin(lat_b) + cos(lat_a) * cos(lat_b) * cos(long_b - long_a);
    return R * acos(c);
}
city c[50];
double graph[50][50] = {SUP};
int visit[50] = {0};
int n = 0;
edge choose[50], low_cost[50];
int main() {
    ifstream fin("data.txt");
    while (!fin.eof()){
        fin>>c[n].name>>c[n].longitude>>c[n].latitude;
        n++;
    }
    fin.close();
    //Build
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j) graph[i][j] = 0;
            else {
                double dist = earth_dist(&c[i], &c[j]);
                graph[i][j] = dist;graph[j][i] = dist;
            }
        }
    }
    int last_vis;
    int cnt=0;int flag=0;
    for(int i = 0; i < n; i++)low_cost[i] = {-1, -1, SUP};
    visit[0] = 1;
    last_vis = 0;
    while (!flag){
        flag = 1;
        //Update
        for(int i = 0; i < n; i++){
            if(visit[i] == 0 && graph[last_vis][i] < low_cost[i].val){
                low_cost[i].from = last_vis;
                low_cost[i].to = i;
                low_cost[i].val = graph[last_vis][i];
            }
        }
        int min_edge_idx = -1;
        double min_edge_dist = SUP;
        //Search
        for (int i = 0; i < n; i++) {
            if(low_cost[i].val != -1.0 && low_cost[i].val < min_edge_dist){
                min_edge_dist = low_cost[i].val;
                min_edge_idx = i;
            }
        }
        choose[cnt] = low_cost[min_edge_idx];
        visit[min_edge_idx] = 1;
        low_cost[min_edge_idx] = {-1, -1, -1.0};
        last_vis = min_edge_idx;
        cnt++;
        for(int i = 0; i < n; i++){
            if(visit[i] == 0){
                flag = 0;
                break;
            }
        }
    }
    double sum = 0.0;
    for(int i = 0; i < cnt; i++){
        cout<<c[choose[i].from].name<<"<>"<<c[choose[i].to].name<<" "<<choose[i].val<<"KM"<<endl;
        sum += choose[i].val;
    }
    /*
    for(int i = 0; i < cnt; i++){
        cout<<"('"<<c[choose[i].from].name<<"','"<<c[choose[i].to].name<<"',"<<choose[i].val<<"),"<<endl;
    }
    */
    cout<<"SUM LEN: "<<sum<<"km"<<endl;
    return 0;
}
