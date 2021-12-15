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
	Point key;    // ���������� �����
	float value; //�������� ����
	node* left;   // ��������� �� ����� ���������
	node* right;  // ��������� �� ������ ���������
	int balance;  // ������� ����� ����� ������������
};

class GrahamScan {
public:
	vector<Point> Get_Random_points(int number_points);
	vector<Point> findMin(vector<Point>& points); // ������� ����� ����� ������ �����
	vector<Point> Calculate(vector<Point>& points, bool flag); 

	vector<Point> QuickSort(vector<Point>& points, int start, int end);
	
	int Height(node* root); // ������� ������ ������
	void SetBalance(node* (&root)); // ���������� ������� ����� �������� �����������
	void TurnLeft(node* (&root));
	void TurnRight(node* (&root));
	void insert(node* (&root), Point p, double d);
	void output(node* p, vector<Point>& points);
	void clear(node** p);
	vector<Point> avlSort(vector<Point>& points, int size);


private:
	int orientation(Point& a, Point& b, Point& c); // ���������� ��������� 3 ����� ������������ 2 ������
	float angle(Point& a, Point& b, Point& c);  // ��������� ���� ����� ��������� ������ � �����������
};