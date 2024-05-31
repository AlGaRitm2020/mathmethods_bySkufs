#include <cmath> //exp()

//lab5
//функция для подсчета намагниченности всей системы
int M_system (int arr[N][N])
{
    int M_sys = 0;
    for(int y=0; y<N; y++)
    {
        for(int x=0; x<N; x++)
        {
            M_sys += arr[y][x];
        }
    }
    
    return M_sys;
}

//полный перебор 2D
void albert2D_lab5(int arr[N][N])
{
    int N_conf = 1<<(N*N); //количество конфигураций
    int *E_arr = new int[N_conf];//массив энергий для каждой конфигурации
    int *M_arr = new int[N_conf];//массив намагниченностей для каждой конфигурации
    
    E_arr[0] = E_system(arr); //энергия нулевой конфигурации
    M_arr[0] = M_system(arr); //намагниченность нулевой конфигурации
    
    int E_min = E_system(arr); //задаем начальное значение для минимальной энергии
    int E; //текущее значение энергии
    
    //цикл полного перебора всех конфигураций
    for(int conf_num = 1; conf_num < (1<<N*N); conf_num++)
    {
        //алгоритм перебора конфигураций
        
        //поиск минимальной энергии и сохранение конфигурации
        
        //запись в массивы энергий и намагниченности для всех конфигураций
        E_arr[conf_num] = E_system(arr);        
        M_arr[conf_num] = M_system(arr);
    }
    
    double Z=0;         //статиcтическая сумма (формула 2)
    double E_sred = 0;  //средняя энергия (формула 4)
    double E2_sred = 0; //среднее квадрата энергии (формула 5)
    double M_sred = 0;  //средняя намагниченность (формула 6)
    double M2_sred = 0; //среднее квадрата намагниченности (формула 7)
    
    double exponenta;
    
    double C;   //удельная теплоемкость (формула 8)
    double Xi;  //магнитная восприимчивость (формула 9)
    
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
        
        C = (E2_sred - E_sred*E_sred)/(T*T)/(N*N);  //удельная теплоемкость (формула 8)
        Xi = (M2_sred - M_sred*M_sred)/T/(N*N);     //магнитная восприимчивость (формула 9)
        
        //записать значения в файл
        //T     E/N     M/N     C/N      Xi/N
        
        //построить графики по заданию
    }
    
    //освобождаем память
    delete [] E_arr;
    delete [] M_arr;
}


int main()
{
    int arr[N][N];
    fill2D(arr);
    albert2D_lab5(arr);
    return 0;
}
