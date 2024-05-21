#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <fstream>


using namespace std;

// Estructura de una palabra con su definicion y puntos
struct Palabra {
    string palabra;
    string definicion;
    int dificultad; // Dificultad de la palabra
    int puntos;     // Puntos que otorga al ser adivinada
};

// Funcion para seleccionar una palabra aleatoria del conjunto de palabras
Palabra seleccionarPalabraAleatoria(const vector<Palabra>& palabras) {
    int indice = rand() % palabras.size();
    return palabras[indice];
}

// Funcion para seleccionar una palabra aleatoria del conjunto de palabras
Palabra seleccionarPalabraAleatoria(const vector<Palabra>& palabras) {
    int indice = rand() % palabras.size();
    return palabras[indice];
    
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
    const int puntajeMaximo = 300;  // Puntuación máxima para ganar el juego
    const int intentosMaximos = 3; // Número máximo de intentos por palabra
    const int pistasMaximas = 1;   // Número máximo de pistas por palabra
    const int penalizacionPorFallo = 10;  // Penalización por no adivinar una palabra
    const int penalizacionPorPista = 5;   // Penalización por aceptar una pista
    const int maximoFallosConsecutivos = 2;  // Máximo de fallos consecutivos permitidos
    const int puntosPorAdivinanzaRapida = 20; // Puntos adicionales por adivinar rápidamente
    const int puntosPorDesafioCompleto = 10; // Puntos adicionales por completar un desafío

    int fallosConsecutivos = 0;

    cout << "Bienvenido, " << nombreJugador<<endl;
    cout<<endl;
	cout << "El siguiente juego consiste en que adivines las capitales de algunos paises de europa, en los que te brindaremos el pais al que pertenece."<<endl;
	cout<< "------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"Reglas\n"<< "1. Busca adivinar la capital, de acuerdo al pais asignado aleatoriamente.\n";
	cout<<"2. Te puntuacion inicial iniciara en 0.\n";
	cout<<"3. Ganaras el juego al acomular 300 puntos.\n";
	cout<<"4. Se te dara diferente cantidad de puntos si adivinas la palabra, de acuerdo a su dificultad\n";
	cout<<"5. Se te daran puntos adicionales por la rapidez de tu respuesta.\n";
	cout<<"6. Podras utilizar una pista por palabra, pero esto te costara 5 puntos.\n";
	cout<<"7. Si fallas la palabra te descotaremos 10 puntos de los que lleves.\n";
	cout<<"8. Despues de cada palabra te pondre un desafio, el cual te dara 10 puntos extras. Este saldra varias veces, despues de que lo respondas correctamente, respondelo mal cuando te vuelva a preguntar. \n";
	cout<<"9. Si fallas dos palabras consecutivamente, perderas.\n";
	cout<<"Que tengas buena suerte: " << nombreJugador<< " !!!"<<endl;
	
	cout<< "------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<< " Comencemos el juego." << endl;

    while (puntaje < puntajeMaximo && fallosConsecutivos < maximoFallosConsecutivos) {
        Palabra palabraActual = seleccionarPalabraAleatoria(palabras);

        // Muestra la definicion de la palabra
        mostrarDefinicion(palabraActual);

        int intentos = 0;
        int pistasUsadas = 0;
        bool correcto = false;

        // Marca el tiempo de inicio para calcular la rapidez del jugador
        time_t tiempoInicio = time(0);

        while (intentos < intentosMaximos && !correcto){
		    // Lógica para que el jugador ingrese la palabra
		    cout << jugadorActual << " ingresa la palabra: ";
            string entradaJugador;
            cin >> entradaJugador;


            // Compara la entrada del jugador con la palabra correcta
            if (entradaJugador == palabraActual.palabra) {
                // Calcula la rapidez del jugador
                time_t tiempoFin = time(0);
                int segundosTranscurridos = static_cast<int>(tiempoFin - tiempoInicio);

                // Calcula los puntos adicionales por adivinar rapido
                int puntosRapidez = max(0, puntosPorAdivinanzaRapida - segundosTranscurridos);

                cout << "¡Correcto! +" << (intentosMaximos - intentos) * 10 + puntosRapidez << " puntos"
                     << " (+" << puntosRapidez << " puntos por rapidez)" << endl;

                // Suma puntos por adivinar la palabra y por rapidez
                puntaje += (intentosMaximos - intentos) * 10 + puntosRapidez;
                correcto = true;
                fallosConsecutivos = 0;  // Resetea el contador de fallos consecutivos
            } else {
                cout << "Incorrecto. Intentos restantes: " << intentosMaximos - intentos - 1 << endl;

                // Si no ha excedido el límite de pistas, ofrece una pista
                if (pistasUsadas < pistasMaximas) {
                    cout << "Quieres una pista? (Si/No): ";
                    string respuesta;
                    cin >> respuesta;

                    if (respuesta == "Si" || respuesta == "si") {
                        mostrarPista(palabraActual.palabra);
                        puntaje -= penalizacionPorPista;  // Penaliza por aceptar la pista
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

        if (!correcto) {
            cout << "La palabra correcta era: " << palabraActual.palabra << endl;
            puntaje -= penalizacionPorFallo;  // Penaliza por no adivinar la palabra
            fallosConsecutivos++;

            // Verifica si el jugador ha perdido el juego por fallos consecutivos
            if (fallosConsecutivos == maximoFallosConsecutivos) {
                cout << "Has perdido el juego. Demasiados fallos consecutivos." << endl;
                break;
            }
        }

        cout << "Puntuacion actual: " << puntaje << " / " << puntajeMaximo << endl;

        // Cambia el turno al siguiente jugador
        turnoJugador1 = !turnoJugador1;

        // Realiza un desafío adicional para obtener puntos adicionales
        Desafio desafioActual = seleccionarDesafioAleatorio(desafios);
        cout << "Desafio adicional para " << jugadorActual << "! - " << desafioActual.pregunta << ": ";
        int respuestaDesafio;
        if (!(cin >> respuestaDesafio)){ // Verificar si la entrada no es un número entero válido
		    cout << "Respuesta incorrecta. Debe ingresar un numero entero." << endl;
            cin.clear(); // Limpiar el flag de error del flujo de entrada


        if (respuestaDesafio == 206) {
            cout << " Correcto! + " << puntosPorDesafioCompleto << " puntos por completar el desafio adicional." << endl;
            puntaje += puntosPorDesafioCompleto;
        } else {
            cout << "Incorrecto. No ganas puntos adicionales por el desafio." << endl;
        }
    }

    // Verifica si el jugador alcanzo la puntuacion maxima
    if (puntaje >= puntajeMaximo) {
        cout << " Felicidades, " << nombreJugador << "! Has alcanzado la puntuacion maxima. Ganaste el juego!" << endl;
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

    // Solicitar el nombre del jugador
    string nombreJugador;
    cout << "Por favor, ingresa tu nombre: ";
    getline(cin, nombreJugador);

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
    };
    
    // Crea el archivo de preguntas
    crearArchivoPreguntas(palabras, desafios);

    // Inicia el juego
    jugar(palabras, desafios, nombreJugador1, nombreJugador2);

    return 0;
}

