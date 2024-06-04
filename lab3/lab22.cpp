#include <iostream>

#define N 3

using namespace std;

void fill1D(int arr[N])
{
    for(int i=0; i<N; i++)
    {
        arr[i]=1;
    }
}

void print1D(int arr[N])
{
    for(int i=0; i<N; i++)
    {
        cout << arr[i] << "\t";
    }
    cout << endl;
}

//полный перебор 1D
void albert1D(int arr[N])
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
    int arr[N];
    fill1D(arr);
    albert1D(arr);
    
    
    
    return 0;
}
