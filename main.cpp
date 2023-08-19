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
    double g; // Cost from the starting point
    double h; //Distance estimation
    double f; //f=g+h

    Node(int x, int y, int g, double h,double f): x(x), y(y), g(g), h(h), f(f) {
    }
};

//h
double heuristic(int x_S,int y_S,int x_F, int y_F){
    double h=sqrt(((x_F-x_S)*(x_F-x_S))+((y_F-y_S)*(y_F-y_S)));//c=sqrt(x^2+b^2)
    return h;
}


void path (int x_S, int y_S,int x_F, int y_F, vector<vector<char>>&v,int row,int col){
    vector<int> dx = {1,-1,0,0};//Sides on which the path can go
    vector<int> dy = {0,0,1,-1};//Sides on which the path can go
    Node current(x_S,y_S,0, heuristic(x_S,y_S,x_F,y_F),heuristic(x_S,y_S,x_F,y_F));

    vector<int> xhelper;
    vector<int> yhelper;
    vector<double> fhelper;
    vector<double> ghelper;
    vector<int> visited;
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
            double newG = current.g + 0.7;//the cost of 1 move = 0.5
            double newF = heuristic(newX, newY, x_F, y_F) + newG;

            //I make sure that I don't go beyond the boundaries
            if(newX>=col || newY>=row || newX<0 || newY<0){
                continue;
            }
            //If a possible move == @ or # or s => skip it
            if(v[newY][newX]=='@'){
                continue;
            }
            if(v[newY][newX]=='#'){
                continue;
            }
            if(v[newY][newX]=='S'){
                continue;
            }
            //writing possible move to vector
            xhelper.push_back(newX);
            yhelper.push_back(newY);
            fhelper.push_back(newF);
            ghelper.push_back(newG);
            index++;
        }

        //Finding the lowest f
        num_help=999999999;
        for(int i =0;i<index;i++){
            if(fhelper[i]<=num_help){
                num=i;
                num_help=fhelper[i];
            }
        }


        current.f=fhelper[num];

        current.g=ghelper[num];

        //writing a new move
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
        
        //I delete those places where I have already been
        fhelper.erase(fhelper.begin()+num);
        xhelper.erase(xhelper.begin()+num);
        yhelper.erase(yhelper.begin()+num);
        ghelper.erase(ghelper.begin()+num);
        index--;


        unsigned int microsecond = 100000;
        usleep(  0.5*microsecond);//sleeps for 0.5 second
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

    //menu
    cout << "A* algorithm:" << endl;
    cout << "1) Select a map" << endl;
    cout << endl ;

    cout << "Choose an action: ";
    cin >> menu_num;

    while(menu_num!=1){
        cout << "There is no such number, please enter the correct number:";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> menu_num;
    }

    system("clear");
    cout << "Maps: " << endl;
    cout << "1) Map1(size: 18*42)" << endl;
    cout << "2) Map2(size: 25*30)" << endl;
    cout << "3) Map3(size: 39*74)" << endl;
    cout << "4) Choose my own map" << endl;
    cout << endl;

    cout << "Choose a map: ";
    cin >> menu_map;

    while(menu_map!=1 && menu_map!=2 && menu_map!=3 && menu_map!=4){
        cout << "There is no such number, please enter the correct number:";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> menu_map;
    }



    //reading .txt and writing up to 2D vector
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

    if(menu_map==4){
        system("clear");
        string name_own_map;
        cout << "Enter file name:" <<endl;
        cin >> name_own_map;
        string file_name[8] ={"cmake-build-debug","a.out","CMakeLists.txt","documentation.txt","main.cpp","map1.txt","map2.txt","map3.txt"};
        bool flag2 = true;

        for (const auto & l : file_name){
            if (name_own_map == l)
                flag2 = false;
        }

        bool flag = false;

        while(!flag) {
            ifstream iff(name_own_map);
            if (iff.good() and flag2){
                flag= true;
            } else {
                cout << "There is no such name, please enter the correct name:";
                cin.clear();
                cin >> name_own_map;
                flag2= true;
                for (const auto & l : file_name){
                    if (name_own_map == l)
                        flag2 = false;
                }

            }
        }

        ifstream map(name_own_map);
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

//Replacing numbers with signs 1==# , 0==.
    int rows=0;
    int columns =0;
    if(menu_map!=4) {
        for (vector<char> &row: vecMap) {
            columns = 0;
            for (char &c: row) {
                if (c == '1') {
                    c = '#';
                }
                if (c == '0') {
                    c = '.';
                }
                cout << c << " ";
                columns++;
            }
            rows++;
            cout << endl;
        }
        //find Start coordinates
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (vecMap[i][j] == 'S') {
                    x_start = j;
                    y_start = i;
                    break;
                }
            }
        }

        //find Finish coordinates
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (vecMap[i][j] == 'F') {
                    x_finish = j;
                    y_finish = i;
                    break;
                }
            }
        }
    }
    else{
        system("clear");

        for (vector<char> &row: vecMap) {
            columns = 0;
            for (char &c: row) {
                if (c == '1') {
                    c = '#';
                }
                if (c == '0') {
                    c = '.';
                }
                cout << c << " ";
                columns++;
            }
            rows++;
            cout << endl;
        }


        cout << rows << columns << endl;
        cout << "set start coordinates" << endl;
        cout << "x-axis: ";
        cin >> x_start;
        while (x_start<0 or x_start >=columns){
            cout << "set a number between 0 and " << columns-1 << endl;
            cin.clear();
            cin >> x_start;
        }
        cout << "y-axis: ";
        cin >> y_start;
        while (y_start<0 or y_start >=rows){
            cout << "set a number between 0 and " << rows-1 << endl;
            cin.clear();
            cin >> y_start;
        }
        cout << "set finish coordinates" << endl;
        cout << "x-axis: ";
        cin >> x_finish;
        while (x_finish<0 or x_finish >=columns){
            cout << "set a number between 0 and " << columns-1 << endl;
            cin.clear();
            cin >> x_finish;
        }
        cout << "y-axis: ";
        cin >> y_finish;
        while (y_finish<0 or y_finish >=rows){
            cout << "set a number between 0 and " << rows-1 << endl;
            cin.clear();
            cin >> y_finish;
        }

        vecMap[y_start][x_start]='S';
        vecMap[y_finish][x_finish]='F';




    }



    path(x_start,y_start,x_finish,y_finish,vecMap,rows,columns);

}