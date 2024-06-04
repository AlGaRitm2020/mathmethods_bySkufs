#include <iostream>
#include <fstream>
#include <cmath>
#define N 5
#define J 1

using namespace std;


//lab4
//сохранение файла с конфигурацией
void conf_file( int arr[N*N]){
    ofstream fout("config.txt");//создание/перезапись файла с именем config.txt
    for(int y=0; y<N; y++)
    {
        for(int x=0; x<N; x++)
        {
            //запись в файл значений
            fout << x << "\t" << y << "\t" << 0 << "\t" << arr[y*N + x] << endl;
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

void albert1D(int arr[N*N])
{
    int E_min = E_system(arr);
    int E_max = E_system(arr);

    conf_file(arr);
    int N_conf = 1<<(N*N);
    int *E_arr = new int[N_conf]; // массив энергий для конф
    int *M_arr = new int[N_conf]; // массив намагниченностей для конф
    
    E_arr[0] = E_system(arr);
    M_arr[0] = M_system(arr);


    for(int conf_num = 1; conf_num < (1<<N*N); conf_num++)
    {
        for(int i=0; i<N*N; i++)
        {
            if(arr[i] == 1) { arr[i] = -1; break;
            }
            else arr[i] = 1;

        }

        // select 4 element 
          

          int E = E_system(arr);

          if (E < E_min) {
            cout << "new min energy: " << endl;
            int D2[N][N];
            from1to2D(D2, arr);

            print2D(D2);

            E_min = E;
            conf_file(arr);
            
          }
          if (E > E_max) {E_max = E;  }

        E_arr[conf_num] = E_system(arr);
        M_arr[conf_num] = M_system(arr);
          //        print2D(D2);
    }
    
    printf("Min energy: %d\n", E_min);
    printf("Max energy: %d\n", E_max);

    double Z=0;         //статиcтическая сумма (формула 2)
    double E_sred = 0;  //средняя энергия (формула 4)
    double E2_sred = 0; //среднее квадрата энергии (формула 5)
    double M_sred = 0;  //средняя намагниченность (формула 6)
    double M2_sred = 0; //среднее квадрата намагниченности (формула 7)
    
    double exponenta;
    
    double C;   //удельная теплоемкость (формула 8)
    double Xi;  //магнитная восприимчивость (формула 9)
    
    ofstream fout("5x5.txt");//создание/перезапись файла с именем config.txt
    for(double T = 0.0001; T<=5; T+=0.01)
    {
        Z=0;
        E_sred = 0;
        E2_sred = 0;
        M_sred = 0;
        M2_sred = 0;
        
        
        for(int conf_num = 0; conf_num < (1<<N*N); conf_num++)
        {
            exponenta = exp(-((E_arr[conf_num]-E_min)/T));
            Z += exponenta;
            
            E_sred += E_arr[conf_num]*exponenta;
            E2_sred += E_arr[conf_num]*E_arr[conf_num]*exponenta;
            
            M_sred += abs(M_arr[conf_num]) * exponenta;
            M2_sred += M_arr[conf_num]*M_arr[conf_num] * exponenta;
        }
        
        E_sred/=Z;
        E2_sred/=Z;
        M_sred/=Z;
        M2_sred/=Z;
        
        C = (E2_sred - E_sred*E_sred)/(T*T);  //удельная теплоемкость (формула 8)
        Xi = (M2_sred - M_sred*M_sred)/T;     //магнитная восприимчивость (формула 9)
        

        fout << T << "\t" << E_sred / (N*N)  << "\t" << M_sred / (N*N) << "\t" << C / (N*N) << "\t" << Xi / (N*N) << endl; 
        
        //записать значения в файл
        //T     E/N     M/N     C/N      Xi/N
        /*
         void conf_file( int arr[N*N]){
    ofstream fout("config.txt");//создание/перезапись файла с именем config.txt
    for(int y=0; y<N; y++)
    {
        for(int x=0; x<N; x++)
        {
            //запись в файл значений
            fout << x << "\t" << y << "\t" << 0 << "\t" << arr[y*N + x] << endl;
        }
    }
    fout.close();
}*/

      

        
        //построить графики по заданию
    }
    
    //освобождаем память
    delete [] E_arr;
    delete [] M_arr;
}



int main()
{

    int arr[N*N];

    
    fill1D(arr);
    albert1D(arr);
//    plot_gp();
/*
    int arr[N][N];
    fill2D(arr);
    albert1D(arr);
    plot_gp();
    */
    return 0;
    
    
}
