#include<iostream>
#include<queue>
#include<cstdio>
using namespace std;
int n,m,s,tot=0,dis[10005],head[500005],mi,t;
bool vis[10005];
struct Edge{
    int next,to,w;
}h[500005];
void add(int u,int v,int w){
    h[++tot].next=head[u];
    h[tot].to=v;
    h[tot].w=w;
    head[u]=tot;
}//前向星存边
inline void spfa(){
    queue<int> q;   
    for(int i=1; i<=n; i++) dis[i]=0x7ffffff0;//赋初值  
    int u,v; q.push(s);
    dis[s]=0; vis[s]=1;   
    while(!q.empty()){//队列优化 
        u=q.front();  
        q.pop(); vis[u]=0; 
        for(int i=head[u];i;i=h[i].next){//SPFA最重要的遍历图 
            v=h[i].to;  
            if(dis[v]>dis[u]+h[i].w){   
                dis[v]=dis[u]+h[i].w; 
                if(!vis[v]){ 
                    vis[v]=1;
                    q.push(v);
                }
            }
        }
    }
}
int main(){
    cin>>n>>m;
    s=1;
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        add(u,v,w);
        //add(v,u,w);
    }
    spfa();
    if(dis[n]==0x7ffffff0)cout<<"-1";
    else cout<<dis[n];
    return 0;
}