#ifndef METEOR_H
#define METEOR_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Meteor : public QObject, public QGraphicsPixmapItem
{
public:
    Meteor();
    void fall();
};

#endif // METEOR_H
