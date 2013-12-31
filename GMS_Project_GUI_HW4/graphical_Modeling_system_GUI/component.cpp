#include "component.h"
#include "group.h"

//ComponentType靜態類別參數設定
int ComponentType::CubeType =1;
int ComponentType::PyramidType = 2;
int ComponentType::SphereType = 3;
int ComponentType::LineType = 4;
//=================================================

//Component
Component::Component(int id, string componentType, string name)
{
    this->id = id;
    this->type = componentType;
    this->name = name;
}
Component::Component( Component& c){
    this->id = c.GetID();
    this->type = c.GetType();
    this->name = c.GetName();
}
int Component::GetID(){
    return this->id;
}
string Component::GetName(){
    return this->name;
}

string Component::GetType(){
    return this->type;
}
void Component::SetName(string name){
    this->name = name;
}
void Component::SetComponentType(string type){
    this->type = type;
}
void Component::SetPositionX(float x){
    this->x = x;
}
void Component::SetPositionY(float y){
    this->y = y;
}
float Component::GetPositionX(){
    return this->x;
}
float Component::GetPositionY(){
    return this->y;
}
void Component::SetWidth(float width){
    this->width = width;
}
void Component::SetHeight(float height){
    this->height = height;
}
float Component::GetWidth(){
    return this->width;
}
float Component::GetHeight(){
    return this->height;

}
bool Component::CheckBePressed(float x,float y){
    if(this->type != "Line" &&  x > this->x && x < this->x + this->width && y < this->y + this->height && y > this->y){
        return true;
    }
    else if(this->type == "Line" &&  x > this->x && x < this->x + this->width && y < this->y + this->height +20 && y > this->y){
        return true;
    }
    return false;

}
