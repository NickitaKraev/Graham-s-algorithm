#include"Graham.h"

using namespace std::chrono;

int main()
{
    setlocale(LC_ALL, "Russian");
    ofstream fout;
    fout.open("Graham_Algorithm.txt");
    int number_points[14] = { 5 , 10, 15, 20, 30, 50, 75, 100, 500, 1000, 2500, 5000, 7500, 10000 };
    for (int i = 0; i < 14; i++) {
        fout << number_points[i] << " ";
    }
    bool flag[2] = { true, false };
    double time_QuikSort[14];
    double time_AVL_Tree[14];
    GrahamScan obj;
    vector<Point> points = obj.Get_Random_points(number_points[0]);
    vector<Point> res = obj.Calculate(points, flag[1]);
    int size = res.size();
    for (int i = 0; i < 14; i++) {
        GrahamScan obj;        
        vector<Point> points = obj.Get_Random_points(number_points[i]);
        auto start = high_resolution_clock::now();
        vector<Point> res = obj.Calculate(points, flag[0]);
        auto stop = high_resolution_clock::now();
        int size = res.size();
        auto duration = duration_cast<microseconds>(stop - start);
        time_QuikSort[i] = double(duration.count())/ 1000000.0;
    }
    fout << "\n";
    for (int i = 0; i < 14; i++) {
        cout << number_points[i] << " " << time_QuikSort[i] << endl;
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
    }
    fout << "\n";
    for (int i = 0; i < 14; i++) {
        cout << number_points[i]<< " " << time_AVL_Tree[i] << endl;
        fout << time_AVL_Tree[i] << " ";
    }
    fout.close();

    return 0;
}