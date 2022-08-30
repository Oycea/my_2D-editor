#define _USE_MATH_DEFINES
#include "ellipse.hpp"
#include <cmath>

// Конструктор.
Ellipse::Ellipse() : _center(Point(0, 0)), _minor_semiaxis(0), _major_semiaxis(0) {}

// Конструктор по всем полям класса.
Ellipse::Ellipse(Point center, double minor_semiaxis, double major_semiaxis) : 
	_center(center), _minor_semiaxis(minor_semiaxis), _major_semiaxis(major_semiaxis) {}

// Конструктор копирования.
Ellipse::Ellipse(const Ellipse& object) {
	_center = object._center;
	_minor_semiaxis = object._minor_semiaxis;
	_major_semiaxis = object._major_semiaxis;
}

// Переопределение оператора сравнения (оператор проверяет идентичность двух объектов класса).
bool Ellipse::operator==(const Ellipse& object) {
	if (_center == object._center && _minor_semiaxis == object._minor_semiaxis && _major_semiaxis == object._major_semiaxis) return true;
	return false;
}

// Переопределение оператора вывода (временно, может понадобится переделать как метод класса).
std::ostream& operator<<(std::ostream& fout, const Ellipse& object) {
	fout << "Ellipse, center:\n" << object._center << "minor semiaxis = " 
	<< object._minor_semiaxis << '\n' << "major semiaxis = " << object._major_semiaxis << '\n';
	return fout;
}

void Ellipse::print(const double koef) const {
	std::cout << "Ellipse, center:\n";
	_center.print(koef);
	std::cout << "minor semiaxis = " << _minor_semiaxis / koef
			  << "\nmajor semiaxis = " << _major_semiaxis / koef
			  << '\n';
}

// Переопределение оператора присваивания.
Ellipse& Ellipse::operator=(const Ellipse& object) {
	if (&object == this) return *this;
	_center = object._center;
	_minor_semiaxis = object._minor_semiaxis;
	_major_semiaxis = object._major_semiaxis;
	return *this;
}

// Метод рисования эллипса.
void Ellipse::draw() {
	int N = 100;
    double alpha = 2 * M_PI / N;
    glLineWidth(3);
	glBegin(GL_LINE_LOOP);
		// Способ рисования: разбиваем линию эллипса на 100 точек и соединяем их линией.
		for (int i = 0; i <= N + 1; i++)
			glVertex2f(_major_semiaxis * cos(alpha * i) + _center.get_x(),
					   _minor_semiaxis * sin(alpha * i) + _center.get_y());
	glEnd();
}