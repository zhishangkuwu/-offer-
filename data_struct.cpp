#include<iostream>
using namespace std;

class diy_sort{
///////////////直接插入排序////////////
public:
    void direct_sort(int a[]){
        int len = sizeof(a)/sizeof(int);
        int tem;
        for(int i=1;i<len;i++){
            tem = i;
            for(int j=i-1;j>=0;j--){
                if(a[tem]<a[j]){
                    swap(a[tem],a[j]);
                    tem = j;
                }
                else
                    break;
            }
        }
    }
///////////////希尔排序///////////////////
public:
    void shell_sort(int a[]){
        int len = sizeof(a)/sizeof(int);
        int gap = len/2;
        int tem;
        while(gap>0){
            for(int i=gap;i<len;i++){
                tem = i;
                for(int j=i-gap;j>=0;j-=gap){
                    if(a[tem]>a[j]){
                        swap(a[tem],a[j]);
                        tem = j;
                    }
                }
            }
            gap /= 2;
        }
    }
//////////////////冒泡排序///////////////
public:
    void bubble_sort(int a[]){
        int len = sizeof(a)/sizeof(int);
        for(int i=0;i<len;i++){
            for(int j=1;j<len;j++){
                if(a[j-1]>a[j])
                    swap(a[j-1],a[j]);
            }
        }
    }

///////////////////////快速排序//////////////////
public:
    //基本算法
    int one_change(int a[],int left,int right){
        int base = a[left];
        while(left<right){
            while(left<right&&a[right]>=a[base]){
                right--;
            }
            a[left] = a[right];
            while(left<right&&a[left]<a[base]){
                left++;
            }
            a[right] = a[left];
        }
        return left;
    }
public:
    void quick_sort(int a[],int left,int right){
        int mid = one_change(a,left,right);
        quick_sort(a,left,mid);
        quick_sort(a,mid+1,right);
    }

///////////////////简单选择排序//////////////
public:
    void easy_choice(int a[]){
        int len = sizeof(a)/sizeof(int);
        int min;
        for(int i=0;i<len;i++){
            min = a[i];
            for(int j=i+1;j<len;j++){
                if(a[j]<min)
                    swap(a[i],a[j]);
            }
        }
    }

///////////////堆排序////////////////
public:
    ///////堆的初始操作///////
    void judge(int a[],int key,int len){
        int child = 2*key+1;
        while(child<len){
            if((child+1)<len&&a[child+1]>a[child])
                child = child + 1;
            if(a[key]>=a[child])
                break;
            swap(a[child],a[key]);
            key = child;
            child = 2*key+1;
        }
    }
    void create_dui(int a[],int len){
        for(int i=len/2;i>=0;i--){
            judge(a,i,len);
        }
    }
    void dui_sort(int a[],int len){
        create_dui(a,len);
        for(int i=len-1;i>=0;i--){
            swap(a[0],a[i]);
            judge(a,0,i);
        }
    }
};

int main(){
    
    return 0;
}