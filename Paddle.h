#ifndef PONG_PADDLE_H
#define PONG_PADDLE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Paddle {
private:
    Vector2f position; //przechowywanie pionowej i poziomej pozycji paletki
    RectangleShape paddleShape; //paletka na ekranie
    float paddleSpeed = 0.2f; //liczba pikseli o ile moze poruszyc sie paletka co jedna klatke
public:
    Paddle(float startX, float startY); //konstruktor z poczatkowymi wspolrzednymi paletki jako parametry
    FloatRect getPosition(); //zwraca granice naszej paletki ktore przydadza nam sie do ustalenia kolizji z pilka
    RectangleShape getShape(); //zwraca kopie paletki aby moc ja rysowac w mainie
    void moveLeft(); //od pozycji x odejmujemy paddleSpeed
    void moveRight(); //do pozycji x dodajemy paddleSpeed
    void update(); //akcje przy odswiezeniu jednej klatki gry takie jak ruch paletki, pilki itp.

};


#endif //PONG_PADDLE_H
