#ifndef DRAWVIEW_H
#define DRAWVIEW_H

#include <QPainter>
#include <QtWidgets>
#include "component.h"
#include <map>
#include <vector>
#include "gmsModel.h"

//紀錄一些資料與參數
class DrawComponentData{
public:
    //繪製的寬與高
    static float CUBE_WIDTH;
    static float CUBE_HEIGHT;
    static float PYRAMID_WIDTH ;
    static float PYRAMID_HEIGHT;
    static float SPHERE_WIDTH;
    static float SPHERE_HEIGHT;
    static float LINE_WIDTH;
    static float LINE_HEIGHT;
    //繪製的類型
    static string SphereType;
    static string PyramidType;
    static string CubeType;
    static string LineType;

    //繪製的起始位置與偏差位移
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
    void SetComponentsDrawPostion(); //設定Component座標
    void SetGroupsDrawPostion(); //設定Group座標

protected:
    bool eventFilter(QObject *, QEvent *);
    void paintEvent(QPaintEvent *);
private:
    bool isComponentPressed; //用來Component記錄有無被按壓到
    bool isGroupPressed; //用來Group記錄有無被按壓到
    Component* dragComponent; //紀錄被拖移的Component
    Group* dragGroup; //紀錄被拖移的Group
    QPoint componentStartPoint; //記錄Component拖移的前一個座標
    QPoint groupStartPoint; //記錄Group拖移的前一個座標
    GMSModel* model;

};

#endif // DRAWVIEW_H
