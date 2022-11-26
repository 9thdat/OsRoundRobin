#include <iostream>

using namespace std;

struct Process{
    int stt; // So thu tu cac tien trinh
    int arr; // Arrival time
    int bur; // Burst time
    int sta; // Start time
    int att; // Turnaround time
    int fin; // Finish time
    int end; // End time
}typedef P;

int n, q; //n la so luong tien trinh, q la quantum time
P pro[15]; // Mang chua thong tin cac tien trinh
int time = 0; // time chua thong tin thoi gian thuc
int stt[15]; // luu so thu tu cac tien trinh

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
        stt[i] = pro[i].stt;
        cout << "\nNhap vao tien trinh thu " << pro[i].stt << " : ";
        cout << "Nhap vao Arrival time: ";
        cin >> pro[i].arr;
        cout << "\nNhap vao Burst time: ";
        cin >> pro[i].bur;
    }
}

void RoundRobin(P pro[], int n, int q){
    int que[15];
    quickSort(pro, 0, n);
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

void Output(P pro[], int n){
    cout << "STT\tArrival time\tBurst time\tStart time\tTurnaround time\tFinish time\tEnd time\n";
    for (int i = 0; i < n; i++)
    {
    cout << pro[i].stt<<"\t"<<pro[i].arr<<"\t"<<pro[i].bur<<"\t"<<pro[i].sta<<"\t"<<pro[i].att<<"\t"<<pro[i].fin<<"\t"<<pro[i].end<<endl;
    }
}

int main() {
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cout << "Nhap vao so luong tien trinh: ";
    cin >> n;

    cout << "\nNhap vao quantum time: ";
    cin >> q;

    Input(pro, n);
    RoundRobin(pro, n, q);
    
    bubbleSort(pro, n);

    Output(pro, n);

    return 0;
}
