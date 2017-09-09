#include <iostream>
#include <string>

#include "xmlDatabase.h"

User::User()
{

}
User::User(const std::string &name, const std::string &password, 
    int gender, const std::string &mobile, const std::string &email)
{
    this->name = name;
    this->password = password;
    this->gender = gender;
    this->mobile = mobile;
    this->email = email;
}

std::string User::GetName() const
{
    return name;
}
std::string User::GetPassword() const
{
    return password;
}
int User::GetGender() const
{
    return gender;
}
std::string User::GetMobile() const
{
    return mobile;
}
std::string User::GetEmail() const
{
    return email;
}

void User::SetName(const std::string &name)
{
    this->name = name;
}
void User::SetPassword(const std::string &password)
{
    this->password = password;
}
void User::SetGender(int gender)
{
    this->gender = gender;
}
void User::SetMobile(const std::string &mobile)
{
    this->mobile = mobile;
}
void User::SetEmail(const std::string &email)
{
    this->email = email;
}

void User::Print() const 
{
    std::cout << "user name:" << name << std::endl;
    std::cout << "password:" << password << std::endl;
    std::cout << "gender:" << gender << std::endl;
    std::cout << "mobile:" << mobile << std::endl;
    std::cout << "email:" << email << std::endl;
}

namespace ParseXML
{
    int CreateXML(const char *xmlPath)
    {
        const char *decl = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>";
        tinyxml2::XMLDocument doc;
        doc.Parse(decl);

        tinyxml2::XMLElement *root = doc.NewElement("DBUser");
        doc.InsertEndChild(root);
        //doc.LinkEndChild(root);

        return doc.SaveFile(xmlPath);
    }

    void InsertXMLNode(tinyxml2::XMLDocument &doc, const User& user)
    {
        /*tinyxml2::XMLDocument doc;
        int ret = doc.LoadFile(xmlPath);
        if (ret != 0)
        {
            std::cerr << "Load xml file failed." << std::endl;
            return ret;
        }*/

        tinyxml2::XMLElement *root = doc.RootElement();
        tinyxml2::XMLElement *userNode = doc.NewElement("User");
        
        userNode->SetAttribute("Name", user.GetName().c_str());
        userNode->SetAttribute("Password", user.GetPassword().c_str());

        root->InsertEndChild(userNode);

        tinyxml2::XMLElement *gender = doc.NewElement("Gender");
        userNode->InsertEndChild(gender);

        tinyxml2::XMLText *genderText = doc.NewText(std::to_string(user.GetGender()).c_str());
        gender->InsertEndChild(genderText);

        tinyxml2::XMLElement *mobile = doc.NewElement("Mobile");
        userNode->InsertEndChild(mobile);
        mobile->InsertEndChild(doc.NewText(user.GetMobile().c_str()));

        tinyxml2::XMLElement *email = doc.NewElement("Email");
        userNode->InsertEndChild(email);
        email->InsertEndChild(doc.NewText(user.GetEmail().c_str()));

        ///return doc.SaveFile(xmlPath);
    }

    const tinyxml2::XMLElement *QueryUserNodeByName(const tinyxml2::XMLElement *root, 
        const std::string &name)
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        const tinyxml2::XMLElement *node = root->FirstChildElement("User");
        while (node != nullptr)
        {
            if (node->Attribute("Name") == name)
            {
                break;
            }
            node = node->NextSiblingElement();
        }
        return node;
    }

    User *QueryUserByName(tinyxml2::XMLDocument &doc, const std::string &name)
    {
        //tinyxml2::XMLDocument doc;
        /*int ret = doc.LoadFile(xmlPath);
        if (ret != 0)
        {
            std::cerr << "Load xml file failed." << std::endl;
            return nullptr;
        }*/
        tinyxml2::XMLElement *root = doc.RootElement();
        const tinyxml2::XMLElement *userNode = QueryUserNodeByName(root, name);
        if (userNode == nullptr)
        {
            std::cerr << "Can't find user node with this name" << std::endl;
            return nullptr;
        }

        User *user = new User;
        user->SetName(name);
        user->SetPassword(userNode->Attribute("Password"));     
        user->SetGender(std::stoi(userNode->FirstChildElement("Gender")->GetText()));
        user->SetMobile(userNode->FirstChildElement("Mobile")->GetText());
        user->SetEmail(userNode->FirstChildElement("Email")->GetText());

        return user;
    }

    bool UpdateUserNode(tinyxml2::XMLDocument &doc, const User &user)
    {
        /*tinyxml2::XMLDocument doc;
        int ret = doc.LoadFile(xmlPath);
        if (ret != 0)
        {
            std::cerr << "Load xml file failed." << std::endl;
            return false;
        }*/

        tinyxml2::XMLElement *root = doc.RootElement();
        tinyxml2::XMLElement *userNode = const_cast<tinyxml2::XMLElement *>(QueryUserNodeByName(root, user.GetName()));
        if (userNode == nullptr)
        {
            std::cerr << "Can't find the node" << std::endl;
            return false;
        }

        if (userNode->Attribute("Password") != user.GetPassword())
        {
            userNode->SetAttribute("Password", user.GetPassword().c_str());
        }

        tinyxml2::XMLElement *genderNode = userNode->FirstChildElement("Gender");
        if (genderNode->GetText() != std::to_string(user.GetGender()))
        {
            genderNode->SetText(std::to_string(user.GetGender()).c_str());
        }

        tinyxml2::XMLElement *mobileNode = userNode->FirstChildElement("Mobile");
        if (mobileNode->GetText() != user.GetMobile().c_str())
        {
            mobileNode->SetText(user.GetMobile().c_str());
        }

        tinyxml2::XMLElement *emailNode = userNode->FirstChildElement("Email");
        if (emailNode->GetText() != user.GetEmail().c_str())
        {
            emailNode->SetText(user.GetEmail().c_str());
        }
        return true;
        /*if (doc.SaveFile(xmlPath) == 0)
        {
            return true;
        }*/
    }

    bool DeleteUserByName(tinyxml2::XMLDocument &doc, const std::string &name)
    {
        /*tinyxml2::XMLDocument doc;
        int ret = doc.LoadFile(xmlPath);
        if (ret != 0)
        {
            std::cerr << "Load file failed." << std::endl;
            return false;
        }*/

        tinyxml2::XMLElement *root = doc.RootElement();
        tinyxml2::XMLElement *userNode = const_cast<tinyxml2::XMLElement *>(QueryUserNodeByName(root, name));     
        if (nullptr == userNode)
        {
            std::cerr << "Can't find the node." << std::endl;
            return false;
        }

        if (userNode == root)
        {
            doc.DeleteChildren();
            //doc.SaveFile(xmlPath);
            return true;
        }

        tinyxml2::XMLNode *userNodeParent = userNode->Parent();
        if (nullptr == userNodeParent)
        {
            std::cerr << "userNodeParent is nullptr" << std::endl;
            return false;
        }

        tinyxml2::XMLElement *userParentEle = userNodeParent->ToElement();
        if (userParentEle != nullptr)
        {
            userParentEle->DeleteChild(userNode);
            //doc.SaveFile(xmlPath);
            return true;
        }
        return false;       
    }

    bool GetXMLDecleration(tinyxml2::XMLDocument &doc, std::string &strDecl)
    {
        /*tinyxml2::XMLDocument doc;
        int ret = doc.LoadFile(xmlPath);
        if (ret != 0)
        {
            std::cerr << "Load xml file failed." << std::endl;
            return false;
        }*/

        tinyxml2::XMLNode *decla = doc.FirstChild();
        if (nullptr == decla)
        {
            std::cerr << "decla is nullptr" << std::endl;
            return false;
        }

        tinyxml2::XMLDeclaration *declaration = decla->ToDeclaration();
        if (nullptr == declaration)
        {
            std::cerr << "declaration is nullptr." << std::endl;
            return false;
        }    
        strDecl = declaration->Value();
        return true;
    }
    bool RemoveXmlFile(const char *xmlPath)
    {
        int ret = std::remove(xmlPath);
        if (ret != 0)
        {
            std::cerr << "Remove xml file failed." << std::endl;
            return false;
        }
        return true;
    }
}

void TestXmlData()
{
    const char *xmlPath = "data.xml";
    int ret = ParseXML::CreateXML(xmlPath);
    if (ret != 0)
    {
        std::cerr << "create xml file failed." << std::endl;
        return;
    }

    tinyxml2::XMLDocument doc;
    ret = doc.LoadFile(xmlPath);
    if (ret != 0)
    {
        std::cerr << "Load xml file failed." << std::endl;
        return;
    }
    doc.Print();

    User qingya("qingya", "123456", 1, "12345678956", "qingya@qq.com");
    User sichan("zijian", "123455", 1, "23454366546", "sichan@qq.com");

     ParseXML::InsertXMLNode(doc, qingya);
    ParseXML::InsertXMLNode(doc, sichan);
    /*if (ret != 0)
    {
        std::cerr << "insert failed." << std::endl;
        return;
    }*/
    std::cout << "***************************************" << std::endl;
    doc.Print();

    User *userPtr = ParseXML::QueryUserByName(doc, "qingya");
    if (userPtr != nullptr)
    {
        userPtr->Print();
    }

    User zijian("zijian", "123456", 0, "12435435436", "zijian@qq.com");
    bool errFlag = ParseXML::UpdateUserNode(doc, zijian);
    doc.Print();

    errFlag = ParseXML::DeleteUserByName(doc, "zijian");
    doc.Print();

    std::string strDecl;
    errFlag = ParseXML::GetXMLDecleration(doc, strDecl);
    std::cout << strDecl << std::endl;

    doc.SaveFile(xmlPath);
    //ParseXML::RemoveXmlFile(xmlPath);
}
