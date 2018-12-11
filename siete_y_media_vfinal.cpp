/*
	Eduardo Abad Ibarrola
	Carlo Dubini Marqués
*/
#include <iostream>
#include <fstream>
#include <list>
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
typedef int tCartasPorAparecer[MAX];
typedef int tMazoCartas[TAMBARAJA];
typedef struct
{
	int cont;
	tMazoCartas cartas;
}tConjuntoCartas;

int menu();
void cargarOpcion(int opcion);
void cargarFichero(ifstream & fich_entrada, string & nombre_fich);
int generarMaxCartas(int  max_cartas);
int determinaGanador(double puntosJugador, double puntosMaquina);
void ejecutarModoA(ifstream & fich_entrada, double & puntosJugador, double & puntosMaquina, int & ganador);
double modoA(ifstream & fich_entrada, int max_cartas);
double Valores(int carta_robada);
void mostrarGanador(int ganador);
void ejecutarModoB(ifstream & fich_entrada, double & puntosMaquina, double & puntosJugador, int & ganador);
double modoBhumano(ifstream & fich_entrada, int max_cartas, double puntosJugador);
double modoBmaquina(ifstream & fich_entrada, int max_cartas, double puntosJugador);
void ejecutarModoC(ifstream& fich_entrada, tCartasPorAparecer & cartas_restantes, string & nombre_fich, double & puntosJugador, double & puntosMaquina, int& ganador);
void modoChumano(ifstream & fich_entrada, tCartasPorAparecer cartas, double & puntos);
void modoCmaquina(ifstream & fich_entrada, tCartasPorAparecer cartas, double puntosJugador, double & puntos);
void iniciarPorAparecer(ifstream & fich_entrada, tCartasPorAparecer cartas);
void reducirCartasMazo(tCartasPorAparecer cartas, int & carta_robada);
void inicializa(tConjuntoCartas & cartas);
void sacar(tConjuntoCartas & mazo, int & carta);
void incluir(tConjuntoCartas & mazo, int & carta);
void crearMazo(tConjuntoCartas & mazo);
void mostrarMazo(tConjuntoCartas & mazo);
void barajar(tConjuntoCartas & mazo);
void ejecutarModoD(tCartasPorAparecer& cartas_restantes, double & puntosJugador, double & puntosMaquina, int & ganador, int & num_partida);
void modoDhumano(tConjuntoCartas& mazo, tCartasPorAparecer cartas, tConjuntoCartas& cartasHumano, double& puntos);
void modoDmaquina(tConjuntoCartas& mazo, tCartasPorAparecer cartas, double puntosJugador, tConjuntoCartas& cartasMaquina, double& puntos);
bool comprobarPuntosJug(double puntosJugador, double puntos);
void iniciarCartasRestantes_D(const tConjuntoCartas & mazo, tCartasPorAparecer cartas_restantes);
bool Seguir();
void compararCartas(const tConjuntoCartas & cartasMaquina, const tCartasPorAparecer cartas_restantes, int & ganador);
bool esProbablePasarse(double puntosMaquina, const tCartasPorAparecer cartas);
void guardarResultado(ofstream & fich_partida, tConjuntoCartas & cartasJugador, double & puntosJugador, tConjuntoCartas& cartasMaquina, double& puntosMaquina, int & ganador, int &num_partida);
void mostrarCartas(tConjuntoCartas& cartas);

int main()
{
	int opcion;

	srand(time(NULL));
	opcion = menu();
	cargarOpcion(opcion);
	system("pause");
	return 0;
}

void cargarOpcion(int opcion)
{
	int ganador = 0, carta = 0, num_partida = 0;
	double puntosJugador = 0, puntosMaquina = 0;
	string nombre_fich;
	tCartasPorAparecer cartas_restantes;
	while (opcion != 0)
	{
		puntosJugador = 0, puntosMaquina = 0;
		if (opcion == 4)
		{
			ejecutarModoD(cartas_restantes, puntosJugador, puntosMaquina, ganador, num_partida);
		}
		else
		{
			ifstream fich_entrada;
			if (opcion == 1)
			{
				cargarFichero(fich_entrada, nombre_fich);
				ejecutarModoA(fich_entrada, puntosJugador, puntosMaquina, ganador);
			}
			if (opcion == 2)
			{
				cargarFichero(fich_entrada, nombre_fich);
				ejecutarModoB(fich_entrada, puntosMaquina, puntosJugador, ganador);
			}
			if (opcion == 3)
			{
				ejecutarModoC(fich_entrada, cartas_restantes, nombre_fich, puntosJugador, puntosMaquina, ganador);
			}
			fich_entrada.close();
		}
		opcion = menu();
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
		else if (puntosJugador > 7.5 && puntosMaquina > 7.5)
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
		else if (puntosMaquina > 7.5 && puntosJugador < 7.5)
		{
			ganador = HUMANO;
		}
		else if (puntosMaquina < 7.5 && puntosJugador > 7.5)
		{
			ganador = MAQUINA;
		}
		else if (puntosJugador == 7.5 && puntosMaquina != 7.5)
		{
			ganador = HUMANO;
		}
		else if (puntosMaquina == 7.5 && puntosJugador != 7.5)
		{
			ganador = MAQUINA;
		}
		else if (puntosJugador == puntosMaquina)
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

	for (int i = 0; i <= max_cartas && seguir && puntosJugador <= 7.5; i++)
	{
		fich_entrada >> carta_robada;
		puntosJugador += Valores(carta_robada);
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
void ejecutarModoC(ifstream& fich_entrada, tCartasPorAparecer & cartas_restantes, string & nombre_fich, double & puntosJugador, double & puntosMaquina, int& ganador)
{
	int cartas_jugador, cartas_maquina;
	cargarFichero(fich_entrada, nombre_fich);
	iniciarPorAparecer(fich_entrada, cartas_restantes);
	fich_entrada.close();
	fich_entrada.open(nombre_fich);
	modoChumano(fich_entrada, cartas_restantes, puntosJugador);
	cartas_jugador = 40 - (cartas_restantes[0] + cartas_restantes[1] + cartas_restantes[2] + cartas_restantes[3] + cartas_restantes[4] + cartas_restantes[5] + cartas_restantes[6] + cartas_restantes[7]);
	modoCmaquina(fich_entrada, cartas_restantes, puntosJugador, puntosMaquina);
	cartas_maquina = 40 - (cartas_jugador + (cartas_restantes[0] + cartas_restantes[1] + cartas_restantes[2] + cartas_restantes[3] + cartas_restantes[4] + cartas_restantes[5] + cartas_restantes[6] + cartas_restantes[7]));
	ganador = determinaGanador(puntosJugador, puntosMaquina);
	mostrarGanador(ganador);
}
void modoChumano(ifstream& fich_entrada, tCartasPorAparecer cartas_restantes, double & puntos)
{
	int carta_robada = 0;
	bool seguir = true;

	while (seguir)
	{
		fich_entrada >> carta_robada;
		puntos += Valores(carta_robada);
		cout << "El jugador ha robado un " << carta_robada << " y tiene " << puntos << endl;
		reducirCartasMazo(cartas_restantes, carta_robada);
		seguir = Seguir();
	}
}
void modoCmaquina(ifstream & fich_entrada, tCartasPorAparecer cartas, double puntosJugador, double & puntos)
{
	int carta_robada;
	bool pasarse = false;
	while (!pasarse && puntos < 7.5 && puntosJugador >= puntos)
	{
		fich_entrada >> carta_robada;
		puntos += Valores(carta_robada);
		cout << "La maquina ha robado un " << carta_robada << " y tiene " << puntos << endl;
		reducirCartasMazo(cartas, carta_robada);
		if (!pasarse && puntos > puntosJugador)
		{
			pasarse = true;
		}
		if (puntos == puntosJugador)
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
	fich_entrada >> leer_cartas_mazo;
	while (!fich_entrada.eof())
	{
		if (leer_cartas_mazo > 7)
		{
			cartas_restantes[0] += 1;
		}
		else
		{
			cartas_restantes[leer_cartas_mazo] += 1;
		}
		fich_entrada >> leer_cartas_mazo;
	}
}
bool esProbablePasarse(double puntosMaquina, const tCartasPorAparecer cartas_restantes)
{
	int sacar = 0, n;
	double probabilidad = 0, s_parcial = 0, s_total = 0;
	bool probab_mayor_50 = false;
	if (puntosMaquina <= 7.5)
	{
		s_total = cartas_restantes[0] + cartas_restantes[1] + cartas_restantes[2] + cartas_restantes[3] + cartas_restantes[4] + cartas_restantes[5] + cartas_restantes[6] + cartas_restantes[7];
		if (puntosMaquina >= 0 && puntosMaquina < 1)
		{
			probabilidad = 0;
		}
		else if (puntosMaquina == 7.5)
		{
			probabilidad = 1;
		}
		else if (puntosMaquina >= 1 && puntosMaquina < 7.5)
		{
			n = 8 - trunc(puntosMaquina);
			if (n >= trunc(puntosMaquina) || n < trunc(puntosMaquina))
			{
				sacar = n;
			}
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
void ejecutarModoD(tCartasPorAparecer& cartas_restantes, double & puntosJugador, double & puntosMaquina, int & ganador, int & num_partida)
{
	tConjuntoCartas mazo;
	tConjuntoCartas cartasHumano;
	tConjuntoCartas cartasMaquina;
	ofstream fich_partida;
	crearMazo(mazo);
	iniciarCartasRestantes_D(mazo, cartas_restantes);
	mostrarMazo(mazo);
	modoDhumano(mazo, cartas_restantes, cartasHumano, puntosJugador);
	modoDmaquina(mazo, cartas_restantes, puntosJugador, cartasMaquina, puntosMaquina);
	if (puntosMaquina == puntosJugador)
	{
		cout << "Como se ha obtenido la misma puntuacion, ganara el que menos cartas haya robado. Si hay mismo numero de cartas,  se decidira ganador aleatoriamente." << endl;
		compararCartas(cartasMaquina, cartas_restantes, ganador);
	}
	else
	{
		ganador = determinaGanador(puntosJugador, puntosMaquina);
	}
	mostrarGanador(ganador);
	guardarResultado(fich_partida, cartasHumano, puntosJugador, cartasMaquina, puntosMaquina, ganador, num_partida);

}
void modoDhumano(tConjuntoCartas& mazo, tCartasPorAparecer cartas_restantes, tConjuntoCartas & cartasHumano, double& puntos)
{
	bool seguir = true;
	int carta_robada = 0;
	cartasHumano.cont = 0;
	tConjuntoCartas &cartas = cartasHumano;
	while (seguir)
	{
		sacar(mazo, carta_robada);
		incluir(cartas, carta_robada);
		puntos += Valores(carta_robada);
		cout << "Cartas: ";
		mostrarCartas(cartas);
		reducirCartasMazo(cartas_restantes, carta_robada);
		seguir = Seguir();
	}
}
void modoDmaquina(tConjuntoCartas& mazo, tCartasPorAparecer cartas_restantes, double puntosJugador, tConjuntoCartas& cartasMaquina, double& puntos)
{
	int carta_robada = 0;
	bool pasarse = false;
	cartasMaquina.cont = 0;
	tConjuntoCartas &cartas = cartasMaquina;
	while (!pasarse && puntos < puntosJugador)
	{
		sacar(mazo, carta_robada);
		incluir(cartas, carta_robada);
		puntos += Valores(carta_robada);
		reducirCartasMazo(cartas_restantes, carta_robada);
		if (puntos >= puntosJugador)
		{
			pasarse = true;
		}
		if (puntos == puntosJugador)
		{
			pasarse = esProbablePasarse(puntos, cartas_restantes);
		}
	}
	cout << "Las cartas de la maquina son: ";
	mostrarCartas(cartas);
}
void inicializa(tConjuntoCartas & mazo)
{
	int cantidad = 1;
	mazo.cont = 0;
	for (int i = 0; i < 28; i++)
	{
		mazo.cartas[i] = cantidad;
		if (i == 3 || i == 7 || i == 11 || i == 15 || i == 19 || i == 23)
		{
			cantidad++;
		}
		mazo.cont++;
	}
	cantidad = 10;
	for (int i = mazo.cont; i < TAMBARAJA; i++)
	{
		mazo.cartas[i] = cantidad;
		if (i == 31 || i == 35)
		{
			cantidad++;
		}
		mazo.cont++;
	}
}
void sacar(tConjuntoCartas & mazo, int & carta_robada)
{
	int i = mazo.cont - 1;
	carta_robada = mazo.cartas[i];
	mazo.cartas[TAMBARAJA - 1 - i];
	mazo.cont -= 1;
}
void incluir(tConjuntoCartas & cartas, int & carta_robada)
{
	int i = cartas.cont;
	cartas.cartas[i] = carta_robada;
	cartas.cont += 1;
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
	if (i1 == i2)
	{
		i1 = rand() % 39;
		i2 = rand() % 39;
	}
	else
	{
		for (int i = 0; i < TAMBARAJA; i++)
		{
			aux = mazo.cartas[i1];
			mazo.cartas[i1] = mazo.cartas[i2];
			mazo.cartas[i2] = aux;
			i1 = rand() % 39;
			i2 = rand() % 39;
		}
	}
}
void mostrarMazo(tConjuntoCartas & mazo)
{
	for (int i = 0; i < TAMBARAJA; i++)
	{
		cout << mazo.cartas[i] << " ";
	}
	cout << endl;
}
void iniciarCartasRestantes_D(const tConjuntoCartas & mazo, tCartasPorAparecer cartas_restantes)
{
	int leer_cartas_mazo;
	for (int i = 0; i < MAX; i++) { cartas_restantes[i] = 0; }
	for (int i = 0; i < mazo.cont; i++)
	{
		leer_cartas_mazo = mazo.cartas[i];
		if (leer_cartas_mazo > 7)
		{
			cartas_restantes[0] += 1;
		}
		else if (leer_cartas_mazo >= 0 && leer_cartas_mazo <= 7)
		{
			cartas_restantes[leer_cartas_mazo] += 1;
		}
	}
}
void guardarResultado(ofstream & fich_partida, tConjuntoCartas & cartasJugador, double & puntosJugador, tConjuntoCartas& cartasMaquina, double& puntosMaquina, int & ganador, int& num_partida)
{
	string nombre_partida;
	nombre_partida = "partida" + to_string(num_partida) + ".txt";
	fich_partida.open(nombre_partida);
	if (!fich_partida.is_open())
	{
		cout << "No se ha guardado la partida." << endl;

	}
	else
	{
		fich_partida << "Numero de partida: " << num_partida << endl;
		if (ganador == 1)
		{
			fich_partida << "Ganador: Humano" << endl;
		}
		else
		{
			fich_partida << "Ganador: Maquina" << endl;
		}
		fich_partida << "Humano. Puntos: " << puntosJugador << endl;
		fich_partida << "Cartas: ";
		for (int i = 0; i < cartasJugador.cont; i++)
		{
			fich_partida << cartasJugador.cartas[i] << " ";
		}
		fich_partida << endl;
		fich_partida << "Maquina. Puntos: " << puntosMaquina << endl;
		fich_partida << "Cartas: ";
		for (int i = 0; i < cartasMaquina.cont; i++)
		{
			fich_partida << cartasMaquina.cartas[i] << " ";
		}
		fich_partida << endl;
	}
	num_partida++;
	fich_partida.close();
}
void mostrarCartas(tConjuntoCartas& cartas)
{
	for (int i = 0; i < cartas.cont; i++)
	{
		cout << cartas.cartas[i] << " ";
	}
	cout << endl;
}
//-------------------------------------------otras----------------------------------------------------
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
void cargarFichero(ifstream & fich_entrada, string & nombre_fich)
{
	cout << "Introduce nombre del mazo: ";
	cin >> nombre_fich;
	fich_entrada.open(nombre_fich);
	while (!fich_entrada.is_open())
	{
		cout << "Error de lectura de mazo. Reinsertelo: ";
		cin >> nombre_fich;
		fich_entrada.open(nombre_fich);
	}
}
double Valores(int carta_robada)
{
	double valor = 0;
	if (carta_robada > 0 && carta_robada <= 7) { valor = carta_robada; }
	if (carta_robada > 9 && carta_robada < 13) { valor = 0.5; }
	return valor;
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
void reducirCartasMazo(tCartasPorAparecer cartas_restantes, int & carta_robada)
{
	if (carta_robada > 7)
	{
		cartas_restantes[0] -= 1;
	}
	else
	{
		cartas_restantes[carta_robada] -= 1;
	}
}
void compararCartas(const tConjuntoCartas & cartasMaquina, const tCartasPorAparecer cartas_restantes, int & ganador)
{
	int cartasjugador, cartas_sobrantes = 0;
	for (int i = 0; i < MAX; i++)
	{
		cartas_sobrantes += cartas_restantes[i];
	}
	cartasjugador = 40 - cartas_sobrantes + cartasMaquina.cont;
	if (cartasjugador < cartasMaquina.cont)
	{
		ganador = HUMANO;
	}
	else if (cartasjugador > cartasMaquina.cont)
	{
		ganador = MAQUINA;
	}
}