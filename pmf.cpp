#include <iostream>
#include "matrix.h"
#include "math.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

double Object_value(Matrix* R,Matrix* U,Matrix* V,double std,double stdU,double stdV);
double sub_object_value_U(int U_row,Matrix* R,Matrix* U,Matrix* V,double std,double stdU,double stdV);
double sub_object_value_V(int V_col,Matrix* R,Matrix* U,Matrix* V,double std,double stdU,double stdV);

bool go_Down_User(int row,int K,Matrix* R,Matrix* U,Matrix* V,double std,double stdU,double stdV,double step_size);
bool go_Down_Item(int col,int K,Matrix* R,Matrix* U,Matrix* V,double std,double stdU,double stdV,double step_size);

void UNDO_Ui(Matrix* U,vector<double> res, int row);
void UNDO_Vj(Matrix* V,vector<double> res, int col);

void Partial_Differential_User(int row,int K,Matrix* R,Matrix* U,Matrix* V,vector<double>& output,double std,double stdU);
void Partial_Differential_Item(int col,int K,Matrix* R,Matrix* U,Matrix* V,vector<double>& output,double std,double stdV);
double UiVj(Matrix* U,Matrix* V,int i,int j);

void Ui(Matrix* U,int row,vector<double>& output);
void Vj(Matrix* V,int col,vector<double>& output);

void vector_multi(vector<double> &a,double m);
void vector_add(vector<double> &a,vector<double> b);

void NormalizeVecor(vector<double>& v ,double step_size);

void ConvertSlopeToDirection(vector<double>& v);

void updateU(Matrix* U,vector<double> v,int row);
void updateV(Matrix* V,vector<double> v,int col);

void set_R_hat(Matrix* U,Matrix* V,Matrix* R_hat);

//=========================================================================================================
double Object_value(Matrix* R,Matrix* U,Matrix* V,double std,double stdU,double stdV)
{
    //此結果值已將二提出
    double res=0;
    //第一項
    for(int i =0;i<R->row;i++)
    {
        for(int j =0;j<R->col;j++)
        {
            if(R->m[i][j]!=-1)
            {
                
                res=res+pow((R->m[i][j]-UiVj(U,V,i,j)),2);
                //cout<<res<<endl;
            }
        }
    }
    
    //第二項
    double res2=0;
    for(int i =0;i<U->row;i++)
    {
        double tmp=0;
        for(int j =0;j<U->col;j++)
        {
            tmp=tmp+(U->m[i][j]*U->m[i][j]);
        }
        res2=res2+pow(tmp,1/2)*std/stdU;
    }
    //第三項
    double res3=0;
    for(int i =0;i<V->col;i++)
    {
        double tmp=0;
        for(int j =0;j<V->row;j++)
        {
            tmp=tmp+(V->m[j][i]*V->m[j][i]);
        }
        res3=res3+pow(tmp,1/2)*std/stdV;
    }
    //cout<<res<<"\t"<<res2<<"\t"<<res3<<endl;
    return res+res2+res3;
    
    //return res;
}
double sub_object_value_U(int U_row,Matrix* R,Matrix* U,Matrix* V,double std,double stdU,double stdV)
{
    //此結果值已將二提出
    double res=0;
    //第一項
    for(int j =0;j<R->col;j++)
    {
        //cout<<"start "<<U->row<<"\t"<<j<<endl;
        //cout<<R->m[U_row][j]<<endl;
        
        if(R->m[U_row][j]!=-1)
        {
            
            res=res+pow((R->m[U_row][j]-UiVj(U,V,U_row,j)),2);
            //cout<<res<<endl;
        }
    }
    //cout<<"pass"<<endl;
    
    //第二項
    double res2=0;
    double tmp=0;
    for(int j =0;j<U->col;j++)
    {
        tmp=tmp+(U->m[U_row][j]*U->m[U_row][j]);
    }
    res2=res2+pow(tmp,1/2)*std/stdU;
    //cout<<res<<"\t"<<res2<<"\t"<<res3<<endl;
    return res+res2;
    
}
double sub_object_value_V(int V_col,Matrix* R,Matrix* U,Matrix* V,double std,double stdU,double stdV)
{
    //此結果值已將二提出
    double res=0;
    //第一項
    for(int i =0;i<R->row;i++)
    {
        if(R->m[i][V_col]!=-1)
        {
            
            res=res+pow((R->m[i][V_col]-UiVj(U,V,i,V_col)),2);
            //cout<<res<<endl;
        }
    }
    
    
    //第二項
    double res2=0;
    double tmp=0;
    for(int i =0;i<V->row;i++)
    {
        tmp=tmp+(V->m[i][V_col]*V->m[i][V_col]);
    }
    res2=res2+pow(tmp,1/2)*std/stdV;
    //cout<<res<<"\t"<<res2<<"\t"<<res3<<endl;
    return res+res2;
    
}

bool go_Down_User(int row,int K,Matrix* R,Matrix* U,Matrix* V,double std,double stdU,double stdV,double step_size)
{
    //double originalValue=Object_value(R,U,V,std,stdU,stdV);
    double originalValue=sub_object_value_U(row,R,U,V,std,stdU,stdV);
    
    //cout<<"當前目標值："<<dbl2str(originalValue)<<endl; //原始值
    vector<double> res ;
    Partial_Differential_User(row,K,R,U,V,res,std,stdU);
    ConvertSlopeToDirection(res);
    
    NormalizeVecor(res,step_size);
    //printVector(res);
    updateU(U,res,row);
    
    //double newValue=Object_value(R,U,V,std,stdU,stdV);
    double newValue=sub_object_value_U(row,R,U,V,std,stdU,stdV);
    
    //cout<<"更新目標值："<<dbl2str(newValue)<<endl; //更新值
    
    if(newValue>originalValue || newValue<=0)
    {
        UNDO_Ui(U,res,row);
        //cout<<"不更新"<<endl;
        return 0;
    }
    return 1;
}
bool go_Down_Item(int col,int K,Matrix* R,Matrix* U,Matrix* V,double std,double stdU,double stdV,double step_size)
{
    //double originalValue=Object_value(R,U,V,std,stdU,stdV);
    double originalValue=sub_object_value_V(col,R,U,V,std,stdU,stdV);
    
    //cout<<"當前目標值："<<dbl2str(originalValue)<<endl; //原始值
    vector<double> res ;
    Partial_Differential_Item(col,K,R,U,V,res,std,stdV);
    //轉換後依據setpsize對於res正規化
    ConvertSlopeToDirection(res);
    
    NormalizeVecor(res,step_size);
    //printVector(res);
    updateV(V,res,col);
    
    //double newValue=Object_value(R,U,V,std,stdU,stdV);
    double newValue=sub_object_value_V(col,R,U,V,std,stdU,stdV);

    //cout<<"更新目標值："<<dbl2str(newValue)<<endl; //更新值
    
    if(newValue>originalValue || newValue<=0)
    {
        UNDO_Vj(V,res,col);
        //cout<<"不更新"<<endl;
        return 0;
    }
    return 1;
}

//對於Ui偏微分，取得斜率分量
void Partial_Differential_User(int row,int K,Matrix* R,Matrix* U,Matrix* V,vector<double>& output,double std,double stdU)
{
    output.resize(K);
    //前項
    for(int j=0;j<R->col;j++)
    {
        if(R->m[row][j]!=-1)
        {
            double tmp=(R->m[row][j]-UiVj(U,V,row,j))*(-1);
            //Vj
            vector<double> v;
            v.resize(K);
            
            Vj(V,j,v);
            vector_multi(v,tmp);
            
            vector_add(output,v);
            
        }
    }
    /*
    for(int i =0;i<R->row;i++)
    {
        for(int j=0;j<R->col;j++)
        {
            if(R->m[i][j]!=-1)
            {
                double tmp=(R->m[i][j]-UiVj(U,V,i,j))*(-1);
                //Vj
                vector<double> v;
                v.resize(K);
                
                Vj(V,j,v);
                vector_multi(v,tmp);
                
                vector_add(output,v);
                
            }
        }
    }*/
    
    //後項
    vector<double> v2;
    Ui(U,row,v2);
    vector_multi(v2,std/stdU);
    vector_add(output,v2);
    
}
//對於Vj偏微分，取得斜率分量
void Partial_Differential_Item(int col,int K,Matrix* R,Matrix* U,Matrix* V,vector<double>& output,double std,double stdV){
    output.resize(K);
    //前項
    for(int i=0;i<R->row;i++)
    {
        if(R->m[i][col]!=-1)
        {
            double tmp=(R->m[i][col]-UiVj(U,V,i,col))*(-1);
            vector<double> v;
            v.resize(K);
            
            Ui(U,i,v);
            vector_multi(v,tmp);
            
            vector_add(output,v);
            
        }
    }
    
    
    //後項
    vector<double> v2;
    Vj(V,col,v2);
    vector_multi(v2,std/stdV);
    vector_add(output,v2);
}
//done
double UiVj(Matrix* U,Matrix* V,int i,int j)
{
    int K= U->col;
    //cout<<"K="<<K<<endl;
    double tmp =0;
    
    for(int x=0;x<K;x++)
    {
        tmp+=U->m[i][x]*V->m[x][j];
    }
    return tmp;
}

void Ui(Matrix* U,int row,vector<double>& output)
{
    //vector<double> r;
    output.resize(U->col);
    for(int i =0;i<output.size();i++)
    {
        output[i]=U->m[row][i];
    }
    //return r;
}
void Vj(Matrix* V,int col,vector<double>& output)
{
    //vector<double> r;
    output.resize(V->row);
    for(int i =0;i<output.size();i++)
    {
        output[i]=V->m[i][col];
    }
    //return r;
}

void ConvertSlopeToDirection(vector<double>& v)
{
    for(int i=0;i<v.size();i++)
    {
        v[i]=(-1)*v[i];
    }
}
void NormalizeVecor(vector<double>& v ,double step_size)
{
    double total=0;
    for(int i=0;i<v.size();i++)
    {
        total=total+pow(v[i],2);
    }
    //cout<<total<<endl;
    double rate=pow(step_size,2)/total;
    //cout<<rate<<endl;
    vector_multi(v,rate);
}


void UNDO_Ui(Matrix* U,vector<double> res, int row)
{
    int k = U->col;
    for(int i=0;i<k;i++)
    {
        U->m[row][i]=U->m[row][i]-res[i];
    }
}
void UNDO_Vj(Matrix* V,vector<double> res, int col)
{
    int k = V->row;
    for(int i=0;i<k;i++)
    {
        V->m[i][col]=V->m[i][col]-res[i];
    }
}

void updateU(Matrix* U,vector<double> v,int row)
{
    for(int i=0;i<v.size();i++)
    {
        U->m[row][i]=U->m[row][i]+v[i];
    }
}
void updateV(Matrix* V,vector<double> v,int col)
{
    for(int i=0;i<v.size();i++)
    {
        V->m[i][col]=V->m[i][col]+v[i];
    }
}
void set_R_hat(Matrix* U,Matrix* V,Matrix* R_hat)
{
    for(int i =0;i<R_hat->row;i++)
    {
        for(int j=0;j<R_hat->col;j++)
        {
            R_hat->set(i,j, UiVj(U,V,i,j));
        }
    }
}

void vector_add(vector<double> &a,vector<double> b)
{
    if(a.size()!=b.size())
    {
        cout<<"error"<<endl;
    }
    else
    {
        for(int i=0;i<a.size();i++)
        {
            a[i]=a[i]+b[i];
        }
    }
}
void vector_multi(vector<double> &a,double m)
{
    for(int i =0;i<a.size();i++)
    {
        a[i]=a[i]*m;
    }
}




