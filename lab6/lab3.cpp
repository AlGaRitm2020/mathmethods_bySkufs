#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

#define N 3
#define J 1

using namespace std;


//lab4
//сохранение файла с конфигурацией
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



    string filename = to_string(0)+".txt"; 
    conf_file(arr,filename);

    int N_conf = 1<<(N*N);
    int *E_arr = new int[N_conf]; // массив энергий для конф
    int *M_arr = new int[N_conf]; // массив намагниченностей для конф
    
    E_arr[0] = E_system(arr);
    M_arr[0] = M_system(arr);
    

    // filling script for creationg img with null config
    ofstream gnuplot_file("gnup_multifora.gp");
    gnuplot_file << "set terminal png font \"Verdana,14\" size 1000, 1000" << endl;
    gnuplot_file << "set output \"0.png\" " <<endl;
    gnuplot_file << "set title \"Cofiguration: 0\" font \"Verdana,20\" " << endl;
    gnuplot_file << "plot [-1:" << N << "][-1:" << N << "] '0.txt' using ($1-($3/4)):($2-($4/4)):($3/2):($4/2) with vectors notitle, '0.txt' using 1:2 pt 7 ps 2 lc 7 notitle" << endl << endl; 


    for(int conf_num = 1; conf_num < (1<<N*N); conf_num++)
    {
        for(int i=0; i<N*N; i++)
        {
            if(arr[i] == 1) { arr[i] = -1; break;
            }
            else arr[i] = 1;

        }

        // select 4 element 
         //сохраняем текущую конфигурацию
        filename = to_string(conf_num)+".txt";
        conf_file(arr, filename);
        
        //запоняем скрипт для создания рисунка с текущей конфигурацией
        gnuplot_file << "set terminal png font \"Verdana,14\" size 1000, 1000" << endl;
        gnuplot_file << "set output \"" << conf_num << ".png\" " <<endl;
        gnuplot_file << "set title \"Cofiguration: " << conf_num << "\" font \"Verdana,20\" " << endl;
        gnuplot_file << "plot [-1:" << N << "][-1:" << N << "] '" << conf_num << ".txt' using ($1-($3/4)):($2-($4/4)):($3/2):($4/2) with vectors notitle, '" << conf_num << ".txt' using 1:2 pt 7 ps 2 lc 7 notitle" << endl << endl; 
          //        print2D(D2);
    }
    gnuplot_file.close();    
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
