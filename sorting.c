#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//Create Array data
  //typedef struct creates SortingThreadParameters
  typedef struct {
    int * subArray;
    unsigned int size;
  } SortingThreadParameters;

  //typedef struct creates MergingThreadParameters
  typedef struct {
    SortingThreadParameters left;
    SortingThreadParameters right;
  } MergingThreadParameters;

//Define functions
  //thread functions
  void sort(SortingThreadParameters *param);
  void merge(MergingThreadParameters *param);
  //helper functions
  void mergeSort(int a[], int m, int b[], int n, int sorted[]);
  void bubbleSort(int arr[], int n);
  void printArray(int arr[], int size);

//data defined here is shared between all threads
  #define SIZE (sizeof(list)/sizeof(*list))
  //array initially filled with unsorted numbers
  int list[] = { 7, 12, 19, 3, 18, 4, 2, -5, 6, 15, 8};
  //same contents as unsorted Array, but unsorted
  int result[SIZE] = {0};

//Begin main funtion
int main () {
  //Create Process Thread data
    //the thread identifier
    pthread_t tid;
    pthread_t tid2;
    pthread_t tid3;

    //set of the thread attributes
    pthread_attr_t attr;
    pthread_attr_t attr2;
    pthread_attr_t attr3;

    // set the default attributes of the thread
    pthread_attr_init(&attr);
    pthread_attr_init(&attr2);
    pthread_attr_init(&attr3);

  //Create Left SortingThreadParameters
    SortingThreadParameters * paramsLeft = malloc( sizeof( SortingThreadParameters) );
    paramsLeft->subArray = list;
    paramsLeft->size =  SIZE/2;

  //Create Right SortingThreadParameters
    SortingThreadParameters * paramsRight = malloc (sizeof (SortingThreadParameters));
    paramsRight->subArray = list + paramsLeft->size;
    //take difference address an add number of elements
    paramsRight->size = SIZE - paramsLeft->size;

    // Now create the first sorting thread passing it paramsLeft as a parameter
    pthread_create(&tid, &attr, sort, paramsLeft);

    //Now create the second sorting thread passing it paramsRight as a parameter
    pthread_create(&tid2, &attr2, sort, paramsRight);

    pthread_join(tid,NULL);

    pthread_join(tid2,NULL);

  //Merge both SortingThreadParameters
    MergingThreadParameters* paramsMerge = malloc(sizeof(MergingThreadParameters));
    paramsMerge->left = *paramsLeft;
    paramsMerge->right = *paramsRight;
    /* Now create the merging thread passing it paramsMerge as a parameter */
    pthread_create(&tid3, &attr3, merge, paramsMerge);
    //wait for the merging thread to complete
    pthread_join(tid3,NULL);

    //Print Result
    printf("Result: ");
    //call helpfer function to print
    printArray(result,SIZE);

    printf("\n");
    return 0;
}

//Thread Call Sort Function
void sort(SortingThreadParameters *param) {
  bubbleSort(param->subArray, param->size);
  pthread_exit(0);
}

//Thread Call MergeSort Function
void merge(MergingThreadParameters *param) {
  //call merge function
  mergeSort(param->left.subArray,param->left.size,param->right.subArray,param->right.size, result);
  pthread_exit(0);
}

//Merge sorting helper function - based on a MergeSort Algorithm found in my Algorithms textbook
void mergeSort(int leftArr[], int leftSize, int rightArr[], int rightSize, int sorted[]) {
  int i;
  int j = 0, k = 0;
  for (i = 0; i < leftSize + rightSize;) {
    if (j < leftSize && k < rightSize) {
      if (leftArr[j] < rightArr[k]) {
        sorted[i] = leftArr[j];
        j++;
      } //end if
      else {
        sorted[i] = rightArr[k];
        k++;
      }//end else
      i++;
    } //end if
    else if (j == leftSize) {
      for (; i < leftSize + rightSize;) {
        sorted[i] = rightArr[k];
        k++;
        i++;
      }//end for
    }//end else if
    else {
      for (; i < leftSize + rightSize;) {
        sorted[i] = leftArr[j];
        j++;
        i++;
      }//end for
    }//end else
  }//end main for
}//end merge function

// Basic Bubble Sort helper function - based on the popular Bubble Sort Algoirthm
void bubbleSort(int unsorted[], int n)
{
  for (int i = 0; i < n-1; i++) {
    for (int j = 0; j < n-i-1; j++) {
      if (unsorted[j] > unsorted[j+1]) {
        int temp = unsorted[j];
        unsorted[j] = unsorted[j+1];
        unsorted[j+1] = temp;
      }//end if
    }//end for
  }//end for
}//end bubbleSort

//helper function to print
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
}
