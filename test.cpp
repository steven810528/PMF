#include<iostream>
#include"matrix.h"
#include<vector>
using namespace std;

int main()
{
    vector<int>v (9,0);
    for(int i=0;i<v.size();i++)
    {
        v[i]=i*i;
    }
	Matrix A(3,3);
    A.set(v);
    //A.m[0][0]=33;
    cout<<"A:"<<endl;
    A.m[0][0]=20;
    A.m[1][1]=30;
    A.print();
    //Matrix B(3,2);
    //B.set(v);
    //cout<<"B:"<<endl;
    //B.print();
    //Matrix C(&A,1,1);
    cout<<A.det()<<endl;
    //cout<<C.row;
    //cout<<C.det();
    //cout<<C.row;
    //cout<<A.det()<<endl;
}
