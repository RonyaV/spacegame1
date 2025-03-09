#ifndef UFO_H
#define UFO_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Ufo : public QObject, public QGraphicsPixmapItem
{
public:
    Ufo();
    void fall();
};

#endif // UFO_H
