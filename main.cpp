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

        // Declaracion factorNitro de las lanchas
        float lanchaFactorNitro1 = lancha1.getFactorNitro();
        float lanchaFactorNitro2 = lancha2.getFactorNitro();

        // Calcular el desplazamiento de la ventana
        float lanchaDistancia1 = lancha1.getDistancia() * lanchaFactorNitro1;
        float lanchaDistancia2 = lancha2.getDistancia() * lanchaFactorNitro2;
        float lanchaDistancia = max(lanchaDistancia1, lanchaDistancia2);
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

    sf::Color fondoColor;
    if (lancha1.getDistancia() > lancha2.getDistancia()) {
        cout << "La lancha negra ha ganado la carrera!";
        fondoColor = sf::Color::Black;
    }
    else if (lancha1.getDistancia() < lancha2.getDistancia()) {
        cout << "La lancha roja ha ganado la carrera!";
        fondoColor = sf::Color::Red;
    }
    else {
        cout << "Ha ocurrido un empate!";
        fondoColor = sf::Color::White;
    }

    window2.clear(fondoColor);

    // Crea un cuadro con el color del ganador
    sf::RectangleShape cuadro(sf::Vector2f(100, 200));
    cuadro.setFillColor(fondoColor);

    // Dibuja el cuadro en la ventana
    window2.draw(cuadro);

    // Muestra la ventana
    window2.display();

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
        }
    }

    return 0;
}
