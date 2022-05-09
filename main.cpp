#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Paddle.h"
#include "Ball.h"
using namespace sf;

int main() {

    int windowWidth = 1024; //szerokosc okna
    int windowHeight = 768; //wysokosc okna
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong"); //okno o podanych wymiarach i tytule

    unsigned int lives = 3; //nieujemne zycia gracza
    unsigned int score = 0; //nieujemny wynik gracza

    bool gameRunning = true; //na podstawie tej zmiennej okresle czy na ekranie ma sie wyswietlac dzialajaca gra czy ekran przegranej

    Paddle paletka (windowWidth/2, windowHeight-20);
    Ball pilka (windowWidth/2, 1);

    Font czcionka;
    czcionka.loadFromFile("calibri.ttf"); //zaladowanie czcionki "calibri.ttf"

    Text hud; //stworzenie i ustawienie parametrow napisu podczas rozgrywki
    hud.setFont(czcionka);
    hud.setCharacterSize(50);
    hud.setFillColor(Color::White);

    Text gameOver; //stworzenie i ustawienie parametrow napisu w przypadku przegranej
    gameOver.setFont(czcionka);
    gameOver.setCharacterSize(80);
    gameOver.setFillColor(Color::White);
    gameOver.setPosition(100,100);


    sf::SoundBuffer BounceSoundbuffer; //stworzenie, zaladowanie, i przyciszenie dzwieku odbicia
    BounceSoundbuffer.loadFromFile("Bounce.wav");
    sf::Sound BounceSound;
    BounceSound.setVolume(25);
    BounceSound.setBuffer(BounceSoundbuffer);

    sf::SoundBuffer MissSoundbuffer; //stworzenie, zaladowanie, i przyciszenie dzwieku skucia
    MissSoundbuffer.loadFromFile("Miss.wav");
    sf::Sound MissSound;
    MissSound.setVolume(25);
    MissSound.setBuffer(MissSoundbuffer);


    while (window.isOpen()) //glowna petla renderujaca klatki gdy okno jest otwarte
    {
        Event event;
        while (window.pollEvent(event)) //petla sprawdzajaca wydarzenia ktore zadzialy sie w oknie
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if(gameRunning == true) { //wykonujacy sie kod gry gdy zmienna gameRunning zwraca true
            if (Keyboard::isKeyPressed(Keyboard::Left)) //sterowanie paletka w lewo
            {
                paletka.moveLeft();
            }
            else if (Keyboard::isKeyPressed(Keyboard::Right)) //sterowanie paletka w prawo
            {
                paletka.moveRight();
            }
            else if (Keyboard::isKeyPressed(Keyboard::Escape)) //wyjscie z gry za pomoca klawisza Escape
            {
                window.close();
            }
            if (pilka.getPosition().top >windowHeight) //zdarzenie gdy pilka dotknie dolnej krawedzi (odbije sie, odejmie 1 zycie i odtworzy dzwiek)
            {
                MissSound.play();
                pilka.hitBottom();
                lives--;
                if (lives < 1) //jesli skoncza sie zycia ekran zmieni sie na Game Over
                {
                    gameRunning = false;
                }
            }
            if (pilka.getPosition().top <0) //zdarzenie gdy pilka dotknie gornej krawedzi okna (odbije sie, doda 1 punkt do wyniku i odtworzy dzwiek)
            {
                BounceSound.play();
                pilka.bouncePaddleOrTop();
                score++;
            }
            if (pilka.getPosition().left < 0 || pilka.getPosition().left + 10 > windowWidth) //odbicie sie od bokow okna i odtworzenie dzwieku
            {
                BounceSound.play();
                pilka.bounceSides();
            }
            if (pilka.getPosition().intersects(paletka.getPosition())) //odbicie sie pilki od paletki gdy sie dotkna i odtworzenie dzwieku
            {
                BounceSound.play();
                pilka.bouncePaddleOrTop();
            }

            pilka.update(); //aktualizacja pozycji i kierunku pilki
            paletka.update(); //aktualizacja pozycji paletki

            std::stringstream sshud; //strumien napisowy ktory pozwoli mi wyswietlac tekst oraz zmieniajace sie liczby zyc i wyniku w jednym napisie podczas rozgrywki
            sshud << "  Score: " << score << std::endl << "  Lives: " << lives;
            hud.setString(sshud.str());

            std::stringstream ssgover; //strumien napisowy wyswietlany na ekranie porazki
            ssgover << "Game Over!" << std::endl << std::endl << "Your score: " << score << std::endl << std::endl << std::endl << "Press Space to play again";
            gameOver.setString(ssgover.str());



            window.clear(Color(0, 102, 204, 255)); //wyczysczenie okna i ustawienie koloru tla na jasnoniebieski
            window.draw(paletka.getShape()); //rysowanie paletki, pilki i hudu w obecnej klatce
            window.draw(pilka.getShape());
            window.draw(hud);
            window.display(); //wyswietlenie calej klatki
        }
        else{ //ekran przegranej gdy zmienna gameRunning zwraca false
            if (Keyboard::isKeyPressed(Keyboard::Space)) //zmiana zmiennej gameRunning ktora odtworzy petle rozgrywki
            {  // dopiero po wcisnieciu spacji wynik i zycia zresetuja sie aby wynik mogl byc wyswietlony na ekranie porazki
                gameRunning = true;
                score = 0;
                lives = 3;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
            window.clear(Color(0,102,204,255)); //wyczysczenie okna i ustawienie koloru tla na jasnoniebieski
            window.draw(gameOver); //narysowanie napisu Game Over ...
            window.display(); //wyswietlenie calej klatki
        }
    }

    return 0;
}
