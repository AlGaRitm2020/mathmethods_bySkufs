#include <iostream>
#include <fstream> //работа с файлами
#include <cmath> //exp()
#include <string> //строки
#include <queue> //работа с очередью
#include <ctime>//для работы time

#define N 2
#define J 1

#define MC_steps N*N*1000 //задаем количество Монте-Карло шагов

using namespace std;
//lab9


void conf_file( int arr[N*N], string filename){

    ofstream fout(filename);//создание/перезапись файла с именем config.txt
    for(int y=0; y<N; y++)
    {
        for(int x=0; x<N; x++)
        {
            //запись в файл значений
            fout << x << "\t" << y << "\t" << 0 << "\t" << arr[(N - y-1)*N + x] << endl;
        }
    }
    fout.close();
}


int calc_ei(int arr[N*N], int ii) {

                   
  int sum = 0;
  int rn = arr[((ii + 1) % N) + (int)(ii/N) * N] * arr[ii];
  int ln = arr[(ii - 1) % N + (int)(ii/N) * N] * arr[ii];
  int un = arr[(ii + N) % (N*N)] * arr[ii];
  int dn = arr[(ii - N) % (N*N)] * arr[ii];

  if (ii - 1< 0) ln = arr[(ii - 1) + N + (int)(ii/N) * N] * arr[ii];
    
  if (ii -N < 0)
    dn = arr[(ii - N) + N*N] * arr[ii];

  sum = rn + ln + un + dn;

//  printf("\n %d %d %d %d \n", rn, ln, un, dn);
  return sum * -J;
    //


}

int E_system(int arr[N*N]) {
    // calculate all all_energy
    int all_energy = 0; 
    for (int j=0; j<N*N; j++)
        all_energy += calc_ei(arr, j);
    return all_energy * 0.5;
//  


}
// намагниченность 
int M_system (int arr[N*N])
{
    int M_sys = 0;
    for(int y=0; y<N; y++)
    {
        for(int x=0; x<N; x++)
        {
            M_sys += arr[y*N + x];
        }
    }
    
    return M_sys;
}

void wolf(int arr[N*N])
{
    //маркируем все элементы '0'
    int cluster_mark[N][N];
    
    int E;
    int M;
    double E_sred, E2_sred, M_sred, M2_sred;
    double f;//вероятность
    double r; //случайное число [0;1)
    
    srand(time(NULL));
    
    //координаты
    int x,y;

    ofstream gnuplot_file("gnup_multifora.gp");

    string strn = to_string(N);
    string conffile = strn + "x" + strn + ".txt";
    ofstream fout(conffile);//создание/перезапись файла с именем config.txt
    
    //цикл по температуре
    for(double T=5; T>0; T-=0.01)
    {
        E_sred=0;
        E2_sred=0;
        M_sred=0;
        M2_sred=0;
        
        f = 1 - exp(-2/T);
        cout << "T " << T << " and f " << f << endl;
        
        //цикл Монте-Карло
        for(int step=1; step<=MC_steps; step++)
        {

            if (T==1 && step<=50) {
                    //сохраняем текущую конфигурацию
                int t = step; // индекс кадра от 0 до 499
                string filename = "high/"+to_string(t)+".txt";
                string filename_png = "high/"+to_string(t)+".png";
                conf_file(arr, filename);
                // ffmpeg -r 24 -start_number 0 -i "%d.png" -y -vcodec mpeg4 test.avi
                //запоняем скрипт для создания рисунка с текущей конфигурацией
                gnuplot_file << "set terminal png font \"Verdana,14\" size 1000, 1000" << endl;
                gnuplot_file << "set output \"" << filename_png <<"\" " <<endl;
                gnuplot_file << "set title \"T=5, step: " << t << "\" font \"Verdana,20\" " << endl;
                gnuplot_file << "plot [-1:" << N << "][-1:" << N << "] '" << filename << "' using ($1-($3/4)):($2-($4/4)):($3/2):($4/2) with vectors notitle, '" << filename << "' using 1:2 pt 7 ps 2 lc 7 notitle" << endl << endl; 
                
            }
            //присваиваем всем элементам маркер '0'
            for(int i=0; i<N; i++)
            {
                for(int j=0; j<N; j++)
                {
                    cluster_mark[i][j] = 0;
                }
            }
            
            queue <int> check;//очередь для проверки соседей
            
            //координаты зерна роста кластера
            x = rand()%N;
            y = rand()%N;

            int seed = arr[y*N + x];
            
            //добавляем в очередь координаты кластера
            check.push(x);
            check.push(y);
            
            //цикл проверки соседей для добавления в кластер
            while(check.empty() != 1)
            {
                x = check.front();//обращаемся к первому элементу в очереди
                check.pop();//удаляем первый элемент из очереди
                y = check.front();
                check.pop();
                
                //маркируем элемент
                cluster_mark[y][x] = 1 * seed ; // EDITED SEED
                
                //проверяем соседей справа
                r = rand()/(double)RAND_MAX;//случайное число от 0 до 1
                if(x == N-1)
                {
                    if(arr[y*N + x] == arr[y*N] && cluster_mark[y][0] == 0)
                    {
                        if(r>f)
                        {
                            //cluster_mark[y][0] = -1;
                        }
                        else
                        {
                            check.push(0);
                            check.push(y);
                        }
                    }
                }
                else
                    if(arr[y*N + x] == arr[y*N +x+1] && cluster_mark[y][x+1] == 0)
                    {
                        if(r>f)
                        {
                            //cluster_mark[y][x+1] = -1;
                        }
                        else
                        {
                            check.push(x+1);
                            check.push(y);
                        }
                    }
                
                //проверяем соседей слева
                r = rand()/(double)RAND_MAX;//случайное число от 0 до 1
                if(x == 0)
                {
                    if(arr[y*N + x] == arr[y*N + N-1] && cluster_mark[y][N-1] == 0)
                    {
                        if(r>f)
                        {
                            //cluster_mark[y][N-1] = -1;
                        }
                        else
                        {
                            check.push(N-1);
                            check.push(y);
                        }
                    }
                }
                else
                    if(arr[y*N + x] == arr[y* N + x-1] && cluster_mark[y][x-1] == 0)
                    {
                        if(r>f)
                        {
                            //cluster_mark[y][x-1] = -1;
                        }
                        else
                        {
                            check.push(x-1);
                            check.push(y);
                        }
                    }
                
                //проверяем соседей сверху
                r = rand()/(double)RAND_MAX;//случайное число от 0 до 1
                if(y == 0)
                {
                    if(arr[y*N + x] == arr[(N-1)*N + x] && cluster_mark[N-1][x] == 0)
                    {
                        if(r>f)
                        {
                            //cluster_mark[N-1][x] = -1;
                        }
                        else
                        {
                            check.push(x);
                            check.push(N-1);
                        }
                    }
                }
                else
                    if(arr[y*N + x] == arr[(y-1)*N+x] && cluster_mark[y-1][x] == 0)
                    {
                        if(r>f)
                        {
                            //cluster_mark[y-1][x] = -1;
                        }
                        else
                        {
                            check.push(x);
                            check.push(y-1);
                        }
                    }
                
                //проверяем соседей снизу
                r = rand()/(double)RAND_MAX;//случайное число от 0 до 1
                if(y == N-1)
                {
                    if(arr[y*N + x] == arr[0*N + x] && cluster_mark[0][x] == 0)
                    {
                        if(r>f)
                        {
                            //cluster_mark[0][x] = -1;
                        }
                        else
                        {
                            check.push(x);
                            check.push(0);
                        }
                    }
                }
                else
                    if(arr[y*N + x] == arr[(y+1) * N + x] && cluster_mark[y+1][x] == 0)
                    {
                        if(r>f)
                        {
                            //cluster_mark[y+1][x] = -1;
                        }
                        else
                        {
                            check.push(x);
                            check.push(y+1);
                        }
                    }
                
            }//while
            
            //задаем новое значение для кластера
            int new_value;
           
            if(rand()%2) 
                new_value = 1;
            else 
                new_value = -1;
            
            //меняем значения кластера
            for(int i=0; i<N; i++)
            {
                for(int j=0; j<N; j++)
                {
                    if(cluster_mark[i][j] ==seed)
                    {
                        arr[i*N + j] = new_value;
                    }
                }
            }
            
            //вычисляем параметры новой конфигурации
            E = E_system(arr);
            M = M_system(arr);
            
            //вычисляем средне значения
            M_sred += (abs(M) - M_sred) / step;
            M2_sred += ((M*M) - M2_sred) / step;
            E_sred += (E - E_sred) / step;
            E2_sred += ((E*E) - E2_sred) / step;
        }//монте-карло


        int t = 500 - (T * 100); // индекс кадра от 0 до 499
        string filename = "all_temp/" + to_string(t)+".txt";
        string filename_png = "all_temp/" + to_string(t)+".png";
        conf_file(arr, filename);
        // ffmpeg -r 24 -start_number 0 -i "%d.png" -y -vcodec mpeg4 test.avi
        //запоняем скрипт для создания рисунка с текущей конфигурацией
        gnuplot_file << "set terminal png font \"Verdana,14\" size 1000, 1000" << endl;
        gnuplot_file << "set output \"" << filename_png << "\" " <<endl;
        gnuplot_file << "set title \"Temerature: " << T << "\" font \"Verdana,20\" " << endl;
        gnuplot_file << "plot [-1:" << N << "][-1:" << N << "] '" << filename<<"' using ($1-($3/4)):($2-($4/4)):($3/2):($4/2) with vectors notitle, '" << filename<<"' using 1:2 pt 7 ps 2 lc 7 notitle" << endl << endl; 
        
        
        //считаем теплоемкость и магнитную восприимчивость, сохраняемм в файл
        //дальше все как в предыдущей лабораторной
        double C = (E2_sred - E_sred*E_sred)/(T*T)/(N*N);  //удельная теплоемкость (формула 2)
        double Xi = (M2_sred - M_sred*M_sred)/T/(N*N);     //магнитная восприимчивость (формула 3)
        
      
     //записать значения в файл
    
    fout << T << "\t" << E_sred / (N*N)  << "\t" << M_sred / (N*N) << "\t" << C  << "\t" << Xi  << endl;
        //построить графики по заданию
    }//температура
}

void fill2D(int arr[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            arr[i][j] = ((rand() % 2) * -2) + 1; 

}

void fill1D(int arr[N*N])
{
    for(int i=0; i<N*N; i++)
    {
        arr[i]=(rand() % 2)*-2 + 1;
    }
}


int main()
{
    int arr[N*N];
    srand(time(NULL));
    //случайным образом заполнить массив
    fill1D(arr);
    wolf(arr);
    
    return 0;
}