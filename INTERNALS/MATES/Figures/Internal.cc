#include <bits/stdc++.h> 
using namespace std;

//DEFINICIONS

#define x first
#define y second

typedef pair<double, double> punt;
typedef vector<pair<double, double>> cords;

int n=3;

//CREACIÓN DE LOS 2 PUNTOS

//Para trisecar el segmento marcado por 2 puntos:
// Creamos el vector que une los dos puntos (a, b) 
// y lo dividimos por 3 i lo aplicamos dos veces 
//sobre el punto a
void nSecar(punt A, punt B, cords &novaForma){
	punt vecAB;
	vecAB.x = (B.x - A.x);
	vecAB.y = (B.y - A.y);
	for(int i = 0; i<n-1; i++){
		novaForma.push_back(make_pair(A.x+(vecAB.x/n), A.y+(vecAB.y/n)));
		A.x += vecAB.x/n;
		A.y += vecAB.y/n;
	}
}

//CRACIÓN DE LA NUEVA FORMA 
//Para trisecar todos los vertices, usamos un bucle que cicle 
// por tdos los vertices que tiene la figura
// necesitem un programa que vagi ciclant els vertex, 
// este bucle no puede ser de repetición constante debido a que
// cada iteración del programa multiplica por dos los vertices
// anteriores
//
//Ex: con el primer triangulo:
//	(vertex0, vertex1) --> novaForma.push_back(las 2 Trisecaciones);
//	(vertex1, vertex2) --> novaForma.push_back(las 2 Trisecaciones);
//	(vertex2, vertex0) --> novaForma.push_back(las 2 Trisecaciones);
//
void createForm(int numVert, cords Forma, cords &novaForma){
	for(int j =0; j < numVert-1; j++){
		nSecar(Forma[j], Forma[j+1], novaForma);
	}
	nSecar(Forma[numVert-1], Forma[0], novaForma);
	//ara cal fer una 
}


int main(){
//OPTIMITZACIÓN                     
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

//DECLARACIÓN DE LAS VARIABLES
	int numVert;
	//cords TOT;
	cords Forma(numVert);
	cords novaForma;
	cords Area;

//CREACIÓN DE LOS PUNTOS INICIALES
	cout << "Numero de Vertices?" << endl;
	cin >> numVert;
	char anw;
	cout << "Regular? (input 'y' or 'n')" << endl;
	cin >> anw;
	if(anw=='Y'||anw=='y'){ 
	// Si es regular podemos usar las raices da la 
	// unidad para calcular la posición de los vertices
	//		(2·pi·k)
	//		_________ --> donde k va de 1 a n
	//		 numVert
		for(int k = 1; k <=numVert; k++ ){
			double angle = M_PI*2*k/numVert;
			Forma[k-1].x = cos(angle);
			Forma[k-1].y = sin(angle);
			Area.push_back(make_pair(cos(angle), sin(angle)));
		}
	}
	else if(anw == 'N' || anw == 'n'){
		for(int k = 1; k <=numVert; k++){
			cout << "Vertex " << k << ':' << endl;

			double xi, yi;
			cin >> xi >> yi;
			Forma[k-1].x = xi;
			Forma[k-1].y = yi;
			Area.push_back(make_pair(xi, yi));
		} 
	}
	else return 0;

//AREA INICIAL

	cout << "Area 1: ";
	//Shoelace formula: 
	// 1/2*(abs((sum_(i=1)^n-1, x_i * y_i+1) +x_n*y_1 - (sum_(i=1)^n-1, x_i+1 * y_i) - x_1*y_n)))
	double A1 = 0;
	for(int i = 0; i<numVert-1; ++i) A1 += Area[i].x*Area[i+1].y;
	for(int i = 0; i<numVert-1; ++i) A1 -= Area[i+1].x*Area[i].y;
	A1 += Area[numVert-1].x*Area[0].y;
	A1 -= Area[numVert-1].y*Area[0].x;
	Area.clear();
	cout << fixed << setprecision(15);
	cout << abs(A1)*0.5 << '\n';
	cout << fixed << setprecision(7);

//PUNTOS DE LAS FIGURES

	cout << '\n' <<"Graphics[Line[{";
	for(auto p : Forma) {
	cout << '{'<< p.x<<", "<<p.y<<"}, ";
		//TOT.push_back(p); // per si vui guardar tots els valors en un vector
	}
	cout << '{'<< Forma[0].x<<", "<<Forma[0].y<<"}, ";

	//ara cal crear una nova forma fent servir la 
	//forma que tenim, aquesta es crea n-sacant els
	//costats, i així obtenim els vertex de la nova figura
	int iteracions = 7;
	for(int i = 2; i <= iteracions; i++){
		createForm(numVert, Forma, novaForma);
			Forma = novaForma;
			novaForma.clear();
			numVert*=2;

		for(auto p : Forma) {
			if(i == iteracions) Area.push_back(make_pair(p.x, p.y));
			cout << '{'<< p.x<<", "<<p.y<<"}, ";
			//TOT.push_back(p); //per si vui guardar tots els valors en un vector
		}
		//Aixó es fa per tal de que les lines creades tornin al punt de inici
		if(i < iteracions)
			cout << '{'<< Forma[0].x<<", "<<Forma[0].y<<"}, ";
		else{
			cout << '{'<< Forma[0].x<<", "<<Forma[0].y<<"}";
		}
	}
	cout << "}]]" << '\n';

//AREA FINAL

	cout << '\n' << "Area final: ";
	//Shoelace formula: 
	// 1/2*(abs((sum_(i=1)^n-1, x_i * y_i+1) +x_n*y_1 - (sum_(i=1)^n-1, x_i+1 * y_i) - x_1*y_n)))
	double A2 = 0;
	for(int i = 0; i<numVert-1; ++i) A2 += Area[i].x*Area[i+1].y;
	for(int i = 0; i<numVert-1; ++i) A2 -= Area[i+1].x*Area[i].y;
	A2 += Area[numVert-1].x*Area[0].y;
	A2 -= Area[numVert-1].y*Area[0].x;
	Area.clear();
	cout << fixed << setprecision(15);
	cout << abs(A2)*0.5 << '\n';
}