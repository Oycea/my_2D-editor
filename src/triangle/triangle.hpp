#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <iostream>

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

#include "../Ishape.hpp"
#include "../point/point.hpp"
#include "../segment/segment.hpp"

class Triangle : public Ishape{
private:
	Point _vertices[3];
public:
	// Конструкторы:
	Triangle();
	Triangle(Point, Point, Point);
	// Копирования.
	Triangle(const Triangle&);
	
	// Деструктор.
	~Triangle() {};

	// Переопределение операторов.
	Triangle& operator=(const Triangle&);
	bool operator==(const Triangle&);
	friend std::ostream& operator<<(std::ostream&, const Triangle&);

	void print(const double) const override;

	// Метод возвращает тип объекта.
	std::string type() const override { return "triangle"; };

	void zoom(const double koef) override { _vertices[0].zoom(koef), _vertices[1].zoom(koef),
											_vertices[2].zoom(koef); }

	// Методе рисования треугольника.
	void draw() override;	

	// Медиана из вершины A на сторону BC.
	Segment medianA();
	// Медиана из вершины B на сторону AC.
	Segment medianB();
	// Медиана из вершины C на сторону AB.
	Segment medianC();

	// Высота из вершины A на сторону BC.
	Segment heightA();
	// Высота из вершины B на сторону AC.
	Segment heightB();
	// Высота из вершины C на сторону AB.
	Segment heightC();

	// Средняя линия.
	Segment middle_line();
};

#endif // TRIANGLE_HPP