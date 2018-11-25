#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int const HUMANO = 1;
int const MAQUINA = 2;
const int MAX = 8;
typedef int tCartasPorAparecer[MAX];

int menu();
int generarMaxCartas(int  max_cartas);
int determinaGanador(double puntosJugador, double puntosMaquina);
double modoA(ifstream & fich_entrada, int max_cartas);
double Valores(int carta_robada);
double modoBhumano(ifstream & fich_entrada, int max_cartas, double puntosJugador);
double modoBmaquina(ifstream & fich_entrada, int max_cartas, double puntosJugador);
void modoChumano(ifstream & fich_entrada, tCartasPorAparecer cartas, double & puntos);
void modoCmaquina(ifstream & fich_entrada, tCartasPorAparecer cartas, double puntosJugador, double & puntos);
void iniciarPorAparecer(ifstream & fich_entrada, tCartasPorAparecer cartas);
void reducirCartasMazo(tCartasPorAparecer cartas, int &carta_robada);
bool comprobarPuntosJug(double puntosJugador, double puntos);
bool Seguir();
bool esProbablePasarse(double puntosMaquina, const tCartasPorAparecer cartas);


int main()
{
	int opcion, max_cartas = 0, ganador = 0;
	double puntosJugador = 0, puntosMaquina = 0;
	bool terminado = false, seguir = true;
	string nombre_fich;

	opcion = menu();
	while (opcion != 0)
	{
		cout << "Introduce nombre del mazo: ";
		cin >> nombre_fich;
		ifstream fich_entrada;
		fich_entrada.open(nombre_fich);
		if (!fich_entrada.is_open()) { cout << "Error de Lectura del mazo" << nombre_fich << endl; }
		else
		{
			if (opcion == 1)
			{
				if (puntosMaquina <= 20 || puntosJugador <= 20)
				{
					max_cartas = generarMaxCartas(max_cartas);
					puntosJugador = modoA(fich_entrada, max_cartas);
					cout << "El jugador tiene: " << puntosJugador << endl;
					puntosMaquina = modoA(fich_entrada, max_cartas);
					cout << "La maquina tiene: " << puntosMaquina << endl;
				}
				ganador = determinaGanador(puntosJugador, puntosMaquina);
				if (ganador != 2)
				{
					cout << "Ha ganado el jugador." << endl;
				}
				else
				{
					cout << "Ha ganado la maquina." << endl;
				}

			}
			if (opcion == 2)
			{
				max_cartas = generarMaxCartas(max_cartas);
				puntosJugador = modoBhumano(fich_entrada, max_cartas, puntosJugador);
				puntosMaquina = modoBmaquina(fich_entrada, max_cartas, puntosJugador);
				ganador = determinaGanador(puntosJugador, puntosMaquina);
				if (ganador == 1)
				{
					cout << "Ha ganado el jugador." << endl;
				}
				else
				{
					cout << "Ha ganado la maquina." << endl;
				}
			}
			if (opcion == 3)
			{
				tCartasPorAparecer cartas;
				iniciarPorAparecer(fich_entrada, cartas);
				fich_entrada.close();
				fich_entrada.open(nombre_fich);
				modoChumano(fich_entrada, cartas, puntosJugador);
				modoCmaquina(fich_entrada, cartas, puntosJugador, puntosMaquina);
				ganador = determinaGanador(puntosJugador, puntosMaquina);
				if (ganador == 1)
				{
					cout << "Ha ganado el jugador." << endl;
				}
				else
				{
					cout << "Ha ganado la maquina." << endl;
				}

			}
			fich_entrada.close();
			opcion = menu();
		}
	}
	system("pause");
	return 0;
}

int menu() {
	int opcion;
	cout << "1.- Jugar modo A" << endl;
	cout << "2.- Jugar modo B" << endl;
	cout << "3.- Jugar modo C" << endl;
	cout << "0.- Salir" << endl;
	cin >> opcion;
	while (opcion < 0 || opcion > 4) {
		cout << "Opcion erronea";
		cin >> opcion;
	}
	return opcion;
}
int generarMaxCartas(int max_cartas)
{
	srand(time(NULL));
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
			srand(time(NULL));
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
	while (cont <= max_cartas)
	{
		fich_entrada >> carta;
		valor = Valores(carta);
		cout << "Ha cogido un: " << carta << endl;
		puntos_loc = puntos_loc + valor;
		cont++;
	}
	return puntos_loc;
}
//-----------------------------------------ModoB------------------------------------------------
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
	if (puntosJugador > 7.5 > puntos || puntosJugador < puntos < 7.5) { plantarse = true; }
	return plantarse;
}
//-----------------------------------------ModoC------------------------------------------------
void modoChumano(ifstream& fich_entrada, tCartasPorAparecer cartas, double & puntos)
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
			reducirCartasMazo(cartas, carta_robada);
			seguir = Seguir();
		}
	}
}
void modoCmaquina(ifstream & fich_entrada, tCartasPorAparecer cartas, double puntosJugador, double & puntos)
{
	int carta_robada;
	bool pasarse = false;
	while (puntos < puntosJugador && pasarse = false)
	{
		fich_entrada >> carta_robada;
		puntos += Valores(carta_robada);
		cout << "La maquina ha robado un " << carta_robada << " y tiene " << puntos << endl;
		reducirCartasMazo(cartas, carta_robada);
		if (puntos == puntosJugador)
		{
			pasarse = esProbablePasarse(puntos, cartas);
		}
		
	}

}
void iniciarPorAparecer(ifstream & fich_entrada, tCartasPorAparecer cartas)
{
	int leer_cartas_mazo = 0;
	for (int i = 0; i < MAX; i++)
	{
		cartas[i] = 0;
	}
	while (!fich_entrada.eof())
	{
		fich_entrada >> leer_cartas_mazo;
		if (leer_cartas_mazo > 7)
		{
			cartas[0] += 1;
		}
		if (leer_cartas_mazo == 1)
		{
			cartas[1] += 1;
		}
		if (leer_cartas_mazo == 2)
		{
			cartas[2] += 1;
		}
		if (leer_cartas_mazo == 3)
		{
			cartas[3] += 1;
		}
		if (leer_cartas_mazo == 4)
		{
			cartas[4] += 1;
		}
		if (leer_cartas_mazo == 5)
		{
			cartas[5] += 1;
		}
		if (leer_cartas_mazo == 6)
		{
			cartas[6] += 1;
		}
		if (leer_cartas_mazo == 7)
		{
			cartas[7] += 1;
		}
	}
}
bool esProbablePasarse(double puntosMaquina, const tCartasPorAparecer cartas)
{
	int s_parcial = 0, s_total = 0, sacar = 0;
	double probabilidad;
	bool probab_mayor_50 = false;
	if (puntosMaquina < 7.5)
	{
		s_total = cartas[0] + cartas[1] + cartas[2] + cartas[3] + cartas[4] + cartas[5] + cartas[6] + cartas[7];

		if (puntosMaquina < 7.5)
		{
			if (puntosMaquina >= 1 && puntosMaquina < 2) { sacar = 7; }
			if (puntosMaquina >= 2 && puntosMaquina < 3) { sacar = 6; }
			if (puntosMaquina >= 3 && puntosMaquina < 4) { sacar = 5; }
			if (puntosMaquina >= 4 && puntosMaquina < 5) { sacar = 4; }
			if (puntosMaquina >= 5 && puntosMaquina < 6) { sacar = 3; }
			if (puntosMaquina >= 6 && puntosMaquina < 7) { sacar = 2; }
			if (puntosMaquina == 7) { sacar = 1; }
			for (int i = sacar; i <= 7.5; i++)
			{
				s_parcial += cartas[i];
			}
		}
		probabilidad = s_parcial / s_total;
		if (puntosMaquina >= 0 && puntosMaquina < 1)
		{
			probabilidad = 0;
		}
		if (puntosMaquina == 7.5)
		{
			probabilidad = 1;
		}
		if (probabilidad >= 0.5)
		{
			probab_mayor_50 = true;
		}
	}
	return probab_mayor_50;
}
void reducirCartasMazo(tCartasPorAparecer cartas, int& carta_robada)
{
	if (carta_robada > 7)
	{
		cartas[0] -= 1;
	}
	if (carta_robada == 7)
	{
		cartas[7] -= 1;
	}
	if (carta_robada == 6)
	{
		cartas[6] -= 1;
	}
	if (carta_robada == 5)
	{
		cartas[5] -= 1;
	}
	if (carta_robada == 4)
	{
		cartas[4] -= 1;
	}
	if (carta_robada == 3)
	{
		cartas[3] -= 1;
	}if (carta_robada == 2)
	{
		cartas[2] -= 1;
	}if (carta_robada == 1)
	{
		cartas[1] -= 1;
	}
}
