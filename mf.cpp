#include<iostream>
#include <unistd.h>
#include <cstdlib>
#include"matrix.h"
#include<vector>
#include<fstream>

#include <stdlib.h>
#include <math.h>

//#include "connectDB.cpp"

using namespace std;

int main()
{
    //vector <double> D;
    //cout<<connect(D)<<endl;
    
    
    int M=10000;
    int N=10000;
    int K=50;
    //初始化
    Matrix R(M,N);
    vector<int> v;
	
   while(v.size()<R.row*R.row){
        v.push_back(rand()%5+1);
    }
R.set(v);		
    for(int i=0;i<M*N*0.999;i++)
{
	R.set(rand()%R.row,rand()%R.col,-1);
}
cout<<"start"<<endl;
    //R.set(v);
    //開始計算
    Matrix U(M,K);
    Matrix V(K,N);
    Matrix R_hat(M,N);
    //U.print();
    
    //cout<<"################"<<endl;
    //R.print();
    
    R.mf(K,&U,&V,0.001,1,1,&R_hat,100);
    //
    
    
    //cout<<"################"<<endl;
    //U.print();
    //cout<<"################"<<endl;
    //V.print();
    cout<<"################"<<endl;
    
    //R_hat.print();
    /*
    double ustd=U.cal_std();
    double vstd=V.cal_std();
    double std=R_hat.cal_std();
    
    R.mf(K,&U,&V,std,ustd,vstd,&R_hat);
    R_hat.print();
    */
}
double K_fold(Matrix Data,int kf,int K,double std,double ustd,double vstd)
{
    //計算資料總數
    int num =0;
    for(int i=0;i<Data.row;i++)
    {
        for(int j=0;j<Data.col;j++)
        {
            if(Data.m[i][j]!=-1)
                num++;
        }
    }
    //產生亂數序列
    vector<int> ran;
    int fold_num=num/kf;
    ran.resize(num);
    for(int i=0;i<num;i++)
    {
        int a = i/fold_num;
        if(a>kf)
            a=kf;
        
        ran[i]=a;
    }
    //打亂序列
    for(int i=0;i<num;i++)
    {
        int r = rand()*num;
        int tmp = ran[r];
        ran[r]=ran[i];
        ran[i]=tmp;
    }
    //
    return 0;
    
}


double test(Matrix training, Matrix test,int K,double std,double ustd,double vstd,double step_size)
{
    int M=training.row;
    int N=test.col;
    double MSE=0;
    int num=0;
    
    Matrix U(M,K);
    Matrix V(K,N);
    Matrix R_hat(M,N);
    
    training.mf(K,&U,&V,std,ustd,vstd,&R_hat,step_size);
    
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(test.m[i][j]!=-1)
            {
                MSE+=pow(test.m[i][j]-R_hat.m[i][j],2);
            }
        }
    }
    return MSE;
}






