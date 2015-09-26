#include <iostream>
#include "matrix.h"
#include "math.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#include "toolbox.cpp"

#include "print.cpp"

#include "pmf.cpp"

//#######################################################
static double step_size_descrese_rate= 0.9;
Matrix::Matrix(int r,int c)
{
    this->setSize(r,c);
}
//exception creation
Matrix::Matrix(Matrix *copy, int r,int c)
{
    int a =copy->row-1;
    int b =copy->col-1;
    //cout<<copy->row<<endl;;
    //cout<<a<<endl;
    this->setSize(a,b);
    //cout<<m.row<<endl;
    vector<int> v;
    //v.resize(a*b);
    for (int i=0;i<copy->row;i++)
    {
        for(int j = 0;j<copy->col;j++)
        {
            if(i!=r && j!=c){
                v.push_back(copy->m[i][j]);
            }
        }
    }
    //cout<<v[a*b]<<endl;
    //<<v[0]<<endl;
    //cout<<this->row<<endl;
    this->set(v);
    //this->print();
    //cout<<"r="<<r<<endl;
    //cout<<"c="<<c<<endl;
}
Matrix::Matrix(){}

void Matrix::setSize(int r,int c)
{
    this->row=r;
    this->col=c;
    this->m.resize(r);
    for(int i =0;i<r;i++)
    {
        this->m[i].resize(c);
    }
}
void Matrix::set(int r,int c,double num)
{
    if(r<row && c<col)
        this->m[r][c]=num;
    else
        cerr<<"can't set the num!"<<endl;
}
void Matrix::set(vector<int>v)
{
    int tmp =0;
    if(v.size()>=(this->row*this->col))
    {
        for(int i =0;i<this->row;i++)
        {
            for(int j=0;j<this->col;j++)
            {
                this->m[i][j]=v[tmp];
                tmp+=1;
            }
        }
    }
}
Matrix* Matrix::operator+(Matrix add)
{
    if(add.row==this->row && add.col==this->col)
    {
        for (int i=0;i<this->row;i++)
        {
            for (int j =0; j<this->col;j++)
            {
                this->m[i][j]+= add.m[i][j];
            }
        }
    }
    else
        cout<<"Can't run this operator"<<endl;
    return this;
}
Matrix* Matrix::operator-(Matrix* sub)
{
    if(sub->row==this->row && sub->col==this->col)
    {
        for (int i=0;i<this->row;i++)
        {
            for (int j =0; j<this->col;j++)
            {
                this->m[i][j]-= sub->m[i][j];
            }
        }
    }
    else
        cout<<"Can't run this operator"<<endl;
    return this;
}
Matrix Matrix::operator*(Matrix multi)
{
    Matrix result(0,0);
    if(this->col==multi.row)
    {
        int l = this->col;
        result.setSize(this->row,multi.col);
        for (int i =0;i<result.row;i++)
        {
            for (int j=0;j<result.col;j++)
            {
                for(int k =0;k<l;k++)
                {
                    result.m[i][j]+=(this->m[i][k])*multi.m[k][j];
                }
            }
        }
    }
    else
        cout<<"Can't run this operator"<<endl;
    return result;
    //result.print();

}
Matrix Matrix::operator*(Matrix* multi)
{
    Matrix result(0,0);
    if(this->col==multi->row)
    {
        int l = this->col;
        result.setSize(this->row,multi->col);
        for (int i =0;i<result.row;i++)
        {
            for (int j=0;j<result.col;j++)
            {
                for(int k =0;k<l;k++)
                {
                    result.m[i][j]+=(this->m[i][k])*multi->m[k][j];
                }
            }
        }
    }
    else
        cout<<"Can't run this operator"<<endl;
    return result;
    //result.print();
}
void Matrix::operator=(Matrix copy)
{
    this->setSize(copy.row,copy.col);
    for(int i = 0;i<this->row;i++)
    {
        for (int j = 0;j<this->col;j++)
        {
            this->m[i][j]=copy.m[i][j];
        }
    }
}
void Matrix::operator=(Matrix *copy)
{
    this->setSize(copy->row,copy->col);
    for(int i = 0;i<this->row;i++)
    {
        for (int j = 0;j<this->col;j++)
        {
            this->m[i][j]=copy->m[i][j];
        }
    }
}
void Matrix::print()
{
    for (int i =0;i<this->row;i++)
    {
        for(int j =0;j<this->col;j++)
        {
            cout<< this->m[i][j]<<"\t\t";
        }
        cout<<endl;
    }
}
/*
int Matrix::det()
{
    if(this->row!=this->col)
    {
        cout<<"The matrix must be square marrix"<<endl;
        return -1;
    }
    else if(this->row<=1 )
    {
        //cout<<"ZZZ";
        return this->m[0][0];
    }
    else
    {
        int result=0;
        for(int i = 0;i<this->col;i++)
        {
            
            //cout<<"!"<<endl;
            int j=1;
            if(i%2!=0)
                j=-1;
            Matrix m(this,0,i);
            //m.print();
            //cout<<m.det()<<endl;
            result=result+(this->m[0][i]*m.det()*j);
            //cout<<m.det()<<endl;
            //cout<<"!!"<<endl;
            
        }
            return result;
    }
}
 
double Matrix::Fnorm()
{
    double res=0;
    for(int i=0;i<this->row;i++)
    {
        for(int j = 0;j<this->col;j++)
        {
            res+=pow(this->m[i][j],2);
        }
    }
    res/=(row*col);
    res=sqrt(res);
    return res;
}
*/
 //實驗方法PMF，更新U,V
void Matrix::mf(int K,Matrix* U,Matrix* V,double std,double stdU,double stdV,Matrix* R_hat,double step_size)
{
    time_t tStart = time(NULL);
    //宣告長度
    U->setSize(this->row,K);
    V->setSize(K,this->col);
    //依據segma設定初始factor
    for(int i =0;i<U->row;i++){
        for(int j =0 ;j<U->col;j++)
        {
            U->set(i,j,gauss_distribution(0,stdU));
        }
    }
    for(int i =0;i<V->row;i++){
        for(int j =0 ;j<V->col;j++)
        {
            V->set(i,j,gauss_distribution(0,stdV));
        }
    }
    
    //cout<<"################"<<endl;
    //U->print();
    //cout<<"################"<<endl;
    //V->print();
    set_R_hat(U,V,R_hat);
    //cout<<"################"<<endl;
    //R_hat->print();
    
    //更新UiVj下降目標值
    double oValue=Object_value(this,U,V,std,stdU,stdV);
    
    bool lower_size=0;
    int counter=0;
    while(step_size>1)
    {
        //double step_size=0.1;
        vector<int> t;
        
        for(int i=0;i<U->row;i++)
        {
            t.push_back(go_Down_User(i,K,this,U,V,std,stdU,stdV,step_size));
        }
        for(int i=0;i<V->col;i++)
        {
            t.push_back(go_Down_Item(i,K,this,U,V,std,stdU,stdV,step_size));
        }
        //oValue=Object_value(this,U,V,std,stdU,stdV);
        ///
        lower_size=1;
        for(int i =0;i<t.size();i++)
        {
            if(t[i]==1)
            {
                lower_size=0;
            }
        }
        counter++;
        cout<<counter<<"\t";
        
        if(lower_size==1)
        {
            	cout<<endl<<"****************************************"<<endl;
		step_size=step_size*step_size_descrese_rate;
		cout<<"新step sixe為："<<step_size<<endl;
        	cout<<"當前目標值為："<<Object_value(this,U,V,std,stdU,stdV)<<endl;
	}
        
    }
	cout<<"實驗環境為"<<this->row<<""<<this->col<<endl;
	cout<<"K="<<K<<endl;
    double originalValue=Object_value(this,U,V,std,stdU,stdV);
    cout<<"收斂目標值："<<dbl2str(originalValue)<<endl; //原始值
    set_R_hat(U,V,R_hat);
    time_t tEnd = time(NULL);
    cout<<"執行時間為"<<tEnd-tStart<<endl;
}

double Matrix::cal_std()
{
    double sum=0;
    double mean=0;
    for(int i=0;i<this->row;i++)
    {
        for(int j=0;j<this->col;j++)
        {
            sum=sum+this->m[i][j];
        }
    }
    mean=sum/this->row/this->col;
    sum=0;
    for(int i=0;i<this->row;i++)
    {
        for(int j=0;j<this->col;j++)
        {
            sum=sum+pow((this->m[i][j]-mean),2);
        }
    }
    return sum/this->row/this->col;
}




