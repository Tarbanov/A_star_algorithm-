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
    double h=sqrt(((x_F-x_S)*(x_F-x_S))+((y_F-y_S)*(y_F-y_S)));
    return h;
}


void path (int x_S, int y_S,int x_F, int y_F, vector<vector<char>>&v,int row,int col){

    vector<int> dx = {1,-1,0,0};
    vector<int> dy = {0,0,1,-1};
    Node current(x_S,y_S,0, heuristic(x_S,y_S,x_F,y_F),heuristic(x_S,y_S,x_F,y_F));

    vector<int> xhelper;
    vector<int> yhelper;
    vector<double> fhelper;
    int index =0;

    int k=x_S;
    int l=y_S;
    while(v[l][k]!='F'){
         for(int i=0;i<4;++i) {
             int newX = current.x + dx[i];
             int newY = current.y + dy[i];
             int newG = current.g + 0.1;
             double newF = heuristic(newX, newY, x_F, y_F) + newG;


             if(v[newY][newX]=='#'){
                 continue;
             }




             if (newF<current.f+current.g) {



                 current.f=newF;
                 current.g=newG;

                 for(int n =0;n<row;n++){
                     for(int m=0;m<col;m++){
                         v[newY][newX]='@';
                         cout << v[n][m] << " ";
                     }
                     cout << endl;
                 }

                 k=newX;
                 l=newY;
                 current.y=newY;
                 current.x=newX;
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
            if(c==' '){
                continue;
            }
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
            cout << c << " ";
            columns++;
        }
        rows++;
        cout << endl;
    }

    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(vecMap[i][j]=='S'){
                x_start=j;
                y_start=i;
                break;
            }
        }
    }


    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(vecMap[i][j]=='F'){
                x_finish=j;
                y_finish=i;
                break;
            }
        }
    }

    cout << x_start << " " << y_start << endl;
    cout << x_finish << " " << y_finish << endl;


    path(x_start,y_start,x_finish,y_finish,vecMap,rows,columns);


}