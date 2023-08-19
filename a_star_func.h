#ifndef A_STAR_ALGORITHM_A_STAR_FUNC_H
#define A_STAR_ALGORITHM_A_STAR_FUNC_H

#endif //A_STAR_ALGORITHM_A_STAR_FUNC_H

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

int right_coordinates_x(int x_st, int col){
    while (x_st<0 or x_st >=col){
        cout << "set a number between 0 and " << col-1 << endl;
        cin.clear();
        cin >> x_st;
    }
    return x_st;
}

int right_coordinates_y(int y_st, int row){
    while (y_st<0 or y_st >=row){
        cout << "set a number between 0 and " << row-1 << endl;
        cin.clear();
        cin >> y_st;
    }
    return y_st;
}

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
        usleep(  microsecond);//sleeps for 1 second
    }
}

