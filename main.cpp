#include"Graham.h"

using namespace std::chrono;

int main()
{
    setlocale(LC_ALL, "Russian");
    ofstream fout;
    fout.open("result.txt");
    int number_points[14] = { 5 , 10, 15, 20, 30, 50, 75, 100, 500, 1000, 2500, 5000, 7500, 10000 };
    for (int i = 0; i < 14; i++) {
        fout << number_points[i] << " ";
    }
    bool flag[2] = { true, false };
    double time_QuikSort[14];
    double time_AVL_Tree[14];

    for (int i = 0; i < 14; i++) {
        GrahamScan obj;        
        vector<Point> points = obj.Get_Random_points(number_points[i]);
        auto start = high_resolution_clock::now();
        vector<Point> res = obj.Calculate(points, flag[0]);
        auto stop = high_resolution_clock::now();
        int size = res.size();
        auto duration = duration_cast<microseconds>(stop - start);
        time_QuikSort[i] = double(duration.count())/ 1000000.0;
        cout << "Быстрая сортировка" << endl;
        cout << "Количество точек: " << number_points[i] << endl << "Время выполнения: " << time_QuikSort[i] << endl;
        cout << "Количество точек в конечном множестве: " << size << endl;
        for (int i = 0; i < size; i++) { cout << res[i].x << " " << res[i].y << endl; }
        cout << endl;
    }

    fout << "\n";
    for (int i = 0; i < 14; i++) {
        fout << time_QuikSort[i] << " ";
    }

    for (int i = 0; i < 14; i++) {
        GrahamScan obj;
        vector<Point> points = obj.Get_Random_points(number_points[i]);
        auto start = high_resolution_clock::now();
        vector<Point> res = obj.Calculate(points, flag[1]);
        auto stop = high_resolution_clock::now();
        int size = res.size();
        auto duration = duration_cast<microseconds>(stop - start);
        time_AVL_Tree[i] = double(duration.count()) / 1000000.0;
        cout << "АВЛ-дерево" << endl;
        cout << "Количество точек: " << number_points[i] << endl << "Время выполнения: " << time_AVL_Tree[i] << endl;
        cout << "Количество точек в конечном множестве: " << size << endl;
        for (int i = 0; i < size; i++) { cout << res[i].x << " " << res[i].y << endl; }
        cout << endl;
    }

    fout << "\n";
    for (int i = 0; i < 14; i++) {
        fout << time_AVL_Tree[i] << " ";
    }
    fout.close();

    return 0;
}