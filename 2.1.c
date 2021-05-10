#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 50000

void tampil(int data[]);
void menu(int data[]);
void alokasi(int data2[]);

void MergeSortRekursif(int data[], int l, int r);
void Merge(int data[], int left, int median, int right); 

int Partition(int data[], int p, int r);
void QuickSort(int data[], int p, int r);

int ascDesc = 0;

int n;
int pilihan;

time_t t1, t2;
long int waktukomputasi;

int main(){
	int data[MAX], data2[MAX];
	
	jumlahN();
	
	srand(time(NULL));
	alokasi(data2);
	
	do {
		copyData(data2, data);
		menu(data);
	} while(pilihan != 7);
	
}

int jumlahN(){
	printf("%-25s", "Jumlah data "); printf(": ");
	scanf("%d", &n);
	fflush(stdin);
}

void menu(int data[]){
	printf("========================\n");
	printf(" MENU METODE SORTING\n");
	printf("========================\n");
	printf("1. Insertion Sort\n");
	printf("2. Selection Sort\n");
	printf("3. Bubble Sort\n");
	printf("4. Shell Sort\n");
	printf("5. Merge Sort\n");
	printf("6. Quick Sort\n");
	printf("7. Keluar\n");
	printf("%-25s", "Pilih Menu"); printf(": ");
	scanf("%d", &pilihan);
	fflush(stdin);
	
	if(pilihan == 7)
		exit(0);
		
	modeUrut();
		
	switch(pilihan){
		case 1:
			time(&t1);
			insertion(data);
			time(&t2);
			waktukomputasi= difftime(t2,t1);
			break;
		case 2:
			time(&t1);
			selection(data);
			time(&t2);
			waktukomputasi= difftime(t2,t1);
			break;
		case 3:
			time(&t1);
			bubble(data);
			time(&t2);
			waktukomputasi= difftime(t2,t1);
			break;
		case 4:
			time(&t1);
			shell(data);
			time(&t2);
			waktukomputasi= difftime(t2,t1);
			break;
		case 5:
			time(&t1);
			MergeSortRekursif(data, 0, n-1);
			time(&t2);
			waktukomputasi= difftime(t2,t1);
			break;
		case 6:
			time(&t1);
			QuickSort(data, 0, n-1);
			time(&t2);
			waktukomputasi= difftime(t2,t1);
			break;
	}
	
	printf("\n");
	printf("%-25s", "Waktu Komputasi"); printf(": %d\n\n", waktukomputasi);
}

int modeUrut(){
	printf("========================\n");
	printf(" MENU MODE SORTING\n");
	printf("========================\n");
	printf("1. Ascending\n");
	printf("2. Descending\n");
	printf("%-25s", "Pilih Menu"); printf(": ");
	scanf("%d", &ascDesc);
	fflush(stdin);
}

void alokasi(int data2[]){
	int i;
	
	for(i=0; i<n; i++){
		data2[i] = rand()/1000;
	}
}

int copyData(int data2[], int data[]){
	int i;
	
	for(i=0; i<n; i++)
		data[i] = data2[i];
}

int insertion(int data[]){
	
	int i, j, kondisi = 0;
	int key;
	
	for(i=1; i<n; i++){
		key = data[i];
		j = i - 1;
		while(j >= 0){
			if(ascDesc == 1)
				kondisi = data[j] > key;	
			else if(ascDesc == 2)
				kondisi = data[j] < key;
				
			if(kondisi){
				data[j+1] = data[j];
				j = j - 1;
			} else {
				break;	
			}
		}
		data[j+1] = key;
	}
}

int selection(int data[]){
	
	int i,j, x, kondisi = 0;
    for(i=0; i<n-1; i++){
        x = i;
        for(j = i+1; j<n; j++){
        	if(ascDesc == 1)
				kondisi = data[j] < data[x];	
			else if(ascDesc == 2)
				kondisi = data[j] > data[x];

        	if(kondisi){
        		x = j;
			}
		}
        tukar(&data[i], &data[x]);
    }
	
}

int bubble(int data[]){
	
	int i, j, kondisi = 0, flag = 1, akhir = n-2;

	for(i=0; i<=n-2; i++){
		flag = 0;
		for(j=0; j<=n-2; j++){
			if(ascDesc == 1)
				kondisi = data[j] > data[j+1];
			else if(ascDesc == 2)
				kondisi = data[j] < data[j+1];
			
			if(kondisi){
				tukar(&data[j], &data[j+1]);
				flag = 1;
			}

			if(akhir == j)
				break;
		}
		if(flag == 0)
			break;
		akhir--; 
	}
}

int shell(int data[]){
	
	int i, j, y,  kondisi = 0, flag;
	int key;
	
	for(y=n/2; y>=1; y=y/2){
		flag = 1;
		while(flag == 1){
			flag = 0; 
			for(i=0; i<n-y; i++){
				if(ascDesc == 1)
					kondisi = data[i] > data[i+y];
				else if(ascDesc == 2)
					kondisi = data[i] < data[i+y];
					
				if(kondisi){
					tukar(&data[i], &data[i+y]);
					flag = 1;
				}
			}
		}
	}
}


void MergeSortRekursif(int data[], int l, int r){
	int med;
	
	if(l<r){
		med = (l+r) / 2;
		MergeSortRekursif(data, l, med);
		MergeSortRekursif(data, med+1, r);
		Merge(data, l, med, r);
	}
}

void Merge(int data[], int left, int median, int right){
	int kiri1, kanan1, kiri2, kanan2;
	int i, j, hasil[n], kondisi;
	
	kiri1 = left;
	kanan1 = median;
	kiri2 = median + 1;
	kanan2 = right;
	i = left;
	
	while(kiri1 <= kanan1 && kiri2<=kanan2){
		if(ascDesc == 1)
			kondisi = data[kiri1] <= data[kiri2];
		else 
			kondisi = data[kiri1] >= data[kiri2];
			
		if(kondisi){
			hasil[i] = data[kiri1];
			kiri1++;
		} else {
			hasil[i] = data[kiri2];
			kiri2++;
		}
		i++;
	}
	
	while(kiri1<=kanan1){
		hasil[i] = data[kiri1];
		kiri1++;
		i++;
	}
	
	while(kiri2<=kanan2){
		hasil[i] = data[kiri2];
		i++;
		kiri2++;
	}
	
	j=left;
	
	while(j<=right){
		data[j] = hasil[j];
		j++;
	}
}



void QuickSort(int data[], int p, int r){
	int q;
	if(p < r){
		q = Partition(data, p, r);
		QuickSort(data, p, q);
		QuickSort(data, q+1, r);
	}
}

int Partition(int data[], int p, int r){
	int x, i, j, kondisi;
	
	x = data[p];
	i = p;
	j = r;
	
	while(i<j) {
		do {
			if(ascDesc == 1)
				kondisi = data[j] > x;
			else 
				kondisi = data[j] < x;
				
			if(kondisi)
				j--;
		} while(kondisi);
		
		do {
			if(ascDesc == 1)
				kondisi = data[i] < x;
			else 
				kondisi = data[i] > x;
				
			if(kondisi)
				i++;
		} while(kondisi);
		
		if(i < j){
			tukar(&data[i], &data[j]);
			j--;
		} else {
			return j;
		}
	}
}


int tukar(int *a, int *b){
	int temp;
	
    temp = *a;
    *a = *b;
    *b = temp;
}

void tampil(int data[]){
	int i;
	for(i=0; i<n; i++){
		printf("%d ", data[i]);
	}
	printf("\n");
}
