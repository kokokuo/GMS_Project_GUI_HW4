#include "drawView.h"


float DrawComponentData::CUBE_WIDTH = 60;
float DrawComponentData::CUBE_HEIGHT = 60;
float DrawComponentData::PYRAMID_WIDTH = 80;
float DrawComponentData::PYRAMID_HEIGHT = 50;
float DrawComponentData::SPHERE_WIDTH = 50;
float DrawComponentData::SPHERE_HEIGHT = 50;
float DrawComponentData::LINE_WIDTH = 50;
float DrawComponentData::LINE_HEIGHT = 1;

string DrawComponentData::SphereType ="Sphere";
string DrawComponentData::PyramidType ="Pyramid";
string DrawComponentData::CubeType = "Cube";
string DrawComponentData::LineType = "Line";

float DrawComponentData::COMPONENT_BEGIN_X = 50;
float DrawComponentData::COMPONENT_BEGIN_Y = 50;
float DrawComponentData::COMPONENT_DIFF_Y = 70;


float DrawComponentData::GROUP_BEGIN_X = 250;
float DrawComponentData::GROUP_BEGIN_Y = 50;
float DrawComponentData::GROUP_DIFF_Y = 50;

DrawView::DrawView(GMSModel *gmsModel)
{
    this->model = gmsModel;
    installEventFilter(this);
}
void DrawView::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.fillRect(0,0,this->width(),this->height(),Qt::white); //作為背景,寬與高會隨著拖拉而改變

    vector<Component*> drawComponents = this->model->GetComponents().GetAllComponent();
    if(drawComponents.size() >0 ){
        for(unsigned int i = 0; i < drawComponents.size(); i++){
            //文字的矩形
            QRect rect(drawComponents[i]->GetPositionX(),
                   drawComponents[i]->GetPositionY(),
                   drawComponents[i]->GetWidth(),
                   drawComponents[i]->GetHeight());

            if(drawComponents[i]->GetType() == DrawComponentData::CubeType){
                painter.setPen(Qt::black);
                painter.drawText(rect,Qt::AlignCenter,QString::fromStdString(drawComponents[i]->GetName()));
                painter.setPen(Qt::blue);
                painter.drawRect(rect);
            }
            else if(this->model->GetComponents().GetAllComponent()[i]->GetType() == DrawComponentData::PyramidType){
               //三角形的座標
                QPolygon polygon;
                polygon << QPoint( drawComponents[i]->GetPositionX() + (drawComponents[i]->GetWidth()/2 ) , drawComponents[i]->GetPositionY())
                        << QPoint(drawComponents[i]->GetPositionX(), drawComponents[i]->GetPositionY() + drawComponents[i]->GetHeight() )
                       << QPoint(drawComponents[i]->GetPositionX() + drawComponents[i]->GetWidth(), drawComponents[i]->GetPositionY() + drawComponents[i]->GetHeight());
                painter.setPen(Qt::black);
                painter.drawText(rect,Qt::AlignCenter,QString::fromStdString(drawComponents[i]->GetName()) );
                painter.setPen(Qt::blue);
                painter.drawPolygon(polygon);
            }
            else if(this->model->GetComponents().GetAllComponent()[i]->GetType() == DrawComponentData::SphereType){
                painter.drawEllipse(drawComponents[i]->GetPositionX(),drawComponents[i]->GetPositionY()
                                    ,drawComponents[i]->GetWidth(),drawComponents[i]->GetHeight());

                painter.setPen(Qt::black);
                painter.drawText(rect,Qt::AlignCenter,QString::fromStdString(drawComponents[i]->GetName()));
                painter.setPen(Qt::blue);
            }
            else if(this->model->GetComponents().GetAllComponent()[i]->GetType() == DrawComponentData::LineType){
                painter.setPen(Qt::blue);
                painter.drawRect(drawComponents[i]->GetPositionX(),drawComponents[i]->GetPositionY()+30
                                 ,drawComponents[i]->GetWidth(),drawComponents[i]->GetHeight());
                painter.setPen(Qt::black);
                painter.drawText(drawComponents[i]->GetPositionX(),drawComponents[i]->GetPositionY()
                                 ,drawComponents[i]->GetWidth(),drawComponents[i]->GetHeight()+25,Qt::AlignCenter,QString::fromStdString(drawComponents[i]->GetName()));
            }
        }
    }
    vector<Group*> drawGroups = this->model->GetGroups().GetGroupByVectorContainer();
     if(drawGroups.size() >0 ){
          for(unsigned int i = 0; i < drawGroups.size(); i++){
              painter.drawText(drawGroups[i]->GetPositionX(),drawGroups[i]->GetPositionY(),QString::fromStdString(drawGroups[i]->GetName() + ":" + drawGroups[i]->GetMembersIdByStringFormat()));
          }
     }
}
void DrawView::SetComponentsDrawPostion(){
    if(this->model->GetComponents().GetAllComponent().size() >0 ){
        for(unsigned int i = 0; i < this->model->GetComponents().GetAllComponent().size(); i++){
            this->model->GetComponents().GetAllComponent()[i]->SetPositionX(DrawComponentData::COMPONENT_BEGIN_X);
            this->model->GetComponents().GetAllComponent()[i]->SetPositionY(DrawComponentData::COMPONENT_BEGIN_Y + i * DrawComponentData::COMPONENT_DIFF_Y);
            if(this->model->GetComponents().GetAllComponent()[i]->GetType() == DrawComponentData::CubeType){
                this->model->GetComponents().GetAllComponent()[i]->SetWidth(DrawComponentData::CUBE_WIDTH);
                this->model->GetComponents().GetAllComponent()[i]->SetHeight(DrawComponentData::CUBE_HEIGHT);
            }
            else if(this->model->GetComponents().GetAllComponent()[i]->GetType() == DrawComponentData::PyramidType){
                this->model->GetComponents().GetAllComponent()[i]->SetWidth(DrawComponentData::PYRAMID_WIDTH);
                this->model->GetComponents().GetAllComponent()[i]->SetHeight(DrawComponentData::PYRAMID_HEIGHT);
            }
            else if(this->model->GetComponents().GetAllComponent()[i]->GetType() == DrawComponentData::SphereType){
                this->model->GetComponents().GetAllComponent()[i]->SetWidth(DrawComponentData::SPHERE_WIDTH);
                this->model->GetComponents().GetAllComponent()[i]->SetHeight(DrawComponentData::SPHERE_HEIGHT);
            }
            else if(this->model->GetComponents().GetAllComponent()[i]->GetType() == DrawComponentData::LineType){
                this->model->GetComponents().GetAllComponent()[i]->SetWidth(DrawComponentData::LINE_WIDTH);
                this->model->GetComponents().GetAllComponent()[i]->SetHeight(DrawComponentData::LINE_HEIGHT);
            }
        }
    }
}
void DrawView::SetGroupsDrawPostion(){
    if(this->model->GetGroups().GetGroupByVectorContainer().size() >0 ){
        for(unsigned int i = 0; i < this->model->GetGroups().GetGroupByVectorContainer().size(); i++){
            this->model->GetGroups().GetGroupByVectorContainer()[i]->SetPositionX(DrawComponentData::GROUP_BEGIN_X);
            this->model->GetGroups().GetGroupByVectorContainer()[i]->SetPositionY(DrawComponentData::GROUP_BEGIN_Y + i * DrawComponentData::GROUP_BEGIN_Y);
        }
    }
}
bool DrawView::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *e = (QMouseEvent*)event;

    }
    else if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *e = (QMouseEvent*)event;

    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *e = (QMouseEvent*)event;

    }

    return false;
}
