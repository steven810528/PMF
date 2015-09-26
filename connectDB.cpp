#include  <iostream>
#include  <stdio.h>
#include  <stdlib.h>
#include  <sqlite3.h>
#include  <vector>
#include  <sstream>



//#include "toolbox.cpp"
int s2int(string s);
double s2dbl(string s);
void initialBuffer();
static vector<vector< double > > Buffer;
static int maxRow=10000;
static int maxCol=50000;

//static int maxRow=55935;
//static int maxCol=303409;

static int callback(void *data, int argc, char **argv, char **azColName){
    
    //fprintf(stderr, "%s: ", (const char*)data);
    //cout<<azColName[0];
    string user=string(argv[0]);
    string item=string(argv[1]);
    string value=string(argv[2]);
    if(s2int(user)<maxRow && s2int(item)<maxCol){
        Buffer[s2int(user)][s2int(item)]=s2dbl(value);
    }
    
    return 0;
}
int connect(vector<double> &Dma)
{
    initialBuffer();
    
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    const char* data = "A record had been read";
    
    
    /* Open database */
    rc = sqlite3_open("test.db", &db);
    if( rc )
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
        return 0;
    }
    else{
        fprintf(stderr, "Opened database successfully\n");
        
        //################################################################
        //開始將資料庫轉入Vector內
        
        sql="SELECT Account, Item, Rating FROM Ratings_ori";
        rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
        
        if( rc != SQLITE_OK ){
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }else{
            fprintf(stdout, "Operation done successfully\n");
            cout<<maxRow<<endl;
            cout<<maxCol<<endl;
        }
        
        //################################################################
        return 1;
    }
    
    sqlite3_close(db);
    
}
void initialBuffer()
{
    
    Buffer.resize(maxRow);
    for(int i=0;i<Buffer.size();i++)
    {
        Buffer[i].resize(maxCol);
    }
    
    for(int i=0;i<Buffer.size();i++)
    {
        for(int j=0;j<Buffer[i].size();j++)
        {
            Buffer[i][j]=-1;
        }
    }
}
int s2int(string s){
    stringstream ss(s);
    int a ;
    ss>>a;
    return a;
}
double s2dbl(string s)
{
    stringstream ss(s);
    double a ;
    ss>>a;
    return a;
}
