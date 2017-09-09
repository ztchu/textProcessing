#pragma once
#include <string>

#include "tinyxml2.h"

class User
{
public:
    User();
    User(const std::string &name, const std::string &password, int gender, const std::string &moblie, const std::string &email);

    std::string GetName() const;
    std::string GetPassword() const;
    int GetGender() const;
    std::string GetMobile() const;
    std::string GetEmail() const;

    void SetName(const std::string &name);
    void SetPassword(const std::string &password);
    void SetGender(int gender);
    void SetMobile(const std::string &gender);
    void SetEmail(const std::string &email);

    void Print() const;
private:
    std::string name;
    std::string password;
    int gender;
    std::string mobile;
    std::string email;
};

namespace ParseXML
{
    int CreateXML(const char *xmlPath);
    int InsertXMLNode(const char* xmlPath, const User& user);
    const tinyxml2::XMLElement *QueryUserNodeByName(const tinyxml2::XMLElement *root,
        const std::string &name);
    User *QueryUserByName(const char *xmlPath, const std::string &name);
    bool UpdateUserNode(const char *xmlPath, const User &user);
    bool DeleteUserByName(const char *xmlPath, const std::string &name);
    bool GetXMLDecleration(const char *xmlPath, std::string &strDecl);
}

void TestXmlData();
