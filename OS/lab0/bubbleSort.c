#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void swap(int* one, int* two){
	*one+= *two;
	*two= *one - *two;
	*one= *one - *two;
}
int* arrCopy(int* arr, int n){
	int *copy= (int*)malloc(n*sizeof(int));
	return (int*)memcpy(copy, arr, n*sizeof(int));
}
void arrPrint(int *arr, int n){
	for(int i=0; i<n; ++i)
		printf("%d ", arr[i]);
	printf("\n");
}
void bubbleSort(int *arr, int n){
	for(int i=0; i<=n-2; ++i)
		for(int j=0; j<=n-2-i; ++j)
			if( arr[j] > arr[j+1] )
				swap(arr+j, arr+j+1);
}
void insertionSort(int *arr, int n){
	for(int i=1,j,curr; i<=n-1; ++i){
		curr= arr[i];
		j=i;
		while(j > 0 && arr[j-1] > curr)
			arr[j]= arr[j-- -1];
		arr[j]= curr;
	}
}
void selectionSort(int *arr, int n){
	for(int i=0, min_i; i<=n-2; ++i){
		min_i= i;
		for(int j=i+1; j<=n-1; ++j)
			min_i= arr[min_i]>arr[j]? j: min_i;
		if (min_i!=i)
			swap(arr+min_i, arr+i);
	}	
}

int main(){
	int arr[] = {122,22,4,2,4,5,3,6,2,5,43,5,2,4,3,5,5,3,5,6,34};
	int n= sizeof(arr)/sizeof(int), *copy;
	arrPrint(arr, n);
	char *titles[]= {"Bubble Sort", "Insertion Sort", "Selection Sort"};
	void (*sorter[])(int*, int)= {bubbleSort, insertionSort, selectionSort};
	int nf= sizeof(sorter)/sizeof(sorter[0]);
	for (int i=0; i<nf; ++i){
		copy= arrCopy(arr, n);
		printf("%s\n", titles[i]);
		sorter[i](copy, n);
		arrPrint(copy, n);
		free(copy);	
	}
	return 0;
}
