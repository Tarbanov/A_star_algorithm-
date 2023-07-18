#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

struct Node{
    int x; //X coordinate
    int y; //Y coordinate
    int g; // Cost from the starting point
    double h; //Distance estimation
    double f; //f=g+h

    Node(int x, int y, int g, double h,double f): x(x), y(y), g(g), h(h), f(f) {

    }
};

//h
double heuristic(int x_S,int y_S,int x_F, int y_F){
    double h=sqrt(((x_S-x_F)*(x_S-x_F))+((y_S-y_F)*(y_S-y_F)));
    return h;
}


void path (int x_S, int y_S,int x_F, int y_F, vector<vector<char>>&v,int row,int col){

    vector<int> dx = {2,-2,0,0};
    vector<int> dy = {0,0,1,-1};
    Node current(x_S,y_S,0, heuristic(x_S,y_S,x_F,y_F),heuristic(x_S,y_S,x_F,y_F));

//    vector<vector<int>> gScore(row,vector<int>(col));
//    gScore[x_S][y_S]=0;

    int k=x_S;
    int l=y_S;
    while(v[k][l]!='F'){
         for(int i=0;i<4;i++) {
             int newX = current.x + dx[i];
             int newY = current.y + dy[i];

             int newG = current.g + 1;
             int newF = heuristic(newX, newY, x_F, y_F) + newG;

             if(v[newX][newY]=='#'){
                 break;
             }

             if (newF<current.f) {
                 x_S=newX;
                 y_S=newY;
                 current.f=newF;
                 current.g=newG;

                 for(int n =0;n<row;n++){
                     for(int m=0;m<col;m++){
                         v[newX][newY]='@';
                         cout << v[n][m];
                     }
                     cout << endl;
                 }
             }
         }
    }



}



int main() {
    int x_start=0;
    int y_start=0;
    int x_finish=0;
    int y_finish=0;

    string line;
    vector<vector<char>> vecMap;

    ifstream map("map1.txt");
    while(getline(map,line)){
        vector<char> row;
        for(char &c : line){
            row.push_back(c);
        }
        vecMap.push_back(row);
    }

    int rows=0;
    int columns =0;
    for(vector<char> &row : vecMap){
        columns=0;
        for(char &c: row){

            if(c=='1'){
                c='#';
            }
            if(c=='0'){
                c='.';
            }
            cout << c;
            columns++;
        }
        rows++;
        cout << endl;
    }

    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(vecMap[i][j]=='S'){
                x_start=i;
                y_start=j;
                break;
            }
        }
    }

    cout << x_start << " " << y_start << endl;

    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(vecMap[i][j]=='F'){
                x_finish=i;
                y_finish=j;
                break;
            }
        }
    }


    heuristic(x_start,y_start,x_finish,y_finish);
    path(x_start,y_start,x_finish,y_finish,vecMap,rows,columns);


}