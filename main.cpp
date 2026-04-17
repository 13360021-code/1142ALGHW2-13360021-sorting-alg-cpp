#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ==============================
// 工具函式
// ==============================
void printArray(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << "\n";
}

void printTitle(const string& title) {
    cout << "\n==============================\n";
    cout << title << "\n";
    cout << "==============================\n";
}

// ==============================
// 1. Selection Sort
// ==============================
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    //sort(arr.begin(),arr.end());
    for(int i=0;i<n-1;i++){
       int minIndex = i;
       for(int j=i+1;j<n;j++){
         //if(arr[j]<arr[minIndex])swap(arr[j],arr[minIndex]);
         if(arr[j]<arr[minIndex])minIndex=j;
       }
       swap(arr[i],arr[minIndex]);
    }
    // TODO:
    // 使用挑選排序法將 arr 由小到大排序
    //
    // 提示：
    // 1. 外圈從 i = 0 到 n-2
    // 2. 在未排序區間中找最小值的位置 minIndex
    // 3. 將 arr[i] 與 arr[minIndex] 交換
}

// ==============================
// 2. Insertion Sort
// ==============================
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for(int i=1;i<n;i++){
        int key = arr[i];
        int j = i;
        while((j>0)&&(arr[j-1]>key)){
            arr[j] = arr[j-1];// 如果前面的數字比 key 大，就把前面的數字往後移一格
            j--;
        } //arr[j]會一直和前面j-1個比較,只要key<a[j-1]就繼續排序,否則就退出來
        arr[j]=key;
    }
    // TODO:
    // 使用插入排序法將 arr 由小到大排序
    //
    // 提示：
    // 1. 外圈從 i = 1 到 n-1
    // 2. 設 key = arr[i]
    // 3. 將比 key 大的元素往右移
    // 4. 把 key 插入正確位置
}

// ==============================
// 3. Bubble Sort
// ==============================
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for(int i=0;i<n-1;i++){
        bool swapped=false;//每一輪開始前，先假設已經排好了,沒交換
        for(int j=0;j<n-1-i;j++){   // 為什麼是 n-i-1？因為每一輪結束後，最後面 i 個數字已經是最大的，不用再比了
            if(arr[j]>arr[j+1]){
               swap(arr[j],arr[j+1]);
               swapped=true;  //有發生交換，代表還沒完全排好
            }
        }
        if(!swapped)break;  //整輪完全沒交換就提前離開
    }
    // TODO:
    // 使用氣泡排序法將 arr 由小到大排序
    //
    // 提示：
    // 1. 每一輪把最大值往右推
    // 2. 可使用 swapped 變數判斷是否提早結束
}

// ==============================
// 4. Shell Sort
// ==============================
void shellSort(vector<int>& arr) {
    int n = arr.size();
    for(int gap=n/2;gap>0;gap/=2){  // 1. 間隔控制
        for(int i=gap;i<n;i++){     // 2. 點名：從 gap 開始往後掃描
            int temp = arr[i];      // 先把當前要插入的人拿起來
            int j;                  // 3. 跳躍比較：j >= gap 確保 j-gap 不會變負數
            for(j=i;j>=gap && arr[j-gap]>temp;j-=gap){
                arr[j] = arr[j-gap];   // 前面的比較大，就往後挪
            }
            arr[j] = temp;
        }
    }
    // TODO:
    // 使用 Shell 排序法將 arr 由小到大排序
    //
    // 提示：
    // 1. gap 先設為 n/2
    // 2. 每次 gap /= 2
    // 3. 對每個 gap 做類似 insertion sort
}

// ==============================
// 5. Merge Sort
// ==============================
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int>leftArr,rightArr;
    for(int i=left;i<=mid;i++){leftArr.push_back(arr[i]);}
    for(int j=mid+1;j<=right;j++){rightArr.push_back(arr[j]);}
    int n=0,m=0,q=left;
    while(n<leftArr.size() && m<rightArr.size()){
       if(leftArr[n]<=rightArr[m]){
          arr[q++]=leftArr[n++];
       }
       else {
          arr[q++]=rightArr[m++];
       }
    }
    while(n<leftArr.size()){arr[q++]=leftArr[n++];}
    while(m<rightArr.size()){arr[q++]=rightArr[m++];}
    
    // TODO:
    // 合併 arr[left..mid] 與 arr[mid+1..right]
    //
    // 提示：
    // 1. 先建立 leftArr 與 rightArr
    // 2. 比較兩邊元素，小的先放回 arr
    // 3. 最後把剩餘元素補回 arr
}

void mergeSort(vector<int>& arr, int left, int right) {
    if(left<right){  //回到上一個呼叫我的地方 ex 現在是merge(A,0,0) return了 ;回到merge(A,0,1)
    int mid=left+(right-left)/2; //和(left+right)/2是一樣的 但用前者可以預防超過int上限(21億),以防溢位產生
    mergeSort(arr,left,mid);
    mergeSort(arr,mid+1,right);
    
    merge(arr,left,mid,right);
    // TODO:
    // 使用遞迴完成 merge sort
    //
    // 提示：
    // 1. 終止條件：left >= right
    // 2. 找中間 mid
    // 3. 遞迴排序左半部
    // 4. 遞迴排序右半部
    // 5. 呼叫 merge()
    }
}

// ==============================
// 6. Quick Sort
// ==============================
int partitionArray(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i=low-1;
    for(int j=low;j<=high-1;j++){
        if(arr[j] < pivot){
            i++; //ex i=low-1, i++ ==> i=low;
            swap(arr[i],arr[j]); 
        }
    }
    swap(arr[i+1],arr[high]);// 此時 i+1 就是 pivot 的正確排序位置
    // TODO:
    // 以 arr[high] 作為 pivot，完成 partition
    //
    // 提示：
    // 1. pivot = arr[high]
    // 2. i = low - 1
    // 3. 掃描 j = low 到 high - 1
    // 4. 若 arr[j] < pivot，則交換到左側
    // 5. 最後將 pivot 放到正確位置
    return i+1;  // 6. 回傳 pivot 的索引
}

void quickSort(vector<int>& arr, int low, int high) {
    if(low<high){
       int part = partitionArray(arr,low,high);
       quickSort(arr,low,part-1); //左半部  //如果low < part-1 還成立,就繼續quickSort
       quickSort(arr,part+1,high); //右半部 //如果 part+1 < high 還成立,就繼續quickSort
           
    }
    // TODO:
    // 使用遞迴完成 quick sort
    //
    // 提示：
    // 1. 若 low < high
    // 2. 呼叫 partitionArray()
    // 3. 遞迴排序左半部與右半部
}

// ==============================
// 7. Radix Sort
// 僅處理非負整數
// ==============================
void countingSortByDigit(vector<int>& arr, int exp) {
    // TODO:
    // 依照指定位數 exp 進行 counting sort
    //
    // 提示：
    // 1. digit = (arr[i] / exp) % 10
    // 2. count[10] 紀錄各數字出現次數
    // 3. 轉成累計次數
    // 4. 由右往左放入 output，保持穩定性
    // 5. 將 output 複製回 arr
}

void radixSort(vector<int>& arr) {
    // TODO:
    // 使用 radix sort 將 arr 由小到大排序
    //
    // 提示：
    // 1. 找出最大值 maxVal
    // 2. 從個位數開始 exp = 1
    // 3. 每次乘以 10，直到 maxVal / exp == 0
    // 4. 每次呼叫 countingSortByDigit(arr, exp)
}

// ==============================
// 8. Heap Sort
// ==============================
void heapify(vector<int>& arr, int n, int i) {
    // TODO:
    // 維護以 i 為根的 max-heap
    //
    // 提示：
    // 1. largest = i
    // 2. left = 2*i + 1, right = 2*i + 2
    // 3. 找出三者中最大者
    // 4. 若最大者不是 i，交換後遞迴 heapify
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    // TODO:
    // 使用 heap sort 將 arr 由小到大排序
    //
    // 提示：
    // 1. 先建立 max heap
    // 2. 再把堆頂元素和最後元素交換
    // 3. 縮小 heap 範圍後重新 heapify
}

// ==============================
// 執行單一排序並輸出
// ==============================
void runSingleTest(const string& sortName, void (*sortFunc)(vector<int>&), const vector<int>& data) {
    vector<int> arr = data;
    cout << sortName << "\n";
    cout << "Before: ";
    printArray(arr);
    sortFunc(arr);
    cout << "After : ";
    printArray(arr);
    cout << "\n";
}

void runMergeSortTest(const vector<int>& data) {
    vector<int> arr = data;
    cout << "Merge Sort\n";
    cout << "Before: ";
    printArray(arr);
    mergeSort(arr, 0, arr.size() - 1);
    cout << "After : ";
    printArray(arr);
    cout << "\n";
}

void runQuickSortTest(const vector<int>& data) {
    vector<int> arr = data;
    cout << "Quick Sort\n";
    cout << "Before: ";
    printArray(arr);
    quickSort(arr, 0, arr.size() - 1);
    cout << "After : ";
    printArray(arr);
    cout << "\n";
}

// ==============================
// 主程式
// ==============================
int main() {
    vector<int> bestCase1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> bestCase2 = {1, 2, 3, 4, 6, 5, 7, 8, 9, 10};
    vector<int> worstCase1 = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> worstCase2 = {100, 90, 80, 70, 60, 50, 40, 30, 20, 10};
    vector<int> radixCase  = {329, 457, 657, 839, 436, 720, 355};
    vector<int> mixedCase  = {42, 17, 93, 8, 23, 55, 4, 16, 77, 61};

    printTitle("Test Data 1: Best Case - Sorted");
    runSingleTest("Selection Sort", selectionSort, bestCase1);
    runSingleTest("Insertion Sort", insertionSort, bestCase1);
    runSingleTest("Bubble Sort", bubbleSort, bestCase1);
    runSingleTest("Shell Sort", shellSort, bestCase1);
    runMergeSortTest(bestCase1);
    runQuickSortTest(bestCase1);
    runSingleTest("Radix Sort", radixSort, bestCase1);
    runSingleTest("Heap Sort", heapSort, bestCase1);

    printTitle("Test Data 2: Near Best Case - Almost Sorted");
    runSingleTest("Selection Sort", selectionSort, bestCase2);
    runSingleTest("Insertion Sort", insertionSort, bestCase2);
    runSingleTest("Bubble Sort", bubbleSort, bestCase2);
    runSingleTest("Shell Sort", shellSort, bestCase2);
    runMergeSortTest(bestCase2);
    runQuickSortTest(bestCase2);
    runSingleTest("Radix Sort", radixSort, bestCase2);
    runSingleTest("Heap Sort", heapSort, bestCase2);

    printTitle("Test Data 3: Worst Case - Reverse Sorted");
    runSingleTest("Selection Sort", selectionSort, worstCase1);
    runSingleTest("Insertion Sort", insertionSort, worstCase1);
    runSingleTest("Bubble Sort", bubbleSort, worstCase1);
    runSingleTest("Shell Sort", shellSort, worstCase1);
    runMergeSortTest(worstCase1);
    runQuickSortTest(worstCase1);
    runSingleTest("Radix Sort", radixSort, worstCase1);
    runSingleTest("Heap Sort", heapSort, worstCase1);

    printTitle("Test Data 4: Another Reverse Large Values");
    runSingleTest("Selection Sort", selectionSort, worstCase2);
    runSingleTest("Insertion Sort", insertionSort, worstCase2);
    runSingleTest("Bubble Sort", bubbleSort, worstCase2);
    runSingleTest("Shell Sort", shellSort, worstCase2);
    runMergeSortTest(worstCase2);
    runQuickSortTest(worstCase2);
    runSingleTest("Radix Sort", radixSort, worstCase2);
    runSingleTest("Heap Sort", heapSort, worstCase2);

    printTitle("Test Data 5: Radix Test");
    runSingleTest("Selection Sort", selectionSort, radixCase);
    runSingleTest("Insertion Sort", insertionSort, radixCase);
    runSingleTest("Bubble Sort", bubbleSort, radixCase);
    runSingleTest("Shell Sort", shellSort, radixCase);
    runMergeSortTest(radixCase);
    runQuickSortTest(radixCase);
    runSingleTest("Radix Sort", radixSort, radixCase);
    runSingleTest("Heap Sort", heapSort, radixCase);

    printTitle("Test Data 6: Random Mixed");
    runSingleTest("Selection Sort", selectionSort, mixedCase);
    runSingleTest("Insertion Sort", insertionSort, mixedCase);
    runSingleTest("Bubble Sort", bubbleSort, mixedCase);
    runSingleTest("Shell Sort", shellSort, mixedCase);
    runMergeSortTest(mixedCase);
    runQuickSortTest(mixedCase);
    runSingleTest("Radix Sort", radixSort, mixedCase);
    runSingleTest("Heap Sort", heapSort, mixedCase);

    return 0;
}
