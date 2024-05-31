#include <fstream> //работа с файлами


//lab4
//сохранение файла с конфигурацией
void conf_file( int arr[N*N]){
    ofstream fout("config.txt");//создание/перезапись файла с именем config.txt
    for(int y=0; y<N; y++)
    {
        for(int x=0; x<N; x++)
        {
            //запись в файл значений
            fout << x << "\t" << y << "\t" << 0 << "\t" << arr[y*N+ x] << endl;
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


//полный перебор 1D
void albert1D(int arr[N])
{
    int min = E_system(arr); // задаем начальное значение
    int E; //текущее значение энергии
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
        E = E_system(arr);
        if(E < min)//поиск минимальной энергии и сохранение конфигурации
        {
            min=E;
            conf_file(arr);
        }
    }
}

int main()
{
    int arr[N][N];
    fill2D(arr);
    albert1D(arr);
    plot_gp();
    return 0;
}
