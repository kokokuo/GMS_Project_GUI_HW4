#include "groups.h"

Groups::Groups()
{
    this->groupID = 1;
}

void Groups::AddGroup(string Gid,Group* newGroup){

    groups.insert( pair<string,Group*>(Gid,newGroup) );
    //紀錄vector模式中
    groupsVec.push_back(newGroup);

}
//加入Members到指定Group (使用前記得先呼叫 CheckGroupHasBeenExisted)判斷
void Groups::AddMembersToGroup(int groupId,vector<int> members){
    stringstream ss;
    ss << "G" << groupId; //轉換成GID 作為map的Key值直接取得value
    groups[ss.str()]->AddMembers(members);
}

//判斷Group是否已存在
bool Groups::CheckGroupHasBeenExisted(int groupId){
    for(map<string,Group*>::iterator it =  this->groups.begin();it != this->groups.end();it++){
        if( (it->second)->GetID() == groupId  ){
            return true;
        }
    }
    return false;
}
//取得Group(使用使方法前請先呼叫 CheckGroupHasBeenExisted 判斷有無存在)
Group* Groups::GetGroup(int groupId){
    stringstream ss;
    ss << "G" << groupId; //轉換成GID 作為map的Key值直接取得value
    return groups[ss.str()];

}
//取得所有Group
map<string,Group*> Groups::GetAllGroups(){
    return this->groups;
}
//清除所有Group
void Groups::ClearAllGroup(){
    groupsVec.clear();
    for(map<string,Group*>::iterator it =  this->groups.begin();it != this->groups.end();it++){
        delete it->second;
    }
    groups.clear();
}
//從檔案中從檔案中加入Group ,記得先呼叫清除所有Group ClearAllGroup
void Groups::SetGroupsFromLoadData(Group* group){
    stringstream ss;
    ss << "G" <<  group->GetID(); //轉換成GID 作為map的Key值直接取得value
    groups[ss.str()] = group;
    //紀錄vector模式中
    groupsVec.push_back(group);


    //Group,從載入的XML資料中去看
    //如果有資料,取得檔案中最大的ID,並加一為現在的ID
    if(groups.size() >0){
        groupID = groupsVec[groupsVec.size()-1]->GetID() +1;
    }

}
//取得Vector容器裝置方式的Groups
vector<Group*> Groups::GetGroupByVectorContainer(){
    return this->groupsVec;
}

int Groups::GetCurrentGeneratedGroupId(){
     if(groupID ==1)
         return groupID;
     else
        return groupID; //扣掉被累加的即為當下ID
}
void Groups::AddGroupID(){
    groupID++;
}
void Groups::MinusGroupID(){
    groupID--;
}
void Groups::DeleteGroup(int id){
    for(map<string,Group*>::iterator it =  this->groups.begin();it != this->groups.end();it++){
        if(it->second->GetID() == id){
            delete it->second;
            groups.erase(it);
        }
    }
}
//取得Group
Group* Groups::GetGroupById(int id){
    stringstream ss;
    ss << "G" << id; //轉換成GID 作為map的Key值直接取得value
    return groups[ss.str()];
}
//給予指定的Group ID移除Members
void Groups::DeleteMembersFromGroupById(int groupId, vector<int> removeMembers){
    stringstream ss;
    ss << "G" << groupId; //轉換成GID 作為map的Key值直接取得value
    //移除Members
    groups[ss.str()]->RemoveMembers(removeMembers);
}
