#ifndef GMSMODEL_H
#define GMSMODEL_H

#include <map>
#include <vector>
#include <sstream>
#include "component.h"
#include "components.h"
#include "xmlManager.h"
#include "group.h"
#include "groups.h"

class GMSModel
{
public:
    GMSModel();

    //存檔XML檔案,路徑
    int SaveXMLFormatRecord(string path);
    //載入XML檔案,路徑
    int LoadXMLFormatRecord(string path);

    //實作加入Components部分,id,類型,名稱
    void AddComponents(string componentType, string componentName,int* addedId);
    //復原加入實作加入Components部分
    void UnDoAddComponents(int addedId);

    //編輯Component名稱
    string EditComponentName(int editId,string newName);
    //復原編輯Component名稱
    void UnDoEditComponentName(int editId, string orignalName);

    //編輯Component Type
    string EditComponentType(int editId,string newType);
    //復原編輯Component Type
    void UnDoEditComponentType(int editId, string orginalType);

    //刪除Component
    Component *DeleteComponent(int id);
    //復原刪除Component
    void UnDoDeleteComponent(Component *removedComponent);

    //加入新的Group
    void AddNewGroup(int* addedId, string name, vector<int> addMembers);
    //復原加入新的Group
    void UnDoAddNewGroup(int addedId);

    //加入members ID到Group
    void AddMembersToGroup(int groupId,vector<int> addMembers);
    //復原加入members ID到Group
    void UnDoAddMembersToGroup(int groupId,vector<int> addMembers);

    //取得所有Component
    Components GetComponents();

    //取得Groups
    Groups GetGroups();

    //取得想要的Group
    Group* FindGroupByGroupId(int groupId);

    //取得產生Component到目前的最大ID
    int GetCurrentComponentMakerID();

    //取得產生Group到目前的最大ID
    int GetCurrentGroupMakerID();



    //判斷GroupId有無存在
    bool CheckGroupHasBeenExisted(int groupId);
    //判斷這個Component的ID是否存在Components
    bool CheckComponentIDHasBeenExisted(int id);

    //判斷這個MemberId是否存在指定的groupId
    bool CheckMemberIDHasBeenTheGroup(int groupId,int memberId);

private:
    Components components; //記錄所有的Components
    XMLManager xmlManager; //實際負責XML所有部分的操作,被GMS系統擁有,調用
    Groups groups; //紀錄Groups

};

#endif // GMSMODEL_H
