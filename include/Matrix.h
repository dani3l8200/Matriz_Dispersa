#ifndef MATRIX_H
#define MATRIX_H
#include <string>
using namespace std;
class nodeMatrix{
	public:
		nodeMatrix *up, *down,*next,*prev,*start,*last;
		int dato;
		string prueba;

};

class Matrix
{
	public:
		Matrix();
		nodeMatrix * newNode(string,int);
		void inserteElement(string,string,int,string);
		nodeMatrix * createY(string);
		nodeMatrix * createX(string);
		nodeMatrix * searchY(string,nodeMatrix *);
		nodeMatrix * searchX(string,nodeMatrix *);
		bool VerificarDataY(string,nodeMatrix*,nodeMatrix*);
		bool VerificarDataX(string,nodeMatrix*,nodeMatrix*);
		void generateReport();
		void printX();
		void printY();

		~Matrix();



	private:
		 nodeMatrix * header;

};

#endif // MATRIX_H
