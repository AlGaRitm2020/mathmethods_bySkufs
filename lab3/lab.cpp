#include <iostream>

#define N 4
#define J 1

using namespace std;


//lab3
//функция для подсчета энергии одного спина
int E_spin (int arr[N][N], int x, int y)
{
    int E = 0;
    
    //1 условие центральный элемент
    if(x>0 && x<N-1 && y>0 && y<N-1)
    {
        E = -J * arr[y][x]*
                  (arr[y][x-1] + //сосед слева
                   arr[y][x+1] + //сосед справа
                   arr[y-1][x] + //сосед сверху
                   arr[y+1][x]); //сосед снизу
    }
    //2 условие верхний левый
    else if(x == 0 && y == 0)
    {
        E = -J * arr[y][x]*
                  (arr[y][N-1] + //сосед слева
                   arr[y][x+1] + //сосед справа
                   arr[N-1][x] + //сосед сверху
                   arr[y+1][x]); //сосед снизу
    }
    //3 условие верхняя грань
    else if(x > 0 && x<N-1 && y == 0)
    {
        E = -J * arr[y][x]*
                  (arr[y][x-1] + //сосед слева
                   arr[y][x+1] + //сосед справа
                   arr[N-1][x] + //сосед сверху
                   arr[y+1][x]); //сосед снизу
    }
    //4 условие правый нижний
        else if(x == N-1 && y == N-1)
        {
            E = -J * arr[y][x]*
                      (arr[y][x-1] + //сосед слева
                       arr[y][0] + //сосед справа
                       arr[y-1][x] + //сосед сверху
                       arr[0][x]); //сосед снизу
        }
    
    //5 условие нижняя грань
    //6 условие левая грань
    //7 условие правая грань
    //8 условие нижний левый
    //9 условие верхний правый
    
    return E;
}

//функция для подсчета энергии всей системы
int E_system (int arr[N][N])
{
    int E_sys = 0;
    for(int y=0; y<N; y++)
    {
        for(int x=0; x<N; x++)
        {
            E_sys += E_spin(arr,x,y);
        }
    }
    
    E_sys/=2;
    
    return E_sys;
}


int main()
{
    int arr[N][N];
    fill2D(arr);
    print2D(arr);
    cout << "E_system = " << E_system(arr) << endl;
    int x=0,y=0;
    //вывести энергию случайного элемента
    //его координаты
    
    cout << "E_spin = " << E_spin(arr,x,y) << endl;
    
    
    return 0;
}
