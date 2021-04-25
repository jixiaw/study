#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <random>
#include <vector>
#include <iostream>
#include <algorithm>

#define print_vector(v)             \
    do {                            \
        for (auto & e : v) {        \
            std::cout << e << " ";  \
        }                           \
        std::cout << std::endl;     \
    } while (0)


using namespace std;

time_t GetCurrentTime() {
    struct timeval tm;
    gettimeofday(&tm, NULL);
    time_t t = tm.tv_sec * 1000 + tm.tv_usec / 1000;
    return t;
}

vector<int> GenerateVec(int len=100000) {
    vector<int> res(len);
    int maxVal = len * 10;
    for (int i = 0; i < len; ++i) {
        res[i] = rand() % (maxVal);
    }
    return res;
}

inline void Swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void BubbleSort(vector<int>& v) {
    for (int i = 0; i < v.size()-1; ++i) {
        bool flag = false;
        for (int j = 1; j < v.size()-i; ++j) {
            if (v[j-1] > v[j]) {
                Swap(v[j-1], v[j]);
                flag = true;
            }
        }
        // print_vector(v);
        if (!flag) break;
    }
}

void SelectSort(vector<int>& v) {
    for (int i = 0; i < v.size()-1; ++i) {
        int minId = i;
        for (int j = i+1; j < v.size(); ++j) {
            if (v[minId] > v[j]) minId = j;
        }
        Swap(v[minId], v[i]);
        // print_vector(v);
    }
}

void InsertSort(vector<int>& v) {
    for (int i = 1; i < v.size(); ++i) {
        int temp = v[i];
        int j = i-1;
        while(j >= 0 && v[j] > temp) {
            v[j+1] = v[j];
            --j;
        }
        v[j+1] = temp;
        // print_vector(v);
    }
}

int Partation(vector<int>& v, int left, int right) {
    int temp = v[left];
    while (left < right) {
        while (left < right && v[right] >= temp) --right;
        v[left] = v[right];
        while (left < right && v[left] <= temp) ++left;
        v[right] = v[left];
    }
    v[left] = temp;
    return left;
}

void QuickSort(vector<int>& v, int left, int right){
    if (left < right) {
        int pos = Partation(v, left, right);
        QuickSort(v, left, pos-1);
        QuickSort(v, pos+1, right);
        // print_vector(v);
    }
}

void AdjustHeap(vector<int>& v, int left, int right) {
    int temp = v[left];
    int i = left, j = left * 2 + 1;
    while (j <= right) {
        if (j+1 < right && v[j+1] > v[j]) j++;
        if (v[i] < v[j]) {
            Swap(v[i], v[j]);
            i = j;
            j = j * 2 + 1;
        } else {
            break;
        }
    }
}

void CreateHeap(vector<int>& v) {
    for (int i = v.size() / 2; i >= 0; --i) {
        AdjustHeap(v, i, v.size()-1);
    }
}

void HeapSort(vector<int>& v) {
    CreateHeap(v);
    for (int i = v.size()-1; i > 0; --i) {
        Swap(v[i], v[0]);
        AdjustHeap(v, 0, i-1);
        // print_vector(v);
    }
}

void MergeSort(vector<int>& v, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = (left + right) / 2;
    MergeSort(v, left, mid);
    MergeSort(v, mid+1, right);
    vector<int> temp;
    temp.reserve(right - left + 1);
    int i = left, j = mid+1;
    while(i <= mid && j <= right) {
        if (v[i] > v[j]) temp.push_back(v[j++]);
        else temp.push_back(v[i++]);
    }
    while(i <= mid) temp.push_back(v[i++]);
    while(j <= right) temp.push_back(v[j++]);
    for (int i = left; i <= right; ++i) {
        v[i] = temp[i-left];
    }
    // print_vector(v);
}

int main() {
    vector<int> v{1, 3, 5, 7, 2, 3, 5, 0, 12, 4};
    BubbleSort(v);
    // MergeSort(v, 0, v.size()-1);
    v = {1, 3, 5, 3, 9, 5, 13, 12, 11};
    // MergeSort(v, 0, v.size()-1);
    #if 1
    v = GenerateVec();
    vector<int> v1;
    long t1, t2;

    // print_vector(v1);
    v1 = v;
    t1 = GetCurrentTime();
    InsertSort(v1);
    t2 = GetCurrentTime();
    std::cout<<"Insert sort: "<<t2 - t1<<endl;

    v1 = v;
    t1 = GetCurrentTime();
    BubbleSort(v1);
    t2 = GetCurrentTime();
    std::cout<<"Buble sort: "<<t2 - t1<<endl;

    v1 = v;
    t1 = GetCurrentTime();
    SelectSort(v1);
    t2 = GetCurrentTime();
    std::cout<<"Select sort: "<<t2 - t1<<endl;

    v1 = v;
    t1 = GetCurrentTime();
    HeapSort(v1);
    t2 = GetCurrentTime();
    std::cout<<"Heap sort: "<<t2 - t1<<endl;

    v1 = v;
    t1 = GetCurrentTime();
    MergeSort(v1, 0, v1.size()-1);
    t2 = GetCurrentTime();
    std::cout<<"Merge sort: " << t2 - t1<<endl;

    v1 = v;
    t1 = GetCurrentTime();
    QuickSort(v1, 0, v1.size()-1);
    t2 = GetCurrentTime();
    std::cout<<"Quick sort: " << t2 - t1<<endl;

    v1 = v;
    t1 = GetCurrentTime();
    std::sort(v1.begin(), v1.end());
    t2 = GetCurrentTime();
    std::cout<<"std::sort: "<<t2 - t1<<endl;

    #endif
    return 0;
}