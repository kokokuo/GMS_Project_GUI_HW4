#include "gmsModel.h"

GMSModel::GMSModel()
{
}
//把components 與groups存入檔案
int GMSModel::SaveXMLFormatRecord(string path){
    return xmlManager.SaveXML(path,components,groups);
}
//載入components與groups
int GMSModel::LoadXMLFormatRecord(string path){
    int code =xmlManager.CheckFilePathIsExisted(path);
    //如果檔案存在
    if(code == XMLErrorCode::OK){
        components.ClearAll(); //清除原先的Components
        groups.ClearAllGroup(); //清除原先的Group
        code = xmlManager.LoadXML(path,&components,&groups);
    }
    return code;
}


string GMSModel::EditComponentName(int editId, string newName){
    //執行編輯Name
    Component* wantEditComponent = components.GetComponentById(editId);
    string originalName = wantEditComponent->GetName();
    wantEditComponent->SetName(newName);
    return originalName;
}
void GMSModel::UnDoEditComponentName(int editId, string orignalName){
    //移除執行編輯Name
    Component* wantEditComponent = components.GetComponentById(editId);
    wantEditComponent->SetName(orignalName);
}


string GMSModel::EditComponentType(int editId, string newType){
    //執行編輯Name
    Component* wantEditComponent = components.GetComponentById(editId);
    string originalType = wantEditComponent->GetType();
    wantEditComponent->SetComponentType(newType);
    return originalType;
}
void GMSModel::UnDoEditComponentType(int editId, string orginalType){
    //移除執行編輯Name
    Component* wantEditComponent = components.GetComponentById(editId);
    wantEditComponent->SetComponentType(orginalType);

}

void GMSModel::AddComponents(string addComponentType, string AddName, int *addedId){
    if(*addedId ==0) //等於0表示尚未加入Componenet(如此判斷下次加入回去才不會影響ID
        *addedId = components.GetCurrentGeneratedComponentID();
    //創建新的Component並加入智vector中
    Component *component = new Component(*addedId,addComponentType,AddName);
    this->components.AddComponentToList(component);
    //累加ID
    this->components.AddComponentID();
}
void GMSModel::UnDoAddComponents(int addedId){
    this->components.DeleteComponentFromList(addedId);
    //遞減ID 回到加入之前生產的ID編號
    this->components.MinusComponentID();
}


//刪除Component與判斷有無存在
Component* GMSModel::DeleteComponent(int id){
    //先複製出一份要移除的Component (復原時要使用)
    //加入point,傳入指向的實際物件記憶體區塊到Copy Constructor中
    Component* removedComponent = new Component( *(this->components.GetComponentById(id)) );
    //移除
    this->components.DeleteComponentFromList(id);
    return removedComponent;
}
void GMSModel::UnDoDeleteComponent(Component* removedComponent){
    this->components.AddComponentToList(removedComponent);
    //不需遞減ID 此部分只加放回移除的Component
}


//取得所有Components
Components GMSModel::GetComponents(){
    return this->components;
}
//取得目前生產的ComponentsID
int GMSModel::GetCurrentComponentMakerID(){
    return this->components.GetCurrentGeneratedComponentID();
}
//取得目前生產的GroupID
int GMSModel::GetCurrentGroupMakerID(){
    return this->groups.GetCurrentGeneratedGroupId();
}

//判斷group有無存在
bool GMSModel::CheckGroupHasBeenExisted(int groupId){
    return this->groups.CheckGroupHasBeenExisted(groupId);
}

//判斷這個ComponentID有無存在Components
bool GMSModel::CheckComponentIDHasBeenExisted(int id){
    return this->components.CheckIDHasBeenExisted(id);
}
//取得所有Group
Groups GMSModel::GetGroups(){
    return groups;
}


//判斷這個MemberId是否存在指定的groupId(使用前請先透過 CheckGroupHasBeenExisted判斷Group有無存在)
bool GMSModel::CheckMemberIDHasBeenTheGroup(int groupId, int memberId){
    Group* g =  groups.GetGroup(groupId);
    return  g->CheckMemberHasBeenExisted(memberId);

}
//加入新的Group
void GMSModel::AddNewGroup(int* addedId,string name, vector<int> addMembers){
    if(*addedId ==0)
       *addedId = this->groups.GetCurrentGeneratedGroupId(); //等於0表示尚未加入Componenet(如此判斷下次加入回去才不會影響ID
    stringstream ss;
    ss << "G" << *addedId; //轉換成GID 作為map的Key值
    Group* newGroup = new Group(*addedId,name,addMembers);
    this-> groups.AddGroup(ss.str(),newGroup);
    //累加GroupID
    this->groups.AddGroupID();
}

void GMSModel::UnDoAddNewGroup(int addedId){
    //刪除加入的Group
    this->groups.DeleteGroup(addedId);
    //遞減ID 回到加入之前生產的ID編號
    this->groups.MinusGroupID();

}
//取得想要的Group
Group* GMSModel::FindGroupByGroupId(int groupId){
    return groups.GetGroup(groupId);

}
//加入members ID到Group
void GMSModel::AddMembersToGroup(int groupId, vector<int> addMembers){
    //執行加入Member
     groups.AddMembersToGroup(groupId,addMembers);
}
void GMSModel::UnDoAddMembersToGroup(int groupId, vector<int> addMembers){
    //移除剛剛加入的成員
    groups.DeleteMembersFromGroupById(groupId,addMembers);
}
