/*------------------------------------|
|:C++で書いているので gcc ではコンパイルできないです. g++ 入れて
|:将来的にclassにしちゃう予定, 多分..
|2019/1/28~
|------------------------------------*/
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

void xyRecUpdata(double *x,double *y){
    y[2] = 1.0/x[2];
    y[3] = -1.0*x[3];
    convKyokuToHukuso(y);
}

void multiValu(double *x,double *y,double *ans){
    ans[2] = x[2]*y[2];
    ans[3] = x[3]+y[3];
    convKyokuToHukuso(ans);
}

////////////////////////////////////
//IO系の関数
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
            cout << "無効な価です!!" << endl;
        }
    }
}

void xyImputController(double *x,double *y){
    if(selectHukusoOrKoku() == true){
        cout << ": 値入れて : " << endl;
        inputData(x,1);
        convHukusoToKyoku(x);
    }else{
        inputData(x,2);
        convKyokuToHukuso(x);
    }
    //ここでYに変換かけとく
    xyRecUpdata(x,y);
}
/*中身の表示用*/
void showData(double *array,int select){
    if(select == 1){
        cout << array[0] << " + j(" << array[1] << ")" << endl;
    }else if(select == 2){
        cout << array[2] << " < " << array[3] << "°" << endl;
    }
}
void showData(double *array,int selectKH, int V_A_OHM_S){ /*K=1, H=2,| V=1, A=2, OHM=3, S=4 */ 
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

void sceneChange(int num){
    switch(num){
        case 1:
            sceneChange();
        break;
        case 2:
            cout << "|~~~~~~~~~~~~~~~~~~~~" << endl;
        break;
        default:
            cout << "実はわたくしAMDerなんですよ...申し訳ないですが" << endl;
        break;
    }
}
/////////////////////////////////////////////
// MAIN関数 
int main(){
    // 後で構造体かなんかにする予定
    /*使用変数群*/
    int endAbleFlg = 0;
    int selectMode;
    double z[4] = {0.0};
    double y[4] = {0.0};
    double z2[4] = {0.0};
    double y2[4] = {0.0};
    double v[4] = {0.0};
    double i[4] = {0.0};
    double ans[4] = {0.0};

    /*メインループ*/
    while(true){
        sceneChange();
        cout << ": 初期値設定 : インピーダンスは1を, アドミンタンスは2を入力 : \n select = ";
        cin >> selectMode;
        //cout << "----------" << endl;
        switch(selectMode){
            case 1:
                xyImputController(z,y);
            break;
            case 2:
                xyImputController(y,z);
            break;
            default:
                cout << "無効な価です" << endl;
            break;
        }
        sceneChange();

        ///////////////////////////////////////////////
        // メイン画面(暇になったら関数にしてループに突っ込む)
        while(true){
            cout << ": 現在の抵抗値 :" << endl;
            showData(z,1,3);
            showData(z,2,3);
            cout << "---" << endl;
            showData(y,1,4);
            showData(y,2,4);
            sceneChange();
            /*MODE選択画面*/
            cout << ":MODE SELECT: 1-抵抗の加算, 2-電圧の導出, 3-電流の導出, 4-初期設定に戻る, 0-終了" << endl;
            cout << " select = ";
            cin >> selectMode;
            //cout << "----------" << endl;
            if(selectMode == 4){
                cout << "初期設定画面にジャンプします" << endl;
                sceneChange(1);
                sceneChange(2);
                sceneChange(2);
                sceneChange(2);
                sceneChange(2);
                break;
            }
            switch(selectMode){
                /*終了処理*/
                case 0:
                    cout << "終了します" << endl;
                    return 0;
                break;

                /*抵抗の加算*/
                case 1:
                    cout << ": インピーダンスは1を, アドミンタンスは2を入力 : \n select = ";
                    cin >> selectMode;
                    //cout << "----------" << endl;
                    if(selectMode == 1){
                        xyImputController(z2,y);
                    }else if(selectMode == 2){
                        xyImputController(y2,z);
                    }else{
                        cout << "まともに価をいれろや" << endl;
                    }
                    z[0] += z2[0];
                    z[1] += z2[1];
                    convHukusoToKyoku(z);
                    xyRecUpdata(z,y);
                    sceneChange(1);
                    cout << "! 加算後 ";
                break;

                /*電圧の導出*/
                case 2:
                    cout << ": 電流のパラメータ : 複素表示は1を, フェーザ表示は2を入力 : \n select = ";
                    cin >> selectMode;
                    //cout << "----------" << endl;
                    if(selectMode == 1){
                        inputData(i,1);
                        convHukusoToKyoku(i);
                    }else if(selectMode == 2){
                        inputData(i,2);
                        convKyokuToHukuso(i);
                    }else{
                        cout << "まともに価をいれろや" << endl;
                    }
                    multiValu(z,i,ans);
                    cout << "#############" << endl;
                    cout << ": 求めた電圧 :" << endl;
                    showData(ans,1,1);
                    showData(ans,2,1);
                    cout << "#############" << endl;
                break;

                /*電流の導出*/
                case 3:
                    cout << ": 電圧のパラメータ : 複素表示は1を, フェーザ表示は2を入力 : \n select = ";
                    cin >> selectMode;
                    //cout << "----------" << endl;
                    if(selectMode == 1){
                        inputData(v,1);
                        convHukusoToKyoku(v);
                    }else if(selectMode == 2){
                        inputData(v,2);
                        convKyokuToHukuso(v);
                    }else{
                        cout << "まともに価をいれろや" << endl;
                    }
                    multiValu(y,v,ans);
                    cout << "#############" << endl;
                    cout << ": 求めた電流 :" << endl;
                    showData(ans,1,2);
                    showData(ans,2,2);
                    cout << "#############" << endl;
                break;
                default:
                    cout << "!!画面を更新します!!" << endl;
                    sceneChange(2);
                    sceneChange(2);
                    sceneChange(2);
                    sceneChange(2);
                break;
            }
        }
    }
}