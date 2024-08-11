#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//用于生成随机数据
//生成的数据数量是N,范围在[s,t],T是生成数据的类型
//T 1顺序递增 2顺序递减 3随机取值
//这里的递增和递减指的是严格单调递增和严格严格单调递减
int super_rand(int s,int t);

void f1(FILE *fp,int N,int s,int t){
    int tmp=super_rand(s,t);
    fprintf(fp,"%u ",tmp);
    int tmp1;
    for(int i=2;i<=N;i++){
        tmp1=super_rand(s,t);
        while(tmp1<tmp){
            tmp1=super_rand(s,t);
        }
        tmp=tmp1;
        fprintf(fp,"%u ",tmp);
    }
}
void f2(FILE *fp,int N,int s,int t){
    int tmp=super_rand(s,t);
    fprintf(fp,"%d ",tmp);
    int tmp1;
    for(int i=2;i<=N;i++){
        tmp1=super_rand(s,t);
        while(tmp1>tmp){
            tmp1=super_rand(s,t);
        }
        tmp=tmp1;
        fprintf(fp,"%d ",tmp);
    }
}
void f3(FILE *fp,int N,int s,int t){
    int tmp;
    for(int i=1;i<=N;i++){
        tmp=super_rand(s,t);
        fprintf(fp,"%d ",tmp);
    }
}

int super_rand(int s,int t){
    //为什么我要写一个super_rand?因为我的库函数中 RAND_MAX仅仅为32767
    //rand()生成的数据在[0,RAND_MAX] 这么小的数据，显然是无法很好地获得随机数据
    //我通过线性映射，近似地将[0,RAND_MAX]映射到了我们需要的[s,t]
    long long randlen=RAND_MAX+1;
    long long mylen=(long long)t-(long long)s+1; //由于t-s+1可能超过int的范围，我用long long类型来存

    double tmp1=(double)(rand())/randlen;
    long long tmp2=mylen*tmp1;
    int ans=(int)(tmp2+(long long)s);
    return ans;
}

/*
int main(){
    int N,s,t,T;
    scanf("%d%d%d%d",&N,&s,&t,&T);
    srand(time(NULL));
    FILE *fp1;
    fp1=fopen("get-random-num-result.txt","w");
    if(T==1)f1(fp1,N,s,t);
    else if(T==2)f2(fp1,N,s,t);
    else f3(fp1,N,s,t);

    if(fclose(fp1)){
        printf("cannot close the file!\n");
        exit(0);
    }
    
    return 0;
}
*/
