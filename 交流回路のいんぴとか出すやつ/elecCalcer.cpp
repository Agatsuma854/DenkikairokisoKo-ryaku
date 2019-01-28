/*------------------------------------*/
/*C++で書いているので gcc ではコンパイルできないです...スマソ
// g++ ってコンパイラいれれば使えるはず.
//
//C++と言ってもほぼCの記述ですが, 
/*
/*------------------------------------*/
#include <iostream>
#include <cmath>
using namespace std;

void convHukusoToKyoku(double *array){
    array[2] = hypot(array[0],array[1]);
    array[3] = atan2(array[1],array[0])*180.0/M_PI;
}

void convKyokuToHukuso(double *array){
    array[0] = array[2]*cos((array[3]/180*M_PI));
    array[1] = array[2]*sin((array[3]/180*M_PI));
}

void inputData(double *array,int mode){
    if(mode == 1){
        cin >> array[0];
        cin >> array[1];
    }else if(mode == 2){
        cin >> array[2];
        cin >> array[3];
    }
}

bool selectHukusoOrKoku(){
    int num1=0;
    while(!(num1==1&&num1==2)){
        cout << "複素数表示なら1を, 極座標表示なら2を入力 /n select = ";
        cin >> num1;
        if(num1 == 1){
            return true; // 複素数なら true
        }else if(num1 == 2){
            return false; // 極表示なら false
        }else{
            cout << "まともな数入れろ!!" << endl;
        }
    }
}

int main(){
    /*使用変数群*/
    int endAbleFlg = 0;
    int selectMode;
    double z[4] = {0.0};
    double y[4] = {0.0};
    double memory[4] = {0.0};

    /*メインループ*/
    while(true){
        cout << ": MODE SELECT :" << endl;
        cout << "初期値設定 : インピーダンスは1を, アドミンタンスは2を /n select = ";
        cin >> selectMode;

        /*いんぴ*/
        if(selectMode == 1){
            if(selectHukusoOrKoku() == true){
                cout << "値入れろ" << endl;
                inputData(z,1);
                convHukusoToKyoku(z);
            }else{
                inputData(z,2);
                convKyokuToHukuso(z);
            }
        /*あどみ*/
        }else if(selectMode == 2){
            if(selectHukusoOrKoku() == true){
                cout << "値入れろ" << endl;
                inputData(y,1);
                convHukusoToKyoku(y);
            }else{
                inputData(y,2);
                convKyokuToHukuso(y);
            }
        }else{
            cout << "入力値が違います" << endl;
        }

        cout << "終了時は1を, 続行するなら2を入力" << endl;
        cin >> endAbleFlg;
        if(endAbleFlg == 1){
        return 0;
        }
    }
}