#include "Paddle.h"

Paddle::Paddle(float startX, float startY) {
    position.x = startX;
    position.y = startY;
    paddleShape.setSize(Vector2f(80,10)); //rozmiar paletki
    paddleShape.setPosition(position); //ustawienie paletki na pozycje startowa
}

FloatRect Paddle::getPosition() {
    return paddleShape.getGlobalBounds();
}

RectangleShape Paddle::getShape() {
    return paddleShape;
}

void Paddle::moveLeft() {
    position.x -= paddleSpeed;
}

void Paddle::moveRight() {
    position.x += paddleSpeed;
}

void Paddle::update() {
    paddleShape.setPosition(position);
}
