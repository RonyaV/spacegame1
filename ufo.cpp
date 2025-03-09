#include "ufo.h"
#include <QPixmap>

Ufo::Ufo() {
    setPixmap(QPixmap(":/images/ufo.png").scaled(70, 70));
}

void Ufo::fall(){
    setY(y()+5);
}
