//Write a Program to implement Binary search

#include<stdio.h>

int binary_search(int arr[], int low, int high, int x)
{
 while(high >= low)
 {
  int mid = (low+high)/2;
  if(x == arr[mid])
  {
    return mid;
  }
  else if(x < arr[mid])
  {
    return binary_search(arr, 0, mid-1, x);
  }
  else{
    return binary_search(arr, mid+1, high, x);
  }
 }
 return -1;
}

int main()
{
 int arr[] = {1,5,7,1,3,9,6};
 int n = sizeof(arr)/sizeof(arr[0]), x;
 printf("Enter the element you want to search: \n");
 scanf("%d", x);

 int index = binary_search(arr, 0, n-1, x);

 if(index == -1)
 {
  printf("The elemtent you are looking for is not present in the array!\n");
 }
 else{
  printf("The element is present in the array at position %d", index);
 }

 return 0;

}


//The above implementation is done by using arrays, but the problem is, if the same element is persent more than one positions in the array then the program will only return that value of position which is closest to the mid element. To overcome this, we use linked list in place of arrays so that each element can be holded as a separate node. 
//NOTE: I am not implying that this problem cannot be overcome by using arrays itself, it is always possible to check and count the number of element present in the arrays which match with the value of element passes by the user to search in the list. But doing this will significantly increaase the time and space complexity of the program, That is why we prefer linked list!

