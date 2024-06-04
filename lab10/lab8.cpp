#include <queue> //работа с очередью
#include <ctime>//для работы time
#include <iostream>
#include <fstream>
#include <cmath>

#define N 8
#define J 1





using namespace std;


//lab10
void clusters(int arr[N][N])
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
    
    int num_cluster = 0;
    
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(cluster_mark[i][j] == 0)
            {
                num_cluster++;
                string filename = to_string(num_cluster) + ".txt";
                ofstream clusterout(filename);
                
                
                x = j;
                y = i;
                
                //добавляем в очередь координаты кластера
                check.push(x);
                check.push(y);
                
                //цикл проверки соседей
                while(check.empty() != 1)
                {
                    x = check.front();//обращаемся к первому элементу в очереди
                    check.pop();//удаляем первый элемент из очереди
                    y = check.front();
                    check.pop();
                    
                    //маркируем элемент
                    cluster_mark[y][x] = num_cluster;
                    clusterout << x << "\t" << y << "\t" << 0 << "\t" << arr[y][x] << endl;
                    
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
                
            }//if
        }//j
    }//i
    
    cout << "Number of clusters = " << num_cluster << endl;
    
    //выводим на экран маркировку кластеров
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            cout << cluster_mark[i][j] << "\t";
        }
        cout << endl;
    }

    ofstream clusterplot("cls2.gp");

  
    //string filename = "high/"+to_string(t)+".txt";
    string filename_png = "clusters.png";

    // ffmpeg -r 24 -start_number 0 -i "%d.png" -y -vcodec mpeg4 test.avi
    //запоняем скрипт для создания рисунка с текущей конфигурацией
    clusterplot << "set terminal png font \"Verdana,14\" size 1000, 1000" << endl;
    clusterplot << "set output \"" << filename_png <<"\" " <<endl;
    clusterplot << "set title \"PLOT "<< N<<"x"<<N<<": "  << num_cluster <<"clusters \" font \"Verdana,20\" " << endl;
    clusterplot << "plot [-1:" << N<< "][-1:" << N<< "] " ;

    for (int i = 1; i < num_cluster; i++) {
        clusterplot << "'" << i << ".txt'  using ($1-($3/4)):($2-($4/4)):($3/2):($4/2) with vectors lw 3 notitle, " ;
    }
    clusterplot << "'" << num_cluster<< ".txt'  using ($1-($3/4)):($2-($4/4)):($3/2):($4/2) with vectors lw 3 notitle" ;


    
}

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




int main()
{
    int arr2D[N][N];
    srand(time(NULL));
    fill2D(arr2D);
    print2D(arr2D);
    
    clusters(arr2D);
    return 0;
}