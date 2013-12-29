#include "components.h"

Components::Components()
{
    this->componentID = 1;
}
void Components::AddComponentToList(Component *component){

    components.push_back(component);
    //排序
    Component* temp;
    for (unsigned int i = 1; i < components.size(); i++)
    {
        for (unsigned int j = 0; j < components.size() - i; j++)
        {
            if (components[j]->GetID() > components[j + 1]->GetID())
            {
                temp = components[j];
                components[j] = components[j + 1];
                components[j + 1] = temp;
            }
        }
    }
}
//從vector中刪除component
void Components::DeleteComponentFromList(int id){
    for(unsigned int index = 0; index < components.size();index ++){
        if(components[index]->GetID() == id ){
            Component* c = components[index];
            components.erase((components.begin() + index));
            delete c;
            break;
        }
    }
}
vector<Component*>  Components::GetAllComponent(){
    return this->components;
}
//從Load檔案中取得Components,記得先呼叫清除 ClearComponents
void Components::SetComponentsFromLoadData(Component *component){
    this->components.push_back(component);


    //設定Component現在的最大ID,從載入的XML資料中去看
    //如果有資料,取得檔案中最大的ID,並加一為現在的ID
    if(components.size() >0){
        componentID = components[components.size()-1]->GetID() +1;
    }

}
//清除Components
void Components::ClearAll(){
    //重新載入新的XML,要把原先的資料先全部移除,避免有Memory Leak,再從新添加從XML載入的資料
    if(components.size() > 0){
        for(vector<Component*>::iterator it = components.begin();it != components.end();it++){
            delete (*it);
        }
        components.clear();
    }
}
//判斷ID有無存在
bool Components::CheckIDHasBeenExisted(int id){
    for(vector<Component*>::iterator it =  this->components.begin();it != this->components.end();it++){
        if((*it)->GetID() == id){
            return true;
        }
    }
    return false;

}
//取得目前生產出的ID編號
int Components::GetCurrentGeneratedComponentID(){
    if(componentID ==1)
        return componentID;
    else
        return this->componentID;  //扣掉被累加的即為當下ID
}
//透過Id取得Component
Component* Components::GetComponentById(int id){
    for(vector<Component*>::iterator it =  this->components.begin();it != this->components.end();it++){
        if((*it)->GetID() == id){
            return *it;
        }
    }
    return NULL;
}

void Components::AddComponentID(){
    componentID++;
}
void Components::MinusComponentID(){
    componentID--;
}

