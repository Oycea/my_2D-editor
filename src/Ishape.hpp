#ifndef ISHAPE_HPP
#define ISHAPE_HPP

#include <string>

class Ishape {
public:
	virtual ~Ishape() {};

	void virtual print(const double) const = 0;
	std::string virtual type() const = 0;
	void virtual zoom(const double) = 0;
	void virtual draw() = 0;
};

#endif // ISHAPE_HPP
