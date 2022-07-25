#include <iostream>

using namespace std;



int GetIndexFromCoordinates(int i, int j, int width);
void DrawLevel(char level[], int width, int height);

int main(){

    constexpr int mWidth = 40;
    constexpr int mHeight = 30;

    char levelArray[]{ '+','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','+',
                       '|',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                       '|',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                       '|',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                       '|',' ',' ','+',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ','+',' ',' ',' ',' ',' ','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ','D',' ',' ',' ',' ',' ','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                       '|',' ','-','-','-','-','-','-','-','-','=','=','=','=','=','=','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                       '|',' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                       '|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',
                       '+','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','+' };

            DrawLevel(levelArray, mWidth, mHeight);


    }

int GetIndexFromCoordinates(int i, int j, int width){
        return i + j * width;
    }

void DrawLevel(char level[], int width, int height){
    for (int j = 0; j < height; j++){
        for (int i = 0; i < width; i++){
            int ind = GetIndexFromCoordinates(i, j, width);
            cout << level[ind];
        }
        cout <<endl;
    }
}


