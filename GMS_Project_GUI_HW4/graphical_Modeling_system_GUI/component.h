#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>

using namespace std;

class Group;

class ComponentType{
public:
    static int SphereType;
    static int PyramidType;
    static int CubeType;
    static int LineType;
};

//=================================================


class Component
{
public:
    //加入編號，類型，與元件名稱
    Component(int id, string componentType, string name);
    //加入MemberToGroup時,要建立連結
    void AddGroup(Group* );
    //復原時,要移除連結
    void RemoveGroup(Group* );
    //copy constructor
    Component(Component &c);
    ~Component(){}
    int GetID(); //取得ID
    string GetType(); //取得Type
    string GetName(); //取得名稱
    void SetName(string name); //設定名稱
    void SetComponentType(string type); //設定類型

    //GUI用 設定座標
    void SetPositionX(float x);
    void SetPositionY(float Y);
    float GetPositionX();
    float GetPositionY();

    void SetWidth(float width);
    void SetHeight(float height);
    float GetWidth();
    float GetHeight();
    //確認GUI滑鼠的點擊座標是否有按掉
    bool BePressed(float x,float y);

protected:
    int id;
    string type;
    string name;
    vector<Group*> GroupsAddedComponent; //紀錄有加入此Component的Group記憶體位址
    float x,y;
    float width,height;
};

#endif // COMPONENT_H
