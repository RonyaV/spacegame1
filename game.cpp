#include "game.h"

Game::Game(QWidget *parent): QGraphicsView(parent), lives(3) {
    scene = new QGraphicsScene(0, 0, 500, 700, this); //это мои изменения
    setScene(scene);
    setFixedSize(500, 700);

    //Установка фона
    background = new QGraphicsPixmapItem(QPixmap(":/images/background.png").scaled(500, 700));
    scene->addItem(background);

    //Создание корабля
    player = new Player();
    player->setPos(215, 600);
    scene->addItem(player);

    // Текст жизней
    livesText = new QGraphicsTextItem("Жизни: 3");
    livesText->setDefaultTextColor(Qt::white);
    livesText->setFont(QFont("Arial", 16));
    livesText->setPos(10, 10);
    scene->addItem(livesText);

    // Текст таймера
    timerText = new QGraphicsTextItem("Время: 10");
    timerText->setDefaultTextColor(Qt::white);
    timerText->setFont(QFont("Arial", 16));
    timerText->setPos(360, 10);
    scene->addItem(timerText);

    // Таймеры
    meteorTimer = new QTimer(this);
    connect(meteorTimer, &QTimer::timeout, this, &Game::spawnMeteor);
    meteorTimer->start(1000);

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &Game::updateGame);
    gameTimer->start(20);

    // Таймер для уменьшения времени
    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &Game::decreaseTime);
    countdownTimer->start(1000);

    // Кнопка "Продолжить игру"
    continueButton = new QPushButton("Продолжить игру", this);
    continueButton->setGeometry(150, 350, 200, 50);
    continueButton->hide();
    connect(continueButton, &QPushButton::clicked, this, &Game::nextLevel);
}

void Game::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Left) player->setMovingLeft(true);
    if(event->key() == Qt::Key_Right) player->setMovingRight(true);
}

void Game::keyReleaseEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Left) player->setMovingLeft(false);
    if(event->key() == Qt::Key_Right) player->setMovingRight(false);
}

void Game::spawnMeteor() {
    Meteor *meteor = new Meteor();
    meteor->setPos(rand() % 450, -50);
    scene->addItem(meteor);
    meteors.append(meteor);
}

void Game::spawnUFO() {
    Ufo *ufo = new Ufo();
    ufo->setPos(rand() % 450, -50);
    scene->addItem(ufo);
    ufos.append(ufo);
}


void Game::updateGame(){
    player->move();

    if(timeRemaining <= 0){
        if(level == 1){
            //Завершение 1 уровня
            meteorTimer->stop();
            gameTimer->stop();
            continueButton->show();
        } else {
            //Завершение 2 уровня
            endGame();
        }
        return;
    }

    for(auto it = meteors.begin(); it != meteors.end(); ){
        Meteor *meteor = *it;
        meteor->fall();

        if(meteor->collidesWithItem(player)){
            scene->removeItem(meteor);
            delete meteor;
            it = meteors.erase(it);
            lives--;

            // Обновление текста жизней
            livesText->setPlainText(QString("Жизни: %1").arg(lives));
            if (lives <= 0) {
                livesText->setPlainText("Игра окончена!");
                meteorTimer->stop();
                gameTimer->stop();
            }
        } else if (meteor->y() > 700) {
            scene->removeItem(meteor);
            delete meteor;
            it = meteors.erase(it);
        } else {
            ++it;
        }
    }

    if(level == 2){
        for(auto it = ufos.begin(); it != ufos.end(); ){
            Ufo *ufo = *it;
            ufo->fall();

            if(ufo->collidesWithItem(player)){
                scene->removeItem(ufo);
                delete ufo;
                it = ufos.erase(it);
                lives++;

                // Обновление текста жизней
                livesText->setPlainText(QString("Жизни: %1").arg(lives));
                if (lives <= 0) {
                    livesText->setPlainText("Игра окончена!");
                    ufoTimer->stop();
                    gameTimer->stop();
                }
            } else if (ufo->y() > 700) {
                scene->removeItem(ufo);
                delete ufo;
                it = ufos.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void Game::nextLevel(){
    level = 2;
    timeRemaining = 20;
    timerText->setPlainText(QString("Время: %1").arg(timeRemaining));
    continueButton->hide();

    countdownTimer->start(1000);
    meteorTimer->start(800); // Увеличение частоты метеоров
    ufoTimer = new QTimer(this);
    connect(ufoTimer, &QTimer::timeout, this, &Game::spawnUFO);
    ufoTimer->start(2000);

    gameTimer->start(20);
}

void Game::decreaseTime() {
    timeRemaining--;
    timerText->setPlainText(QString("Время: %1").arg(timeRemaining));

    if(timeRemaining <= 0){
        countdownTimer->stop();
        if(level == 1){
            // Завершение 1 уровня
            meteorTimer->stop();
            gameTimer->stop();
            continueButton->show();
        } else {
            // Завершение 2 уровня
            endGame();
        }
    }
}

void Game::endGame(){
    meteorTimer->stop();
    gameTimer->stop();
    countdownTimer->stop();
    if (ufoTimer) ufoTimer->stop();
    livesText->setPlainText("Игра окончена!");
}
