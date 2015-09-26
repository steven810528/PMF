#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <sstream>
#include <math.h>

void printVector(vector<string> );
void printBigVector(vector<vector<string> >);
void printArray(double[],int );

void printArray(double a[],int length)
{
    for (int i =0;i<length;i++)
    {
        cout<<a[i]<<"\t";
    }
    cout<<endl;
}

void printVector(vector <string >v)
{
    int size = v.size();
    for(int i=0;i<size;i++)
    {
        cout<<v[i]<<"\t";
    }
    cout<<endl;
}
void printVector(vector <int >v)
{
    int size = v.size();
    for(int i=0;i<size;i++)
    {
        cout<<v[i]<<"\t";
    }
    cout<<endl;
}
void printVector(vector <double >v)
{
    int size = v.size();
    for(int i=0;i<size;i++)
    {
        cout<<v[i]<<"\t";
    }
    cout<<endl;
}

void printBigVector(vector<vector<int> >v)
{
    int row = v.size();
    for(int i =0;i<row;i++)
    {
        printVector(v[i]);
    }
}
void printBigVector(vector<vector<double> >v)
{
    int row = v.size();
    for(int i =0;i<row;i++)
    {
        printVector(v[i]);
    }
}
void printBigVector(vector<vector<string> >v)
{
    int row = v.size();
    for(int i =0;i<row;i++)
    {
        printVector(v[i]);
    }
}
