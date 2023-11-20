/* ¿No te pasa que tienes un montón de cosas por hacer y no sabes por cual empezar? 
¡En este programa introduzca las cosas que tiene por hacer, escoga cuál de ellas quiere priorizar 
y el resto se ordenarán aleatoriamente!*/

/* Además puedes crear un planing de varios dias en el que programas varios eventos siguiendo la dinámica anterior */

#include <iostream>
#include <vector>
#include <string>


//Esto también es un template?
#include <random> //
using namespace std;


//prototipos

void mix_cosas(vector<string> &cosas, int veces_mix, default_random_engine &generator);


//Clases
template <typename T>
class evento {
	T posicion_atri;
	vector<string> acciones_atri;

public:
	evento() {
		acciones_atri.clear();
		int posicion = 0;
	}
	evento(T posicion, vector<string> acciones) {
		acciones_atri = acciones;
		posicion_atri = posicion;
	}

	void get() {

	
	int i;
	cout << "\n\n\nLa posicion del evento es: " << posicion_atri << "\n";

	cout << "Las cosas que quieres hacer son: \n";

	for (i = 0; i < acciones_atri.size(); i++) {
		cout << (i+1) <<": " << acciones_atri[i] <<"\n";
	}
	}

	
};





int main(){
	//Inicio un generador de números aleatorios
	default_random_engine generator;

	vector<evento<string>> plan_futuro; //Me hago un vector de eventos. 99 Cambiar esto
	string posicion = ""; // 99 Cambiar esto
	plan_futuro.clear(); //Limpiamos el vector
	int cant_eventos = 0, i, e;

	do {
		cout << "\nCuantos eventos quieres planificar.\n";
		cin >> cant_eventos;
		cin.ignore();  // Limpia el buffer de entrada.
	} while (0 > cant_eventos);



	evento<string> *pq = new evento<string>[cant_eventos]; //99 Cambiar esto
	for (e = 0; e < cant_eventos; e++) {

		cout << "\nCual es la posicion de tu evento: \n";
		cin >> posicion;
		cin.ignore();  // Limpia el buffer de entrada.

		//Variables
		int cant_links = 0;
		string cadena_entrada = "";
		vector<string> cosas;
		cosas.clear(); //Limpiamos


		//Escojo la cantidad de cosas que quiero hacer
		do {
			cout << "\nCuantas cosas quieres hacer? (Tienen que ser mas de dos)\n";
			cin >> cant_links;
			cin.ignore();  // Limpia el buffer de entrada.
		} while (cant_links < 3);

		//Creo una distribución de probabilidad para el número de veces que mezcla.
		uniform_int_distribution<int> distribution_veces_mix(cant_links, (cant_links * 2)); //Mezclaremos de cant_links a 2*cant_links veces

		cout << "Que cosas quieres hacer?\n";

		//Relleno de enlaces
		for (i = 0; i < cant_links; i++) {
			cout << "\nIntroduce la cosa que quieres hacer:\n" << (i + 1) << ": ";
			getline(cin, cadena_entrada);
			cosas.push_back(cadena_entrada);
		}


		//Mezclamos las cosas. A la función le paso el vector, un entero que me genera aleatoriamente y el generador para usarlo dentro de la función.
		mix_cosas(cosas, distribution_veces_mix(generator), generator);

		//Una vez mezcladas, las mostramos.
		for (i = 0; i < cant_links; i++) {

			cout << (i + 1) << ": " << cosas[i] << "\n";

		}
		//Hacemos los pushback.
		pq[e] = evento<string>(posicion, cosas); //99 Cambiar esto.
		plan_futuro.push_back(pq[e]);
	}//Ya lo hemos hecho todo

	for (e = 0; e < cant_eventos; e++) {
		plan_futuro[e].get();
	}


	delete[] pq; //Liberar memoria
	return 0;
}


void mix_cosas(vector<string>& cosas, int veces_mix, default_random_engine &generator)
{

	int i = 0, link_priorizar=0;
	//Espacio auxiliar
	string primera = "";

	cout << "Quieres priorizar algun sitio web? (indica el indice del sitio)";
	cin >> link_priorizar;
	cin.ignore();  // Limpia el buffer de entrada.

	//Guardamos aquello que priorizamos.
	primera = cosas[link_priorizar - 1];
	
	//Eliminamos ese elemento del vector.
	cosas.erase(cosas.begin() +  (link_priorizar - 1));



	

	//Mezclamos el resto de elementos.
	for (i = 0; i < veces_mix; i++) {

		int rand1 = 0, rand2 =0;
		string aux;

		//Creamos una nueva distribución para escoger qué dos elementos queremos intercambiar de posición.

		uniform_int_distribution<int> distribution(0, (cosas.size() - 1)); //Mezclaremos de una a seis veces

		rand1 = distribution(generator);

		do {
			rand2 = distribution(generator);
		} while (rand1 == rand2); //Queremos que los dos rand sean diferentes

		//Intercambiamos los valores
		aux = cosas[rand1];
		cosas[rand1] = cosas[rand2];
		cosas[rand2] = aux;
	}
	//Insertamos el valor priorizado al principio del vector.
	cosas.insert(cosas.begin(), primera);

	



}


