// lancha.h

#ifndef lancha_h // Verifico si no esta definido. En ese caso lo añado al archivo. Si ya esta definido, el bloque entre #ifndef y #endif se omite
#define lancha_h

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Lancha {
private:
    float velocidad;
    float distancia;
    int nitro;
    string nombre;
    sf::Color color; // Agregamos un color como atributo
    sf::Vector2f posicion; // Atributo para almacenar la posición de la lancha

public:
    Lancha(string nombreLancha, sf::Color colorLancha);

    void giraDado();

    int usoNitro();

    void actualizaDistancia();

    float getDistancia() const;

    string getNombre() const;

    void draw(sf::RenderWindow& window) const;

    void setPosition(sf::Vector2f nuevaPosicion);

    sf::Vector2f getPosition() const; // Declaramos el método getPosition() que devuelve la posición de la lancha

};

#endif // lancha_h
#pragma once
