#include<iostream>
#include<vector>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include<sstream>
//高斯分布
double gauss_distribution(double mean, double std)
{
    double u = rand() / (double)RAND_MAX;
    double v = rand() / (double)RAND_MAX;
    double x = sqrt(-2 * log(u)) * cos(2 * M_PI * v) * std + mean;
    
    return x;
}
string dbl2str(double i) {
    string s;
    stringstream ss(s);
    ss << i;
    
    return ss.str();
}

string int2str(int i) {
    string s;
    stringstream ss(s);
    ss << i;
    
    return ss.str();
}

/*
int str2int(string s){
    stringstream ss(s);
    int a ;
    ss>>a;
    return a;
}*/
double str2dbl(string s){
    stringstream ss(s);
    double a ;
    ss>>a;
    return a;
}
string v2str(vector<int> v){
    stringstream ss;
    for(int i=0;i<v.size();i++)
    {
        ss<<v[i]<<" ";
    }
    return ss.str();
}
