#include <iostream>
#include <cmath>
#include <SFML\Graphics.hpp>


int main(){

    int nSize = 5 , nWidth = 600;  //  nSize => Size of each cell , nWidth => width of window
    int nGridSize = nWidth / nSize;

    sf::RenderWindow window(sf::VideoMode(nWidth, nWidth), "Falling Sand", sf::Style::Close);
    window.setFramerateLimit(60);

    int nCellType = 1; // Variable to select block type; 1 => Sand ; 2 => Rock
    int nPrevGrid[nGridSize][nGridSize];  // 2D array to save previous state
    int nGrid[nGridSize][nGridSize];  // 2D array to save current state

    // initializing both grids to 0
    for(int i = 0 ; i < nGridSize - 1; i++){
        for(int j = 0 ; j < nGridSize - 1 ; j++){
            nPrevGrid[i][j] = 0;
            nGrid[i][j] = 0;
        }
    }

    // Placing Rock on bottom
    for(int i = 0 ; i <= nGridSize - 1; i++){
        nPrevGrid[nGridSize - 2][i] = 2;
        nGrid[i][nGridSize - 2] = 2;
    }




    while(window.isOpen()){
        sf::Event evnt;

        while(window.pollEvent(evnt)){
            if(evnt.type == sf::Event::Closed)
                window.close();


            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){  // placing the block as per nCellType at cursor location
                sf::Vector2i mPos = sf::Mouse::getPosition(window);
                int nGridx = floor(mPos.x / nSize);
                int nGridy = floor(mPos.y / nSize);
                nGrid[nGridx][nGridy] = nCellType;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){ // press S for sand
                nCellType = 1;
            }if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){  // press D for Rock
                nCellType = 2;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){  // Reseting grids when R is pressed
                for(int i = 0 ; i < nGridSize - 1; i++){
                    for(int j = 0 ; j < nGridSize - 1 ; j++){
                        nPrevGrid[i][j] = 0;
                        nGrid[i][j] = 0;
                    }
                }

                for(int i = 0 ; i <= nGridSize - 1; i++){
                    nPrevGrid[nGridSize - 2][i] = 2;
                    nGrid[i][nGridSize - 2] = 2;
                }

            }

        }


        // Updating the girds
        for(int i = 0 ; i< nGridSize - 1; i++){
            for(int j = 0 ; j< nGridSize - 1; j++){
                if(nPrevGrid[i][j] == nCellType){
                        if(nCellType == 1){  // nCellType = 1 =>  Sand
                            if(nPrevGrid[i][j + 1] == 0 && nPrevGrid[i][j + 1] != 2){
                                nGrid[i][j] = 0;
                                nGrid[i][j + 1] = 1;
                            }
                            else if(nPrevGrid[i-1][j+1] == 0 && nPrevGrid[i+1][j+1] == 0 && nPrevGrid[i-1][j+1] != 2 && nPrevGrid[i+1][j+1] != 2){
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
                            else if(nPrevGrid[i-1][j+1] == 0 && nPrevGrid[i-1][j+1] != 2){
                                nGrid[i][j] = 0;
                                nGrid[i-1][j+1] = 1;
                            }
                            else if(nPrevGrid[i+1][j+1] == 0 && nPrevGrid[i+1][j+1] != 2){
                                nGrid[i][j] = 1;
                                nGrid[i+1][j+1] = 0;
                            }
                        }
                        if(nCellType == 2){  // nCellType = 2 => Rock
                            // do nothing when its a rock
                        }
                }

            }
        }


        window.clear(sf::Color::Black);


        // Drawing the current grid
        for(int i = 0 ; i< nGridSize  - 1 ; i++){
            for(int j = 0 ; j< nGridSize  - 1 ; j++){
                    if(nGrid[i][j] == 1){
                        sf::RectangleShape shape;
                        shape.setFillColor(sf::Color(255 , 200 , 0));
                        shape.setSize(sf::Vector2f(nSize , nSize));
                        shape.setPosition(sf::Vector2f(i * nSize , j * nSize));
                        window.draw(shape);
                    }
                    if(nGrid[i][j] == 2){
                        sf::RectangleShape shape;
                        shape.setFillColor(sf::Color(100 , 100 , 100 , 200));
                        shape.setSize(sf::Vector2f(nSize , nSize));
                        shape.setPosition(sf::Vector2f(i * nSize , j * nSize));
                        window.draw(shape);
                    }
                nPrevGrid[i][j] = nGrid[i][j]; // updating previous grid
            }
        }
        window.display();
    }

    return 0;
}
