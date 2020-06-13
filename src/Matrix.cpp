#include "Matrix.h"
#include <string>
#include <cstring>
#include<stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;
Matrix::Matrix()
{
	header = newNode("Admin",-1);
}
nodeMatrix * Matrix::newNode(string info,int data){
	nodeMatrix * temp;
	temp = new nodeMatrix;
	temp->dato = data;
	temp->prueba = info;
	temp->down = nullptr;
	temp->next = nullptr;
	temp->prev = nullptr;
	temp->last = nullptr;
	temp->start = nullptr;
	temp->up = nullptr;
	return temp;
}

nodeMatrix * Matrix::createY(string datoy){
	nodeMatrix * temp,*p;
	temp = newNode(datoy,-1);
	p = header;

	while(p->down != nullptr){
			p = p->down;
	}
	p->down = temp;
	temp->up = p;

	return temp;
}

nodeMatrix * Matrix::createX(string datox){
	nodeMatrix * temp, *p;
	temp = newNode(datox,-1);
	p = header;
	while(p->next != nullptr){
				p = p->next;
	}
	p->next = temp;
	temp->prev = p;

	return temp;
}

nodeMatrix * Matrix::searchX(string datox,nodeMatrix * p){
	nodeMatrix * temp = p;
	while(temp != nullptr){

		if(temp->prueba == datox)
			return temp;
		temp = temp->next;
	}
	return nullptr;
}

nodeMatrix * Matrix::searchY(string datoy,nodeMatrix * p){
	nodeMatrix * temp = p;
	while(temp != nullptr){

		if(temp->prueba == datoy)
			return temp;
		temp = temp->down;
	}
	return nullptr;
}

void  Matrix::inserteElement(string datoy,string dato,int index,string datox){
	nodeMatrix * nodeData,* nodeDatay, * nodeDatax;

	nodeData = newNode(dato,index);

	nodeDatay = searchY(datoy,header);

	nodeDatax = searchX(datox,header);

	if(nodeDatax == nullptr)
		nodeDatax = createX(datox);
	if (nodeDatay == nullptr)
		nodeDatay = createY(datoy);

		//Insertar al Inicio datoY
	if(nodeDatax->down == nullptr){

		nodeDatax->down = nodeData;
		nodeData->up =nodeDatax;
	}

	else if(nodeDatay->down == nullptr){

		nodeMatrix * temp = nodeDatax->down;

		while(temp->down != nullptr){
			temp = temp->down;
		}

		if(!VerificarDataY(datoy,temp,nodeData)){
			temp->down = nodeData;
			nodeData->up = temp;
		}

	}
	else{
			nodeMatrix * temp = nodeDatax;
			do{
				temp = temp->down;

				if(!VerificarDataY(datoy,temp,nodeData)){
					nodeMatrix * auxY = temp->prev;
					while(auxY->prev != nullptr){
						auxY = auxY->prev;
					}
					while(auxY->up != nullptr){
						if(auxY->prueba == datoy){
							nodeData->down = temp;
							nodeData->up = temp->up;

							temp->up->down = nodeData;
							temp->up = nodeData;
							break;
						}
						auxY = auxY->up;
					}
				}

			}while(temp->down != nullptr && nodeData->up == nullptr);

		  if(nodeData->up == nullptr && nodeData->start == nullptr){
			temp->down = nodeData;
			nodeData->up = temp;
		  }
	}

	if(nodeData->start != nullptr){
		return;
	}

		//Insertar al inicio datoX
	if(nodeDatay->next == nullptr){

		nodeDatay->next = nodeData;
		nodeData->prev = nodeDatay;
	}
	else if(nodeDatax->next == nullptr){
		nodeMatrix * temp = nodeDatay->next;
		while(temp->next != nullptr){
			temp = temp->next;
		}
		if(!VerificarDataX(datox,temp,nodeData)){
			temp->next = nodeData;
			nodeData->prev = temp;
		}
	}

	else{
		nodeMatrix * temp = nodeDatay;
		do{
			temp = temp->next;
			if(!VerificarDataX(datox,temp,nodeData)){
				nodeMatrix * auxX = temp->up;

				while(auxX->up != nullptr){

					auxX = auxX->up;

				}
				while(auxX->prev !=nullptr){
					if(auxX->prueba == datox){
						nodeData->next = temp;
						nodeData->prev = temp->prev;

						temp->prev->next = nodeData;
						temp->prev = nodeData;
						break;
					}
					auxX = auxX->prev;
				}

			}

		}while(temp->next != nullptr && temp->prev == nullptr);
		if(nodeData->prev == nullptr && nodeData->start == nullptr){
			temp->next = nodeData;
			nodeData->prev = temp;
		}
	}


}

void Matrix::printX(){
 nodeMatrix * p = header;
 while(p->next != nullptr){
	cout<<p->prueba<<endl;
	p = p->next;
 }
 cout << p->prueba<<endl;
}

void Matrix::printY(){
	nodeMatrix * p = header;
	while(p->down != nullptr){

		cout<<p->prueba<<endl;
		p = p->down;
	}
	cout << p->prueba<<endl;
}

bool Matrix::VerificarDataY(string dataY,nodeMatrix * p,nodeMatrix * Data){
	nodeMatrix * temp  = p->prev;
	while(temp->prev != nullptr){
		temp = temp->prev;
	}
	if(temp->prueba == dataY){

		while(p->last != nullptr){
			p = p->last;
		}
		p->last = Data;
		Data->start = p;
		return true;
	}
	return false;
}

bool Matrix::VerificarDataX(string dataX,nodeMatrix * p,nodeMatrix * Data){
	nodeMatrix * temp  = p->up;
	while(temp->up != nullptr){
		temp = temp->up;
	}
	if(temp->prueba == dataX){
		while(p->last != nullptr){
			p = p->last;
		}
		p->last = Data;
		Data->start = p;

		return true;

	}
	return false;
}

void Matrix::generateReport(){
	if(header->down != nullptr && header->next != nullptr){
		string report2;
		report2 += "digraph Matrix{\n\t";
		report2 += "graph[bgcolor=black, fontcolor =white,label=\"USUARIOS\", fontsize = 25];\n\t";
		report2 += "edge[color = white];\n\t nodesep = 0.7;\n\t ranksep = 0.7;\n\t node[shape= box];\n\t Mt[label=\"";
		report2 +=  header->prueba + "\", width = 1.5,style=filled, fillcolor = firebrick1, group = 1];\n\t";

		int aux = 1;

		nodeMatrix *temp;
			temp = header->down;

		report2 += "//filas\n\tU0 [label = \""  + temp->prueba +"\",pos=\"5.3, 3.5!\", width = 1.5, style = filled, fillcolor = aquamarine2, group=1];\n\t";
		temp = temp->down;
		while(temp != nullptr){
			report2 += "U" + to_string(aux) + "[label = \""  + temp->prueba + "\", width = 1.5, style = filled, fillcolor = aquamarine2, group=1];\n\t";
			aux++;
			temp = temp->down;
		}
		report2 += "\n\t//Linkear filas\n\t";

		aux = 0;

		temp = header->down;
		while(temp->down != nullptr){
			report2 += "U" + to_string(aux) + "->";
			aux++;
			temp = temp->down;
		}

		report2 += "U" + to_string(aux) + "[dir=both];\n\t";

		report2 +=  "\t// Columnas\n\t";

		aux = 0;

		temp = header->next;
		while(temp != nullptr){
			report2 += "A" + to_string(aux) + "[label = \""  + temp->prueba + "\", width = 1.5, style = filled, fillcolor = azure1, group=" + to_string(temp->dato + 2) + "];\n\t";
			aux++;
			temp = temp->next;
		}

		report2 +=  "// Linkear columnas\n\t";
		aux = 0;
		temp = header->next;
		while(temp->next != nullptr){
			report2 += "A" + to_string(aux) + "->";
			aux++;
			temp = temp->next;
		}
		report2 += "A" + to_string(aux) + "[dir=both];\n\t";

		   /* -------------------- Link the principal nodes to the header -------------------- */

		report2 += "// Nodo raiz con primera fila y columna\n\t";
		report2 += "Mt -> U0 [dir = both];\n\tMt -> A0 [dir=both];\n\n\t";

		aux = 0;
		temp = header->next;
		string columns;
		while(temp != nullptr){
			columns += "A" + to_string(aux) + "; ";
			aux++;
			temp = temp->next;
		}

		report2 += "\t// Colocar columnas de manera alineada\n";
		report2 += "\t {rank = same; Mt; " + columns + "} \n\t";

		int xPos = 0, yPos = 0;

		report2 += "\t// Creation of nodes\n\t";

		temp = header->down;

		while(temp != nullptr){
			report2 += "\t// Fila " + to_string(yPos) + "\n";
			nodeMatrix *p_temp = temp->next;
			xPos = 0;
			while(p_temp != nullptr){

				report2 += "\tN" + to_string(p_temp->dato) + "_L" + p_temp->prueba + " [label=\"" + p_temp->prueba + "\n" + to_string(p_temp->dato) +"\",  width=1.5, group =" + to_string(p_temp->dato + 2) + ", style = filled, fillcolor = burlywood2];\n";

				p_temp = p_temp->next;
				xPos++;
			}
			report2 += "\n\n";
			temp = temp->down;
			yPos++;
		}


		xPos = 0; yPos = 0;
		temp = header->down;
		while(temp != nullptr){
			report2 +=  "\t// Linkeando Fila " + to_string(yPos) + "\n\tU" + to_string(yPos);
			string rankSame = "U" + to_string(yPos);
			nodeMatrix * p_temp = temp->next;
			while(p_temp != nullptr){
				report2 += "->N" + to_string(p_temp->dato) + "_L" + p_temp->prueba + "";
				rankSame += "; N"+ to_string(p_temp->dato) +"_L" + p_temp->prueba;

				p_temp = p_temp->next;

			}
			report2 += " [constraint=false,dir=both];\n\n";
			report2 += "{rank = same; " + rankSame + "}";
			report2 += "\n\n";
			temp = temp->down;
			yPos++;

		}
		xPos = 0;
		temp = header->next;
		while(temp != nullptr){
			report2 +=  "\t// Linkeando Columna " + to_string(xPos) + "\n";
			report2 +=  "\tA" + to_string(xPos);
			nodeMatrix * p_temp = temp->down;
			while(p_temp != nullptr){
				report2 += "->N" + to_string(p_temp->dato) +"_L" + p_temp->prueba + "";

				p_temp = p_temp->down;
			}
			report2 += "[dir=both]";
			report2 += ";\n\n";

			temp = temp->next;

			xPos++;
		}
		report2 += "}";

		char cstr[report2.size() + 1];
	strcpy(cstr, &report2[0]);
       FILE* pFile;

		pFile = fopen("report2.dot","w");

		fputs(cstr ,pFile);

		fclose(pFile);

    system("dot -Tpdf report2.dot  -o report2.pdf");
    system("report2.pdf");

	}



}

Matrix::~Matrix()
{

}
