#include "quadrangle.hpp"
#include <algorithm>

// Метод сортирует вершины четырехугольника по часовой стрелке.
// !!note!! В методе баг, в случае с вогнутыми четырехугольниками, может построить не тот
// четырехугольник, что задумывал юзер.
void Quadrangle::vertices_sort() {
	// Метод сортирует сначала точки по координате у, а потом упорядычевает попарно по иксу.
	std::sort(_vertices, _vertices + 4, [](Point first, Point second) {
		return std::abs(first.get_y()) > std::abs(second.get_y());
	});
	if (std::abs(_vertices[0].get_x()) > std::abs(_vertices[1].get_x())) {
		Point temp = _vertices[0];
		_vertices[0] = _vertices[1];
		_vertices[1] = temp;
	}
	if (std::abs(_vertices[3].get_x()) > std::abs(_vertices[2].get_x())) {
		Point temp = _vertices[2];
		_vertices[2] = _vertices[3];
		_vertices[3] = temp;
	}
}

// Конструкторы.
Quadrangle::Quadrangle() : _vertices{Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0)} {}

Quadrangle::Quadrangle(Point point1, Point point2, Point point3, Point point4) :
	_vertices{point1, point2, point3, point4} {
	if (point1 == point2 || point1 == point3 || point1 == point4 ||
		point2 == point3 || point2 == point4 || point3 == point4) throw 1;
	vertices_sort();
}

// Копирования.
Quadrangle::Quadrangle(const Quadrangle& object) {
	for (int i = 0; i < 4; i++)
		_vertices[i] = object._vertices[i];
}

// Переопределение оператора присваивания.
Quadrangle& Quadrangle::operator=(const Quadrangle& object) {
	if (&object == this) return *this;
	for (int i = 0; i < 4; i++)
		_vertices[i] = object._vertices[i];
	return *this;
}

// Переопределение оператора сравнения (оператор проверяет идентичность двух объектов).
bool Quadrangle::operator==(const Quadrangle& object) {
	for (int i = 0; i < 4; i++) {
		bool flag = false;
		for (int j = 0; j < 4; j++)
			if (_vertices[i] == object._vertices[j]) flag = true;
		if (!flag) return false;
	}
	return true;
}

// Переопределение оператора вывода (временно, возможно придется переделать как метод класса).
std::ostream& operator<<(std::ostream& fout, const Quadrangle& object) {
	fout << "Quadrangle, vertices: " << '\n';
	for (int i = 0; i < 4; i++)
		fout << object._vertices[i];
	return fout;
}

void Quadrangle::print(const double koef) const {
	std::cout << "Quadrangle, vertices:\n";
	for (int i = 0; i < 4; i++)
		_vertices[i].print(koef);
}

// Метод рисования четырёхугольника.
void Quadrangle::draw() {
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
		glVertex2f(_vertices[0].get_x(), _vertices[0].get_y());
		glVertex2f(_vertices[1].get_x(), _vertices[1].get_y());
		glVertex2f(_vertices[2].get_x(), _vertices[2].get_y());
		glVertex2f(_vertices[3].get_x(), _vertices[3].get_y());
	glEnd();
}

//Диагональ из левой верхней вершины.
Segment Quadrangle::left_diagonal() {
	Segment diagonal(_vertices[0], _vertices[2]);
	return diagonal;
}

// Диагональ из правой верхней вершины.
Segment Quadrangle::right_diagonal() {
	Segment diagonal(_vertices[1], _vertices[3]);
	return diagonal;
}

// Средняя линия.
Segment Quadrangle::middle_line() {
	Segment left_side(_vertices[0], _vertices[3]),
		right_side(_vertices[1], _vertices[2]);
	Segment mid_line(left_side.div_in_ratio(1.0, 1.0), right_side.div_in_ratio(1.0, 1.0));
	return mid_line;
}