

#include <iostream>
#define N 3
using namespace std; 



void fill1D(int arr[N]){
  for (int i = 0; i < N; i++) {
    arr[i] = 1;
  } 
}




void print1D(int arr[N]) {
  for (int i = 0; i < N; i++) {
    cout << arr[i] << '\t';
    
  }
  cout << endl;
}

void fullEnum_canon(int arr[N]) {

  for (int conf=1; conf < (1<N); conf++) {

  }
}





int main ()
{
  int arr[N];
  fill1D(arr);
  print1D(arr);
  


  return 0;
}
