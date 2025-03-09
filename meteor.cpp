#include "meteor.h"
#include <QPixmap>

Meteor::Meteor() {
    setPixmap(QPixmap(":/images/meteor.png").scaled(50,50));
}

void Meteor::fall(){
    setY(y()+5);
}
