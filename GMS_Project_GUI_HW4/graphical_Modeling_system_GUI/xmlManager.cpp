#include "xmlmanager.h"

XMLManager::XMLManager()
{

}
//判斷檔案路徑是否存在
int XMLManager::CheckFilePathIsExisted(string filePath){
    //開檔,但是不會自動create(以讀檔的方式才能確保不會自動創建)
    xmlFile.open(filePath.c_str(),ios::in);

    //透過檢查是否開啟來判斷有無存在檔案
    if(xmlFile.is_open()){
        xmlFile.close();
        return XMLErrorCode::OK;
    }
    else{
        xmlFile.close();
        //不存在
        return XMLErrorCode::Open_NotExist;
    }

}
int XMLManager::SaveXML(string fileName, Components components, Groups groups){
    //創建檔案
    xmlFile.open(fileName.c_str(),ios::out);
    if(xmlFile.is_open()){
        AddComponentAndGroupToXMLFile(components.GetAllComponent(),groups.GetAllGroups());
        this->xmlFilePath = fileName; //把路徑記錄下來
         xmlFile.close();
        return XMLErrorCode::OK;
    }
    else{ //創建後如果無開啟 代表可能有錯誤
        xmlFile.close();
        return XMLErrorCode::Save_PathError;
    }
}
//Components* components是為了能夠直接取得整個vector的記憶體位置,這樣外部呼叫時傳入vector,處理完後才能夠拿到載入好的資料(因為回傳值拿來作為回傳錯誤碼用)
int XMLManager::LoadXML(string fileName, Components* components,Groups* groups){

    //開檔,但是不會自動create(以讀檔的方式才能確保不會自動創建)
    xmlFile.open(fileName.c_str(),ios::in);

    //透過檢查是否開啟來判斷有無存在檔案
    if(xmlFile.is_open()){
        this->xmlFilePath = fileName; //把路徑記錄下來
        ParserXMLFile(components,groups); //取出XML中的資料到記憶體vector
        xmlFile.close();

        return XMLErrorCode::OK;
    }
    else{
        xmlFile.close();
        //不存在
        return XMLErrorCode::Open_NotExist;
    }

}

void XMLManager::AddComponentAndGroupToXMLFile(vector<Component*> components,map<string,Group*> groups){
    try{
        xmlFile << "<GMS>\n";
        xmlFile << "\t<Components>\n";
        //迴圈的方式一個一個抓取Component並寫入到檔案中
        for(vector<Component*>::iterator it = components.begin();it != components.end();it++){
            xmlFile << "\t\t<Node>\n";
            xmlFile << "\t\t\t<ID>" << (*it)->GetID() << "</ID>\n";
            xmlFile << "\t\t\t<Name>" << (*it)->GetName() << "</Name>\n";
            xmlFile << "\t\t\t<Type>" << (*it)->GetType() << "</Type>\n";
            xmlFile << "\t\t</Node>\n";
        }
        xmlFile << "\t</Components>\n";

        //Group
        xmlFile << "\t<Group>\n";
        for(map<string,Group*>::iterator it =groups.begin();it != groups.end();it++){
            xmlFile << "\t\t<Node>\n";
            xmlFile << "\t\t\t<ID>" << it->second->GetID() << "</ID>\n";
            xmlFile << "\t\t\t<Name>" << it->second->GetName() << "</Name>\n";
            xmlFile << "\t\t\t<Member>" << it->second->GetMembersIdByStringFormat() << "</Member>\n";
            xmlFile << "\t\t</Node>\n";
        }
        xmlFile << "\t</Group>\n";

        xmlFile <<  "</GMS>"; //補上</GMS>標籤

    }
    catch(exception ex){
        cout << ex.what() <<endl;
    }

}
string XMLManager::GetTagValue(string startTag,string endTag,string line){
    int foundStartTagPos = line.find(startTag);
    int foundEndTagPos = line.find(endTag);
    //第一個參數:起始位置,找到開始Tag的位置 + 開始Tag本身的長度 會得到 開始Tag後的位置
    //第二個參數:擷取字串的長度,結尾Tag的位置 - 開始Tag尾後的位置(開始Tag位置 + 開始tag長度)
    string sub = line.substr( ( foundStartTagPos + startTag.size() ), ( foundEndTagPos - (foundStartTagPos + startTag.size()) ) );
    return sub;
}
//components指標型態用來存放檔案中所有Parser出的Component
//groups指標型態用來存放檔案中所有Parser出的group
void XMLManager::ParserXMLFile( Components* components,Groups* groups){

    //判斷有無找到Component Node
    bool IsFindComponentNode = false,IsFindComponents = false;
    //判斷有無讀取到Component ID,Type,Name
    bool IsGetComponentID, IsGetComponentType , IsGetComponentName;
    //判斷有無找到Group Node
    bool IsFindGroupNode = false,IsFindGroups = false;
    //判斷有無讀取到Group ID,Name,Member
    bool IsGetGroupID,IsGetGroupName,IsGetGroupMembers;

    IsGetComponentID = IsGetComponentType = IsGetComponentName = false;
    IsGetGroupID = IsGetGroupName = IsGetGroupMembers = false;

    int id;
    string type,name;
    string members;
    string line;
    while(getline(xmlFile,line)){
        //cout << line <<endl; //測試用

        //尋找是在Components或Group Node
        if(line.find("<Components>") != string::npos){
           IsFindComponents = true;
        }
        else if(line.find("<Group>") != string::npos){
           IsFindGroups = true;
        }

         //如果有找到Node,用Bool值紀錄
        if(line.find("<Node>") != string::npos  && IsFindComponents){
            IsFindComponentNode = true;
        }
        else if(line.find("<Node>") != string::npos  && IsFindGroups){
            IsFindGroupNode = true;
        }
        //找到開始尋找是在Components <Node>
        if(IsFindComponentNode){

            //如果有找到<ID>標籤與</ID>標籤,則擷取標籤中資料
            if( (line.find("<ID>") != string::npos) && ( line.find("</ID>")  != string::npos ) ){
                id = atoi( GetTagValue("<ID>","</ID>",line).c_str() );
                IsGetComponentID = true;
            }
            else if( (line.find("<Name>") != string::npos) && ( line.find("</Name>")  != string::npos ) ){
                name = GetTagValue("<Name>","</Name>",line);
                IsGetComponentName = true;
            }
            else if( (line.find("<Type>") != string::npos) && ( line.find("</Type>")  != string::npos ) ){
                type = GetTagValue("<Type>","</Type>",line);
                IsGetComponentType = true;
            }
        }
        //找到</Node> 並且 <Node> 也有找到,也取得了Node中的標籤資料
        if(IsFindComponentNode && line.find("</Node>") != string::npos && IsGetComponentID && IsGetComponentName && IsGetComponentType){
             //加入Component
            components->SetComponentsFromLoadData(new Component(id,type,name));
            //從新設定回false
            IsFindComponentNode = IsGetComponentID = IsGetComponentType = IsGetComponentName = false;
        }
        if(line.find("</Components>") != string::npos){
            IsFindComponents = false;
        }

        //找到開始尋找是在Group <Node>
        if(IsFindGroupNode){
            //如果有找到<ID>標籤與</ID>標籤,則擷取標籤中資料
            if( (line.find("<ID>") != string::npos) && ( line.find("</ID>")  != string::npos ) ){
                id = atoi( GetTagValue("<ID>","</ID>",line).c_str() );
                IsGetGroupID = true;
            }
            else if( (line.find("<Name>") != string::npos) && ( line.find("</Name>")  != string::npos ) ){
                name = GetTagValue("<Name>","</Name>",line);
                IsGetGroupName = true;
            }
            else if( (line.find("<Member>") != string::npos) && ( line.find("</Member>")  != string::npos ) ){
                members = GetTagValue("<Member>","</Member>",line);
                IsGetGroupMembers = true;
            }
        }
        //找到</Node> 並且 <Node> 也有找到,也取得了Node中的標籤資料
        if(IsFindGroupNode && line.find("</Node>") != string::npos && IsGetGroupID && IsGetGroupName && IsGetGroupMembers){
            //轉型回int member id
            vector<int> membersId = ConvertToMembersId(members);
            //加入Group
            groups->SetGroupsFromLoadData(new Group(id,name,membersId));
            //從新設定回false
            IsFindGroupNode = IsGetGroupID = IsGetGroupMembers = IsGetGroupName = false;
        }

        if(line.find("</Group>") != string::npos){
            IsFindGroups = false;
        }
    }

}
//把從檔案取得的string型態資料轉回int
vector<int> XMLManager::ConvertToMembersId(string memberStr){
    vector<int> membersId;
    for(unsigned int index =0 ;index <memberStr.size(); index++){
        if( memberStr[index] == ',')
            memberStr[index] = ' ' ;
    }
    stringstream ss;
    ss << memberStr;
    int memberId;
    while(ss >>memberId){
        cout << memberId <<endl;
        membersId.push_back(memberId);
    }

    return membersId;
}
