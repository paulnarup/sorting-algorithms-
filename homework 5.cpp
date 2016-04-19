//============================================================================
// Name        : homework.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int numbers[10000];
int qcomp,qswap,mcomp,mswap;


bool read_file(){
	ifstream numFile;
	string file;

	cout<<"Enter file to sort: \n";
	cin>>file;
	numFile.open(file.c_str());

	if(numFile.is_open()){
		int i =0;
		while(!numFile.eof()){
			numFile >> numbers[i];
			i++;
		}
	}else{
		cout<<"The file could not be opened, check location\n";
		read_file();
	}
	numFile.close();

	return false;
}

void bubblesort(int A[], int n){
	int i, j, temp, comparisions,swaps;
	comparisions=0;
	swaps =0;
	for (i = 1; i<n;i++){
		for(j=0;j<n-1;j++){
			comparisions++;
			if(A[j]>A[j+1]){//if bigger then swap
				temp = A[j];
				A[j]=A[j+1];
				A[j+1]=temp;
				swaps++;
			}

		}
	}

	cout<<"\nComp "<<comparisions;
	cout<<"\nSwap "<<swaps;
}

void insertionsort(int A[], int n)
{
	int i, j, element;
	int comparisions =0;
	int swaps =0;
	for(i=1; i<n; i++){
		element =A[i];//selects number to insert
		j=i;
		comparisions++;

		while((j>0)&& (A[j-1]>element)){//moves element to proper spot
			comparisions++;
			swaps++;
			A[j] = A[j-1];
			j = j-1;
		}
		A[j]= element;
	}

	cout<<"\nComp "<<comparisions;
	cout<<"\nSwap "<<swaps;
}

void selectionsort(int A[], int n){
	int i, j;
	int minpos,temp;
	int comparisions =0, swaps =0;

	for(i = 0;i<n-1;i++){
		minpos =i;
		for(j=i+1;j<n;j++){//finds smallest
			comparisions++;
			if(A[j]<A[minpos]){
				minpos = j;
			}
		}
		if(minpos!=i){//swaps
			temp = A[i];
			A[i] = A[minpos];
			A[minpos] = temp;
			swaps++;

		}
	}

	cout<<"\nComp "<<comparisions;
	cout<<"\nSwap "<<swaps;
}



int partition(int a[], int left, int right, int pivotIndex)
{
    int pivot = a[pivotIndex];
    do
    {
    	//compare numbers with pivot
        while (a[left] < pivot) left++,qcomp++;
        while (a[right] > pivot) right--,qcomp++;

        if (left < right && a[left] != a[right])//swap
        {
        	qswap++;
        	swap(a[left], a[right]);
        }
        else
        {
            return right;
        }
    }
    while (left < right);
    return right;
}

void quicksort(int a[], int left, int right)
{
    if (left < right)//update pivot and run recursively
    {
        int pivot = (left + right) / 2; // pivot == middle number
        int pivotNew = partition(a, left, right, pivot);
        quicksort(a, left, pivotNew - 1);//updates pivot
        quicksort(a, pivotNew + 1, right);
    }
}

void shell_sort(int A[], int n){
	int temp, gap, i;
	int swaps=0, comparisons=0;
	int swapped;
	gap = n/2;
	do{
		do{
			swapped = 0;
			for(i = 0;i<n-gap;i++){
				comparisons++;
				if(A[i]>A[i+gap]){//compares numbers fixed distance apart
					swaps++;
					temp = A[i];
					A[i] = A[i+gap];
					A[i+gap]= temp;
					swapped = 1;
				}
			}
		}while(swapped==1);//runs while numbers are swapped
	}while((gap=gap/2)>=1);
	cout<<"\nComp "<<comparisons;
	cout<<"\nSwap "<<swaps<<endl;
}

void merge(int A[], int low, int high, int mid){
	int comparisons=0, swaps=0;
	int i, j, k, C[10000];//second array to compare
	i = low;
	j = mid+1;
	k = 0;
	while((i <= mid)&& (j <= high)){
		if(A[i]<A[j]){//compare to midpoint
			C[k]=A[i++];
		}else{//swap
			C[k]=A[j++];
			mswap++;
		}
		mcomp++;
		k++;
	}
	while(i<=mid){
		C[k++] = A[i++];
	}
	while(j<=high){
		C[k++] = A[j++];
	}
	for(i = low, j=0;i<=high;i++,j++){
		A[i]=C[j];//re-enter numbers into A from C
	}
}
void mergesort(int A[], int low, int high){
	int mid;
	if(low<high){
		mid = ((low +high)/2);
		mergesort(A,low,mid);
		mergesort(A,mid+1,high);
		merge(A, low,high,mid);
	}
}
int main() {
	read_file();
	bubblesort(numbers,10000);
	insertionsort(numbers,10000);
	selectionsort(numbers,10);
	quicksort(numbers,0,9999);
	shell_sort(numbers,10000);
	mergesort(numbers,0,9999);
	/*for(int k =0;k<10;k++){
		cout<<numbers[k]<<" ";
	}*/
	cout<<"mcomp"<<mcomp<<"\n";
	cout<<"mswap"<<mswap<<"\n";
	cout<<"qcomp"<<qcomp<<"\n";
	cout<<"qswap"<<qswap<<"\n";
	return 0;
}
