#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include "TextDisplay.h"
#include "Pickup.h"
#include "Wall.h"
#include "Powerup.h"
#include "Room.h"
#include "Heal.h"
#include <vector>

int main(int, char const**)
{
    srand(5);

    //Variables
    int counter = 0;
    int counter2 = 0;
    int counter3 = 0;
    sf::Clock clock1;
    sf::Clock clock2;
    sf::Clock clock3;

    bool isFocused = true;

    sf::Clock coolDown;
    sf::Clock echoSlamCoolDown;

    //********************* NETWORK *********************************

    sf::Vector2f prevPosition;

    sf::Vector2f buffPos;

    sf::Packet packet;

    sf::IpAddress ip;
    sf::TcpSocket socket;
    char connectionType;

    std::cout << "Enter (s) for server, enter (c) for client >> ";
    std::cin >> connectionType;

    if(connectionType == 's') {
        sf::TcpListener listener;
        listener.listen(2241);
        listener.accept(socket);
    }
    else
        std::cout << "Input ip address >> ";
        std::string ipBuff;
        std::cin >> ipBuff;
        ip = sf::IpAddress(ipBuff);
        socket.connect(ip, 2241);

    socket.setBlocking(false);

    //*************************** FONTS **************************************

    sf::Font textFont;
    textFont.loadFromFile("sansation.ttf");

    //**************************** TEXTURES **************************************

    //CharacterTexture
    sf::Texture textureCharacter;
    if(!textureCharacter.loadFromFile("char.png"))
        return EXIT_FAILURE;

    //Enemy texture
    sf::Texture enemyTexture;
    if(!enemyTexture.loadFromFile("zombie.png"))
        return EXIT_FAILURE;

    //Fireball texture
    sf::Texture fireball;
    if(!fireball.loadFromFile("fireball.png"))
        return EXIT_FAILURE;

    //Pickup texture
    sf::Texture coinTexture;
    if(!coinTexture.loadFromFile("Coins16x16.png"))
        return EXIT_FAILURE;

    //Powerup texture
    sf::Texture powerupTexture;
    if(!powerupTexture.loadFromFile("powerups.png"))
        return EXIT_FAILURE;

    //Heal texture
    sf::Texture healTexture;
    if(!healTexture.loadFromFile("GemsAndHearts.png"))
        return EXIT_FAILURE;

    //Wall texture
    sf::Texture wallTexture;
    if(!wallTexture.loadFromFile("Back_002.png"))
        return EXIT_FAILURE;

    //Box texture
    sf::Texture boxTexture;
    if(!boxTexture.loadFromFile("Crate_001.png"))
        return EXIT_FAILURE;

    //Echo slam texture
    sf::Texture echoSlamTexture;
    if(!echoSlamTexture.loadFromFile("echoSlam.png"))
        return EXIT_FAILURE;

    //******************************* SOUNDS *****************************************

    //Main theme music
    sf::Music mainTheme;
    if(!mainTheme.openFromFile("mainTheme2.wav")) {
        return EXIT_FAILURE;
    }
    mainTheme.setVolume(4);
    mainTheme.setLoop(true);
    mainTheme.play();

    //Shot sound
    sf::Music shotSound;
    if(!shotSound.openFromFile("fireballSound.wav")) {
        return EXIT_FAILURE;
    }
    shotSound.setVolume(30);
    shotSound.setPitch(3);
    shotSound.setPosition(sf::Vector3f(0,0,0));

    //Coin pickup sound
    sf::Music coinSound;
    if(!coinSound.openFromFile("coin.wav")) {
        return EXIT_FAILURE;
    }
    coinSound.setVolume(50);

    //Echo slam sound
    sf::Music echoSlamSound;
    if(!echoSlamSound.openFromFile("echoSlam.wav")) {
        return EXIT_FAILURE;
    }
    echoSlamSound.setVolume(40);

    //Collision
    sf::Music collisionSound;
    if(!collisionSound.openFromFile("collision.ogg")) {
        return EXIT_FAILURE;
    }
    collisionSound.setVolume(60);

    //***************************** VECTOR ARRAYS ************************************

    //Powerup array
    std::vector<Powerup>::const_iterator powerupIter;
    std::vector<Powerup> powerupArr;

    //Projectile vector array
    std::vector<Projectile>::const_iterator projectileIterator;
    std::vector<Projectile> projectileArray;

    //Enemy vector array
    std::vector<Enemy>::const_iterator enemyArrayIter;
    std::vector<Enemy> enemyArray;

    //Picup vector array
    std::vector<Pickup>::const_iterator pickupIter;
    std::vector<Pickup> pickupArr;

    //Wall vector
    std::vector<Wall>::const_iterator wallIter;
    std::vector<Wall> wallArr;

    // TextDisplay vector array
    std::vector<TextDisplay>::const_iterator textIter;
    std::vector<TextDisplay> textDisplayArr;

    //Heal vector array
    std::vector<Heal>::const_iterator healIter;
    std::vector<Heal> healArr;

    //**************************** GENERATING MAIN GAMEPLAY OBJECTS **********************************

    //Generating the main window
    sf::RenderWindow window(sf::VideoMode(1024, 680), "SFML window", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    //Random room generating
    // for(int i = 0; i < 4; i++) {
    //     int startRoomX = rand() % 2500 - 500;
    //     int startRoomY = rand() % 2500 - 500;
    //     Room room1(startRoomX, startRoomY, wallArr);
    //     //Enemy generation
    //     Enemy::spawnEnemies(6, room1, enemyArray, enemyTexture);
    // }

    //Location generating
    Room room1(0,0,8,8,2,3, wallArr, wallTexture, boxTexture);
    Enemy::spawnEnemies(6, room1, enemyArray, enemyTexture, textFont);
    Room room2(0-8*Wall::getProps(), 0+8*Wall::getProps(), 8, 8, 4, 4, wallArr, wallTexture, boxTexture);
    Enemy::spawnEnemies(6, room2, enemyArray, enemyTexture, textFont);
    Room room3(0+8*Wall::getProps(), 0+8*Wall::getProps(), 8, 8, 3, 4, wallArr, wallTexture, boxTexture);
    Enemy::spawnEnemies(6, room3, enemyArray, enemyTexture, textFont);
    Room room4(0,0+16*Wall::getProps(), 8,8, 1, 3, wallArr, wallTexture, boxTexture);
    Enemy::spawnEnemies(6, room4, enemyArray, enemyTexture, textFont);

    //******************************* GAMEPLAY OBJECTS *************************************

    //Player object
    Player player1;
    player1.sprite.setTexture(textureCharacter);
    player1.rect.setPosition(300,300);

    Player player2;
    player2.sprite.setTexture(textureCharacter);
    player2.rect.setPosition(300, 300);

    //Powerup object
    Powerup powerup1;
    powerup1.sprite.setTexture(powerupTexture);
    powerup1.rect.setPosition(420,420);
    powerupArr.push_back(powerup1);

    //Pickup object
    Pickup coin;
    coin.sprite.setTexture(coinTexture);
    coin.rect.setPosition(500,500);
    Pickup coin2;
    coin2.sprite.setTexture(coinTexture);
    coin2.rect.setPosition(400,400);
    pickupArr.push_back(coin);
    pickupArr.push_back(coin2);

    //TextDisply object
    TextDisplay textDisplay1;
    textDisplay1.text.setPosition(player1.rect.getPosition().x + 16, player1.rect.getPosition().y - 16);
    textDisplay1.text.setFont(textFont);
    textDisplay1.text.setColor(sf::Color::Black);
    textDisplay1.text.setCharacterSize(16);
    textDisplay1.text.setString(std::to_string(player1.hp));
    textDisplayArr.push_back(textDisplay1);

    //Heal object
    Heal heal1(healTexture, room4.startX + ((room4.endX - room4.startX)/2), room4.startY + ((room4.endY - room4.startY)/2), textFont);
    healArr.push_back(heal1);

    //Projectile object
    Projectile projectile1;
    projectile1.sprite.setTexture(fireball);

    //******************************************** UI TEXT *********************************************

    //Money text
    sf::Text moneyText;
    moneyText.setCharacterSize(18);
    moneyText.setFont(textFont);
    moneyText.setColor(sf::Color::Black);
    moneyText.setPosition(window.getSize().x/2, 0);

    //Hp text
    sf::Text hpText;
    hpText.setCharacterSize(18);
    hpText.setFont(textFont);
    hpText.setColor(sf::Color::Black);
    hpText.setPosition(window.getSize().x/2, 25);   

    //Player view
    sf::View view1;
    view1.setSize(sf::Vector2f(window.getSize().x-100, window.getSize().y-100));
    view1.setCenter(player1.rect.getPosition());
    window.setView(view1);

    //Echo slam icon
    sf::Sprite echoSlamSprite;
    echoSlamSprite.setTexture(echoSlamTexture);

    //Echo slam cooldown text
    sf::Text esCooldown;
    esCooldown.setFont(textFont);
    esCooldown.setCharacterSize(16);
    esCooldown.setColor(sf::Color::Black);

    //******************************************* MAIN LOOP ****************************************************************************8

    while (window.isOpen())
    {

        sf::Time elapsed1 = clock1.getElapsedTime();
        sf::Time elapsed2 = clock2.getElapsedTime();
        sf::Time elapsed3 = clock3.getElapsedTime();

        prevPosition = player1.rect.getPosition();

        window.setView(view1);

        //****************************** HANDLING EVENTS ******************************

        sf::Event event;//Enemy generation
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            //Zoom in/out
            if(event.type == sf::Event::MouseWheelMoved) {
                if(event.mouseWheel.delta > 0)
                    view1.zoom(0.95);
                else if(event.mouseWheel.delta < 0)
                    view1.zoom(1.05);
            }
            if(event.type == sf::Event::LostFocus) {
                isFocused = false;
            }
            if(event.type == sf::Event::GainedFocus) {
                isFocused = true;
            }
        }

        // Clear screen
        window.clear(sf::Color::White);

        //**************************** RENDERING OBJECTS *********************************

        //Wall rendering
        counter = 0;
        for(wallIter = wallArr.begin(); wallIter != wallArr.end(); wallIter++) {
            if(wallArr[counter].destructable) {
                wallArr[counter].rect.setFillColor(sf::Color::Yellow);
            }
            window.draw(wallArr[counter].rect);
            window.draw(wallArr[counter].sprite);
            counter++;
        }

        //Player rendering
        window.draw(player1.sprite);
        window.draw(player2.sprite);

        //Draw projectiles
        int prCounter = 0;
        for(projectileIterator = projectileArray.begin(); projectileIterator != projectileArray.end(); projectileIterator++) {
            projectileArray[prCounter].update();
            window.draw(projectileArray[prCounter].sprite);
            prCounter++;
        }

        //Draw enemies
        int enemyCoutner = 0;
        for(enemyArrayIter = enemyArray.begin(); enemyArrayIter != enemyArray.end(); enemyArrayIter++) {
            enemyArray[enemyCoutner].update();
            enemyArray[enemyCoutner].updateMovement();
            window.draw(enemyArray[enemyCoutner].sprite);
            window.draw(enemyArray[enemyCoutner].text);
            enemyCoutner++;
        }

        //Draw coins
        counter = 0;
        for(pickupIter = pickupArr.begin(); pickupIter != pickupArr.end(); pickupIter++) {
            pickupArr[counter].update();
            window.draw(pickupArr[counter].sprite);
            counter++;
        }

        //Draw powerup
        counter = 0;
        for(powerupIter = powerupArr.begin(); powerupIter != powerupArr.end(); powerupIter++) {
            powerupArr[counter].update();
            window.draw(powerupArr[counter].sprite);
            counter++;
        }

        //Draw shop heal
        counter = 0;
        for(healIter = healArr.begin(); healIter != healArr.end(); healIter++) {
            window.draw(healArr[counter].sprite);
            window.draw(healArr[counter].text);
            counter++;
        }

        //Draw text
        counter = 0;
        for(textIter = textDisplayArr.begin(); textIter != textDisplayArr.end(); textIter++) {
            textDisplayArr[counter].update();
            window.draw(textDisplayArr[counter].text);
            counter++;
        }

        //*************************************** COLLISIONS *******************************************

        //Wall colision with player
        counter = 0;
        for(wallIter = wallArr.begin(); wallIter != wallArr.end(); wallIter++) {
            if(player1.rect.getGlobalBounds().intersects(wallArr[counter].rect.getGlobalBounds())) {
                if(player1.direction == 1) {
                    player1.canMoveUp = false;
                    player1.rect.move(0,player1.movementSpeed+2);
                    player1.update();
                }
                else if(player1.direction == 2) {
                    player1.canMoveDown = false;
                    player1.rect.move(0,-player1.movementSpeed-2);
                    player1.update();
                }
                else if(player1.direction == 3) {
                    player1.canMoveLeft = false;
                    player1.rect.move(player1.movementSpeed+2,0);
                    player1.update();
                }
                else if(player1.direction == 4) {
                    player1.canMoveRight = false;
                    player1.rect.move(-player1.movementSpeed-2,0);
                    player1.update();   
                }
            }
            counter++;
        }

        //Wall colision with enemy
        counter = 0;
        for(enemyArrayIter = enemyArray.begin(); enemyArrayIter != enemyArray.end(); enemyArrayIter++) {
            counter2 = 0;
            for(wallIter = wallArr.begin(); wallIter != wallArr.end(); wallIter++) {
                if(enemyArray[counter].rect.getGlobalBounds().intersects(wallArr[counter2].rect.getGlobalBounds())) {
                    if(enemyArray[counter].direction == 1) {
                        enemyArray[counter].canMoveUp = false;
                        enemyArray[counter].rect.move(0,enemyArray[counter].movementSpeed);
                        enemyArray[counter].update();
                    }
                    else if(enemyArray[counter].direction == 2) {
                        enemyArray[counter].canMoveDown = false;
                        enemyArray[counter].rect.move(0,-enemyArray[counter].movementSpeed);
                        enemyArray[counter].update();
                    }
                    else if(enemyArray[counter].direction == 3) {
                        enemyArray[counter].canMoveLeft = false;
                        enemyArray[counter].rect.move(enemyArray[counter].movementSpeed,0);
                        enemyArray[counter].update();
                    }
                    else if(enemyArray[counter].direction == 4) {
                        enemyArray[counter].canMoveRight = false;
                        enemyArray[counter].rect.move(-enemyArray[counter].movementSpeed,0);
                        enemyArray[counter].update();
                    }
                }
                counter2++;
            }
            counter++;
        }

        //Player collision with pickup
        counter = 0;
        for(pickupIter = pickupArr.begin(); pickupIter != pickupArr.end(); pickupIter++) {
            if(pickupArr[counter].rect.getGlobalBounds().intersects(player1.rect.getGlobalBounds())) {
                if(pickupArr[counter].isCoin) {
                    coinSound.play();
                    player1.money += 15;
                }
                pickupArr[counter].destroy = true;
            }
            counter++;
        }

        //Player collision with shop heal
        counter = 0;
        for(healIter = healArr.begin(); healIter != healArr.end(); healIter++) {
            if(coolDown.getElapsedTime().asSeconds() >= healArr[counter].coolDownDuration && healArr[counter].isOnCoolDown == true) {
                healArr[counter].isOnCoolDown = false;
                healArr[counter].update();
            }
            if(player1.rect.getGlobalBounds().intersects(healArr[counter].rect.getGlobalBounds())) {
                if(player1.money >= healArr[counter].price && healArr[counter].isOnCoolDown == false) {
                    player1.money -= healArr[counter].price;
                    player1.hp += 25;
                    healArr[counter].isOnCoolDown = true;
                    coolDown.restart();
                    healArr[counter].update();
                }
            }
            counter++;
        }

        //Player collision with powerups
        counter = 0;
        for(powerupIter = powerupArr.begin(); powerupIter != powerupArr.end(); powerupIter++) {
            if(player1.rect.getGlobalBounds().intersects(powerupArr[counter].rect.getGlobalBounds())) {
                player1.powerupLevel++;
                powerupArr[counter].destroy = true;
            }
            counter++;
        }

        //Enemy Aggro
        counter = 0;
        for(enemyArrayIter = enemyArray.begin(); enemyArrayIter != enemyArray.end(); enemyArrayIter++) {
            if(enemyArray[counter].isAggro) {
                if(std::abs(enemyArray[counter].rect.getPosition().x - player1.rect.getPosition().x) >= 250 || std::abs(enemyArray[counter].rect.getPosition().y - player1.rect.getPosition().y) >= 250) {
                    enemyArray[counter].isAggro = false;
                    std::cout << "Enemy aggro: false" << std::endl;
                    continue;
                }

                if(elapsed3.asSeconds() >= 1) {
                    clock3.restart();
                    int enemyAction = generateRandom(3);

                    projectile1.attackDamage = enemyArray[counter].attackDamage;

                    if(enemyAction == 1) {
                        if(player1.rect.getPosition().x < enemyArray[counter].rect.getPosition().x && std::abs(player1.rect.getPosition().y - enemyArray[counter].rect.getPosition().y) <= 40) {
                            shotSound.play();
                            projectile1.enemyProjectile = true;
                            projectile1.direction = 3;
                            projectile1.rect.setPosition(enemyArray[counter].rect.getPosition());
                            projectileArray.push_back(projectile1);
                            projectile1.enemyProjectile = false;

                            enemyArray[counter].direction = 3;
                        }

                        if(player1.rect.getPosition().x > enemyArray[counter].rect.getPosition().x && std::abs(player1.rect.getPosition().y - enemyArray[counter].rect.getPosition().y) <= 40) {
                            shotSound.play();
                            projectile1.enemyProjectile = true;
                            projectile1.direction = 4;
                            projectile1.rect.setPosition(enemyArray[counter].rect.getPosition());
                            projectileArray.push_back(projectile1);
                            projectile1.enemyProjectile = false;

                            enemyArray[counter].direction = 4;
                        }

                        if(player1.rect.getPosition().y < enemyArray[counter].rect.getPosition().y && std::abs(player1.rect.getPosition().x - enemyArray[counter].rect.getPosition().x) <= 40) {
                            shotSound.play();
                            projectile1.enemyProjectile = true;
                            projectile1.direction = 1;
                            projectile1.rect.setPosition(enemyArray[counter].rect.getPosition());
                            projectileArray.push_back(projectile1);
                            projectile1.enemyProjectile = false;

                            enemyArray[counter].direction = 1;
                        }

                        if(player1.rect.getPosition().y > enemyArray[counter].rect.getPosition().y && std::abs(player1.rect.getPosition().x - enemyArray[counter].rect.getPosition().x) <= 40) {
                            shotSound.play();
                            projectile1.enemyProjectile = true;
                            projectile1.direction = 2;
                            projectile1.rect.setPosition(enemyArray[counter].rect.getPosition());
                            projectileArray.push_back(projectile1);
                            projectile1.enemyProjectile = false;

                            enemyArray[counter].direction = 2;
                        }
                    }
                }
            }
            counter++;
        }

        //Enemy projectile collides with player
        counter = 0;
        for(projectileIterator = projectileArray.begin(); projectileIterator != projectileArray.end(); projectileIterator++) {
            if(projectileArray[counter].enemyProjectile && projectileArray[counter].rect.getGlobalBounds().intersects(player1.rect.getGlobalBounds())) {
                collisionSound.play();
                projectileArray[counter].destroy = true;
                textDisplay1.text.setString("-" + std::to_string(projectileArray[counter].attackDamage));
                textDisplay1.text.setPosition(player1.rect.getPosition().x + 20, player1.rect.getPosition().y - 20);
                textDisplay1.text.setColor(sf::Color::Black);
                textDisplayArr.push_back(textDisplay1);
                player1.hp -= projectileArray[counter].attackDamage;
            }
        }

        //Projectile collision with enemy
        counter = 0;
        for(projectileIterator = projectileArray.begin(); projectileIterator != projectileArray.end(); projectileIterator++) {
            counter2 = 0;
            for(enemyArrayIter = enemyArray.begin(); enemyArrayIter != enemyArray.end(); enemyArrayIter++) {
                if(!projectileArray[counter].enemyProjectile && projectileArray[counter].rect.getGlobalBounds().intersects(enemyArray[counter2].rect.getGlobalBounds())) {
                    collisionSound.play();
                    enemyArray[counter2].isAggro = true;
                    textDisplay1.text.setString("-" + std::to_string(player1.attackDamage));
                    textDisplay1.text.setPosition(enemyArray[counter2].rect.getPosition().x + 16, enemyArray[counter2].rect.getPosition().y - 16);
                    textDisplay1.text.setColor(sf::Color::Red);
                    textDisplayArr.push_back(textDisplay1);
                    projectileArray[counter].destroy = true;
                    enemyArray[counter2].hp -= player1.attackDamage;
                    if(enemyArray[counter2].hp <= 0) {
                        enemyArray[counter2].alive = false;
                    }
                }
                counter2++;
            }
            counter++;
        }

        // Projectile collision with wall
        counter = 0;
        for(projectileIterator = projectileArray.begin(); projectileIterator != projectileArray.end(); projectileIterator++) {
            counter2 = 0;
            for(wallIter = wallArr.begin(); wallIter != wallArr.end(); wallIter++) {
                if(projectileArray[counter].rect.getGlobalBounds().intersects(wallArr[counter2].rect.getGlobalBounds())) {
                    projectileArray[counter].destroy = true;
                    if(wallArr[counter2].destructable == true) {
                        wallArr[counter2].hp -= player1.attackDamage;
                    }
                }
                counter2++;
            }
            counter++;
        }

        //Enemy collision with player
        if(elapsed2.asSeconds() >= 0.42) {
            counter = 0;
            clock2.restart();
            for(enemyArrayIter = enemyArray.begin(); enemyArrayIter != enemyArray.end(); enemyArrayIter++) {
                if(enemyArray[counter].rect.getGlobalBounds().intersects(player1.rect.getGlobalBounds())) {
                    textDisplay1.text.setString(std::to_string(player1.hp));
                    textDisplay1.text.setPosition(player1.rect.getPosition().x + 16, player1.rect.getPosition().y - 16);
                    textDisplayArr.push_back(textDisplay1);
                    player1.hp -= enemyArray[counter].attackDamage;
                    player1.powerupLevel = 0;
                }
                counter++;
            }
        }

        //Continue movement if no wall around
        bool canReset = true;
        counter = 0;
        for(wallIter = wallArr.begin(); wallIter != wallArr.end(); wallIter++) {
            if(wallArr[counter].rect.getGlobalBounds().intersects(player1.rect.getGlobalBounds())) {
                canReset = false;
            }
        }
        if(canReset)
            player1.resetMoveLimits();

        //************************************* DESTROY ITEMS ***************************************

        //Destroy picked up powerup
        counter = 0;
        for(powerupIter = powerupArr.begin(); powerupIter != powerupArr.end(); powerupIter++) {
            if(powerupArr[counter].destroy == true) {
                powerupArr.erase(powerupIter);
                break;
            }
            counter++;
        }

        //Destroy wall
        counter = 0;
        for(wallIter = wallArr.begin(); wallIter != wallArr.end(); wallIter++) {
            if(wallArr[counter].hp < 0) {
                wallArr.erase(wallIter);
                break;
            }
            counter++;
        }

        //Destroy coins
        counter = 0;
        for(pickupIter = pickupArr.begin(); pickupIter != pickupArr.end(); pickupIter++) {
            if(pickupArr[counter].destroy == true) {
                pickupArr.erase(pickupIter);
                break;
            }
            counter++;
        }

        //Destroy text
        counter = 0;
        for(textIter = textDisplayArr.begin(); textIter != textDisplayArr.end(); textIter++) {
            if(textDisplayArr[counter].destroy == true) {
                textDisplayArr.erase(textIter);
                break;
            }
            counter++;
        }

        //Destroy dead enemy
        counter = 0;
        for(enemyArrayIter = enemyArray.begin(); enemyArrayIter != enemyArray.end(); enemyArrayIter++) {
            if(enemyArray[counter].alive == false) {
                if(generateRandom(5) == 4) {
                    coin.rect.setPosition(enemyArray[counter].rect.getPosition().x, enemyArray[counter].rect.getPosition().y);
                    pickupArr.push_back(coin);
                }
                if(generateRandom(10) == 5) {
                    powerup1.rect.setPosition(enemyArray[counter].rect.getPosition());
                    powerupArr.push_back(powerup1);
                }
                enemyArray.erase(enemyArrayIter);
                break;
            }
            counter++;
        }

        //Destory projectiles
        counter = 0;
        for(projectileIterator = projectileArray.begin(); projectileIterator != projectileArray.end(); projectileIterator++) {
            if(projectileArray[counter].destroy == true) {
                projectileArray.erase(projectileIterator);
                break;
            }
        }

        //************************************** OTHER **********************************************

        //Fire Missle
        if(elapsed1.asSeconds() >= 0.1 && isFocused) {
            clock1.restart();
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                projectile1.direction = player1.direction;
                projectile1.rect.setPosition(player1.rect.getPosition().x+player1.rect.getSize().x/2 - projectile1.rect.getSize().x/2, player1.rect.getPosition().y+player1.rect.getSize().y/2-projectile1.rect.getSize().y/2);
                projectile1.sprite.setTextureRect(sf::IntRect(0,0,32,32));
                projectileArray.push_back(projectile1);
                shotSound.play();

                if(player1.powerupLevel == 1) {
                    projectile1.rect.setPosition(player1.rect.getPosition().x+player1.rect.getSize().x/2+16 - projectile1.rect.getSize().x/2, player1.rect.getPosition().y+player1.rect.getSize().y/2+16 - projectile1.rect.getSize().y/2);
                    projectileArray.push_back(projectile1);
                }

                if(player1.powerupLevel >= 2) {
                    for(int i = 1; i <= 4; i++) {
                        if(i == player1.direction) {
                            continue;
                        }
                        projectile1.direction = i;
                        projectileArray.push_back(projectile1);
                    }
                }
            }
        }

        if(!player1.echoSlam.readyToCast && isFocused) {
            if(echoSlamCoolDown.getElapsedTime().asSeconds() >= player1.echoSlam.getSpellCoolDown()) {
                player1.echoSlam.readyToCast = true;
            }
        }

        //Echo slam
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && player1.echoSlam.readyToCast && isFocused) {
            counter = 0;
            for(enemyArrayIter = enemyArray.begin(); enemyArrayIter != enemyArray.end(); enemyArrayIter++) {
                if(player1.rect.getPosition().x - enemyArray[counter].rect.getPosition().x <= 300 && player1.rect.getPosition().x - enemyArray[counter].rect.getPosition().x >= -300) {
                    if(player1.rect.getPosition().y - enemyArray[counter].rect.getPosition().y <= 300 && player1.rect.getPosition().y - enemyArray[counter].rect.getPosition().y >= -300) {
                        echoSlamSound.play();
                        textDisplay1.text.setString("-" + std::to_string(player1.echoSlam.getDamage()));
                        textDisplay1.text.setPosition(enemyArray[counter].rect.getPosition().x + 16, enemyArray[counter].rect.getPosition().y - 16);
                        textDisplay1.text.setColor(sf::Color::Red);
                        textDisplayArr.push_back(textDisplay1);
                        enemyArray[counter].hp -= player1.echoSlam.getDamage();
                        if(enemyArray[counter].hp <= 0) {
                            enemyArray[counter].alive = false;
                        }
                    }
                }
                counter++;
            }
            player1.echoSlam.readyToCast = false;
            echoSlamCoolDown.restart();
        }

        moneyText.setPosition(view1.getCenter().x-300, view1.getCenter().y-200);
        moneyText.setString("Money: "+std::to_string(player1.money));
        hpText.setPosition(view1.getCenter().x-300, view1.getCenter().y-180);
        hpText.setString("HP: "+std::to_string(player1.hp));        
        echoSlamSprite.setPosition(view1.getCenter().x-300, view1.getCenter().y-100);
        window.draw(moneyText);
        window.draw(hpText);
        if(player1.echoSlam.readyToCast)
            window.draw(echoSlamSprite);
        else {
            esCooldown.setString(std::to_string(player1.echoSlam.getSpellCoolDown() - (int)echoSlamCoolDown.getElapsedTime().asSeconds()));
            esCooldown.setPosition(view1.getCenter().x-300, view1.getCenter().y-100);
            window.draw(esCooldown);
        }

        if(isFocused) {
            player1.update();
            player1.updateMovement();
        }

        if(prevPosition != player1.rect.getPosition()) {
            packet << player1.rect.getPosition().x << player1.rect.getPosition().y;
            socket.send(packet);
        }

        socket.receive(packet);
        if(packet >> buffPos.x >> buffPos.y) {
            player2.rect.setPosition(buffPos);
            player2.update();
            player2.updateMovement();
        }

        view1.setCenter(player1.rect.getPosition());
        window.display();
    }

    return EXIT_SUCCESS;
}