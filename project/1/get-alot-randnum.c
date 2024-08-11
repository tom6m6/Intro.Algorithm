#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
//这个程序用来生成题中需要的大量的数据集
//这个程序要调用 getrandnum.c中定义的函数
//默认取值范围0x80000000到0x7FFFFFFF (int范围)


extern void f1(FILE *fp,int N,int s,int t);
extern void f2(FILE *fp,int N,int s,int t);
extern void f3(FILE *fp,int N,int s,int t);
extern void super_rand(int s,int t);


int s=0x80000000,t=0x7FFFFFFF;
char filename[17][128];
char tmp1[]="./dataset/randnum-",tmp2[]=".txt",tmp3[10]="100";
char tmp4[]="-increase",tmp5[]="-decrease",tmp6[]="-rand";
//生成的文件名形如 ./dataset/randnum-100-increase.txt
void Solve_Filename(){
    for(int i=1;i<=15;i++){
        strcpy(filename[i],tmp1);
    }
    for(int i=2;i<=6;i++){
        strcat(filename[1+(i-2)*3],tmp3);
        strcat(filename[2+(i-2)*3],tmp3);
        strcat(filename[3+(i-2)*3],tmp3);

        strcat(filename[1+(i-2)*3],tmp4);
        strcat(filename[2+(i-2)*3],tmp5);
        strcat(filename[3+(i-2)*3],tmp6);

        strcat(filename[1+(i-2)*3],tmp2);
        strcat(filename[2+(i-2)*3],tmp2);
        strcat(filename[3+(i-2)*3],tmp2);
        tmp3[i+1]='0';
        tmp3[i+2]='\0';
    }
}
int main(){
    srand(time(NULL));
    Solve_Filename();
    int tmp=100;
    for(int i=2;i<=6;i++){
        FILE *fp1,*fp2,*fp3;

        fp1=fopen(filename[1+(i-2)*3],"w");
        fp2=fopen(filename[2+(i-2)*3],"w");
        fp3=fopen(filename[3+(i-2)*3],"w");

        f1(fp1,tmp,s,t);
        f2(fp2,tmp,s,t);
        f3(fp3,tmp,s,t);
        if(fclose(fp1)){
            printf("cannot close the file!\n");
            exit(0);
        }
        if(fclose(fp2)){
            printf("cannot close the file!\n");
            exit(0);
        }
        if(fclose(fp3)){
            printf("cannot close the file!\n");
            exit(0);
        }
        tmp*=10;
    }

    return 0;
}