#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include<unistd.h>  

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
    vector<double> ghelper;
    vector<int> visited;
    int visited_num=0;
    int index =0;
    int num;
    double num_help;

    int k=x_S;
    int l=y_S;
    while(l!=y_F || k!=x_F){
        system("clear");
        for(int i=0;i<4;++i) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];
            double newG = current.g + 0.6;
            double newF = heuristic(newX, newY, x_F, y_F) + newG;

            if(newX>=col || newY>=row || newX<0 || newY<0){
                continue;
            }

            if(v[newY][newX]=='@'){
                continue;
            }
            if(v[newY][newX]=='#'){
                continue;
            }
            if(v[newY][newX]=='S'){
                continue;
            }

            xhelper.push_back(newX);
            yhelper.push_back(newY);
            fhelper.push_back(newF);
            ghelper.push_back(newG);
            index++;
        }

        num_help=999999999;
        for(int i =0;i<index;i++){
            if(fhelper[i]<=num_help){
                num=i;
                num_help=fhelper[i];
            }
        }



        visited.push_back(num);
        visited_num++;

        current.f=fhelper[num];
        current.g=ghelper[num];

        v[yhelper[num]][xhelper[num]] = '@';
        for (int n = 0; n < row; n++) {
            for (int m = 0; m < col; m++) {
                cout << v[n][m] << " ";
            }
            cout << endl;
        }



        k=xhelper[num];
        l=yhelper[num];
        current.x=xhelper[num];
        current.y=yhelper[num];

        fhelper.erase(fhelper.begin()+num);
        xhelper.erase(xhelper.begin()+num);
        yhelper.erase(yhelper.begin()+num);
        ghelper.erase(ghelper.begin()+num);
        index--;


        unsigned int microsecond = 1000000;
        usleep( 0.5* microsecond);//sleeps for  second
    }
}



int main() {
    int x_start=0;
    int y_start=0;
    int x_finish=0;
    int y_finish=0;

    int menu_num;
    int menu_map;

    string line;
    vector<vector<char>> vecMap;

    system("clear");
    cout << "A* algorithm:" << endl;
    cout << "1) Select a map" << endl;
    cout << endl ;

    cout << "Choose an action: ";
    cin >> menu_num;

    while(menu_num!=1){
        cout << "There is no such number, please enter the correct number:";
        cin.clear();
        cin >> menu_num;
    }

    system("clear");
    cout << "Maps: " << endl;
    cout << "1) Map1(size: 18*42)" << endl;
    cout << "2) Map2(size: 25*30)" << endl;
    cout << endl;

    cout << "Choose a map: ";
    cin >> menu_map;

    while(menu_map!=1 && menu_map!=2 && menu_map!=3){
        cout << "There is no such number, please enter the correct number:";
        cin.clear();
        cin >> menu_num;
    }



    if(menu_map==1){
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
    }
    if(menu_map==2){
        ifstream map("map2.txt");
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
    }

    if(menu_map==3){
        ifstream map("map3.txt");
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

    path(x_start,y_start,x_finish,y_finish,vecMap,rows,columns);

}