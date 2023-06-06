#include <iostream>
#include <vector>
#include <cmath>
#define M_PI 3.14159265358979323846


class Shape {
public:
	Shape() {}
	virtual double getPerimeter() = 0;
};

class Rectangle : public Shape {
private:
	int a, b;

public:
	Rectangle(int a, int b) {
		this->a = a;
		this->b = b;
	}

	double getPerimeter() override {
		return 2*(a+b);
	}
};

class Circle : public Shape {
private:
	int r;

public:
	Circle(int r) {
		this->r = r;
	}

	double getPerimeter() override {
		return 2 * M_PI * r;
	}
};

class Triangle : public Shape {
private:
	int a, b, c;

public:
	Triangle(int a, int b, int c) {
		this->a = a;
		this->b = b;
		this->c = c;
	}

	double getPerimeter() override {
		return ((a >= b + c) or (b >= a + c) or (c >= b + a)) ? 0 : a + b + c;
	}
};

int main() {
	int momentum;
	std::cin >> momentum;
	srand(momentum);
	std::vector<Shape*> shapes(rand() % 100 + 1);
	for (int i = 0; i < shapes.size(); i++) {
		int a = rand() % 10 + 1, b = rand() % 10 + 1, c = rand() % 10 + 1;
		//std::cout << a << ' ' << b << ' ' << c << " ";
		if (rand() % 3 == 0) { shapes[i] = new Rectangle(a, b); std::cout << "Rec\n"; }
		else if (rand() % 3 == 1) { shapes[i] = new Circle(c); std::cout << "Circ\n"; }
		else { shapes[i] = new Triangle(a, b, c); std::cout << "Tri\n"; }
	}

	double sum = 0;
	for (auto shape : shapes) {
		//std::cout << shape->getPerimeter() << "\n";
		sum += shape->getPerimeter();
	}

	std::cout << (int)sum;
}