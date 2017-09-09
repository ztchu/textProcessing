#include <iostream>

#include "testJson.h"
#include "json.hpp"

void TestCinCoutJson()
{
    nlohmann::json jn;
    std::cin >> jn;
    std::cout << jn;
}

void TestCreateJsonByKey()
{
    nlohmann::json jn;
    jn["pi"] = 3.141;
    jn["happy"] = true;
    jn["name"] = "Niles";
    jn["nothing"] = nullptr;
    jn["answer"]["everything"] = 42;
    jn["list"] = { 1, 0, 2 };
    jn["object"] = { {"currency", "USD"}, {"value", 42.99} };

    nlohmann::json jn2 = {
        {"pi", 3.141},
        {"happy", true},
        {"name", "Niles"},
        {"nothing", nullptr},
        {"answer", {{"everything", 42}}},
        {"list", {1, 0, 2}},
        {"object", {{"currency", "USD"}, {"value", 42.99}}}
    };
    
    std::cout << jn << std::endl;
    std::cout << jn2 << std::endl;
}

void TestJsonArray()
{
    nlohmann::json array1 =
    {
        "a", 6, "xin", 8
    };
    std::cout << array1[1] << std::endl;
}

void TestJsonValue()
{
    nlohmann::json array1 =
    {
        {"a", 6}
    };
    std::cout << array1["a"] << std::endl;
}

void TestJsonWithDump()
{
    nlohmann::json jn = { {"qingya", 21}, {"zijian", 24}, {"sichan", 25}, {"zhuiyuan", 26} };
    
    std::string sr = jn.dump();
    std::cout << sr << std::endl;

    std::cout << jn.dump(4) << std::endl;
}

void TestJsonWith_json()
{
    nlohmann::json jn1 = "{\"happy\" :true, \"pi\":3.14}"_json;
    nlohmann::json jn2 = R"(
    {
        "happy" :["true", "good", "well"],
        "pi":3.14
    }
    )"_json;
    nlohmann::json jn3 = 
    {
        {"happy" ,{true, "good", "well"}},
        {"pi",3.14}, 
        {"qingya", 23}
    };

    std::cout << jn2 << std::endl;
    std::cout << jn2["happy"][0] << std::endl;
    std::cout << jn2["pi"] << std::endl;
    std::cout << jn3["pi"] << std::endl;
}

void TestJsonArrayInArray()
{
    nlohmann::json array1 = { {"a", 5}, "qing", 8 };
    std::cout << array1[0][0] << std::endl;
}

void TestJsonArrayWithObject()
{
    nlohmann::json array1 = {
        {{"a", 6}}, "qingya", 8 };

    nlohmann::json array2 = {
    {"first",3},
    {"zijian",34} };

    nlohmann::json jn = { "qingya", 32 };

    std::cout << array2["first"] << std::endl;

    std::cout << jn[0] << std::endl;
}

//±¾µØ¿ËÂ¡  
