#include <iostream>

using namespace std;

struct Process{
    int stt = -1; // So thu tu cac tien trinh
    int arr = 0; // Arrival time
    int bur = 0; // Burst time
    int sta = 0; // Start time
    int tat = 0; // Turnaround time
    int wt = 0;
    int fin = 0; // Finish time
}typedef P;

int n, q; //n la so luong tien trinh, q la quantum time
P pro[15]; // Mang chua thong tin cac tien trinh
int time = 0; // time chua thong tin thoi gian thuc

void swap(int &a, int &b){
    int t = a;
    a = b;
    b = t;
}

int partition (P pro[], int low, int high){
    int pivot = pro[high].arr;   
    int left = low;
    int right = high - 1;
    while(true){
        while(left <= right && pro[left].arr < pivot) left++;
        while(right >= left && pro[right].arr > pivot) right--;
        if (left >= right) break;
        swap(pro[left], pro[right]);
        left++;
        right--;
    }
    swap(pro[left], pro[high]);
    return left;
}

void quickSort(P pro[], int low, int high){
    if (low < high)
    {
        int pi = partition(pro, low, high);
        quickSort(pro, low, pi - 1);
        quickSort(pro, pi + 1, high);
    }
}

void Input(P pro[], int n){
    for (int i = 0; i < n; i++)
    {
        pro[i].stt = i + 1;
        cout << "\nNhap vao tien trinh thu " << pro[i].stt << " : ";
        cout << "\nNhap vao Arrival time: ";
        cin >> pro[i].arr;
        cout << "\nNhap vao Burst time: ";
        cin >> pro[i].bur;
    }
}

void bubbleSort(P pro[], int n){
    int i, j;
    P temp;
    bool haveSwap = false;
    for (i = 0; i < n-1; i++){
        haveSwap = false;
        for (j = 0; j < n-i-1; j++){
            if (pro[j].stt > pro[j+1].stt){
                {            
                    temp = pro[j];
                    pro[j] = pro[j + 1];
                    pro[j] = temp;
                }
                haveSwap = true;
            }
        }
        if(haveSwap == false){
            break;
        }
    }
}


void RoundRobin(P pro[], int n, int q){
    int que[15];
    int count = n;

    pro[0].sta = pro[0].arr;
    time = pro[0].arr;
    if (pro[0].bur > q){
        pro[0].tat += q;
        pro[0].bur -= q;
        time += q;
    }
    else{
        pro[0].tat += pro[0].bur;
        time += pro[0].bur;
        pro[0].fin = pro[0].bur;
        pro[0].bur = 0;
        pro[0].wt
    }
}

void Output(P pro[], int n){
    cout << "STT\tArrival time\tBurst time\tStart time\tTurnaround time\tWaiting time\tFinish time\n";
    for (int i = 0; i < n; i++)
    {
    cout << pro[i].stt<<"\t"<<pro[i].arr<<"\t\t"<<pro[i].bur<<"\t\t"<<pro[i].sta<<"\t\t"<<pro[i].tat<<"\t\t"<<pro[i].wt<<"\t\t"<<pro[i].fin<<endl;
    }
}

void CopyPtoT(P pro[], P temp[], int n){
    for (int i = 0; i < n; i++){
        temp[i].stt = pro[i].stt;
        temp[i].arr = pro[i].arr;
        temp[i].bur = pro[i].bur;
    }
}

void CopyPtoT(P pro[], P temp[], int n){
    for (int i = 0; i < n; i++){
        pro[i].tat = temp[i].tat;
        pro[i].fin = temp[i].fin;
        pro[i].sta = temp[i].sta;
        pro[i].wt = temp[i].wt;
    }
}

int main() {
    cout << "Nhap vao so luong tien trinh: ";
    cin >> n;

    cout << "\nNhap vao quantum time: ";
    cin >> q;

    Input(pro, n);

    quickSort(pro, 0, n);

    P temp[15];
    CopyPtoT(pro, temp, n);

    RoundRobin(temp, n, q);

    CopyTtoP(pro, temp, n)
    
    bubbleSort(pro, n);

    Output(pro, n);

    return 0;
}
