#ifndef QUADRILATERAL_HPP
#define QUADRILATERAL_HPP

#include "../segment/segment.hpp"
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

class Quadrangle : public Ishape {
private:
	// Метод сортирует вершины четырехугольника по часовой стрелке.
	// !!note!! В методе баг, в случае с вогнутыми четырехугольниками, может построить не тот
	// четырехугольник, что задумывал юзер.
	void vertices_sort();

	Point _vertices[4];
public:
	// Конструкторы.
	Quadrangle();
	// В конструкторе есть баг.
	Quadrangle(Point, Point, Point, Point);
	// Копирования.
	Quadrangle(const Quadrangle&);

	// Деструктор.
	~Quadrangle() {}

	// Переадресовка операторов.
	Quadrangle& operator=(const Quadrangle&);
	bool operator==(const Quadrangle&);
	friend std::ostream& operator<<(std::ostream&, const Quadrangle&);

	void print(const double) const override;

	// Метод возвращает тип объекта.
	std::string type() const override { return "quadrangle"; };

	void zoom(const double koef) override { _vertices[0].zoom(koef), _vertices[1].zoom(koef),
											_vertices[2].zoom(koef), _vertices[3].zoom(koef); }

	// Метод рисования черырёхугольника.
	void draw() override;

	// Диагональ из левой верхней вершины.
	Segment left_diagonal();
	// Диагональ из из правой верхней вершины.
	Segment right_diagonal();

	// Средняя линия.
	Segment middle_line();
};

#endif // QUADRILATERAL_HPP
