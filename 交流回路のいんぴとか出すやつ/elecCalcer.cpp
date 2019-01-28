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

/////////////////////////////////////
// CALC系の関数

/*複素数を極表示に変換*/
void convHukusoToKyoku(double *array){
    array[2] = hypot(array[0],array[1]);
    array[3] = atan2(array[1],array[0])*180.0/M_PI;
}
/*極表示を複素表示に変換*/
void convKyokuToHukuso(double *array){
    array[0] = array[2]*cos((array[3]/180*M_PI));
    array[1] = array[2]*sin((array[3]/180*M_PI));
}

////////////////////////////////////
//IMPUT系の関数

/*複素か極で値の受取*/
void inputData(double *array,int mode){
    if(mode == 1){
        cout << " num = ";
        cin >> array[0];
        cout << " img = ";
        cin >> array[1];
    }else if(mode == 2){
        cout << " num = ";
        cin >> array[2];
        cout << " θ = ";
        cin >> array[3];
    }
}
/*mode変更サブルーチン*/
bool selectHukusoOrKoku(){
    int num1=0;
    while(!(num1==1&&num1==2)){
        cout << ": 複素数表示なら1を, 極座標表示なら2を入力 : \n select = ";
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

////////////////////////////////////////
// OUTPUT系の関数 

/*中身の表示用*/
void showData(double *array,int select){
    if(select == 1){
        cout << array[0] << " + j(" << array[1] << ")" << endl;
    }else if(select == 2){
        cout << array[2] << " < " << array[3] << "°" << endl;
    }
}
void showData(double *array,int selectKH, int V_A_OHM_S){ /*K=1, H=2, V=1, A=2, OHM=3, S=4 */ 
    if(selectKH == 1){
        cout << array[0] << " + j(" << array[1] << ")";
    }else if(selectKH == 2){
        cout << array[2] << " < " << array[3] << "°";
    }

    switch(V_A_OHM_S){
        case 1:
            cout << "[V]" << endl;
        break;
        case 2:
            cout << "[A]" << endl;
        break;
        case 3:
            cout << "[Ω]" << endl;
        break;
        case 4:
            cout << "[S]" << endl;
        default:
        break;
    }
}

/*シーン移行用*/
void sceneChange(){
    cout << "|===========================================================|" << endl;
}
void sceneChange(int i){
    switch (i){
        case 1/* constant-expression */:
            /* code */
            cout << "|===========================================================|" << endl;
            break;
    
        default:
            break;
    }
    
}

/////////////////////////////////////////////
// MAIN関数
int main(){
    /*使用変数群*/
    int endAbleFlg = 0;
    int selectMode;
    double z[4] = {0.0};
    double y[4] = {0.0};
    double z2[4] = {0.0};
    double y2[4] = {0.0};
    double v[4] = {0.0};
    double i[4] = {0.0};
    double memory[4] = {0.0};

    /*メインループ*/
    while(true){
        sceneChange(1);
        cout << ": 初期値設定 : インピーダンスは1を, アドミンタンスは2を入力 : \n select = ";
        cin >> selectMode;

        /*いんぴ*/
        if(selectMode == 1){
            if(selectHukusoOrKoku() == true){
                cout << ": 値入れて : " << endl;
                inputData(z,1);
                convHukusoToKyoku(z);
            }else{
                inputData(z,2);
                convKyokuToHukuso(z);
            }
        /*あどみ*/
        }else if(selectMode == 2){
            if(selectHukusoOrKoku() == true){
                cout << ": 値入れて :" << endl;
                inputData(y,1);
                convHukusoToKyoku(y);
            }else{
                inputData(y,2);
                convKyokuToHukuso(y);
            }
        }else{
            cout << "入力値が違います" << endl;
        }
        sceneChange(1);

        ///////////////////////////////////////////////
        // メイン画面
        cout << ": 現在値 :" << endl;
        if(selectMode == 1){
            showData(z,1,3);
            showData(z,2,3);
        }else{
            showData(y,1,3);
            showData(y,2,3);
        }

        cout << ":MODE SELECT: 1_Z-Y変換, 2_抵抗の加算, ";

        cout << "\n終了時は1を, 続行するなら2を入力 : ";
        cin >> endAbleFlg;
        if(endAbleFlg == 1){
        return 0;
        }
    }
}