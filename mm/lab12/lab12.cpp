// lab12
#include <iostream>
#include <cmath> //sqrt()
#include <algorithm> // next_permutation()
#include <fstream>

using namespace std;

#define N_cities 12  //количество городов
#define n N_cities+1 //добавляем последний город, который равен первому, для замыкания пути


void conf_file( int arr[n][n], string filename){

    ofstream fout(filename);//создание/перезапись файла с именем config.txt
    for(int y=0; y<n; y++)
    {
        for(int x=0; x<n; x++)
        {
            //запись в файл значений
            //fout << x << "\t" << y << "\t" << 0 << "\t" << arr[(N - y-1)*N + x] << endl;
            fout << x << "\t" << y << "\t" << 0 << "\t" << arr[y][x] << endl;
        }
    }
    fout.close();

}

//функция заполняет номера городов
void set_num_cities(int cities[])
{
	for (int i = 0; i < N_cities; i++)
	{
		cities[i] = i; // присваиваем каждому городу свой номер
	}
	cities[N_cities] = cities[0]; // последний город равен первому, чтобы замкнуть путь
}

// функция заполняет координаты городов случайным образом
void set_coord(int x[], int y[])
{
	for (int i = 0; i < N_cities; i++)
	{
		x[i] = rand() % 10001;
		y[i] = rand() % 10001;
	}
}

// функция вычисляет расстояния между всеми городами и сохраняет в массив
void calc_distance(double r[][N_cities], int x[], int y[])
{
	for (int i = 0; i < N_cities; i++)
	{
		for (int j = 0; j < N_cities; j++)
		{
			r[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
		}
	}
}
void file_write(int x[], int y[], int cities[], string filename) {
    ofstream fout(filename);
    for (int i = 0; i < n; i++)
	{
		fout << x[cities[i]] << "\t" << y[cities[i]] << endl;
	}

}

// функция вычисляет путь через все города
double calc_path(int cities[], double r[][N_cities])
{
	double path = 0;
	for (int i = 0; i < N_cities; i++)
	{
		path += r[cities[i]][cities[i + 1]];
	}
	return path;
}

// lab12
// функция перебора всех вариантов прохождения городов
void perebor(int cities[], double r[][N_cities], int x[], int y[])
{
	double path;	  // хранит длину пути между городами
	double path_min; // хранит минимальный путь
	path_min = calc_path(cities, r); // задаем начальный путь как минимальный

    file_write(x,y,cities, "first.txt");

    ofstream all("all.txt");

	// цикл полного перебора всех вариантов путей между городами
	// алгоритм next_permutation() делает перестановки символов, чтобы перебрать все возможные комбинации
	do
	{
		path = calc_path(cities, r); // для каждой комбинации вычисляем длину пути

		// ищем минимальный путь, который надо будет сохранить в файл для визуализации
		if (path_min > path)
		{
			path_min = path;
			//cout << "new min\n";
			
            file_write(x,y,cities, "optimal.txt");
		}

		for (int i = 0; i < n; i++)
			{
				all << x[cities[i]] << "\t" << y[cities[i]] << endl;
			}


        

        //file_write(x,y,cities, "all.txt");
		// в next_permutation указываем начальный и конечный адрес диапазона элементов, которые надо переставить
	} while (next_permutation(cities + 1, cities + N_cities)); 
    // первый и последний элементы не участвуют в перестановке, т.к. путь замкнутый
    
}

int main()
{
	//устанавливаем seed ГСЧ
	srand(7);//здесь необходимо использовать свой seed, в соответствии с номером варианта в таблице

	int cities[n]; //массив городов
	set_num_cities(cities);//заполняем номера городов
	
	int x[N_cities], y[N_cities]; // массивы координат городов
	set_coord(x, y); //заполняем координаты городов случайным образом

	// массив для хранения расстояний между городами
	double r[N_cities][N_cities];
	calc_distance(r, x, y); //вычисляем расстояния между всеми городами и сохраняем в массив

	perebor(cities, r, x, y); // lab12

	return 0;
}