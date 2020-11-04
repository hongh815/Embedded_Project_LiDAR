#include <SFML/Graphics.hpp>
using namespace sf;
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
#include <time.h>

#define WIDTH 900
#define HEIGHT 600

struct Position {
    float x;
    float y;
};
int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML Mapping System");
    RectangleShape rect;
    Texture t1;
    t1.loadFromFile("mapfiles/img/carup.png");
    Sprite carArr[1];
    carArr[0] = Sprite(t1);
    static const float CAR_Y_CENTER = HEIGHT - (t1.getSize().y + 250.0f);
    static const float CAR_X_CENTER = WIDTH - (t1.getSize().x + 400.0f);
    carArr[0].setRotation(90.f);
    Position carPos;
    carPos.x = CAR_X_CENTER;
    carPos.y = CAR_Y_CENTER;
    
    float frame = 0.f;
    float framespeed = 0.4f;

    Texture t3;
    t3.loadFromFile("mapfiles/img/tree50.png");
    Sprite tree[100];
    for(int i=0; i<100; i++) {
        tree[i] = Sprite(t3);
    }

    const float treeSpeed = 0.05f;

    Position treePos;
    treePos.x = CAR_X_CENTER+10;
    treePos.y = CAR_Y_CENTER+10;
    int index = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        if(Keyboard::isKeyPressed(Keyboard::Right)) {
            carPos.x += 0.1f;
        } 
        else if(Keyboard::isKeyPressed(Keyboard::Left)) {
            carPos.x -= 0.1f;
        }
        if(Keyboard::isKeyPressed(Keyboard::Up)) {
            carPos.y -= 0.1f;
        } 
        else if(Keyboard::isKeyPressed(Keyboard::Down)) {
            carPos.y += 0.1f;
        }
        

        if(treePos.y <= 0) {
            treePos.y = HEIGHT;
        } else {
            treePos.y += treeSpeed;
        }
        
        tree[0].setPosition(treePos.x, treePos.y);
//        tree[1].setPosition(treePos.x+10, treePos.y+12);
 //       tree[2].setPosition(treePos.x+11, treePos.y+292);
   //     tree[3].setPosition(treePos.x+93, treePos.y+112);
        carArr[0].setPosition(carPos.x+23, carPos.y+23);

        index++;
        window.clear(Color::White);
        window.draw(tree[0]);
     //   window.draw(tree[1]);
       // window.draw(tree[2]);
      //  window.draw(tree[3]);
        window.draw(carArr[0]);
        window.display();
    }
    return 0;
}


