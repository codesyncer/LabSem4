#include<stdlib.h>
#include<stdio.h>
#define p_n sizeof(p_sizes)/sizeof(int)
void* mem;
int multiplier=1024;
int mem_size=100;
int p_sizes[] = {1,10,40,30,10,5,2,2};
int p_virtual_to_real_i[p_n];
int p_offset[p_n]={0};
int p_occupied[p_n]={0};
void* first_fit(int size){
	int ri;
	for(int i=0; i<p_n; ++i){
		ri = p_virtual_to_real_i[i];
		if(p_occupied[ri] != 0 && p_sizes[ri] >= size){
			p_occupied[ri]=size;
			return mem+p_offset[ri];
		}
	}
	return NULL;
}
int ge_x(int *arr, int n, int x){
	int low=0, mid, end=n-1;
	do{
		mid= (low+end)/2;
		if(arr[mid] < x)
			low= mid+1;
		else if(arr[mid] >= x)
			end= mid;
	}while(low < end);	
	mid= (low+end)/2;	
	return arr[mid]<x ? -1 : mid;
}
void* best_fit(int size){
	int start_scan = ge_x(p_sizes, p_n, size);
	if (start_scan == -1)
		return NULL;
	for(int i=start_scan; i<p_n; ++i)
		if(p_occupied[i] != 0 && p_sizes[i] >= size){
			p_occupied[i]=size;
			return mem+p_offset[i];
		}
	return NULL;
}
void* alloc(int size, void* (*fitter)(int)){
	fitter(size);
}
void de_alloc(){

}
void swap(int *a, int *b){
	*a += *b;
	*b = *a - *b;
	*a = *a - *b;
}
void prepare_tables(){
	for(int i=0; i<p_n; ++i)
		p_virtual_to_real_i[i]=i;
	for(int i=1; i<p_n; ++i)
		p_offset[i]=p_offset[i-1]+p_sizes[i];
	for(int i=0;i<=p_n-2;++i)
		for(int j=0;j<=p_n-i-2; ++j)
			if(p_sizes[j] > p_sizes[j+1]){
				swap(p_sizes+j, p_sizes+j+1);
				swap(p_virtual_to_real_i+j, p_virtual_to_real_i+j+1);
				swap(p_offset+j, p_offset+j+1);
			}
}
void arrPrint(int *arr, int n){
	for(int i=0; i<n; ++i)
		printf("%5d", arr[i]);
	printf("\n");
}
void pPrint(){
	int ri;
	for(int i=0; i<p_n; ++i){
		ri = p_virtual_to_real_i[i];
		printf("| s:%d o:%d ", p_sizes[ri], p_occupied[ri]);
	}
	printf("|\n");
}
int main(){
	mem = malloc(mem_size*multiplier);
	if(mem == NULL)
		return 1;
	prepare_tables();
	pPrint();
	arrPrint(p_virtual_to_real_i, p_n);
	arrPrint(p_sizes, p_n);
	return 0;
}