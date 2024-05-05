// lancha.cpp

#include "lancha.h"
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

Lancha::Lancha(string nombreLancha, sf::Color colorLancha) : 
    velocidad(0), distancia(0), nitro(1), nombre(nombreLancha), color(colorLancha), factorNitro(1.0f), nitroUsado(false) {}
    // inicializo la velocidad y distancia de la lancha a 0, la nitro a 1, el nombre segun el que recoja como atributo, el color el que reciba,
    // el factor nitro a 1 para que al multiplicarse por este no varie el elemento, y el nitroUsado a falso dado que no se ha usado aun

void Lancha::giraDado() {
    int giro = rand() % 6 + 1;
    cout << "Puntos obtenidos en el dado: " << giro << endl;
    velocidad = velocidad + giro; // Sumo la velocidad con los puntos obtenidos en el dado
    cout << "La velocidad actual es: " << velocidad << "\n";
}

int Lancha::usoNitro() {
    if (nitro > 0 && !nitroUsado) {
        int random = rand() % 2; // Numero random entre 0 y 1
        nitroUsado = true; // Marco que la nitro se ha usado
        if (random == 0) {
            velocidad /= 2.0f; // Divido la velocidad entre dos
            factorNitro /= 2.0f; // Actualizo el valor de factor nitro para que divida
            cout << "El motor de tu lancha ha petado, divide entre dos la velocidad\n";
        }
        else {
            velocidad *= 2.0f; // Multiplico la velocidad por dos
            factorNitro *= 2.0f; // Actualizo el valor de factor nitro para que duplique
            cout << "Tu motor ha mejorado magicamente, duplicas la velocidad\n";
        }
        return nitro;
    }
    cout << "La nitro ya ha sido usada y no puede volverse a usar.\n";
    return 0;
}

void Lancha::actualizaDistancia() {
    distancia = distancia + velocidad * 30 * factorNitro;
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

float Lancha::getFactorNitro()
{
    return factorNitro;
}

void Lancha::draw(sf::RenderWindow& window) const {
    sf::RectangleShape boatShape(sf::Vector2f(50, 30));
    boatShape.setFillColor(color); // Cambia el color de la lancha si lo deseas
    boatShape.setPosition(posicion.x + distancia, posicion.y); // Cambia la posición de la lancha si lo deseas
    window.draw(boatShape);
}
