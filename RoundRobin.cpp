#include <iostream>

using namespace std;

struct Process{
    int stt = 0; // So thu tu cac tien trinh
    int arr = 0; // Arrival realtime
    int bur = 0; // Burst realtime
    int sta = 0; // Start realtime
    int tat = 0; // Turnaround realtime
    int wt = 0;
    int fin = 0; // Finish realtime
}typedef P;

int n, q; //n la so luong tien trinh, q la quantum realtime
P pro[15]; // Mang chua thong tin cac tien trinh
int realtime = 0; // realtime chua thong tin thoi gian thuc
int tempB = 0; //Luu gia tri Burst realtime o lan cuoi cung tien trinh duoc cap CPU
int countS = 0; //Bien dem cac tien trinh da hoan thanh
int countQ = 0; //Bien dem cac tien trinh co trong hang doi

void swap(int &a, int &b){
    int t = a;
    a = b;
    b = t;
}

void bubbleSort(P pro[], int n)
{
    int i, j;
    bool haveSwap = false;
    for (i = 0; i < n-1; i++){
        haveSwap = false;
        for (j = 0; j < n-i-1; j++){
            if (pro[j].arr > pro[j+1].arr){
                swap(pro[j], pro[j+1]);
                haveSwap = true;
            }
        }
        if(haveSwap == false){
            break;
        }
    }
}

void bubbleSortSTT(P pro[], int n)
{
    int i, j;
    bool haveSwap = false;
    for (i = 0; i < n-1; i++){
        haveSwap = false;
        for (j = 0; j < n-i-1; j++){
            if (pro[j].stt > pro[j+1].stt){
                swap(pro[j], pro[j+1]);
                haveSwap = true;
            }
        }
        if(haveSwap == false){
            break;
        }
    }
}

void Input(P pro[], int n){
    for (int i = 0; i < n; i++)
    {
        pro[i].stt = i + 1;
        cout << "Nhap thong tin cua tien trinh thu " << pro[i].stt;
        cout << "\n\tNhap vao Arrival realtime: ";
        cin >> pro[i].arr;
        cout << "\tNhap vao Burst realtime: ";
        cin >> pro[i].bur;
    }
}

void RoundRobin(P temp[], int n, int q){
    P que[15]; //Hang doi cap CPU
    P suc[15]; //Cac tien trinh da hoan thanh
    int count = n; //Bien dem cac tien trinh can xu ly

    //Xu ly tien trinh thu nhat pro[0]
    temp[0].sta = temp[0].arr;
    realtime = temp[0].arr;

    if (temp[0].bur > q){
        temp[0].tat += q;
        temp[0].bur -= q;
        realtime += q;
    }
    else{
        temp[0].tat += temp[0].bur;
        realtime += temp[0].bur;
        temp[0].fin = temp[0].bur;
        temp[0].bur = 0;
        temp[0].wt = 0;
        suc[0] = temp[0];
        countS++;
        for(int i = 0; i < n; i++){
            temp[i] = temp[i + 1];
        }
        n--;
    }

    if (countS == 0){//Kiem tra cac tien trinh co phu hop de vao hang doi khong
        for (int i = 1; i < n; i++){ 
            if (temp[i].arr <= realtime)
            {
                que[countQ] = temp[i];
                for(int m = i; m < n - 1; m++)
                {
                    temp[m] = temp[m + 1];
                }
                i--;
                n--;
                countQ++;
            }
        }
    }
    else{
        for (int i = 0; i < n; i++){ 
            if (temp[i].arr <= realtime)
            {
                que[countQ] = temp[i];
                for(int m = i; m < n - 1; m++)
                {
                    temp[m] = temp[m + 1];
                }
                n--;
                countQ++;
            }
        }
    }
    
    if (countQ != 0){ //Neu co tien trinh trong hang doi
            //Them Waiting realtime cho cac tien trinh trong hang cho
            for (int i = 0; i < countQ; i++){ 
                que[i].wt = realtime - que[i].arr;
            }
    }

    if (countS == 0) // Kiem tra xem tien trinh temp[0] co duoc vao hang doi khong
        {
            que[countQ] = temp[0]; 
            countQ++;
            for(int i = 0; i < n; i++){
                temp[i] = temp[i + 1];
        }
        n--;
        }
    //Xu ly trong Queue
    while(countS != count){     
        //Xu ly tien trinh o dau hang cho
        if (tempB <= q){
            tempB = 0;
        }

        if (que[0].tat == 0){  
            que[0].sta = realtime;
        }

        if (que[0].bur > q){
            que[0].tat += q;
            que[0].bur -= q;
            realtime += q;
            tempB = q;
        }
        else{
            realtime += que[0].bur;
            que[0].fin = realtime;
            que[0].tat = que[0].fin - que[0].arr;
            tempB = que[0].bur;
            que[0].bur = 0;
            suc[countS] = que[0];
            countS++;
        }

        if (countS + countQ != count)
            for (int i = 0; i < n; i++){ //Kiem tra tien trinh co phu hop de vao hang doi khong
                if (temp[i].arr <= realtime){
                    que[countQ] = temp[i];
                    for(int m = i; m < n - 1; m++){
                        temp[m] = temp[m + 1];
                    }
                    n--;
                    countQ++;
                } 
            }

        if (tempB >= q){ //Them Waiting realtime cho cac tien trinh trong hang cho
            for (int i = 1; i < countQ; i++){
                if (que[i].tat != 0){
                    que[i].wt += tempB; 
                }
                else{ 
                    que[i].wt = realtime - que[i].arr;
                }
            }
        }
        else{
            for (int i = 0; i < countQ; i++){ 
                if (que[i].tat != 0){
                        que[i].wt += tempB; 
                    }
                    else{ 
                        que[i].wt = realtime - que[i].arr;
                    }
        }
        }

        if (que[0].bur != 0){ // Kiem tra xem tien trinh vua duoc cap CPU co duoc dua ra sau hang doi khong
            que[countQ] = que[0];
            countQ++;
            for (int i = 0; i < countQ - 1; i++){
                que[i] = que[i + 1];
            }
            countQ--;
        }
        else{
            for (int i = 0; i < countQ - 1; i++){
                que[i] = que[i + 1];
            }
            countQ--;
        }
    }

    for (int i = 0; i < count; i++){ //Copy thong tin cac tien trinh da hoan thanh tu mang suc qua mang temp
        temp[i] = suc[i];
    }
}

void Output(P pro[], int n){
    cout << "STT\tArrival realtime\tBurst realtime\tStart realtime\tTurnaround realtime\tWaiting realtime\tFinish realtime\n";
    for (int i = 0; i < n; i++)
    {
    cout << pro[i].stt<<"\t"<<pro[i].arr<<"\t\t"<<pro[i].bur<<"\t\t"<<pro[i].sta<<"\t\t"<<pro[i].tat<<"\t\t"<<pro[i].wt<<"\t\t"<<pro[i].fin<<endl;
    }
}

void CopyPtoT(P pro[], P temp[], int n){
    for (int i = 0; i < n; i++){
        temp[i] = pro[i];
    }
}

void CopyTtoP(P pro[], P temp[], int n){
    for (int i = 0; i < n; i++){
        temp[i].bur = pro[i].bur;
    }
}

int main() {
    cout << "Nhap vao so luong tien trinh: ";
    cin >> n;

    cout << "Nhap vao quantum realtime: ";
    cin >> q;

    Input(pro, n);

    bubbleSort(pro, n);

    P temp[15];
    CopyPtoT(pro, temp, n);

    RoundRobin(temp, n, q);

    bubbleSortSTT(temp, n);

    CopyTtoP(pro, temp, n);

    Output(temp, n);

    return 0;
}
