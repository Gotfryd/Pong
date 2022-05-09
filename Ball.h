#ifndef PONG_BALL_H
#define PONG_BALL_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Ball {
private:
    Vector2f position; // wiekszosc pol i metod alternatywnie jak w paletce
    RectangleShape ballShape;
    float xVelocity = 0.15f; //pozioma "predkosc" pilki
    float yVelocity = 0.15f; //pionowa "predkosc" pilki
public:
    Ball(float startX, float startY);
    FloatRect getPosition();
    RectangleShape getShape();
    float getXVelocity(); //zwraca pozioma "predkosc" pilki poniewaz inaczej nie mozemy sie do niej odwolac poza klasa (jest prywatna)
    void bounceSides(); //funkcja oblugujaca odbicie sie pilki od obu krawedzi
    void bouncePaddleOrTop(); //funkcja osblugujaca kolizje pilki z paletka lub gorna krawedzia ekranu, zapobiega utknieciu pilki
    void hitBottom(); //funkcja obslugujaca zdarzenie gdy pilka uderzy dolnej krawedzi ekranu
    void update();
};


#endif //PONG_BALL_H
