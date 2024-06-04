#include <iostream>
#include <fstream>
#include <cmath>
#define MC_steps N*N*1000 //задаем количество Монте-Карло шагов, меняем только последнее значение 
#define N 2
#define J 1

using namespace std;


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

//скрипт gnuplot для создания изображения
void plot_gp()
{
    ofstream fout("plot.gp");
    fout << "set terminal png font \"Verdana,14\" size 1000, 1000" << endl;
    fout << "set output \"Ising_model.png\"\n";
    fout << "plot [-1:" << N << "][-1:" << N << "] 'config.txt' using ($1-($3/4)):($2-($4/4)):($3/2):($4/2) with vectors lc 2 notitle, 'config.txt' using 1:2 pt 7 notitle" << endl;
    
    fout.close();
}




void fill1D(int arr[N*N])
{
    for(int i=0; i<N*N; i++)
    {
        arr[i]=(rand() % 2)*-2 + 1;
    }
}
void fill1D_old(int arr[N*N])
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

//lab7
void metropolis(int arr[N*N])
{
    int E;
    int E_old, E_new;
    int M;
    double E_sred, E2_sred, M_sred, M2_sred;
    double f;//вероятность
    double r; //случайное число [0;1)

    double Z=0;         //статиcтическая сумма (формула 2)
    
    double exponenta;
    
    double C;   //удельная теплоемкость (формула 8)
    double Xi;  //магнитная восприимчивость (формула 9)
    
    int x,y;
    
    srand(time(NULL));
    
      // ========= config setup =============
      /*
    string filename = to_string(5)+".txt"; 
    conf_file(arr,filename);
*/

    // filling script for creationg img with null config
    ofstream gnuplot_file("gnup_multifora.gp");
    
    /*
    gnuplot_file << "set terminal png font \"Verdana,14\" size 1000, 1000" << endl;
    gnuplot_file << "set output \"0.png\" " <<endl;
    gnuplot_file << "set title \"Cofiguration: 0\" font \"Verdana,20\" " << endl;
    gnuplot_file << "plot [-1:" << N << "][-1:" << N << "] '0.txt' using ($1-($3/4)):($2-($4/4)):($3/2):($4/2) with vectors notitle, '0.txt' using 1:2 pt 7 ps 2 lc 7 notitle" << endl << endl; 
    *//// ========================================

    string strn = to_string(N);
    string conffile = strn + "x" + strn + ".txt";
    ofstream fout(conffile);//создание/перезапись файла с именем config.txt

    for(double T=5; T>0; T-=0.01)
    {
     E_sred=0;
     E2_sred=0;
     M_sred=0;
     M2_sred=0;

   
     
     //цикл Монте-Карло
     
     for(int step=1; step<=MC_steps; step++)
     {
        if (T==5 && step<=50) {
            //сохраняем текущую конфигурацию
        int t = step; // индекс кадра от 0 до 499
        string filename = "high"+to_string(t)+".txt";
        string filename_png = "high"+to_string(t)+".png";
        conf_file(arr, filename);
        // ffmpeg -r 24 -start_number 0 -i "%d.png" -y -vcodec mpeg4 test.avi
        //запоняем скрипт для создания рисунка с текущей конфигурацией
        gnuplot_file << "set terminal png font \"Verdana,14\" size 1000, 1000" << endl;
        gnuplot_file << "set output \"" << filename_png <<"\" " <<endl;
        gnuplot_file << "set title \"T=5, step: " << t << "\" font \"Verdana,20\" " << endl;
        gnuplot_file << "plot [-1:" << N << "][-1:" << N << "] '" << filename << "' using ($1-($3/4)):($2-($4/4)):($3/2):($4/2) with vectors notitle, '" << filename << "' using 1:2 pt 7 ps 2 lc 7 notitle" << endl << endl; 
        
        }


         x = rand()%(N*N);
   
         
         E_old = E_system(arr);//сохраняем значение энергии системы до переворота
         
         arr[x] = -arr[x];// переворачиваем спин
         
         E_new = E_system(arr);//считаем значение энергии системы после переворота
         
         //проверить >=
         if(E_new >= E_old)
         {
             //вероятность принятия конфигурации
             //чем ниже температура, тем меньше вероятность перехода к новой конфигурации
             f = exp(-(E_new-E_old)/T);
             
             //случайное число [0;1)
             r = rand()/(double)RAND_MAX;
             
             //если случайное число больше или равно вероятности f, то возвращаем спин в исходное состояние
             //r==0 для того, чтобы исключить перевороты в замороженной системе при температуре близкой к 0
             //т.к. f не принимает значение 0, а только очень близкое к 0 
             if(r>=f || r==0)
             {
                 arr[x] = -arr[x];// переворачиваем спин в исходное состояние
             }
             
         }


        
          //        print2D(D2);
         
         //вычисляем параметры новой конфигурации
         E = E_system(arr);
         M = M_system(arr);
         
         //вычисляем средне значения
         M_sred += (abs(M) - M_sred) / step;
         M2_sred += ((M*M) - M2_sred) / step;
         E_sred += (E - E_sred) / step;
         E2_sred += ((E*E) - E2_sred) / step;
     }//MC end

     // save congih
         //сохраняем текущую конфигурацию
        int t = 500 - (T * 100); // индекс кадра от 0 до 499
        string filename = to_string(t)+".txt";
        conf_file(arr, filename);
        // ffmpeg -r 24 -start_number 0 -i "%d.png" -y -vcodec mpeg4 test.avi
        //запоняем скрипт для создания рисунка с текущей конфигурацией
        gnuplot_file << "set terminal png font \"Verdana,14\" size 1000, 1000" << endl;
        gnuplot_file << "set output \"" << t << ".png\" " <<endl;
        gnuplot_file << "set title \"Temerature: " << T << "\" font \"Verdana,20\" " << endl;
        gnuplot_file << "plot [-1:" << N << "][-1:" << N << "] '" << t << ".txt' using ($1-($3/4)):($2-($4/4)):($3/2):($4/2) with vectors notitle, '" << t << ".txt' using 1:2 pt 7 ps 2 lc 7 notitle" << endl << endl; 
        

    
     
     //считаем теплоемкость и магнитную восприимчивость, сохраняемм в файл
     //дальше все как в предыдущей лабораторной
     C = (E2_sred - E_sred*E_sred)/(T*T)/(N*N);  //удельная теплоемкость (формула 2)
     Xi = (M2_sred - M_sred*M_sred)/T/(N*N);     //магнитная восприимчивость (формула 3)
     
     //записать значения в файл
    
    fout << T << "\t" << E_sred / (N*N)  << "\t" << M_sred / (N*N) << "\t" << C  << "\t" << Xi  << endl; 
     //T     E/N     M/N     C/N      Xi/N
     

     
     //построить графики по заданию
    }//T
    
}

int main()
{
    int arr[N*N];
    //случайным образом заполнить массив
    fill1D(arr);
    metropolis(arr);
    
    return 0;
}