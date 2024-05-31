#include <iostream>
#include <fstream>

#define N 3
#define J 1

using namespace std;


//lab4
//сохранение файла с конфигурацией
void conf_file( int arr[N*N], int mode){
    string path = "path";
    if (mode == 0)
      path = "config_min.txt";
    else
      path = "config_max.txt";


    ofstream fout(path);//создание/перезапись файла с именем config.txt
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
void plot_gp(int mode)
{ 
    string path = "";
    if (mode == 0)
      path = "config_min.txt";
    else
      path = "config_max.txt";

    if (mode == 0) {
      ofstream fout("plot_min.gp");
      fout << "set terminal png font \"Verdana,14\" size 1000, 1000" << endl;
      fout << "set output \"Ising_model_min.png\"\n";
      fout << "plot [-1:" << N << "][-1:" << N << "] '" << path << "' using ($1-($3/4)):($2-($4/4)):($3/2):($4/2) with vectors lc 2 notitle, '" << path <<"' using 1:2 pt 7 notitle" << endl;
      fout.close();
    }
    else {
      ofstream fout("plot_max.gp");
      fout << "set terminal png font \"Verdana,14\" size 1000, 1000" << endl;
      fout << "set output \"Ising_model_max.png\"\n";
      fout << "plot [-1:" << N << "][-1:" << N << "] '" << path << "' using ($1-($3/4)):($2-($4/4)):($3/2):($4/2) with vectors lc 2 notitle, '" << path <<"' using 1:2 pt 7 notitle" << endl;
      fout.close();
    }
    
    
    
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

  if (ii - 1< 0)
    ln = arr[(ii - 1) + N + (int)(ii/N) * N] * arr[ii];
    
  if (ii -N < 0)
    dn = arr[(ii - N) + N*N] * arr[ii];

  sum = rn + ln + un + dn;

//  printf("\n %d %d %d %d \n", rn, ln, un, dn);
  return sum * -J;
                                 //


}

int e_system(int arr[N*N]) {
    // calculate all all_energy
    int all_energy = 0; 
    for (int j=0; j<N*N; j++)
        all_energy += calc_ei(arr, j);
    return all_energy * 0.5;
//  


}

void albert1D(int arr[N*N])
{
    int min_energy = e_system(arr);
    int max_energy = e_system(arr);
    conf_file(arr, 0);
    conf_file(arr, 1);
    for(int conf_num = 1; conf_num < (1<<N*N); conf_num++)
    {
        for(int i=0; i<N*N; i++)
        {
            if(arr[i] == 1) { arr[i] = -1; break;
            }
            else arr[i] = 1;

        }

        // select 4 element 
          
          int E = e_system(arr);

          if (E < min_energy) {

            min_energy = E;
            conf_file(arr, 0);

            int D2[N][N];
            from1to2D(D2, arr);
            cout << "E = " << E << "confnum: " << conf_num << endl;
            print2D(D2);


            
          }
          if (E > max_energy) {
            max_energy = E;
            conf_file(arr, 1);
          }
          if (conf_num == 2) {
             int D2[N][N];
            from1to2D(D2, arr);
            cout << "2 spin energy " << calc_ei(arr,3) << endl;
            cout << "E = " << E << "confnum: " << conf_num << endl;
            print2D(D2);

           


          }
          //        print2D(D2);
    }
    
    printf("Min energy: %d\n", min_energy);
    printf("Max energy: %d\n", max_energy);
    cout << "J = "<< J<< endl;
}



int main()
{
    int arr[N*N];
    
    fill1D(arr);
    albert1D(arr);
    plot_gp(0);
    plot_gp(1);
/*
    int arr[N][N];
    fill2D(arr);
    albert1D(arr);
    plot_gp();
    */
    return 0;
    
    
}
