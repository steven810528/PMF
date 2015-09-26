#ifndef MATRIX_H
#define MATRIX_H
#include<vector>

using namespace std;

class Matrix {
	public:
		int row;
		int col;
		vector<vector <double> > m;
    
        Matrix();
        Matrix(int ,int);
        //exception creation
        Matrix(Matrix*, int ,int);
        //oparetor
        Matrix* operator+(Matrix);
        Matrix* operator-(Matrix*);
        Matrix operator*(Matrix);
        Matrix operator*(Matrix*);
        void operator=(Matrix);
        void operator=(Matrix*);
        //normal function
        void setSize(int ,int);
        void set(int ,int ,double);
        void set(vector<int>);
        void print();
    
        void mf(int k ,Matrix*,Matrix*,double,double,double,Matrix* R_hat,double step);
        double cal_std();
        //double Matrix::cal_std();

        //int det();
    
};

#endif
