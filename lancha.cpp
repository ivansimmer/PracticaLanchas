// lancha.cpp

#include "lancha.h"
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

Lancha::Lancha(string nombreLancha, sf::Color colorLancha) : 
    velocidad(0), distancia(0), nitro(1), nombre(nombreLancha), color(colorLancha) {}

void Lancha::giraDado() {
    int giro = rand() % 6 + 1;
    cout << "Puntos obtenidos en el dado: " << giro << endl;
    velocidad = velocidad + giro; // Sumo la velocidad con los puntos obtenidos en el dado
    cout << "La velocidad actual es: " << velocidad << "\n";
}

bool Lancha::turnoConInteraccion(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return false;
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (botonSi.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                return true;
            }
            else if (botonNo.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                return false;
            }
        }
    }
    return false;
}

void Lancha::mostrarMensajeNitro(sf::RenderWindow& window) {
    sf::Font font;
    font.loadFromFile("arial.ttf");
    mensajeNitro.setFont(font);
    mensajeNitro.setString("¿Usar nitro?");
    mensajeNitro.setCharacterSize(30);
    mensajeNitro.setPosition(100, 100);

    botonSi.setSize(sf::Vector2f(80, 50));
    botonSi.setFillColor(sf::Color::Green);
    botonSi.setPosition(100, 200);

    botonNo.setSize(sf::Vector2f(80, 50));
    botonNo.setFillColor(sf::Color::Red);
    botonNo.setPosition(200, 200);

    window.draw(mensajeNitro);
    window.draw(botonSi);
    window.draw(botonNo);
    window.display();
}

int Lancha::usoNitro() {
    if (nitro > 0) {
        int random = rand() % 2; // Numero random entre 0 y 1
        if (random == 0) {
            velocidad /= 2.0f; // Divido la velocidad entre dos
        }
        else {
            velocidad *= 2.0f; // Multiplico la velocidad por dos
        }
        return nitro;
    }
}

void Lancha::actualizaDistancia() {
    distancia = distancia + velocidad * 30;
}

float Lancha::getDistancia() const {
    return distancia;
}

std::string Lancha::getNombre() const {
    return nombre;
}

void Lancha::setPosition(sf::Vector2f nuevaPosicion) {
    // Asigna la nueva posición a la lancha
    posicion = nuevaPosicion;
}

sf::Vector2f Lancha::getPosition() const {
    return posicion;
}

void Lancha::draw(sf::RenderWindow& window) const {
    sf::RectangleShape boatShape(sf::Vector2f(50, 30));
    boatShape.setFillColor(color); // Cambia el color de la lancha si lo deseas
    boatShape.setPosition(posicion.x + distancia, posicion.y); // Cambia la posición de la lancha si lo deseas
    window.draw(boatShape);
}
