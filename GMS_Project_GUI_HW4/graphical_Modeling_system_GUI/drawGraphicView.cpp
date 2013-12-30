#include "drawGraphicView.h"

DrawGraphicView::DrawGraphicView()
{
    setAutoFillBackground(true);
}
void DrawGraphicView::SetDrawComponents(vector<Component*>* components){
     this->drawComponents = components;
}
void DrawGraphicView::SetDrawGroups(map<string,Group*>* groups){
    this->drawGroups = groups;
}

void DrawGraphicView::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.drawLine(100,100,100,120);

}
