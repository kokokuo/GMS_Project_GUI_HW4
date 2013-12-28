#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "component.h"
#include <algorithm>
#include "vector"

using namespace std;

class Components
{
public:
    Components();
    //加入Components
    void AddComponentToList(Component* component);
    //刪除Components
    void DeleteComponentFromList(int id);
    //取得Component
    vector<Component*> GetAllComponent();
    //從Load檔案中取得Components
    void SetComponentsFromLoadData(Component* component);
    //清除Components
    void ClearAll();
    //判斷ID是否存在
    bool CheckIDHasBeenExisted(int id);
    //取得目前生產的ID
    int GetCurrentGeneratedComponentID();
    //累加ID
    void AddComponentID();
   //遞減ID(用來還原AddComponentToList功能時使用,undo)
    void MinusComponentID();
    //透過Id取得Component
    Component* GetComponentById(int id);

private:
    vector<Component*> components;

    int componentID; //Component的編號
};

#endif // COMPONENTS_H
