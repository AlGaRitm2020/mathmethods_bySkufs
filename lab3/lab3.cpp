#include <iostream>

#define N 3
#define J 1

using namespace std;

void fill1D(int arr[N*N])
{
    for(int i=0; i<N*N; i++)
    {
        arr[i]=1;
    }
}
void fill2D(int arr[N])
{
    for(int i=0; i<N; i++)
    {
      for (int j = 0; j < N; j++) {
        
      }
        arr[i]=1;
    }
}

void print1D(int arr[N*N])
{
    for(int i=0; i<N*N; i++)
    {
        cout << arr[i] << "\t";
    }
    cout << endl;
}

void print2D(int arr[N][N])
{
    for(int i=0; i<N; i++)
    {
      for (int j = 0; j < N; j++) {
        
        cout << arr[i][j] << "\t";
      }
    cout << endl;
    }
    cout << endl;
}

void from1to2D(int arr[N][N], int compr_arr[N*N]) {

  for (int i = 0; i < N; i++) {
   
    for (int j = 0; j < N; j++) {
      arr[i][j] = compr_arr[i*N + j];
    }
  }


}
int calc_ei(int arr[N*N], int ii) {
  int sum = 0;
  int rn = arr[(ii + 1) % (N*N)] * arr[ii];
  int ln = arr[(ii - 1) % (N*N)] * arr[ii];
  int un = arr[(ii + N) % (N*N)] * arr[ii];
  int dn = arr[(ii - N) % (N*N)] * arr[ii];

  if (ii - 1< 0)
    ln = arr[(ii - 1) + 9] * arr[ii];
  if (ii -N < 0)
    dn = arr[(ii - N) + 9] * arr[ii];

  sum = rn + ln + un + dn;

  if (ii == 0)
//  printf("\n %d %d %d %d \n", rn, ln, un, dn);
  cout << sum * -J;
  return sum * -J;
                                 //


}

void albert1D(int arr[N*N])
{
    for(int conf_num = 1; conf_num < (1<<N*N); conf_num++)
    {
        for(int i=0; i<N*N; i++)
        {
            if(arr[i] == 1) { arr[i] = -1; break;
            }
            else arr[i] = 1;

        }

        // select 4 element 
        int D2[N][N];
//fill2D(D2);
        from1to2D(D2, arr);

          if (conf_num == 2 ) {
          
          int all_energy = 0;
          print2D(D2);
          cout << calc_ei(arr, 0);

          // calculate all all_energy
          for (int j=0; j<N*N; j++)
            all_energy += calc_ei(arr, j);
//            all_energy += calc_ei(arr, j);
          cout << "All energy: " << all_energy;
          }
          //        print2D(D2);
    }
}


//полный перебор 1D
void albert1D_canon(int arr[N])
{
    print1D(arr);
    for(int conf_num = 1; conf_num < (1<<N); conf_num++)
    {
        for(int i=0; i<N; i++)
        {
            if(arr[i] == 1) 
            {
                arr[i] = -1;
                break;
            }
            else arr[i] = 1;
        }
        print1D(arr);
    }
}

int main()
{
    int arr[N*N];
    
    fill1D(arr);
    albert1D(arr);
    
    
    
    return 0;
}
