#include <iostream>
#include <string>

using namespace std;

int  InsertSort(int *array, int size);//
int  MergeSort(int *array, int size);//
int  BubbleSort(int *array, int size);//
int  QuickSort(int *array, int size);//
int  HeepSort(int *array, int size);//
int  CountingSort(int *array, int size);//
int  RadixSort(int *array, int size);//
int  BucketSort(int *array, int size);//
int  ShellSort(int *array, int size);//
void showArray(int *array, int size);//

int main()
{
	//int array[10] = {23,54,7,76,321,6,345,12,7,54};
	//int array[10] = {2,5,7,6,2,6,3,1,7,5};//counting sort data
	int array[10] = {23,54,73,64,25,66,34,13,72,51};//Radix sort data and bucket sort data
	int size = 10;
	cout << "Sorting the data from low to high: " << endl;
	cout << "Before sorting: " << endl;
	showArray(array,size);

	/*
	cout << "Insert Sorting: " << endl;
	InsertSort(array,size);
	showArray(array,size);

	cout << "Bubble Sorting: " << endl;
	BubbleSort(array,size);
	showArray(array,size);

	cout << "Quick Sorting: " << endl;
	QuickSort(array,size);
	showArray(array,size);
	
	cout << "Merge Sorting: " << endl;
	MergeSort(array,size);
	showArray(array,size);

	cout << "Heep Sorting: " << endl;
	HeepSort(array,size);
	showArray(array,size);

	cout << "Counting Sorting: " << endl;
	CountingSort(array,size);
	showArray(array,size);

	cout << "Radix Sorting: " << endl;
	RadixSort(array,size);
	showArray(array,size);

	cout << "Shell Sorting: " << endl;
	ShellSort(array,size);
	showArray(array,size);
*/
	cout << "Bucket Sorting: " << endl;
	BucketSort(array,size);
	showArray(array,size);

	return 1;
}

void showArray(int *array, int size)
{
	for(int i=0; i<size; i++)
	{
		cout << array[i] << "  ";
	}
	cout << endl;
}

int  InsertSort(int *array, int size)
{
	if(size < 2)
		return 1;
	int tempValue;
	for(int i=1; i<size; i++)
	{
		tempValue = array[i];
		int j=i-1;
		while(j>=0 && array[j] > tempValue)//should compare with the tempValue,not array[i]
		{
			array[j+1] = array[j];
			j--;
		}
		array[j+1] = tempValue;
	}
	return 1;
}

#define MAXVALUE 98999
void Merge(int *array, int start, int middle, int end)
{
	int leftLength = middle - start + 1;
	int rightLength = end -middle; 
	int sumLength = end - start + 1;
	int *leftArray = new int[leftLength+1];
	int *rightArray = new int[rightLength+1];
	int i=0;
	int j=0;
	for(; i<leftLength; i++)
		leftArray[i] = array[start+i];
	leftArray[leftLength] = MAXVALUE;
	for(; j<rightLength; j++)
		rightArray[j] = array[middle+j+1];
	rightArray[rightLength] = MAXVALUE;

	i=0;j=0;
	for(int k=0; k<sumLength; k++)
	{
		if(leftArray[i] <= rightArray[j])
		{
			array[start+k] = leftArray[i];
			i++;
		}
		else
		{
			array[start+k] = rightArray[j];
			j++;
		}
	}
}
void MergeSort1(int *array, int start, int end)
{
	if(start < end)
	{
		int middle = (start+end)/2;
		MergeSort1(array,start,middle);
		MergeSort1(array,middle+1,end);
		Merge(array,start,middle,end);
	}
}
int  MergeSort(int *array, int size)
{

	int middle = (size-1)/2;
	MergeSort1(array,0,size-1);
	return 1;
}

int  BubbleSort(int *array, int size)
{
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size-i;j++)
		{
			if(array[j+1] < array[j])
			{
				int temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}
	return 1;
}


int Partition(int* array, int start, int end)
{
	int tempValue = array[start];
	int j = start;
	for(int i=start+1; i<=end; i++)
	{
		if(array[i] <= tempValue)
		{
			j++;
			int t = array[i];
			array[i] = array[j];
			array[j] = t;
		}
	}
	int t = array[j];
	array[j] = array[start];
	array[start] = t;
	return j;
}
void QuickSort1(int *array,int start,int end)
{
	if(start < end)
	{
		int middleIndex = Partition(array,start,end);
		QuickSort1(array,0,middleIndex-1);
		QuickSort1(array,middleIndex+1,end);
	}
}
int  QuickSort(int *array, int size)
{
	QuickSort1(array,0,size-1);
	return 1;
}

void Heep(int *array, int start, int size)
{
	int leaf = 2*start +1;
	if(leaf < size-1 && array[leaf] < array[leaf+1])
		leaf++;
	if(leaf <= size-1 && array[start] < array[leaf])
	{
		int temp =array[start];
		array[start] = array[leaf];
		array[leaf] = temp;
		Heep(array,leaf,size);
	}
}
void BuildHeep(int *array, int size)
{
	for(int i=size/2; i>=0; i--)
		Heep(array,i,size);
}
void HeepSort1(int *array,int size)
{
	BuildHeep(array,size);
	for(int i=0;i<size;i++)
	{
		int temp = array[0];
		array[0] = array[size-1-i];
		array[size-1-i] = temp;
		Heep(array,0,size-i-1);
	}
}
int  HeepSort(int *array, int size)
{
	
	HeepSort1(array,size);
	return 1;
}

int  CountingSort(int *array, int size)
{
	int max=0;
	int i=0;
	int *mArray = new int[size];
	//find the max value of the data
	for(i=0;i<size;i++)
	{
		mArray[i] = array[i];
		if(array[i] > max)
			max = array[i];
	}
	int *countArray = new int[max+1]; //alloc the memery address to the countArray
	for(i=0;i<max+1;i++)
		countArray[i] = -1;
	for(i=0;i<size;i++)
		countArray[array[i]]=0;
	for(i=0;i<size;i++)
		countArray[array[i]] = countArray[array[i]]+1;
	int sign = 0;
	int first = 0;
	for(i=0;i<max+1;i++)
	{
		int temp = countArray[i];
		if(temp >= 0)
		{
			first++;
			if(first != 1)
				countArray[i] += countArray[sign];
			sign = i;		
		}
	}
	for(i=0;i<size;i++)
	{
		array[countArray[mArray[i]]-1] = mArray[i];
		countArray[mArray[i]]--;
	}
	return 1;
}

int  RadixSort1(int *array, int size, int weiShu)
{
	int *mArray = new int[size];//record the 0-9 every loop
	int *tempArray = new int[size];//the copy of the array
	int *yuShuArray = new int[size];//record the yu shu every loop
	int *yuShuArray2 = new int[size];//the copy of the yuShu
	int i=0;
	for(i=0; i<size; i++)
	{
		yuShuArray[i] = array[i];
	}
	for(int k=0; k<weiShu; k++)
	{
		for(int j=0; j<size; j++)
		{
			tempArray[j] = array[j];
			mArray[j] = yuShuArray[j]%10;
			yuShuArray[j] = yuShuArray[j]/10;
			yuShuArray2[j] = yuShuArray[j];
		}
		int max=0;
		for(i=0;i<size;i++)
		{
			if(array[i] > max)
				max = array[i];
		}
		int *countArray = new int[max+1];
		for(i=0;i<max+1;i++)
			countArray[i] = 0;
		for(i=0;i<size;i++)
			countArray[mArray[i]] = countArray[mArray[i]]+1;
		for(i=1;i<max+1;i++)
		{
			countArray[i] += countArray[i-1];
		}
		for(i=size-1;i>=0;i--)
		{
			array[countArray[mArray[i]]-1] = tempArray[i];
			yuShuArray[countArray[mArray[i]]-1] = yuShuArray2[i];
			countArray[mArray[i]]--;
		}
	}	
	return 1;
}
int RadixSort(int* array,int size)
{
	RadixSort1(array,size,2);
	return 1;
}

int  BucketSort(int *array, int size)
{
	struct bucketItem
	{
		int value;
		bucketItem *next;
	};
	int i=0;
	bucketItem* bucket = new bucketItem[10];
	for(i=0;i<10;i++)
	{
		bucket[i].value = -1;
		bucket[i].next = NULL;
	}	
	bucketItem* largerPoint = new bucketItem();
	bucketItem* lowerPoint = new bucketItem();
	for(i=0; i<size;i++)
	{
		int tempValue = array[i]/10;
		largerPoint = bucket[tempValue].next;
		lowerPoint = largerPoint;
		bucketItem* item = new bucketItem();
		item->value = array[i];
		item->next = NULL;
		if(largerPoint == NULL)
		{
			bucket[tempValue].next = item;
			continue;
		}else if(largerPoint->value > array[i])
		{
			item->next = largerPoint;
			bucket[tempValue].next = item;
			continue;
		}
	    while(largerPoint != NULL && largerPoint->value < array[i])
		{
			lowerPoint = largerPoint;
			largerPoint = largerPoint->next;
		}
		item->next = lowerPoint->next;
		lowerPoint->next = item;
	}
	int j=0;
	for(i=0;i<10;i++)
	{
		largerPoint = bucket[i].next;
		while(largerPoint != NULL)
		{
			array[j] = largerPoint->value;
			largerPoint = largerPoint->next;
			j++;
		}
	}
	return 1;
}

void ShellSort1(int *array, int size, int step)
{
	for(int i=0;i<step;i++)
	{
		for(int j=step;j<size;j+=step)
		{
			int k=j;
			int temp = array[k];
			while(k>=step && temp<array[k-step])
			{
				array[k] = array[k-step];
				k = k-step;
			}
			array[k] = temp;
		}
	}
}
int  ShellSort(int *array, int size)
{
	int steps[3] = {5,3,1};
	for(int i=0;i<3;i++)
		ShellSort1(array,size,steps[i]);
	return 1;
}
