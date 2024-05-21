#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <fstream>

using namespace std;

// Estructura de una palabra
struct Palabra {
    string palabra;
    string definicion;
    int dificultad; // Dificultad
    int puntos;     // Puntos
};

// Estructura de desafío adicional
struct Desafio {
    string pregunta;
    int respuesta;
};

// Estructura de un jugador
struct Jugador {
    string nombre;
    int puntaje;
};

// Funcion para seleccionar una palabra aleatoria del conjunto de palabras
Palabra seleccionarPalabraAleatoria(const vector<Palabra>& palabras) {
    int indice = rand() % palabras.size();
    return palabras[indice];
}
    
// Funcion para seleccionar un desafío aleatorio
Desafio seleccionarDesafioAleatorio(const vector<Desafio>& desafios) {
int indice = rand() % desafios.size();
return desafios[indice];
}

// Función para mostrar la definición de una palabra
void mostrarDefinicion(const Palabra& palabra) {
    cout << "Definicion: " << palabra.definicion << endl;
}

// Funcion para mostrar una pista
void mostrarPista(const string& palabra) {
    cout << "Pista: La palabra comienza con la letra " << palabra[0] << endl;
}

// Funcion para jugar al juego
void jugar(const vector<Palabra>& palabras, const vector<Desafio>& desafios, const string& nombreJugador1, const string& nombreJugador2) {
    int puntajeJugador1 = 0;
    int puntajeJugador2 = 0;
    const int puntajeMaximo = 300;  
    const int intentosMaximos = 3; 
    const int pistasMaximas = 1;   
    const int penalizacionPorFallo = 10;  
    const int penalizacionPorPista = 5;  
    const int maximoFallosConsecutivos = 2;  
    const int puntosPorAdivinanzaRapida = 20; 
    const int puntosPorDesafioCompleto = 10; 

    int fallosConsecutivosJugador1 = 0;
    int fallosConsecutivosJugador2 = 0;
    bool turnoJugador1 = true; // Comienza el jugador 1
	
    cout << "Bienvenidos " << nombreJugador1 << " y " << nombreJugador2 << endl;
    cout << endl;
    cout << "El siguiente juego consiste en que adivinen las capitales de algunos paises de Europa, en los que te brindaremos el pais al que pertenece." << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Reglas\n"
         << "1. Busquen adivinar la capital, de acuerdo con el pais asignado aleatoriamente.\n"
         << "2. Su puntuación inicial iniciara en 0.\n"
         << "3. Ganara el juego el que primero acumule 300 puntos.\n"
         << "4. Se les dara diferente cantidad de puntos si adivinan la palabra, de acuerdo con su dificultad.\n"
         << "5. Se les daran puntos adicionales por la rapidez de sus respuesta.\n"
         << "6. Podran utilizar una pista por palabra, pero esto les costara 5 puntos.\n"
         << "7. Si fallan la palabra les descontaremos 10 puntos de los que lleves.\n"
         << "8. Despues de cada palabra les pondremos un desafio, el cual les dara 10 puntos extras.\n"
         << "9. Si fallas dos palabras consecutivamente perderas.\n"
         << "Que tengan buena suerte " << nombreJugador1 << " y " << nombreJugador2 << "!!!" << endl;

    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Comencemos el juego." << endl;

    while (puntajeJugador1 < puntajeMaximo && puntajeJugador2 < puntajeMaximo &&
           fallosConsecutivosJugador1 < maximoFallosConsecutivos && fallosConsecutivosJugador2 < maximoFallosConsecutivos) {
        string jugadorActual = turnoJugador1 ? nombreJugador1 : nombreJugador2;
        int& puntajeActual = turnoJugador1 ? puntajeJugador1 : puntajeJugador2;
        int& fallosConsecutivosActual = turnoJugador1 ? fallosConsecutivosJugador1 : fallosConsecutivosJugador2;

	Palabra palabraActual = seleccionarPalabraAleatoria(palabras);
	    
	// Muestra la definicion
        mostrarDefinicion(palabraActual);

        int intentos = 0;
        int pistasUsadas = 0;
        bool correcto = false;

        // Calcular rapidez respuesta
        time_t tiempoInicio = time(0);

        while (intentos < intentosMaximos && !correcto){
	    //jugador ingrese la palabra
	    cout << jugadorActual << " ingresa la palabra: ";
            string entradaJugador;
            cin >> entradaJugador;

            // Compara la entrada del jugador con la palabra correcta
            if (entradaJugador == palabraActual.palabra) {
                time_t tiempoFin = time(0);
                int segundosTranscurridos = static_cast<int>(difftime(tiempoFin, tiempoInicio));

                // Calcula los puntos adicionales por adivinar rapido
                int puntosRapidez = max(0, puntosPorAdivinanzaRapida - segundosTranscurridos);

                cout << "¡Correcto! +" << (intentosMaximos - intentos) * 10 + puntosRapidez << " puntos"
                     << " (+" << puntosRapidez << " puntos por rapidez)" << endl;

               // Suma puntos por adivinar la palabra y por rapidez
                puntajeActual += (intentosMaximos - intentos) * 10 + puntosRapidez;
                correcto = true;
                // Resetea el contador de fallos consecutivos
                fallosConsecutivosActual = 0;
            }else {
                cout << "Incorrecto. Intentos restantes: " << intentosMaximos - intentos - 1 << endl;

                // Si no ha excedido el límite de pistas, ofrece una pista
                if (pistasUsadas < pistasMaximas) {
                    cout << "Quieres una pista? (Si/No): ";
                    string respuesta;
                    cin >> respuesta;

                    if (respuesta == "Si" || respuesta == "si") {
                        mostrarPista(palabraActual.palabra);
                        puntajeActual -= penalizacionPorPista;  // Penaliza por aceptar la pista
                        pistasUsadas++;
                    }
                }

                intentos++;
            }
        }
	
	if (!correcto) {
		cout << "La palabra correcta era: " << palabraActual.palabra << endl;
		puntajeActual -= penalizacionPorFallo; // Penaliza por no adivinar la palabra
		fallosConsecutivosActual++;
		
		// Verifica si el jugador ha perdido el juego por fallos consecutivos
		if (fallosConsecutivosActual == maximoFallosConsecutivos) {
			cout << "Has perdido el juego " << jugadorActual << ". Demasiados fallos consecutivos." << endl;
			break;
		}
	}
	    
	    cout << "Puntuacion de " << nombreJugador1 << ": " << puntajeJugador1 << " / " << puntajeMaximo << endl;
	    cout << "Puntuacion de " << nombreJugador2 << ": " << puntajeJugador2 << " / " << puntajeMaximo << endl;
	    
	    // Cambia el turno al siguiente jugador
	    turnoJugador1 = !turnoJugador1;
	    
	    // Realiza un desafío adicional para obtener puntos adicionales
	    Desafio desafioActual = seleccionarDesafioAleatorio(desafios);
	    cout << "Desafio adicional para " << jugadorActual << "! - " << desafioActual.pregunta << ": ";
	    int respuestaDesafio;
	    if (!(cin >> respuestaDesafio)) { // Verificar si la entrada no es un número entero válido
		    cout << "Respuesta incorrecta. Debe ingresar un numero entero." << endl;
		    cin.clear(); // Limpiar el flag de error del flujo de entrada
		    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada no válida
	    } else {
		    if (respuestaDesafio == desafioActual.respuesta) {
			    cout << "Correcto! + " << puntosPorDesafioCompleto << " puntos por completar el desafio adicional." << endl;
			    puntajeActual += puntosPorDesafioCompleto;
		    } else {
			    cout << "Incorrecto. No ganas puntos adicionales por el desafio." << endl;
		    }
	    }	    
	    
	    // Actualiza el archivo de jugadores y puntajes
	    ofstream archivo("jugadores_puntajes.txt", ios::app);
	    
	    if (archivo.is_open()) {
		    archivo << jugadorActual << " " << puntajeActual << endl;
		    archivo.close();
		    cout << "Informacion del jugador actualizada exitosamente." << endl;
	    } else {
		    cout << "No se pudo abrir el archivo de jugadores y puntajes." << endl;
	    }
    }
}

void merge(vector<Jugador>& jugadores, int izquierda, int medio, int derecha) {
	int n1 = medio - izquierda + 1;
	int n2 = derecha - medio;

        // Crear arreglos temporales
	vector<Jugador> izquierdaJugadores(n1);
	vector<Jugador> derechaJugadores(n2);

	// Copiar los datos a los arreglos temporales izquierdo[] y derecho[]
	for (int i = 0; i < n1; i++)
		izquierdaJugadores[i] = jugadores[izquierda + i];
	for (int j = 0; j < n2; j++)
		derechaJugadores[j] = jugadores[medio + 1 + j];

	// Mezclar los arreglos temporales de vuelta en arr[izquierda..derecha]
	int i = 0; // Indice inicial del primer subarreglo
	int j = 0; // Indice inicial del segundo subarreglo
	int k = izquierda; // Indice inicial del subarreglo mezclado
	while (i < n1 && j < n2) {
		if (izquierdaJugadores[i].puntaje >= derechaJugadores[j].puntaje) {
			jugadores[k] = izquierdaJugadores[i];
			i++;
		} else {
			jugadores[k] = derechaJugadores[j];
			j++;
		}
		k++;
	}
	// Copiar los elementos restantes de izquierdaJugadores[], si los hay
	while (i < n1) {
		jugadores[k] = izquierdaJugadores[i];
		i++;
		k++;
	}
	
	// Copiar los elementos restantes de derechaJugadores[], si los hay
	while (j < n2) {
		jugadores[k] = derechaJugadores[j];
		j++;
		k++;
	}
}
	
void mergeSort(vector<Jugador>& jugadores, int izquierda, int derecha) {
    if (izquierda < derecha) {
        // Encuentra el punto medio del arreglo
        int medio = izquierda + (derecha - izquierda) / 2;

        // Ordena primero y segundo subarreglos
        mergeSort(jugadores, izquierda, medio);
        mergeSort(jugadores, medio + 1, derecha);

        // Mezcla los subarreglos
        merge(jugadores, izquierda, medio, derecha);
    }
}

void crearArchivoPreguntas(const vector<Palabra>& palabras, const vector<Desafio>& desafios) {
    ofstream archivo("preguntas_juego.txt");

    if (archivo.is_open()) {
        archivo << "Preguntas de las palabras a adivinar:\n";
        for (const auto& palabra : palabras) {
            archivo << palabra.definicion << " - Respuesta: " << palabra.palabra << endl;
        }
        archivo << "\nPreguntas adicionales:\n";
        for (const auto& desafio : desafios) {
            archivo << desafio.pregunta << " - Respuesta: " << desafio.respuesta << endl;
        }
        archivo.close();
        cout << "Archivo de preguntas creado exitosamente." << endl;
    } else {
        cout << "No se pudo abrir el archivo de preguntas." << endl;
    }
}

void crearArchivoResumenJugadores(const vector<Jugador>& jugadores) {
    ofstream archivo("resumen_jugadores.txt");

    if (archivo.is_open()) {
    	vector<Jugador> jugadoresOrdenados = jugadores; // Copia de los jugadores para no modificar el original
		mergeSort(jugadoresOrdenados, 0, jugadoresOrdenados.size() - 1);
		
		archivo << "Resumen de jugadores ordenados por puntaje:\n";
        for (const auto& jugador : jugadoresOrdenados) {
        	archivo << jugador.nombre << " - Puntuacion: " << jugador.puntaje << endl;
        }
        archivo.close();
        cout << "Archivo de resumen de jugadores creado exitosamente." << endl;
    } 
	else {
		cout << "No se pudo abrir el archivo de resumen de jugadores." << endl;
    }
}

int main() {
	// Inicializacion del generador de números aleatorios
	srand(static_cast<unsigned>(time(0)));
	
	// Solicitar el nombre de los jugadores
	string nombreJugador1, nombreJugador2;
	cout << "Por favor, ingresa el nombre del Jugador 1: ";
	getline(cin, nombreJugador1);
	cout << "Por favor, ingresa el nombre del Jugador 2: ";
	getline(cin, nombreJugador2);

	// Definicion de palabras con sus respectivas definiciones, dificultades y puntos
	vector<Palabra> palabras = {
		{"madrid", "Capital de Espana." , 3 , 15},
        	{"paris", "Capital de Francia." , 4 , 20},
        	{"londres", "Capital de Inglaterra.", 4, 20},
        	{"lisboa", "Capital de Portugal." , 5, 30},
        	{"roma", "Capital de Italia." , 3, 15},
        	{"berlin", "Capital de Alemania." , 5, 30},
        	{"estocolmo", "Capital de suecia." , 5, 30},
        	{"atenas", "Capital de Grecia.", 4 , 20},
        	{"moscu", "Capital de Rusia." , 3 , 15},
        	{"bruselas", "Capital de Belgica." , 5, 30},
		{"oslo", "Capital de Noruega.", 4, 20},
        	{"varsovia", "Capital de Polonia.", 5, 30},
	};

	// Definición de desafíos adicionales
        vector<Desafio> desafios = {
        	{"Cuantos huesos tiene el ser humano?", 206},
       		{"Cuantos departamentos tiene Colombia?", 20},
        	{"Cuantos anos duro la Guerra de los Mil Dias?", 3},
        	{"Cuantos planetas hay en el sistema solar?", 8},
        	{"Cual es el oceano mas grande del mundo? (1: Atlantico, 2: Indico, 3: Pacifico)", 3},
        	{"Cuantos rios principales hay en Colombia?", 7},
        	{"Cuantos continentes tiene el mundo?", 7},
        	{"Cuantas letras tiene el alfabeto espanol?", 27},
        	{"Cuantos elementos tiene la tabla periodica?",118},
        	{"Cuantas semanas tiene un ano normal?",52},
	};
    
    	// Crea el archivo de preguntas
    	crearArchivoPreguntas(palabras, desafios);

    	// Inicia el juego
   	 jugar(palabras, desafios, nombreJugador1, nombreJugador2);

	// Lee los jugadores y puntajes del archivo
    	vector<Jugador> jugadores;
    	ifstream archivo("jugadores_puntajes.txt");
    	if (archivo.is_open()) {
        	string nombre;
        	int puntaje;
        	while (archivo >> nombre >> puntaje) {
			Jugador jugador = {nombre, puntaje};
           	 	jugadores.push_back(jugador);
        	}
        archivo.close();
    } else {
	cout << "No se pudo abrir el archivo de jugadores y puntajes." << endl;
    }
    // Crea el archivo de resumen de jugadores
    crearArchivoResumenJugadores(jugadores);
	
    return 0;
}
//Ya ejecuta, pero no se como hacerlo aca
