#ifndef POINT_HPP
#define POINT_HPP

#include<iostream>
#include "../Ishape.hpp"

#ifdef __APPLE__
	#define GL_SILENCE_DEPRECATION
	#include <OpenGL/gl.h>
	#include <GLUT/glut.h>
#endif
#ifdef __linux__
	#include <GL/glut.h>
#endif
#ifdef _WIN32
	#include "../../build/glut-3.7.6-bin/glut.h"
#endif

class Point : public Ishape {
private:
	double _x, _y;
public:
	// Конструкторы.
	Point() : _x(0), _y(0) {};
	Point(double x, double y) : _x(x), _y(y) {};
	// Копирования.
	Point(const Point& object) : _x(object._x), _y(object._y) {};

	// Деструктор.
	~Point() {}

	// Переопределение операторов.
	bool operator==(const Point&);
	Point& operator=(const Point&);
	friend std::ostream& operator<<(std::ostream&, const Point&);

	// Методы гетеры.
	double get_x() const { return _x; }
	double get_y() const { return _y; }

	void print(const double) const override;

	// Метод возвращает тип объекта.
	std::string type() const override { return "point"; };

	void zoom(const double koef) override { _x *= koef; _y *= koef; }

	// Метод рисования точки.
	void draw() override;
};

#endif // POINT_HPP