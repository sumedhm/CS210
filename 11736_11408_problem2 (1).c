#include<stdio.h>
#include<sys/time.h>
#define maxvalue 100

void quick_sort(int array1[],long long int left, long long int right)
{
      long long int i = left, j = right;
      int temp;
      int pivot = array1[(left + right) / 2];	/*pivot set to mid,can be set to any random number*/

      /* partition */
      while (i <= j) {
            while (array1[i] < pivot)
                  i++;
            while (array1[j] > pivot)
                  j--;
            if (i <= j) {
                  temp = array1[i];
                  array1[i] = array1[j];
                  array1[j] = temp;
                  i++;
                  j--;
        }
    }
    /* recursion */
    if (left < j)
        quick_sort(array1, left, j);
    if (i < right)
            quick_sort(array1, i, right);
}


void merge(int array2[],long long int l,long long int m,long long int h)
{

  long long int n1,n2,i,j,k;
  n1=m-l+1;
  n2=h-m;
  int arr1[n1],arr2[n2]; // Two temporary arrays to  hold the two arrays to be merged

  for(i=0; i<n1; i++)
    arr1[i]=array2[l+i];
  for(j=0; j<n2; j++)
    arr2[j]=array2[m+1+j];

  i=0;
  j=0;k=l;
 while(i<n1 && j<n2)
   {        if(arr1[i]< arr2[j]) { array2[k]=arr1[i++];k++;}
            else {array2[k]=arr2[j++];k++;}
    }
    while(i<n1) { array2[k]=arr1[i]; k++;i++;}
    while(j<n2) { array2[k]=arr2[j];k++;j++;}
return;
}

void merge_sort(int array2[],long long int low,long long int high)
{
  if(low<high) {
    int mid;
    mid=(low+high)/2; // Divide and Conquer
    merge_sort(array2,low,mid);
    merge_sort(array2,mid+1,high);
    // Combine
    merge(array2,low,mid,high);
  }
  return;
}

main(){
        long long int size,i;
	int choice;
	struct timeval startq,endq,startm,endm;
/*Taking input of no.of elements*/
        printf("\nEnter size of the array(No.of elements to be stored): ");
        scanf("%lld",&size);
        int array[size],array1[size],array2[size];
/*Generating random elements less than maxvalue(defined at top) The user may change it*/
	for(i=0;i<size;i++)
	{
		array[i]=random() % maxvalue;
	}
/*Choice of user*/
        printf("\n\n/*What would you like to do:\n\t*1.Show the elements after Quicksort and Mergesort\n\t*2.Show how much time it took for Quicksort and Mergesort\n\t*3.Both of above\n*/\nEnter your choice(1,2,3):\t");
        scanf("%d",&choice);


/* Real main function*/
        printf("\n/*We have generated an array of your desired size*/\n");

	for(i=0;i<size;i++)
		{
		array1[i]=array[i];
		array2[i]=array[i];
		}
	gettimeofday(&startq,NULL);
	quick_sort(array1,0,size-1);
	gettimeofday(&endq,NULL);
	gettimeofday(&startm,NULL);
	merge_sort(array2,0,size-1);
	gettimeofday(&endm,NULL);
	if (choice==1 || choice==3){
	printf("\n Array before sorting:\t");
	for(i=0;i<size;i++)
                printf(" %d",array[i]);
        printf("\n\nSorted elements according Quicksort : ");
        for(i=0;i<size;i++)
                {printf(" %d",array1[i]);}printf("\n");
	printf("\n\nSorted elements according Mergesort : ");
        for(i=0;i<size;i++)
                {printf(" %d",array2[i]);}printf("\n");
	}
	if (choice==2 || choice==3){
	double diffq = (endq.tv_usec- startq.tv_usec) + (endq.tv_sec-startq.tv_sec)*1000000;
	double diffm = (endm.tv_usec- startm.tv_usec) + (endm.tv_sec-startm.tv_sec)*1000000;
	printf("\n\n\t/*The time taken by Quicksort to sort this array was %lf microseconds*/\n\t/*The time taken by Mergesort to sort this array was %lf microseconds*/\n", diffq,diffm);
	}

}
