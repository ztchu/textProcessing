#include "tinyxmlTest.h"

void HelloWorld()
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile("hello.xml");
    const char *content = doc.FirstChildElement("hello")->GetText();
    std::cout << content << std::endl;
}

void TestScene()
{
    tinyxml2::XMLDocument doc;
    int ret = doc.LoadFile("scene.xml");
    if (ret != 0)
    {
        std::cout << "Load xml file failed." << std::endl;
        return;
    }
    tinyxml2::XMLElement *scene = doc.RootElement();
    const tinyxml2::XMLAttribute *sceneAttr = scene->FirstAttribute();
    std::cout << sceneAttr->Name() << ": " << scene->Value() << std::endl;

    tinyxml2::XMLElement *node = scene->FirstChildElement("node");
    while (node != nullptr)
    {
        const tinyxml2::XMLAttribute *nodeAttr = node->FirstAttribute();
        std::cout << nodeAttr->Name() << ":" << nodeAttr->Value() << std::endl;

        tinyxml2::XMLElement *childElement = node->FirstChildElement();
        while (childElement != nullptr)
        {
            const char *content = childElement->GetText();
            std::cout << content << std::endl;
            childElement = childElement->NextSiblingElement();
        }
        node = node->NextSiblingElement();
    }
    //doc.Print();
}