#include "group.h"

Group::Group(int id, string name, vector<int> members)
{
    this->id = id;
    this->groupName = name;
    for(vector<int>::iterator it = members.begin();it != members.end();it++){
        this->membersId.push_back((*it));
    }
}
Group::~Group(){
    membersId.clear();
}
//取得ID
int Group::GetID(){
    return this->id;
}
//取得Group名稱
string Group::GetName(){
    return this->groupName;
}
//取得成員ID
vector<int> Group::GetMembersId(){
    return this->membersId;
}
string Group::GetMembersIdByStringFormat(){
    stringstream ss;
    //不需考慮無資料的情況,作業的部分輸入的範例代表新增Group時一定要有資料
    if(membersId.size() >0){
        ss << membersId[0];
        if(membersId.size() >1){
            for(vector<int>::iterator it = membersId.begin()+1 ;it != membersId.end();it++){
                ss << "," << (*it) ;
            }
        }
    }
    return ss.str();
}
//加入成員
void Group::AddMembers(vector<int> members){
    for(vector<int>::iterator it = members.begin();it != members.end();it++){
        this->membersId.push_back((*it));
    }
    SortMembersById();

}
//判斷memberID有無存在
bool Group::CheckMemberHasBeenExisted(int memberId){
    for(vector<int>::iterator it = membersId.begin();it != membersId.end();it++){
        if((*it) == memberId ){
            return true;
        }
    }
    return false;
}
void Group::RemoveMembers(vector<int> wantToRemoveId){
    for(vector<int>::iterator remvoeIt = wantToRemoveId.begin();remvoeIt != wantToRemoveId.end();remvoeIt++){
        for(vector<int>::iterator it = membersId.begin();it != membersId.end();it++){
            if((*it) == (*remvoeIt) ){
                membersId.erase(it);
                break;
            }
        }
    }
}
void Group::SortMembersById(){
    //排序
    int temp;
    for (unsigned int i = 1; i < membersId.size(); i++)
    {
        for (unsigned int j = 0; j < membersId.size() - i; j++)
        {
            if (membersId[j] > membersId[j + 1])
            {
                temp = membersId[j];
                membersId[j] = membersId[j + 1];
                membersId[j + 1] = temp;
            }
        }
    }

}
void Group::AddSingleMember(int member){
    this->membersId.push_back(member);
    SortMembersById();
}
void Group::RemoveSingleMember(int removeId){
    for(vector<int>::iterator it = membersId.begin();it != membersId.end();it++){
        if((*it) == removeId ){
            membersId.erase(it);
            break;
        }
    }
}


void Group::SetPositionX(float x){
    this->x = x;
}
void Group::SetPositionY(float y){
    this->y = y;
}
float Group::GetPositionX(){
    return this->x;
}
float Group::GetPositionY(){
    return this->y;
}
bool Group::CheckBePressed(float x,float y){
   int wordLength = 16;
   wordLength += this->GetName().length();
   wordLength += 2*(this->membersId.size())-1;

   if(x >= this->x && x<= this->x + wordLength*7 && y >= this->y -10 && y <= this->y)
       return true;
   return false;
}
