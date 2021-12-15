#include"Graham.h"
vector<Point> GrahamScan::Get_Random_points(int number_points) {
	vector<Point> points;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(-10000, 10000);
	for (int i = 0; i < number_points; i++) {
		int x = dis(gen);
		int y = dis(gen);
		points.push_back(Point{ x, y });
	}
	
	return points;
}

vector<Point> GrahamScan::Calculate(vector<Point>& points, bool flag) {
	int n = points.size();
	findMin(points);
	if (flag) { QuickSort(points, 1, n - 1); }
	else avlSort(points, n);
	vector<Point> result;
	result.push_back(points[0]);
	result.push_back(points[1]);
	for (int i = 2; i < n; i++) {
		while ((orientation(result[result.size() - 2], result[result.size() - 1], points[i])) < 0) {
			result.pop_back();
		}
		result.push_back(points[i]);
	}

	return result;
}


vector<Point> GrahamScan::findMin(vector<Point>& points) {
	int n = points.size();
	int y_min = points[0].y;
	int min = 0;
	for (int i = 1; i < n; i++) {
		if ((points[i].y < y_min) || (points[i].y == y_min && points[i].x < points[min].x)) {
			y_min = points[i].y;
			min = i;
		}
	}
	swap(points[0], points[min]);
	return points;
}

int GrahamScan::orientation(Point& a, Point& b, Point& c) {
	int value = (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
	return value;
}

vector<Point> GrahamScan::QuickSort(vector<Point>& points, int start, int end) {
	Point mid = points[start + (end - start) / 2];
	int i = start;
	int j = end;
	while (i <= j) {
		while (orientation(points[0], mid, points[i]) < 0) {
			i++;
		}
		while (orientation(points[0], mid, points[j]) > 0) {
			j--;
		}

		if (i <= j) {
			swap(points[i], points[j]);
			i++;
			j--;
		}
	}
	if (start < j) {
		QuickSort(points, start, j);
	}
	if (end > i) {
		QuickSort(points, i, end);
	}


	return points;
}

int GrahamScan::Height(node* root) {
	if (root == NULL) return 0;
	int hLeft = Height(root->left);
	int hRight = Height(root->right);
	if (hLeft > hRight) return hLeft + 1;
	else return hRight + 1;
}

void GrahamScan::SetBalance(node* (&root)) {
	if (root != NULL)
		root->balance = Height(root->right) - Height(root->left);
}

void GrahamScan::TurnLeft(node* (&root)) {
	node* rightSubTree, * rightSubTreeLeftSubtree;
	rightSubTree = root->right;
	rightSubTreeLeftSubtree = rightSubTree->left;

	rightSubTree->left = root;
	root->right = rightSubTreeLeftSubtree;
	root = rightSubTree;
	SetBalance(root->left);
	SetBalance(root);
}

void GrahamScan::TurnRight(node* (&root)) {
	node* leftSubtree, * leftSubtreeRightSubtree;
	leftSubtree = root->left;
	leftSubtreeRightSubtree = leftSubtree->right;

	leftSubtree->right = root;
	root->left = leftSubtreeRightSubtree;
	root = leftSubtree;
	SetBalance(root->right);
	SetBalance(root);
}

void GrahamScan::insert(node* (&root), Point p, double d) {
	if (root == NULL) {
		root = new node;
		root->key = p;
		root->value = d;
		root->balance = 0;
		root->left = NULL;
		root->right = NULL;
	}
	else {
		if (d > root->value) {
			insert(root->right, p, d);
			if (Height(root->right) - Height(root->left) > 1) {
				if (Height(root->right->right) < Height(root->right->left)) {
					TurnRight(root->right);
				}
				TurnLeft(root);
			}
		}
		else {
			if (d <= root->value) {
				insert(root->left, p, d);
				if (Height(root->left) - Height(root->right) > 1) {
					if (Height(root->left->left) < Height(root->left->right)) {
						TurnLeft(root->left);
					}
					TurnRight(root);
				}
			}

		}
		SetBalance(root);
	}
}

void GrahamScan::output(node* p, vector<Point>& points) {
	if (p != NULL) {
		output(p->left, points);
		points.push_back(p->key);
		output(p->right, points);
	}
}

void GrahamScan::clear(node** p) {
	if ((*p) != NULL) {
		clear(&(*p)->left);
		clear(&(*p)->right);
	}
	delete* p;
	*p = NULL;
}

float GrahamScan::angle(Point& a, Point& b, Point& c) {
	int x1 = b.x - a.x;
	int y1 = b.y - a.y;
	int x2 = c.x - a.x;
	int y2 = c.y - a.y;
	int scalar = x1 * x2 + y1 * y2;
	float agl = scalar / ((sqrt(x1 * x1 + y1 * y1)) * (sqrt(x2 * x2 + y2 * y2)));
	float angle = acos(agl) ;
	return angle;
}

vector<Point> GrahamScan::avlSort(vector<Point>& points, int size) {
	Point first = points[0];
	swap(points[0], points[size - 1]);
	points.pop_back();
	Point second = { first.x + 1,first.y };
	node* root;
	root = NULL;
	for (int i = 0; i < size - 1; i++) {
		insert(root, points[i], angle(first, second, points[i]));
	}
	points.clear();
	points.push_back(first);
	output(root, points);
	clear(&root);
	return points;
}