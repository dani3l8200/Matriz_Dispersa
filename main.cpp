#include <iostream>
#include "include/Matrix.h"
int main()
{
	Matrix * s = new Matrix();
	s->inserteElement("Max", "Juan", 25, "Guatemala");
    s->inserteElement("HP", "Susan", 40, "Jutiapa");
    s->inserteElement("HP", "Susel", 50, "Jalapa");
    s->inserteElement("Walmart", "ROxana", 60, "Jalapa");
    s->inserteElement("Walmart", "Andrea", 80, "Jalapa");
    s->inserteElement("Walmart", "Sebas", 90, "Jalapa");
    s->inserteElement("HP", "andes", 100, "Guatemala");
    s->inserteElement("Max", "willy", 110, "Jalapa");
    s->inserteElement("Max", "Marcos", 1123, "Jutiapa");

	s->generateReport();
    return 0;
}
