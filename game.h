#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QPushButton>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include "player.h"
#include "meteor.h"
#include "ufo.h"

class Game : public QGraphicsView {
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

public slots:
    void spawnMeteor();
    void spawnUFO();
    void updateGame();
    void nextLevel();
    void decreaseTime();
    void endGame();

private:
    QGraphicsScene *scene;
    Player *player;
    QTimer *meteorTimer;
    QTimer *ufoTimer, *gameTimer, *countdownTimer;
    QList<Meteor*> meteors;
    QList<Ufo*> ufos;
    QGraphicsTextItem *livesText;
    QGraphicsTextItem *timerText;
    QGraphicsPixmapItem *background;
    int lives;
    int level = 1;
    int timeRemaining = 10;
    QPushButton *continueButton;

};

#endif // GAME_H

