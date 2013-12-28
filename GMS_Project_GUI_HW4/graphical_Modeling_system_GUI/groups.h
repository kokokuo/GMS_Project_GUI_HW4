#ifndef GROUPS_H
#define GROUPS_H

#include "group.h"
#include <map>
#include <sstream>

using namespace std;

class Groups
{
public:
    Groups();
    //新增Group
    void AddGroup(string Gid, Group *newGroup);
    //加入Members到指定Group
    void AddMembersToGroup(int groupId,vector<int> members);
    //判斷Group是否已存在,回傳ID
    bool CheckGroupHasBeenExisted(int groupId);
    //取得Group
    Group* GetGroup(int groupId);
    //取得所有Group
    map<string,Group*> GetAllGroups();

    //從檔案中從檔案中加入Group
    void SetGroupsFromLoadData(Group* group);
    void ClearAllGroup();

    //取得用Vector容器裝置方式的Groups
    vector<Group*> GetGroupByVectorContainer();

    //選取得現在產生的ID
    int GetCurrentGeneratedGroupId();
    //累加ID
    void AddGroupID();
    //遞減ID(用來還原AddNewGroup功能時使用,undo)
    void MinusGroupID();

    void DeleteGroup(int id);

    //透過Id取得Component
    Group* GetGroupById(int id);

    //從指定的Group中移除Members
    void DeleteMembersFromGroupById(int groupId,vector<int> removeMembers);
private:
    map<string,Group*> groups;
    vector<Group*> groupsVec; //以vector的方式紀錄groups
    int groupID; //group的編號
};

#endif // GROUPS_H
