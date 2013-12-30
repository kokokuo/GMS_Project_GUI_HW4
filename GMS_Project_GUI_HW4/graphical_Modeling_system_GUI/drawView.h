#ifndef DRAWVIEW_H
#define DRAWVIEW_H

#include <QPainter>
#include <QtWidgets>
#include <map>
#include <vector>
#include "gmsModel.h"

class DrawComponentData{
public:
    static float CUBE_WIDTH;
    static float CUBE_HEIGHT;
    static float PYRAMID_WIDTH ;
    static float PYRAMID_HEIGHT;
    static float SPHERE_WIDTH;
    static float SPHERE_HEIGHT;
    static float LINE_WIDTH;
    static float LINE_HEIGHT;

    static string SphereType;
    static string PyramidType;
    static string CubeType;
    static string LineType;

    static float COMPONENT_BEGIN_X ;
    static float COMPONENT_BEGIN_Y;
    static float COMPONENT_DIFF_Y;

    static float GROUP_BEGIN_X;
    static float GROUP_BEGIN_Y;
    static float GROUP_DIFF_Y;
};


class DrawView : public QWidget
{
public:
    DrawView(GMSModel* gmsModel);
    //設定顯示在畫布上的初始位置
    void SetComponentsDrawPostion();
    void SetGroupsDrawPostion();

protected:
    bool eventFilter(QObject *, QEvent *);
    void paintEvent(QPaintEvent *);
private:
    GMSModel* model;

};

#endif // DRAWVIEW_H
