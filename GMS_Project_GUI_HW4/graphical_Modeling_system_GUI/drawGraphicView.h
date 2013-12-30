#ifndef DRAWGRAPHICVIEW_H
#define DRAWGRAPHICVIEW_H

#include <QtWidgets>
#include <QPainter>
#include <QColor>
#include <vector>
#include <map>
#include "component.h"
#include "group.h"

class DrawGraphicView : public QWidget
{
public:
    DrawGraphicView();
    void SetDrawComponents(vector<Component*>* components);
    void SetDrawGroups(map<string,Group*>* groups);
protected:
    void paintEvent(QPaintEvent *);


private:
    QPainter drawPainter;
    vector<Component*>* drawComponents; //知道Components
    map<string,Group*>* drawGroups; //知道Groups
};

#endif // DRAWGRAPHICVIEW_H
