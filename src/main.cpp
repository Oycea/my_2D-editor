#include <iostream>
#include "point/point.hpp"
#include "segment/segment.hpp"
#include "triangle/triangle.hpp"
#include "quadrangle/quadrangle.hpp"
#include "ellipse/ellipse.hpp"
#include "data_structures/dllist.hpp"
#include "data_structures/stack.hpp"
#include "menu/menu.hpp"

#ifdef __APPLE__
	#define GL_SILENCE_DEPRECATION
	#include <OpenGL/gl.h>
	#include <GLUT/glut.h>
#endif
#ifdef __linux__
	#include <GL/glut.h>
#endif
#ifdef _WIN32
	#include "../build/glut-3.7.6-bin/glut.h"
#endif

/* начальная ширина и высота окна */
GLint Width = 1280, Height = 1280;

void change_scale(const double koef) {
	auto iter = _objects_.front();
	while (iter) {
		iter->value()->zoom(koef);
		iter = iter->next();
	}
}

// Функция рисует все фигуры, которые есть в списке.
void draw_objects() {
	auto iter = _objects_.front();
	while (iter) {
		iter->value()->draw();
		iter = iter->next();
	}
}

// Функция чистит список фигур.
void clear_objects() {
	auto iter = _objects_.front();
	while (iter) {
		auto temp = iter->next();
		delete iter->value();
		iter = temp;
	}
}

// Функция чистит буфер фигур.
void clear_buff() {
	Ishape* item;
	while (true) {
		// Сигналом того, что буфер пуст служит ошибка в методе back().
		try {
			item = _buff_.back();
		} catch (...) {
			break;
		}
		delete item;
		_buff_.pop();
	}
}

// Функция удаляет объект с экрана.
void del_object() {
	if (_objects_.is_empty()) return;
	auto item = _objects_.back();
	_buff_.push(item->value());
	_objects_.remove_last();
}

// Функция возвращает удаленный объект на экран.
void return_object() {
	Ishape* item;
	// Сигналом того, что буфер пуст служит ошибка в методе back().
	try {
		item = _buff_.back();
	} catch (...) {
		return;
	}
	_objects_.push_back(item);
	_buff_.pop();
}

// Функция устанавливает белый цвет фона и рисует черную координатную сетку.
void draw_main_window() {
	glColor3ub(0, 0, 0);
	// Сначала рисуем все вертикальные полосы, по две за итерацию цикла.
	for (int i = 0; i < Width; i += _zoom_koef_) {
		if (i == 0)
			glLineWidth(2);
		else
			glLineWidth(1);

		glBegin(GL_LINES);
			glVertex2f(i, Height);
			glVertex2f(i, -Height);
		glEnd();
		
		glBegin(GL_LINES);
			glVertex2f(-i, Height);
			glVertex2f(-i, -Height);
		glEnd();
	}
	// Потом рисуем все горизонтальные полосы, по две за итерацию цикла.
	for (int i = 0; i < Height; i += _zoom_koef_) {
		if (i == 0)
			glLineWidth(2);
		else
			glLineWidth(1);

		glBegin(GL_LINES);
			glVertex2f(Width, i);
			glVertex2f(-Width, i);
		glEnd();
		
		glBegin(GL_LINES);
			glVertex2f(Width, -i);
			glVertex2f(-Width, -i);
		glEnd();
	}
}

void Display(void) {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(255, 0, 0);

	draw_main_window();
	if (_MENU_) main_menu();
	draw_objects();

	glFinish();
}

// Эта функция перерисовывает картинку через опеределенный интервал времени (в этой программе 33
// милисекунды). В ней просто дублируется часть функции Display, отвечающей за отрисовку.
void TimerMove(int value) {
	draw_main_window();
	if (_MENU_) main_menu();
	draw_objects();

	glutPostRedisplay(); 
	glutTimerFunc(33, TimerMove, 1);
}

/* Функция вызывается при изменении размеров окна */
void Reshape(GLint w, GLint h) {
	Width = w;
	Height = h;
	/* устанавливаем размеры области отображения */
	glViewport(0, 0, w, h);

	/* ортографическая проекция */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Команда устанавливает центр координат в центре отоброжаемого окна. Также масштаб координат
	// теперь приравнивается к масштабу пикселей.
	gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* Функция обрабатывает сообщения от клавиатуры */
void Keyboard(unsigned char key, int x, int y) {
	#define ESCAPE '\033'
	// Все клавиши необхожимо нажимать с включенной английской раскладкой.
	// Если нажата клавиша esc окно OpenGL закрывается и программа завершается.
	if (key == ESCAPE) {
		clear_objects();
		clear_buff();
		exit(0);
	}
	// Если нажата клавиша m происходит переключение с окна OpenGL на меню.
	if (key == 109) _MENU_ = true;
	// Если нажата клавиша z то объект удаляется.
	if (key == 122) del_object();
	// Если нажата клавиша x то объект возвращается.
	if (key == 120) return_object();
}

// Функция обрабатывает сообщения от клавиатуры.
void SpecKeyboard(int key, int x, int y) {
    // Если нажата стрелочка вверх, то увеличиваем масштаб в 2 раза, пока он не станет равен 512
    // (ограничение по максимому).
    if (key == GLUT_KEY_UP && _zoom_koef_ < Height / 4) {
    	_zoom_koef_ *= 2;
    	change_scale(2);
    } 
    // Если нажата стрелочка вниз, то уменьшаем в два раза (здесь аналогично ограничение по 
    // минимуму).
    if (key == GLUT_KEY_DOWN && _zoom_koef_ > 10) {
		_zoom_koef_ /= 2;
    	change_scale(0.5);
    } 
}

/* Главный цикл приложения */
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("2D editor");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecKeyboard);
	glutTimerFunc(33, TimerMove, 1);
	glutMainLoop();
}