#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
using namespace std;

const int HUMANO = 1;
const int MAQUINA = 2;
const int MAX = 8;
const int TAMBARAJA = 40;
typedef int tCartasPorAparecer[MAX];//array contador de cartas restantes en el mazo
typedef int tMazoCartas[TAMBARAJA];
typedef struct
{
	int cont;
	tMazoCartas cartas;
}tConjuntoCartas;



int menu();
void cargarFichero(ifstream & fich_entrada);
int generarMaxCartas(int  max_cartas);
int determinaGanador(double puntosJugador, double puntosMaquina);
void ejecutarModoA(ifstream & fich_entrada, double & puntosJugador, double & puntosMaquina, int & ganador);
double modoA(ifstream & fich_entrada, int max_cartas);
double Valores(int carta_robada);
void mostrarGanador(int ganador);
void ejecutarModoB(ifstream & fich_entrada, double & puntosMaquina, double & puntosJugador, int & ganador);
double modoBhumano(ifstream & fich_entrada, int max_cartas, double puntosJugador);
double modoBmaquina(ifstream & fich_entrada, int max_cartas, double puntosJugador);
void ejecutarModoC(ifstream& fich_entrada, tCartasPorAparecer & cartas_restantes, string nombre_fich, double & puntosJugador, double & puntosMaquina, int& ganador);
void modoChumano(ifstream & fich_entrada, tCartasPorAparecer cartas, double & puntos);
void modoCmaquina(ifstream & fich_entrada, tCartasPorAparecer cartas, double puntosJugador, double & puntos);
void iniciarPorAparecer(ifstream & fich_entrada, tCartasPorAparecer cartas);
void reducirCartasMazo(tCartasPorAparecer cartas, int &carta_robada);
void inicializa(tConjuntoCartas & cartas);
void sacar(tConjuntoCartas & cartas, int & carta);
void incluir(tConjuntoCartas & cartas, int & carta);
void crearMazo(tConjuntoCartas & mazo);
void mostrarMazo(tConjuntoCartas & mazo);
void barajar(tConjuntoCartas & mazo);
void ejecutarModoD(tCartasPorAparecer& cartas_restantes, double & puntosJugador, double & puntosMaquina);
void modoDhumano(tConjuntoCartas& mazo, tCartasPorAparecer cartas, tConjuntoCartas& cartasHumano, double& puntos);
void modoDmaquina(tConjuntoCartas& mazo, tCartasPorAparecer cartas, double puntosJugador, tConjuntoCartas& cartasMaquina, double& puntos);
bool comprobarPuntosJug(double puntosJugador, double puntos);
bool Seguir();
bool esProbablePasarse(double puntosMaquina, const tCartasPorAparecer cartas);


int main()
{
	int opcion, ganador = 0, carta = 0;
	double puntosJugador = 0, puntosMaquina = 0;
	string nombre_fich;
	tCartasPorAparecer cartas_restantes;
	srand(time(nullptr));

	opcion = menu();
	while (opcion != 0)
	{
		if (opcion == 4)
		{
			ejecutarModoD(cartas_restantes, puntosJugador, puntosMaquina);
		}

		else
		{
			ifstream fich_entrada;
			if (opcion == 1)
			{
				cargarFichero(fich_entrada);
				ejecutarModoA(fich_entrada, puntosJugador, puntosMaquina, ganador);
			}
			if (opcion == 2)
			{
				cargarFichero(fich_entrada);
				ejecutarModoB(fich_entrada, puntosMaquina, puntosJugador, ganador);
			}
			if (opcion == 3)
			{
				ejecutarModoC(fich_entrada, cartas_restantes, nombre_fich, puntosJugador, puntosMaquina, ganador);
			}
			fich_entrada.close();
		}
		puntosJugador = 0, puntosMaquina = 0;
		opcion = menu();
	}
	system("pause");
	return 0;
}

int menu() {
	int opcion;
	cout << "1.- Jugar modo A" << endl;
	cout << "2.- Jugar modo B" << endl;
	cout << "3.- Jugar modo C" << endl;
	cout << "4.- Jugar modo D" << endl;
	cout << "0.- Salir" << endl;
	cin >> opcion;
	while (opcion < 0 || opcion > 5) {
		cout << "Opcion erronea.";
		cin >> opcion;
	}
	return opcion;
}
void cargarFichero(ifstream & fich_entrada)
{
	string nombre_fich;
	cout << "Introduce nombre del mazo: ";
	cin >> nombre_fich;
	fich_entrada.open(nombre_fich);
	while (!fich_entrada.is_open())
	{
		cout << "Error de lectura de mazo. Reinsertelo: ";
		cin >> nombre_fich;
	}
}
int generarMaxCartas(int max_cartas)
{
	max_cartas = 3 + rand() % 3;
	return max_cartas;
}
int determinaGanador(double puntosJugador, double puntosMaquina)
{
	int ganador = 0, ganador_aleatorio = 0;
	while (ganador != 2 && ganador != 1)
	{
		// ambos por encima o debajo
		if (puntosJugador < 7.5 && puntosMaquina < 7.5)
		{
			if (puntosJugador > puntosMaquina)
			{
				ganador = HUMANO;
			}
			if (puntosJugador < puntosMaquina)
			{
				ganador = MAQUINA;
			}
		}
		if (puntosJugador > 7.5 && puntosMaquina > 7.5)
		{
			if (puntosJugador < puntosMaquina)
			{
				ganador = HUMANO;
			}
			if (puntosJugador > puntosMaquina)
			{
				ganador = MAQUINA;
			}
		}
		// uno por encima y otro por debajo
		if (puntosMaquina > 7.5 && puntosJugador < 7.5)
		{
			ganador = HUMANO;
		}
		if (puntosMaquina < 7.5 && puntosJugador > 7.5)
		{
			ganador = MAQUINA;
		}
		//uno con 7.5 puntos y el otro distinto
		if (puntosJugador == 7.5 && puntosMaquina != 7.5)
		{
			ganador = HUMANO;
		}
		if (puntosMaquina == 7.5 && puntosJugador != 7.5)
		{
			ganador = MAQUINA;
		}
		//ambos obtienen 7.5 o misma puntuacion
		if (puntosJugador == puntosMaquina)
		{
			cout << "Como se ha obtenido la misma puntuacion el ganador se decidira aleatoriamente." << endl;
			ganador_aleatorio = 1 + rand() % 2;
			if (ganador_aleatorio == 1)
			{
				ganador = HUMANO;
			}
			else
			{
				ganador = MAQUINA;
			}
		}
	}
	return ganador;
}
double Valores(int carta_robada)
{
	double valor = 0;
	if (carta_robada > 0 && carta_robada <= 7) { valor = carta_robada; }
	if (carta_robada > 9 && carta_robada < 13) { valor = 0.5; }
	return valor;
}
double modoA(ifstream & fich_entrada, int max_cartas)
{
	int cont = 0, carta;
	double puntos_loc = 0, valor = 0;
	while (cont < max_cartas)
	{
		fich_entrada >> carta;
		valor = Valores(carta);
		cout << "Ha cogido un: " << carta << endl;
		puntos_loc = puntos_loc + valor;
		cont++;
	}
	return puntos_loc;
}
void ejecutarModoA(ifstream & fich_entrada, double & puntosJugador, double & puntosMaquina, int & ganador)
{
	int max_cartas = 0;
	max_cartas = generarMaxCartas(max_cartas);
	puntosJugador = modoA(fich_entrada, max_cartas);
	cout << "El jugador tiene: " << puntosJugador << endl;
	puntosMaquina = modoA(fich_entrada, max_cartas);
	cout << "La maquina tiene: " << puntosMaquina << endl;
	ganador = determinaGanador(puntosJugador, puntosMaquina);
	mostrarGanador(ganador);
}
void mostrarGanador(int ganador)
{
	if (ganador == 1)
	{
		cout << "Ha ganado el jugador." << endl;
	}
	else
	{
		cout << "Ha ganado la maquina." << endl;
	}
}
//-----------------------------------------ModoB------------------------------------------------
void ejecutarModoB(ifstream & fich_entrada, double & puntosMaquina, double & puntosJugador, int & ganador)
{
	int max_cartas = 0;
	max_cartas = generarMaxCartas(max_cartas);
	puntosJugador = modoBhumano(fich_entrada, max_cartas, puntosJugador);
	puntosMaquina = modoBmaquina(fich_entrada, max_cartas, puntosJugador);
	ganador = determinaGanador(puntosJugador, puntosMaquina);
	mostrarGanador(ganador);
}
double modoBhumano(ifstream & fich_entrada, int max_cartas, double puntosJugador)
{
	bool seguir = true;
	int carta_robada = 0;
	double valor = 0;

	for (int i = 0; i <= max_cartas && seguir && puntosJugador <= 7.5; i++)
	{
		fich_entrada >> carta_robada;
		valor = Valores(carta_robada);
		puntosJugador += valor;
		cout << "El jugador ha robado un " << carta_robada << " y tiene " << puntosJugador << endl;
		seguir = Seguir();
	}
	return puntosJugador;
}
double modoBmaquina(ifstream & fich_entrada, int max_cartas, double puntosJugador)
{
	bool plantarse = false;
	int carta = 0, i = 0;
	double puntos = 0, valor = 0;
	while (i <= max_cartas && puntos < 7.5)
	{
		fich_entrada >> carta;
		valor = Valores(carta);
		puntos += valor;
		cout << "La maquina ha robado un " << carta << " y tiene " << puntos << endl;
		plantarse = comprobarPuntosJug(puntosJugador, puntos);
	}
	return puntos;
}
bool Seguir()
{
	int opcion;
	bool seguir = true;
	cout << "Desea seguir robando: (1- robar;0- plantarse)" << endl;
	cin >> opcion;
	while (opcion < 0 || opcion > 1)
	{
		cout << "introduzca opcion correcta: ";
		cin >> opcion;
	}
	seguir = opcion;
	return seguir;
}
bool comprobarPuntosJug(double puntosJugador, double puntos)
{
	bool plantarse = false;
	if (puntosJugador > 7.5 && 7.5 > puntos || puntosJugador < puntos && puntos < 7.5) { plantarse = true; }
	return plantarse;
}
//-----------------------------------------ModoC------------------------------------------------
void ejecutarModoC(ifstream& fich_entrada, tCartasPorAparecer & cartas_restantes, string nombre_fich, double & puntosJugador, double & puntosMaquina, int& ganador)
{
	iniciarPorAparecer(fich_entrada, cartas_restantes);
	fich_entrada.open(nombre_fich);
	modoChumano(fich_entrada, cartas_restantes, puntosJugador);
	modoCmaquina(fich_entrada, cartas_restantes, puntosJugador, puntosMaquina);
	ganador = determinaGanador(puntosJugador, puntosMaquina);
	mostrarGanador(ganador);
}
void modoChumano(ifstream& fich_entrada, tCartasPorAparecer cartas_restantes, double & puntos)
{
	int carta_robada;
	bool seguir = true;

	if (seguir)
	{
		while (seguir)
		{
			fich_entrada >> carta_robada;
			puntos += Valores(carta_robada);
			cout << "El jugador ha robado un " << carta_robada << " y tiene " << puntos << endl;
			reducirCartasMazo(cartas_restantes, carta_robada);
			seguir = Seguir();
		}
	}
}
void modoCmaquina(ifstream & fich_entrada, tCartasPorAparecer cartas, double puntosJugador, double & puntos)
{
	int carta_robada;
	bool pasarse = false;
	while (puntos < 7.5 && puntosJugador <= 7.5 && !pasarse)
	{
		fich_entrada >> carta_robada;
		puntos += Valores(carta_robada);
		cout << "La maquina ha robado un " << carta_robada << " y tiene " << puntos << endl;
		reducirCartasMazo(cartas, carta_robada);
		if (puntos > puntosJugador && !pasarse)
		{
			pasarse = true;
		}
		if (puntos == puntosJugador && puntos < 7.5)
		{
			pasarse = esProbablePasarse(puntos, cartas);
		}
		else
		{
			pasarse = esProbablePasarse(puntos, cartas);
		}
	}
}
void iniciarPorAparecer(ifstream & fich_entrada, tCartasPorAparecer cartas_restantes)
{
	int leer_cartas_mazo = 0;
	for (int i = 0; i < MAX; i++)
	{
		cartas_restantes[i] = 0;
	}
	while (!fich_entrada.eof())
	{
		fich_entrada >> leer_cartas_mazo;
		if (leer_cartas_mazo > 7)
		{
			cartas_restantes[0] += 1;
		}
		if (leer_cartas_mazo == 1)
		{
			cartas_restantes[1] += 1;
		}
		if (leer_cartas_mazo == 2)
		{
			cartas_restantes[2] += 1;
		}
		if (leer_cartas_mazo == 3)
		{
			cartas_restantes[3] += 1;
		}
		if (leer_cartas_mazo == 4)
		{
			cartas_restantes[4] += 1;
		}
		if (leer_cartas_mazo == 5)
		{
			cartas_restantes[5] += 1;
		}
		if (leer_cartas_mazo == 6)
		{
			cartas_restantes[6] += 1;
		}
		if (leer_cartas_mazo == 7)
		{
			cartas_restantes[7] += 1;
		}
	}
}
void reducirCartasMazo(tCartasPorAparecer cartas_restantes, int & carta_robada)
{
	if (carta_robada > 7)
	{
		cartas_restantes[0] -= 1;
	}
	if (carta_robada == 7)
	{
		cartas_restantes[7] -= 1;
	}
	if (carta_robada == 6)
	{
		cartas_restantes[6] -= 1;
	}
	if (carta_robada == 5)
	{
		cartas_restantes[5] -= 1;
	}
	if (carta_robada == 4)
	{
		cartas_restantes[4] -= 1;
	}
	if (carta_robada == 3)
	{
		cartas_restantes[3] -= 1;
	}if (carta_robada == 2)
	{
		cartas_restantes[2] -= 1;
	}if (carta_robada == 1)
	{
		cartas_restantes[1] -= 1;
	}
}
void opcionesProbabilidadMaquina(double puntosMaquina, int & sacar)
{
	if (puntosMaquina >= 1 || puntosMaquina < 2) { sacar = 7; }
	if (puntosMaquina >= 2 || puntosMaquina < 3) { sacar = 6; }
	if (puntosMaquina >= 3 || puntosMaquina < 4) { sacar = 5; }
	if (puntosMaquina >= 4 || puntosMaquina < 5) { sacar = 4; }
	if (puntosMaquina >= 5 || puntosMaquina < 6) { sacar = 3; }
	if (puntosMaquina >= 6 || puntosMaquina < 7) { sacar = 2; }
	if (puntosMaquina >= 7) { sacar = 1; }
}
bool esProbablePasarse(double puntosMaquina, const tCartasPorAparecer cartas_restantes)
{
	int s_parcial = 0, s_total = 0, sacar = 0;
	double probabilidad = 0;
	bool probab_mayor_50 = false;
	if (puntosMaquina <= 7.5)
	{
		s_total = cartas_restantes[0] + cartas_restantes[1] + cartas_restantes[2] + cartas_restantes[3] + cartas_restantes[4] + cartas_restantes[5] + cartas_restantes[6] + cartas_restantes[7];
		if (puntosMaquina >= 0 && puntosMaquina < 1)
		{
			probabilidad = 0;
		}
		if (puntosMaquina == 7.5)
		{
			probabilidad = 1;
		}
		if (puntosMaquina >= 1 && puntosMaquina < 7.5)
		{
			opcionesProbabilidadMaquina(puntosMaquina, sacar);
			for (int i = sacar; i <= 7.5; i++)
			{
				s_parcial += cartas_restantes[i];
			}
			probabilidad = s_parcial / s_total;
		}
		if (probabilidad >= 0.5)
		{
			probab_mayor_50 = true;
		}
	}
	return probab_mayor_50;
}
//-------------------------------------------ModoD---------------------------------------------
void ejecutarModoD(tCartasPorAparecer& cartas_restantes, double & puntosJugador, double & puntosMaquina)
{
	tConjuntoCartas mazo;
	tConjuntoCartas cartasHumano;
	tConjuntoCartas cartasMaquina;
	crearMazo(mazo);
	mostrarMazo(mazo);
	modoDhumano(mazo, cartas_restantes, cartasHumano, puntosJugador);
	modoDmaquina(mazo, cartas_restantes, puntosJugador, cartasMaquina, puntosMaquina);
}
void modoDhumano(tConjuntoCartas& mazo, tCartasPorAparecer cartas_restantes, tConjuntoCartas& cartasHumano, double& puntos)
{

}
void modoDmaquina(tConjuntoCartas& mazo, tCartasPorAparecer cartas_restantes, double puntosJugador, tConjuntoCartas& cartasMaquina, double& puntos)
{

}
void inicializa(tConjuntoCartas & mazo)
{
	int cantidad = 1;
	mazo.cont = 0;
	for (int i = 0; i < TAMBARAJA; i++)
	{
		mazo.cartas[i] = cantidad;
		if (i == 3 || i == 7 || i == 11 || i == 15 || i == 19 || i == 23 || i == 27 || i == 31 || i == 35 || i == 39)
		{
			cantidad++;
		}
		mazo.cont++;
	}
}
void sacar(tConjuntoCartas & cartas, int & carta)
{

}
void incluir(tConjuntoCartas & cartas, int & carta)
{

}
void crearMazo(tConjuntoCartas & mazo)
{
	inicializa(mazo);
	barajar(mazo);
}
void barajar(tConjuntoCartas & mazo)
{
	int i1 = 0, i2 = 0, aux;
	i1 = rand() % 39;
	i2 = rand() % 39;
	while (i1 == i2)
	{
		i1 = rand() % 39;
		i2 = rand() % 39;
	}
	while (i1 != i2)
	{
		for (int i = 0; i < TAMBARAJA; i++)
		{
			aux = mazo.cartas[i1];
			mazo.cartas[i1] = mazo.cartas[i2];
			mazo.cartas[i2] = aux;
		}
	}
}
void mostrarMazo(tConjuntoCartas & mazo)
{

}
void guardarResultado()
{

}
