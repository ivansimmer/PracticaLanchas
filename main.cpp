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

    // Bucle de la jugabilidad con los turnos
    const int numTurnos = 5;
    for (int turno = 1; turno <= numTurnos; turno++) {
        cout << "Turno " << turno << endl;

        lancha1.mostrarMensajeNitro(window);
        bool usarNitroLancha1 = lancha1.turnoConInteraccion(window);
        if (usarNitroLancha1) {
            lancha1.usoNitro();
        }
        lancha1.giraDado();
        lancha1.actualizaDistancia();

        lancha2.mostrarMensajeNitro(window);
        bool usarNitroLancha2 = lancha2.turnoConInteraccion(window);
        if (usarNitroLancha2) {
            lancha1.usoNitro();
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

        sf::sleep(sf::seconds(1.5));
    }

    string mensaje;
    if (lancha1.getDistancia() > lancha2.getDistancia()) {
        mensaje =  "La lancha negra ha ganado la carrera!";
    }
    else if (lancha1.getDistancia() < lancha2.getDistancia()) {
        mensaje = "La lancha roja ha ganado la carrera!";
    }
    else {
        mensaje = "Ha ocurrido un empate!";
    }

    // Crear un objeto de texto para mostrar el mensaje de ganador
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) { 
        cerr << "Error al cargar la fuente" << endl;
        return 1; // Salir del programa si hay un error
    }

    sf::Text ganadorText;
    ganadorText.setFont(font);
    ganadorText.setString(mensaje);
    ganadorText.setCharacterSize(48);
    ganadorText.setFillColor(sf::Color::White);
    ganadorText.setStyle(sf::Text::Bold);

    // Centrar el texto en la ventana
    sf::FloatRect textRect = ganadorText.getLocalBounds();
    ganadorText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    ganadorText.setPosition(sf::Vector2f(screenWidth / 2.0f, screenHeight / 2.0f));

    // Bucle principal para mostrar la ventana emergente
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(backgroundColor);
        window.draw(ganadorText); // Dibujar el texto del ganador
        window.display();
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
