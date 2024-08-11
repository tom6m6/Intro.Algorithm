//code of strassen is complex, but I can make it!
//在完成这个实验的过程中，我通过构造结构体包装相关的功能
//这个适应了矩阵规模N不是2的幂的情况
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstdio>
#include<cstring>
using namespace std;
struct Matrix {
    int row, column;//row*column的矩阵
    int** m; //用来存那个数组
    Matrix(int r, int c) {//初始化
        row=r;
        column=c;
        m=(int**)malloc(sizeof(int*)*r);
        for (int i = 0; i < r; i++)m[i] = (int*)malloc(sizeof(int) * c);
        /*
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                m[i][j]=0;
            }
        }
        */
    }

    ~Matrix(){ //析构函数，销毁时用
        if (m != NULL) {
            for (int i=0;i<row;i++) {
                delete[] m[i];
            }
            delete[] m;
        }
    }
    Matrix(const Matrix& mat) {
		row=mat.row;
		column=mat.column;
		m=(int**)malloc(sizeof(int*)* mat.row);
		for (int i=0;i<mat.row;i++)
			m[i]=(int*)malloc(sizeof(int) * mat.column);
		for (int i=0;i<row;i++){
            for (int j=0;j<column;j++){
                m[i][j]=mat.m[i][j];
            }
        }		
	}

    Matrix& operator = (const Matrix& mat) {
        //重载=
        if (this != &mat) {
            row = mat.row;
            column = mat.column;
            m = (int**)malloc(sizeof(int*) * mat.row);
            for (int i = 0; i < mat.row; i++)
                m[i] = (int*)malloc(sizeof(int) * mat.column);
            for (int i = 0; i < row; i++){
                for (int j = 0; j < column; j++){
                    m[i][j] = mat.m[i][j];
                }
            }
        }
        return *this;
    }

    Matrix operator + (const Matrix& mat) {
        //重载+
        Matrix result=Matrix(row,column);
        for(int i=0;i<row;i++){
            for(int j=0;j<column;j++){
                result.m[i][j]=(*this).m[i][j]+mat.m[i][j];
            }
        }
        return result;
    }

    Matrix operator - (const Matrix& mat) {
        //重载-
        Matrix result=Matrix(row,column);
        for(int i=0;i<row;i++){
            for(int j=0;j<column;j++){
                result.m[i][j]=(*this).m[i][j]-mat.m[i][j];
            }
        }
        return result;
    }


};
Matrix matExtend(Matrix* mat){
    int pos=0,exn;
    int n=(*mat).row;
    while(n){
        pos++;
        n>>=1;
    }
    if(((*mat).row & ((*mat).row - 1)) == 0)exn=(*mat).row;
    else exn=1<<pos;
    Matrix matC=Matrix(exn,exn);
    
    for (int i=0;i<(*mat).row;i++){
        for(int j=0;j<(*mat).column; j++){
            matC.m[i][j]=(*mat).m[i][j];
        }
    }
    for(int i=(*mat).row;i<exn;i++){
        for(int j=0;j<exn;j++){
            matC.m[i][j]=0;
        }
    }
    for(int i=0;i<(*mat).row;i++){
        for(int j=(*mat).column;j<exn;j++){
            matC.m[i][j]=0;
        }
    }
    return matC;
}
Matrix matMini(Matrix mat, int st1, int st2, int ed1, int ed2) {
    //from(st1,st2)to(ed1,ed2)
    Matrix matC=Matrix(ed1-st1+1, ed2-st2+1);
    for (int i=0;i<=(ed1-st1);i++){
        for (int j=0;j<=(ed2-st2);j++) {
            matC.m[i][j]=mat.m[st1+i][st2+j];
        }
    }
    return matC;
}
Matrix combine(Matrix mat1, Matrix mat2, Matrix mat3, Matrix mat4) {
    Matrix newmat=Matrix(mat1.row+mat3.row,mat1.column+mat2.column);
    for (int i=0;i<mat1.row;i++){
        for (int j=0;j<mat1.column;j++){
            newmat.m[i][j]=mat1.m[i][j];
        }
    }

    for (int i=0;i<mat2.row;i++){
        for (int j=0;j<mat2.column;j++){
            newmat.m[i][j+mat1.column]=mat2.m[i][j];
        }
    }
    
    for (int i=0;i<mat3.row;i++){
        for (int j=0;j<mat3.column;j++){
            newmat.m[mat1.row+i][j]=mat3.m[i][j];
        }
    }

    for (int i=0;i<mat4.row;i++){
        for (int j=0;j<mat4.column;j++){
            newmat.m[mat1.row+i][mat1.column+j]=mat4.m[i][j];
        }
    }
    return newmat;
}

Matrix strassen(Matrix* matA, Matrix* matB) {
    if ((*matA).row == 1 && (*matA).column == 1 && (*matB).row == 1 && (*matB).column == 1) {
        Matrix matC=Matrix(1, 1);
        matC.m[0][0]=(*matA).m[0][0]*(*matB).m[0][0];
        return matC;
    }
    int mid1=(*matA).row/2 - 1;
    int mid2=(*matA).column/2 - 1;

    Matrix a11=matMini((*matA),0,0,mid1,mid2);
    Matrix a12=matMini((*matA),0, mid2+1,mid1,(*matA).column- 1);
    Matrix a21=matMini((*matA),mid1+1,0,(*matA).row-1,mid2);
    Matrix a22=matMini((*matA),mid1+1,mid2+1,(*matA).row-1,(*matA).column-1);

    Matrix b11=matMini((*matB),0,0,mid1,mid2);
    Matrix b12=matMini((*matB),0, mid2+1,mid1,(*matB).column- 1);
    Matrix b21=matMini((*matB),mid1+1,0,(*matB).row-1,mid2);
    Matrix b22=matMini((*matB),mid1+1,mid2+1,(*matB).row-1,(*matB).column-1);

    Matrix s1=b12-b22;
    Matrix s2=a11+a12;
    Matrix s3=a21+a22;
    Matrix s4=b21-b11;
    Matrix s5=a11+a22;
    Matrix s6=b11+b22;
    Matrix s7=a12-a22;
    Matrix s8=b21+b22;
    Matrix s9=a11-a21;
    Matrix s10=b11+b12;


    Matrix p1=strassen(&a11,&s1);
    Matrix p2=strassen(&s2,&b22);
    Matrix p3=strassen(&s3,&b11);
    Matrix p4=strassen(&a22,&s4);
    Matrix p5=strassen(&s5,&s6);
    Matrix p6=strassen(&s7,&s8);
    Matrix p7=strassen(&s9,&s10);


    Matrix c11=p5+p4-p2+p6;
    Matrix c12=p1+p2;
    Matrix c21=p3+p4;
    Matrix c22=p5+p1-p3-p7;

    return combine(c11,c12,c21,c22);
}


int n;
int main() {
    std::ios::sync_with_stdio(false);
    ifstream fin("data.txt");
    ofstream fout("result.txt");
    fin>>n;
    Matrix m1=Matrix(n,n);
    Matrix m2=Matrix(n,n);
    Matrix mr=Matrix(n,n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fin>>m1.m[i][j];
        }
    }   
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fin>>m2.m[i][j];
        }
    }
    //我怎样解决输入的矩阵规模N不是 2 的幂的情况？
    //就正常思路，把这个一般矩阵拓展成了矩阵规模N是 2 的幂的情况就行
    Matrix m1e=matExtend(&m1);
    Matrix m2e=matExtend(&m2);
    clock_t start, stop;
    start=clock();
    mr=strassen(&m1e,&m2e);
    stop=clock();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fout<<mr.m[i][j]<<" ";
        }
        fout<<endl;
    }
    cout<<"Time: "<<1000*((double)(stop - start) / CLOCKS_PER_SEC)<<"ms"<< endl;
    fin.close();
    fout.close();
    return 0;
}