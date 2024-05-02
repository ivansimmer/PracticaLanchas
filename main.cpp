// main.cpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include "lancha.h"

using namespace std;

int main() {
    srand(time(0));

    // Obtener la resolución máxima de la pantalla
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktopMode.width;
    unsigned int screenHeight = desktopMode.height;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Carrera de Lanchas");

    // Color de fondo
    sf::Color backgroundColor(135, 206, 250);

    // Creacion lanchas
    Lancha lancha1("Lancha Negra", sf::Color::Black); // Creo una lancha negra
    Lancha lancha2("Lancha Roja", sf::Color::Red); // Creo una lancha roja

    // Posiciones iniciales para las lanchas
    lancha1.setPosition(sf::Vector2f(0, 300));
    lancha2.setPosition(sf::Vector2f(0, 600));

    float windowOffset = 0; // Offset de la ventana

    string opcNitroNegra = "";
    string opcNitroRoja = "";

    // Bucle de la jugabilidad con los turnos
    const int numTurnos = 5;
    for (int turno = 1; turno <= numTurnos; turno++) {
        cout << "Turno " << turno << "--------------------------------------------" << endl;

        cout << "Lancha Negra: ";
        cout << "Quieres usar el nitro (s/n)?";
        cin >> opcNitroNegra;
        if (opcNitroNegra == "s") {
            lancha1.usoNitro();
        }
        lancha1.giraDado();
        lancha1.actualizaDistancia();

        cout << "\n";

        cout << "Lancha Roja: ";
        cout << "Quieres usar el nitro (s/n)?";
        cin >> opcNitroRoja;
        if (opcNitroRoja == "s") {
            lancha2.usoNitro();
        }
        lancha2.giraDado();
        lancha2.actualizaDistancia();

        // Calcular el desplazamiento de la ventana
        float lanchaDistancia = max(lancha1.getDistancia(), lancha2.getDistancia());
        windowOffset = max(windowOffset, lanchaDistancia + 200 - window.getSize().x); // Desplazar la ventana si es necesario

        // Actualizar la posición de las lanchas en relación con el desplazamiento de la ventana
        lancha1.setPosition(sf::Vector2f(lancha1.getPosition().x, lancha1.getPosition().y));
        lancha2.setPosition(sf::Vector2f(lancha2.getPosition().x, lancha2.getPosition().y));

        window.clear();

        window.clear(backgroundColor); // Limpia la ventana con el color de fondo

        // Desplaza la vista de la ventana
        window.setView(sf::View(sf::FloatRect(0, 0, window.getSize().x + windowOffset, window.getSize().y)));

        // Dibuja las lanchas en la ventana
        lancha1.draw(window);
        lancha2.draw(window);

        window.display();

        cout << "\n";

        sf::sleep(sf::seconds(1.5));
    }

    // Crea una ventana de 640x480x32 con el título SFML window
    sf::RenderWindow window2(sf::VideoMode(100, 200, 32), "Ganador");
    sf::RectangleShape cuadro(sf::Vector2f(100, 200));

    if (lancha1.getDistancia() > lancha2.getDistancia()) {
        cout << "La lancha negra ha ganado la carrera!";
        cuadro.setFillColor(sf::Color::Black);
    }
    else if (lancha1.getDistancia() < lancha2.getDistancia()) {
        cout << "La lancha roja ha ganado la carrera!";
        cuadro.setFillColor(sf::Color::Red);
    }
    else {
        cout << "Ha ocurrido un empate!";
    }

    // Game Loop mientras la ventana esté abierta
    while (window2.isOpen())
    {
        // Creamos un objeto evento
        sf::Event event;
        // Procesamos la pila de eventos
        while (window2.isOpen())
        {
            sf::Event event;
            while (window2.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window2.close();
            }

            window2.clear();
            window2.draw(cuadro);
            window2.display();
        }
    }

    return 0;
}

/*
    29/04:
        - Las barcas se mueven 
        - No muestra mensaje de quien es el ganador
        - No muestra mensaje de si se quiere usar nitro ni las opciones s/n
        - Error con la fuente de texto
        - Poner un fondo
        - Mejorar la estetica de las barcas
        - (Contador que se va actualizando de la distancia a la que se encuentran las barcas)
*/
