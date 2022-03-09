#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include<sstream>



int main(){

    int nSize = 5 , nWidth = 600;
    int nGridSize = nWidth / nSize;
    //sf::RenderWindow window(sf::VideoMode(sf::Vector2f(600 , 600)) , "Sand Falling");
    sf::RenderWindow window(sf::VideoMode(nWidth, nWidth), "Falling Sand", sf::Style::Close);
    window.setFramerateLimit(60);

    int nPrevState[nGridSize][nGridSize];
    int nGrid[nGridSize][nGridSize];

    for(int i = 0 ; i < nGridSize - 1; i++){
        for(int j = 0 ; j < nGridSize - 1 ; j++){
            nPrevState[i][j] = 0;
            nGrid[i][j] = 0;
        }
    }
    //sf::Clock clock;
    //float fLastTime = 0;

    while(window.isOpen()){
        sf::Event evnt;

        //float fCurrentTime = clock.restart().asSeconds();
        //float fps = 1 / (fLastTime - fCurrentTime);
        //fLastTime = fCurrentTime;

        while(window.pollEvent(evnt)){
            if(evnt.type == sf::Event::Closed)
                window.close();


            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                sf::Vector2i mPos = sf::Mouse::getPosition(window);
                int nGridx = floor(mPos.x / nSize);
                int nGridy = floor(mPos.y / nSize);
                nGrid[nGridx][nGridy] = 1;
            }

        }
        /*
            updating the grid
        */

        for(int i = 0 ; i< nGridSize - 1; i++){
            for(int j = 0 ; j< nGridSize - 1; j++){
                if(nPrevState[i][j] == 1){

                        if(nPrevState[i][j + 1] == 0){
                            nGrid[i][j] = 0;
                            nGrid[i][j + 1] = 1;
                        }
                        else if(nPrevState[i-1][j+1] == 0 && nPrevState[i+1][j+1] == 0){
                            bool direction = rand() % 2;
                            if(direction == 0){
                                nGrid[i][j] = 0;
                                nGrid[i-1][j+1] = 1;
                            }
                            if(direction == 1){
                                nGrid[i][j] = 0;
                                nGrid[i+1][j+1] = 1;
                            }

                        }
                        else if(nPrevState[i-1][j+1] == 0){
                            nGrid[i][j] = 0;
                            nGrid[i-1][j+1] = 1;
                        }
                        else if(nPrevState[i+1][j+1] == 0){
                            nGrid[i][j] = 1;
                            nGrid[i+1][j+1] = 0;
                        }

                }

            }
        }


        window.clear(sf::Color(100 , 100 , 100));

        /*
            drawing the grid
        */
        for(int i = 0 ; i< nGridSize  - 1 ; i++){
            for(int j = 0 ; j< nGridSize  - 1 ; j++){
                if(nGrid[i][j] == 1){
                    sf::RectangleShape shape;
                    shape.setFillColor(sf::Color(255 , 255 , 0));
                    shape.setSize(sf::Vector2f(nSize , nSize));
                    shape.setPosition(sf::Vector2f(i * nSize , j * nSize));
                    window.draw(shape);
                }
                nPrevState[i][j] = nGrid[i][j];
            }
        }
        window.display();
    }

    return 0;
}
