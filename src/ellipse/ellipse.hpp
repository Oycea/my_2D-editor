#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

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

class Ellipse : public Ishape {
private:
    Point _center;
    double _minor_semiaxis, _major_semiaxis;
public:
    // Конструкторы.
    Ellipse();
    // В конструкторе есть баг.
    Ellipse(Point, double, double);
    // Копирования.
    Ellipse(const Ellipse&);

    //Деструктор.
    ~Ellipse() {}

    // Переадресовка операторов.
    Ellipse& operator=(const Ellipse&);
    bool operator==(const Ellipse&);
    friend std::ostream& operator<<(std::ostream&, const Ellipse&);

    void print(const double) const override;

    // Метод возвращает тип объекта.
    std::string type() const override { return std::string("ellipse"); };

    void zoom(const double koef) override { _minor_semiaxis *= koef, _major_semiaxis *= koef,
                                            _center.zoom(koef); }

    // Метод рисования эллипса.
    void draw() override;
};

#endif // ELLIPSE_HPP

