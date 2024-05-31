#include <queue> //работа с очередью
#include <ctime>//для работы time
#include <iostream>
#include <fstream>
#include <cmath>

#define N 10
#define J 1

using namespace std;

void conf_file( int arr[N][N], string filename){

    ofstream fout(filename);//создание/перезапись файла с именем config.txt
    for(int y=0; y<N; y++)
    {
        for(int x=0; x<N; x++)
        {
            //запись в файл значений
            //fout << x << "\t" << y << "\t" << 0 << "\t" << arr[(N - y-1)*N + x] << endl;
            fout << x << "\t" << y << "\t" << 0 << "\t" << arr[y][x] << endl;
        }
    }
    fout.close();
}

void seed_cluster_save(int x, int y, int direction) {
    ofstream fout("seed_cluster.txt");
    fout << x << "\t" << y << "\t" << 0 << "\t" << direction << endl;
}

void fill2D(int arr[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            arr[i][j] = ((rand() % 2) * -2) + 1; 

}

void print2D(int arr[N][N]) {
    cout << "========PRINTING ARRAY======" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << arr[i][j] << '\t';
        cout << endl;
    }
    cout << "============================" << endl;

}



void cluster(int arr[N][N])
{
    //маркируем все элементы '0'
    int cluster_mark[N][N];
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            cluster_mark[i][j] = 0;
        }
    }
    
    queue <int> check;//очередь для проверки соседей
    
    //координаты
    int x,y;
    
    srand(time(NULL));
    
    //координаты зерна роста кластера
    x = rand()%N;
    y = rand()%N;
    
    int cluster_seed = arr[y][x];
    
    /** 1. сохранить конфигурацию системы в файл */
    conf_file(arr, "config.txt");
    /** 2. сохранить зерно роста кластера в файл */
    seed_cluster_save(x, y, cluster_seed);
    
    //добавляем в очередь координаты кластера
    check.push(x);
    check.push(y);
    
    while(check.empty() != 1)
    {
        x = check.front();//обращаемся к первому элементу в очереди
        check.pop();//удаляем первый элемент из очереди
        y = check.front();
        check.pop();
        
        //маркируем элемент
        cluster_mark[y][x] =  cluster_seed;
        
        //проверяем соседей справа
        if(x == N-1)
        {
            if(arr[y][x] == arr[y][0] && cluster_mark[y][0] == 0)
            {
                check.push(0);
                check.push(y);
            }
        }
        else
        if(arr[y][x] == arr[y][x+1] && cluster_mark[y][x+1] == 0)
        {
            check.push(x+1);
            check.push(y);
        }
        
        //проверяем соседей слева
        if(x == 0)
        {
            if(arr[y][x] == arr[y][N-1] && cluster_mark[y][N-1] == 0)
            {
                check.push(N-1);
                check.push(y);
            }
        }
        else
        if(arr[y][x] == arr[y][x-1] && cluster_mark[y][x-1] == 0)
        {
            check.push(x-1);
            check.push(y);
        }
        //проверяем соседей сверху
        if(y == 0)
        {
            if(arr[y][x] == arr[N-1][x] && cluster_mark[N-1][x] == 0)
            {
                check.push(x);
                check.push(N-1);
            }
        }
        else
        if(arr[y][x] == arr[y-1][x] && cluster_mark[y-1][x] == 0)
        {
            check.push(x);
            check.push(y-1);
        }
        //проверяем соседей снизу
        if(y == N-1)
        {
            if(arr[y][x] == arr[0][x] && cluster_mark[0][x] == 0)
            {
                check.push(x);
                check.push(0);
            }
        }
        else
        if(arr[y][x] == arr[y+1][x] && cluster_mark[y+1][x] == 0)
        {
            check.push(x);
            check.push(y+1);
        }
        
    }//while
    
    //выводим на экран маркировку кластера
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            cout << cluster_mark[i][j] << "\t";
        }
        cout << endl;
    }

    conf_file(cluster_mark, "cluster.txt");
    
    /** 3. сохранить кластер в файл (координаты спинов, которые попали в кластер) */
}



int main()
{
    int arr2D[N][N];
    srand(time(NULL));
    fill2D(arr2D);
    print2D(arr2D);
    
    cluster(arr2D);
    return 0;
}