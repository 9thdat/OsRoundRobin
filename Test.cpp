#include <iostream>

using namespace std;

struct Process{
    int stt = 0; // So thu tu cac tien trinh
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
        cout << "Nhap thong tin cua tien trinh thu " << pro[i].stt;
        cout << "\n\tNhap vao Arrival time: ";
        cin >> pro[i].arr;
        cout << "\tNhap vao Burst time: ";
        cin >> pro[i].bur;
    }
}

void SelectionSort(P A[], int n)
{
    int min;
    for (int i = 0; i < n - 1; i++)
    {
        min = i; // t?m th?i xem A[i] là nh? nh?t
        // Tìm ph?n t? nh? nh?t trong do?n t? A[i] d?n A[n - 1]
        for (int j = i + 1; j < n; j++)
            if (A[j].stt < A[min].stt) // A[j] mà nh? hon A[min] thì A[j] là nh? nh?t
                min = j; // luu l?i v? trí A[min] m?i v?a tìm du?c
        if (min != i) // n?u nhu A[min] không ph?i là A[i] ban d?u thì d?i ch?
            swap(A[i], A[min]);
    }
}

void RoundRobin(P pro[], int n, int q){
    P que[15]; //Hang doi cap CPU
    P suc[15]; //Cac tien trinh da hoan thanh
    int countS = 0; //Bien dem cac tien trinh da hoan thanh
    int countQ = 0; //Bien dem cac tien trinh co trong hang doi

    //Xu ly tien trinh thu nhat pro[0]
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
        pro[0].wt = 0;
        suc[0] = pro[0];
        countS++;
        for(int i = 0; i < n - 1; i++){
            pro[i] = pro[i + 1];
        }
        n--;
    }

    for (int i = 1; i < n; i++){ //Kiem tra cac tien trinh co phu hop de vao hang doi khong
        if (pro[i].arr <= q)
        {
            que[countQ] = pro[i];
            for(int m = i; m < n - 1; m++)
            {
                pro[m] = pro[m + 1];
            }
            i--;
            n--;
            countQ++;
        }
    }
    
    int count = n; //Bien dem cac tien trinh can xu ly
    
    if (countQ != 0){ //Neu co tien trinh trong hang doi
    //Them Waiting time va Turnaround time cho cac tien trinh trong hang cho
        if (pro[0].bur != 0){ 
            for (int i = 1; i < countQ; i++){ 
                que[i].wt = q - que[i].arr;
                que[i].tat = q - que[i].arr;
            }
            
        }
        else
            for (int i = 1; i < countQ; i++){ 
                que[i].wt = pro[i].bur - que[i].arr;
                que[i].tat = pro[i].bur - que[i].arr;
            }
    }

    if (countS == 0) // Kiem tra xem tien trinh pro[0] co duoc vao hang doi khong
        {
            que[countQ] = pro[0]; 
            countQ++;
        }
    
    while(countS != count){     
        //Xu ly tien trinh o dau hang cho  
        que[0].sta = time;

        if (que[0].bur > q){
            que[0].tat += q;
            que[0].bur -= q;
            time += q;
        }
        else{
            que[0].tat += que[0].bur;
            time += pro[0].bur;
            que[0].fin = que[0].tat + que[0].sta;
            pro[0].bur = 0;
            suc[countS] = que[0];
            countS++;
            for(int i = 0; i < countQ - 1; i++){
                que[i] = que[i + 1];
            }
            countQ--;
        }

        for (int i = 0; i < n; i++){ //Kiem tra tien trinh co phu hop de vao hang doi khong
            if (pro[i].arr <= q){
                que[countQ] = pro[i];
                for(int m = i; m < n - 1; m++){
                    pro[m] = pro[m + 1];
                }
                n--;
                i--;
                countQ++;
            } 
        }

        if (que[0].bur != 0){ //Them Waiting time va Turnaround time cho cac tien trinh trong hang cho
            for (int i = 1; i < countQ; i++){ 
                que[i].wt = q - que[i].arr;
                que[i].tat = q - que[i].arr;
            }
        }
        else{
        for (int i = 1; i < countQ; i++){ 
            que[i].wt = que[0].bur - que[i].arr;
            que[i].tat = que[0].bur - que[i].arr;
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
        }
    }

    for (int i = 0; i < count; i++){ //Copy thong tin cac tien trinh da hoan thanh tu mang suc qua mang pro
        pro[i] = suc[i];
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

void CopyTtoP(P pro[], P temp[], int n){
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

    cout << "Nhap vao quantum time: ";
    cin >> q;

    Input(pro, n);

    quickSort(pro, 0, n);

    P temp[15];
    CopyPtoT(pro, temp, n);

    RoundRobin(temp, n, q);

    CopyTtoP(pro, temp, n);
    
    SelectionSort(pro, n);

    Output(pro, n);

    return 0;
}

