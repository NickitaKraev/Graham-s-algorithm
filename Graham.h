#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <math.h>
#include <ctime>
#include <random>
#include <chrono>
#include <fstream>


using namespace std;

struct Point {
	int x, y;
};

struct node {
	Point key;    // координаты точки
	float value; //значение угла
	node* left;   // указатель на левое поддерево
	node* right;  // указатель на правое поддерево
	int balance;  // разница высот между поддеревьями
};

class GrahamScan {
public:
	vector<Point> Get_Random_points(int number_points);
	vector<Point> findMin(vector<Point>& points); // находит самую левую нижнюю точку
	vector<Point> Calculate(vector<Point>& points, bool flag); 

	vector<Point> QuickSort(vector<Point>& points, int start, int end);
	
	int Height(node* root); // подсчёт высоты дерева
	void SetBalance(node* (&root)); // записывает разницу между высотами поддеревьев
	void TurnLeft(node* (&root));
	void TurnRight(node* (&root));
	void insert(node* (&root), Point p, double d);
	void output(node* p, vector<Point>& points);
	void clear(node** p);
	vector<Point> avlSort(vector<Point>& points, int size);


private:
	int orientation(Point& a, Point& b, Point& c); // определяет положение 3 точки относительна 2 других
	float angle(Point& a, Point& b, Point& c);  // вычисляет угол между начальной точкой и сортируемой
};