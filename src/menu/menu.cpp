#include "../point/point.hpp"
#include "../segment/segment.hpp"
#include "../triangle/triangle.hpp"
#include "../quadrangle/quadrangle.hpp"
#include "../ellipse/ellipse.hpp"
#include "../data_check/data_check.hpp"
#include "menu.hpp"
#include <iostream>
#include <string>

#ifdef __APPLE__
	#define CLEAR_CONSOLE "clear"
#endif
#ifdef __linux__
	#define CLEAR_CONSOLE "clear"
#endif
#ifdef _WIN32
	#define CLEAR_CONSOLE "cls"
#endif

// Переменная отвечает за переопредление текущего окна. Если она равна true - вызывается
// окно консоли с меню. Если она равна false - будет вызвано окно GLUT.
bool _MENU_ = true;

List<Ishape*> _objects_;

Stack<Ishape*> _buff_;

int _zoom_koef_ = 10;

// Функция считываем нажатие клавиши enter пользователем.
void read_enter() {
    // Так как нельзя запретить пользователю нажимать друге клавиши, как метод защиты счтываем
    // все что введет пользователь.
    std::string buff;
    getline(std::cin, buff);
}

Ishape* input_point() {
	double x, y;
	std::cout << "Enter coordinates\nX: ";
    check_value(x);
	std::cout << "Y: ";
    check_value(y);
	std::cin.get();
    Ishape* object = new Point(x, y);
    object->zoom(_zoom_koef_);
	return object;
}

Ishape* input_segment() {
	double x1, y1, x2, y2;
    while (true) {
    	std::cout << "Enter the coordinates start of segment\nX: ";
        check_value(x1);;
    	std::cout << "Y: ";
        check_value(y1);
    	std::cout << "Enter the coordinates end of segment\nX: ";
        check_value(x2);
    	std::cout << "Y: ";
        check_value(y2);
    	std::cin.get();
        Ishape* object;
        try {
            object = new Segment(Point(x1, y1), Point(x2, y2));
        } catch (...) {
            std::cout << "Error: matching points\n";
            continue;
        }
        object->zoom(_zoom_koef_);
        return object;
    }
}

Ishape* input_triangle() {
	double x, y;
	Point vertices[3];
    while (true) {
    	for (int i = 0; i < 3; i++) {
    		std::cout << "Enter the coordinates of the vertex " << i + 1 << "\nX: ";
            check_value(x);
    		std::cout << "Y: ";
            check_value(y);
    		vertices[i] = Point(x, y);
    	}
    	std::cin.get();
        Ishape* object;
        try {
            object = new Triangle(vertices[0], vertices[1], vertices[2]);
        } catch (...) {
            std::cout << "Error: matching points\n";
            continue;
        }
        object->zoom(_zoom_koef_);
        return object;
    }
}

Ishape* input_quadrangle() {
	double x, y;
	Point vertices[4];
    while (true) {
    	for (int i = 0; i < 4; i++) {
    		std::cout << "Enter the coordinates of the vertex " << i + 1 <<  "\nX: ";
            check_value(x);
    		std::cout << "Y: ";
            check_value(y);
    		vertices[i] = Point(x, y);
    	}
    	std::cin.get();
        Ishape* object;
        try {
            object = new Quadrangle(vertices[0], vertices[1], vertices[2], vertices[3]);
        } catch (...) {
            std::cout << "Error: matching points\n";
            continue;
        }
        object->zoom(_zoom_koef_);
        return object;
    }
}

Ishape* input_ellipse() {
	double x, y;
	double minor_semiaxis, major_semiaxis;
	std::cout << "Enter the coordinates of the center of ellipse\nX: ";
    check_value(x);
	std::cout << "Y: ";
    check_value(y);
	std::cout << "Enter the minor semiaxis: ";
    check_value(minor_semiaxis);
	std::cout << "Enter the major semiaxis: ";
    check_value(major_semiaxis);
	std::cin.get();
    Ishape* object = new Ellipse(Point(x, y), minor_semiaxis, major_semiaxis);
    object->zoom(_zoom_koef_);
    return object;
}

int choise_triangle_geometry_menu() {
    int choice;
    system(CLEAR_CONSOLE);
    std::cout << "Triangle Geometry Menu\n"
              << "1 - Median from vertex 1\n"
              << "2 - Median from vertex 2\n"
              << "3 - Median from vertex 3\n"
              << "4 - Height from vertex 1\n"
              << "5 - Height from vertex 2\n"
              << "6 - Height from vertex 3\n"
              << "7 - Middle line\n"
              << "8 - Quit\n"
              << "Please choose: ";
    input_menu_command(choice);
    // Убираем мусор из потока.
    std::cin.get();
    return choice;
}

int choise_quadrangle_geometry_menu() {
    int choice;
    system(CLEAR_CONSOLE);
    std::cout << "Quadrangle Geometry Menu\n"
              << "1 - Left diagonal\n"
              << "2 - Righr diagonal\n"
              << "3 - Middle line\n"
              << "4 - Quit\n"
              << "Please choose: ";
    input_menu_command(choice);
    // Убираем мусор из потока.
    std::cin.get();
    return choice;
}

int choise_geometry_menu() {
    int choice;
    system(CLEAR_CONSOLE);
    std::cout << "Geometry Menu\n";
    auto iter = _objects_.front();
    int count = 1;
    while (iter) {
        std::cout << count << ". ";
        iter->value()->print(_zoom_koef_);
        std::cout << '\n';
        ++count;
        iter = iter->next();
    }
    std::cout << "Please choose: ";
    input_menu_command(choice);
    // Убираем мусор из потока.
    std::cin.get();
    return choice;
}

int choise_add_shape_menu() {
    int choice;
    system(CLEAR_CONSOLE);
    std::cout << "Add Shape Menu\n"
              << "1 - Add Point\n"
              << "2 - Add Segment\n"
              << "3 - Add Triangle\n"
              << "4 - Add Quadrangle\n"
              << "5 - Add Ellipse\n"
              << "6 - Quit\n"
              << "Please choose: ";
    input_menu_command(choice);
    // Убираем мусор из потока.
    std::cin.get();
    return choice;
}

// Вывод пунктов второго меню и выбор пункта.
int choise_main_menu() {
    int choice;
    system(CLEAR_CONSOLE);
    std::cout << "Main Menu\n"
              << "1 - Add item\n"
              << "2 - Geometry\n"
              << "3 - Quit\n"
              << "Please choose: ";
    input_menu_command(choice);
    // Убираем мусор из потока.
    std::cin.get();
    return choice;
}

void triangle_geometry_menu(Triangle* object) {
    int choice;
    while (true) {
        choice = choise_triangle_geometry_menu();
        switch (choice) {
            case 1:
                _objects_.push_back(new Segment(object->medianA()));
                std::cout << "Press enter...";
                read_enter();
                break;
            case 2:
                _objects_.push_back(new Segment(object->medianB()));
                std::cout << "Press enter...";
                read_enter();
                break;
            case 3:
                _objects_.push_back(new Segment(object->medianC()));
                std::cout << "Press enter...";
                read_enter();
                break;
            case 4:
                _objects_.push_back(new Segment(object->heightA()));
                std::cout << "Press enter...";
                read_enter();
                break;
            case 5:
                _objects_.push_back(new Segment(object->heightB()));
                std::cout << "Press enter...";
                read_enter();
                break;
            case 6:
                _objects_.push_back(new Segment(object->heightC()));
                std::cout << "Press enter...";
                read_enter();
                break;
            case 7:
                _objects_.push_back(new Segment(object->middle_line()));
                std::cout << "Press enter...";
                read_enter();
                break;
            case 8:
                system(CLEAR_CONSOLE);
                return;
            default:
                std::cout << "No such item\nPress enter...";
                read_enter();
                continue;
        }
    }
}

void quadrangle_geometry_menu(Quadrangle* object) {
    int choice;
    while (true) {
        choice = choise_quadrangle_geometry_menu();
        switch (choice) {
            case 1:
                _objects_.push_back(new Segment(object->left_diagonal()));
                std::cout << "Press enter...";
                read_enter();
                break;
            case 2:
                _objects_.push_back(new Segment(object->right_diagonal()));
                std::cout << "Press enter...";
                read_enter();
                break;
            case 3:
                _objects_.push_back(new Segment(object->middle_line()));
                std::cout << "Press enter...";
                read_enter();
                break;
            case 4:
                system(CLEAR_CONSOLE);
                return;
            default:
                std::cout << "No such item\nPress enter...";
                read_enter();
                continue;
        }
    }
}

void geometry_menu() {
    int choice;
    choice = choise_geometry_menu();
    Ishape* object;
    try {
        object = _objects_.at(choice - 1);
    } catch (...) {
        std::cout << "Error: invalid index\nPress enter...";
        read_enter();
        return;
    }

    if (object->type() == "point") {
        std::cout << "No geometry for the point\n";
        read_enter();
        return;
    } else if (object->type() == "segment") {
        std::cout << "No geometry for the segment\n";
        read_enter();
        return;
    } else if (object->type() == "triangle") {
        triangle_geometry_menu(dynamic_cast<Triangle*>(object));
        return;
    } else if (object->type() == "quadrangle") {
        quadrangle_geometry_menu(dynamic_cast<Quadrangle*>(object));
        return;
    } else if (object->type() == "ellipse") {
        std::cout << "No geometry for the ellipse\n";
        read_enter();
        return;
    }
}

void add_shape_menu() {
    int choice;
    Ishape* object;
    while (true) {
        choice = choise_add_shape_menu();
        switch (choice) {
            case 1:
            	object = input_point();
            	_objects_.push_back(object);
                break;
            case 2:
                object = input_segment();
            	_objects_.push_back(object);
                break;
            case 3:
                object = input_triangle();
            	_objects_.push_back(object);
                break;
            case 4:
                object = input_quadrangle();
            	_objects_.push_back(object);
                break;
            case 5:
                object = input_ellipse();
            	_objects_.push_back(object);
                break;
            case 6:
                system(CLEAR_CONSOLE);
                return;
            default:
                std::cout << "No such item\nPress enter...";
                read_enter();
                continue;
        }
    }
}

void main_menu() {
    int choice;
    while (true) {
        choice = choise_main_menu();
        switch (choice) {
            case 1:
                add_shape_menu();
                break;
            case 2:
                geometry_menu();
                break;
            case 3:
                _MENU_ = false;
                system(CLEAR_CONSOLE);
                return;
            default:
                std::cout << "No such item\nPress enter...";
                read_enter();
                continue;
        }
    }
}