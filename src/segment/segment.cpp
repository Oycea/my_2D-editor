#include "segment.hpp"

// Переопределение оператора сравнения (оператор проверяет идентичность двух объектов класса).
bool Segment::operator==(const Segment& object) {
	if (_point1 == object._point1 && _point2 == object._point2) return true;
	if (_point1 == object._point2 && _point2 == object._point1) return true;
	return false;
}

// Переопределение оператора вывода (временно, может понадобится переделать как метод класса).
std::ostream& operator<<(std::ostream& out, const Segment& object) {
	out << "Segment, points:\n" << object._point1 << object._point2;
	return out;
}

// Переопределение оператора присваивания.
Segment& Segment::operator=(const Segment& object) {
	if (&object == this) return *this;
	_point1 = object._point1;
	_point2 = object._point2;
	return *this;
}

// Функция проверяет пересекаются ли отрезки.
bool Segment::intersect(const Segment& sec) const {
	#define SIGN(x) (((x) < 0) ? -1 : ((x) > 0) ? 1 : 0)

	double comp_z1 = (_point2.get_x() - _point1.get_x()) * (sec._point1.get_y() - _point1.get_y())
		- (_point2.get_y() - _point1.get_y()) * (sec._point1.get_x() - _point1.get_x());
	double comp_z2 = (sec._point2.get_y() - _point1.get_y()) * (_point2.get_x() - _point1.get_x())
		- (sec._point2.get_x() - _point1.get_x()) * (_point2.get_y() - _point1.get_y());

	if (SIGN(comp_z1) == SIGN(comp_z2) && comp_z1 * comp_z2 != 0) return false;

	comp_z1 = (sec._point2.get_x() - sec._point1.get_x()) * (_point2.get_y() - sec._point1.get_y())
		- (sec._point2.get_y() - sec._point1.get_y()) * (_point2.get_x() - sec._point1.get_x());
	comp_z2 = (_point1.get_y() - sec._point1.get_y()) * (sec._point2.get_x() - sec._point1.get_x())
		- (_point1.get_x() - sec._point1.get_x()) * (sec._point2.get_y() - sec._point1.get_y());

	if (SIGN(comp_z1) == SIGN(comp_z2) && comp_z1 * comp_z2 != 0) return false;
	return true;
}

void Segment::print(const double koef) const {
	std::cout << "Segment, points:\n";
	_point1.print(koef);
	_point2.print(koef);
}

// Метод рисования отрезка.
void Segment::draw() {
	glLineWidth(3);
	glBegin(GL_LINES);
		glVertex2f(_point1.get_x(), _point1.get_y());
		glVertex2f(_point2.get_x(), _point2.get_y());
	glEnd();
}

// Точка, делящая отрезок в отношении part1/part2.
Point Segment::div_in_ratio(const double part1, const double part2) {
	double ratio = part1 / part2;
	double x, y;
	x = (_point1.get_x() + ratio * _point2.get_x()) / (1 + ratio);
	y = (_point1.get_y() + ratio * _point2.get_y()) / (1 + ratio);
	Point div(x, y);
	return div;
}