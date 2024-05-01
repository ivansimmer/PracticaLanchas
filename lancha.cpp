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
