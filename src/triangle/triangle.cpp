#include "triangle.hpp"

// Конструкторы:
Triangle::Triangle() : _vertices{Point(0, 0), Point(0, 0), Point(0, 0)} {}

Triangle::Triangle(Point point1, Point point2, Point point3) : _vertices{point1, point2, point3} {
	if (point1 == point2 || point1 == point3 || point2 == point3) throw 1;
}

// Копирования.
Triangle::Triangle(const Triangle& object) {
	for (int i = 0; i < 3; i++)
		_vertices[i] = object._vertices[i];
}

// Переопределение оператора присваивания.
Triangle& Triangle::operator=(const Triangle& value) {
	if (&value == this) return *this;
	for (int i = 0; i < 3; i++)
		_vertices[i] = value._vertices[i];
	return *this;
}

// Переопределение оператора сравнения (оператор проверяет идентичность двух объектов класса).
bool Triangle::operator==(const Triangle& object) {
	for (int i = 0; i < 3; i++) {
		bool flag = false;
		for (int j = 0; j < 3; j++)
			if (_vertices[i] == object._vertices[j]) flag = true;
		if (!flag) return false;
	}
	return true;
}

// Переопределение оператора вывода.
std::ostream& operator<<(std::ostream& fout, const Triangle& object) {
	fout << "Triangle, vertices: " << '\n' << object._vertices[0] << object._vertices[1] << object._vertices[2] << '\n';
	return fout;
}

void Triangle::print(const double koef) const {
	std::cout << "Triangle, vertices:\n";
	_vertices[0].print(koef);
	_vertices[1].print(koef);
	_vertices[2].print(koef);
}

// Метод рисования треугольника.
void Triangle::draw() {
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
		glVertex2f(_vertices[0].get_x(), _vertices[0].get_y());
		glVertex2f(_vertices[1].get_x(), _vertices[1].get_y());
		glVertex2f(_vertices[2].get_x(), _vertices[2].get_y());
	glEnd();
}

// Медиана из вершины A на сторону BC.
Segment Triangle::medianA(){
	// Противоположная сторона треугольника, к которой ищем медиану.
	Segment opposite_side(_vertices[1], _vertices[2]);
	// Медиана.
	Segment median(_vertices[0], opposite_side.div_in_ratio(1.0, 1.0));
	return median;
}

// Медиана из вершины B на сторону AC.
Segment Triangle::medianB(){
	// Противоположная сторона треугольника, к которой ищем медиану.
	Segment opposite_side(_vertices[0], _vertices[2]);
	// Медиана.
	Segment median(_vertices[1], opposite_side.div_in_ratio(1.0, 1.0));
	return median;
}

// Медиана из вершины C на сторону AB.
Segment Triangle::medianC(){
	// Противоположная сторона треугольника, к которой ищем медиану.
	Segment opposite_side(_vertices[0], _vertices[1]);
	// Медиана.
	Segment median(_vertices[2], opposite_side.div_in_ratio(1.0, 1.0));
	return median;
}

// Высота из вершины A на сторону BC.
Segment Triangle::heightA() {
	Point start_height, end_height; 
	start_height = _vertices[0];
	// Координаты конца высоты.
	double height_x, height_y;
	// Коэффициенты в уравнениях прямых.
	double a, b, c1, c2;

	// Находим коэффициенты.
	a = _vertices[2].get_y() - _vertices[1].get_y();
	b = -1 * (_vertices[2].get_x() - _vertices[1].get_x());
	c1 = -_vertices[1].get_x() * a + _vertices[1].get_y() * (-1 * b);
	c2 = -1 * b * start_height.get_x() + a * start_height.get_y();

	// Находим координаты конца высоты.
	height_x = (-1 * b * c2 - c1 * a) / (a * a + b * b);
	if (a == 0) height_y = _vertices[1].get_y();
	else height_y = (c2 + b * height_x) / a;

	// Строим высоту.
	end_height = Point(height_x, height_y);
	Segment height(start_height, end_height);

	return height;
}

// Высота из вершины B на сторону AC.
Segment Triangle::heightB() {
	Point start_height, end_height;
	start_height = _vertices[1];
	// Координаты конца высоты.
	double height_x, height_y;
	// Коэффициенты в уравнениях прямых.
	double a, b, c1, c2;

	// Находим коэффициенты.
	a = _vertices[2].get_y() - _vertices[0].get_y();
	b = -1 * (_vertices[2].get_x() - _vertices[0].get_x());
	c1 = -_vertices[0].get_x() * a + _vertices[0].get_y() * (-1 * b);
	c2 = -1 * b * start_height.get_x() + a * start_height.get_y();

	// Находим координаты конца высоты.
	height_x = (-1 * b * c2 - c1 * a) / (a * a + b * b);
	if (a == 0) height_y = _vertices[0].get_y();
	else height_y = (c2 + b * height_x) / a;

	// Строим высоту.
	end_height = Point(height_x, height_y);
	Segment height(start_height, end_height);

	return height;
}

// Высота из вершины C на сторону AB.
Segment Triangle::heightC() {
	Point start_height, end_height;
	start_height = _vertices[2];
	// Координаты конца высоты.
	double height_x, height_y;
	// Коэффициенты в уравнениях прямых.
	double a, b, c1, c2;

	// Находим коэффициенты.
	a = _vertices[1].get_y() - _vertices[0].get_y();
	b = -1 * (_vertices[1].get_x() - _vertices[0].get_x());
	c1 = -_vertices[0].get_x() * a + _vertices[0].get_y() * (-1 * b);
	c2 = -1 * b * start_height.get_x() + a * start_height.get_y();

	// Находим координаты конца высоты.
	height_x = (-1 * b * c2 - c1 * a) / (a * a + b * b);
	if (a == 0) height_y = _vertices[0].get_y();
	else height_y = (c2 + b * height_x) / a;

	// Строим высоту.
	end_height = Point(height_x, height_y);
	Segment height(start_height, end_height);

	return height;
}

// Средняя линия.
Segment Triangle::middle_line() {
	Segment left_side(_vertices[0], _vertices[1]),
		right_side(_vertices[1], _vertices[2]);
	Segment mid_line(left_side.div_in_ratio(1.0, 1.0), right_side.div_in_ratio(1.0, 1.0));
	return mid_line;
}