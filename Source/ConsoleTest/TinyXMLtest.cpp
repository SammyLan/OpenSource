// ConsoleTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <tinyxml\tinyxml.h>
#include <tinyxml\tinystr.h>
#include <string>
#include <Include/UtilDir.h>
#include <Include/UtilConvert.h>
#include ".\LeakDiag\LeakDiagParser.h"

using namespace std;

string GetXMLPath()
{
	return (LPCSTR)Util::Convert::UnicodeToGBK(Util::Dir::GetDataDir()) +string( "\\QQ_Leak.xml");
}
bool CreateXmlFile(string& szFileName)
{//创建xml文件,szFilePath为文件保存的路径,若创建成功返回true,否则false
    try
    {
        //创建一个XML的文档对象。
        TiXmlDocument *myDocument = new TiXmlDocument();
        //创建一个根元素并连接。
        TiXmlElement *RootElement = new TiXmlElement("Persons");
        myDocument->LinkEndChild(RootElement);
        //创建一个Person元素并连接。
        TiXmlElement *PersonElement = new TiXmlElement("Person");
        RootElement->LinkEndChild(PersonElement);
        //设置Person元素的属性。
        PersonElement->SetAttribute("ID", "1");
        //创建name元素、age元素并连接。
        TiXmlElement *NameElement = new TiXmlElement("name");
        TiXmlElement *AgeElement = new TiXmlElement("age");
        PersonElement->LinkEndChild(NameElement);
        PersonElement->LinkEndChild(AgeElement);
        //设置name元素和age元素的内容并连接。
        TiXmlText *NameContent = new TiXmlText("周星星");
        TiXmlText *AgeContent = new TiXmlText("22");
        NameElement->LinkEndChild(NameContent);
        AgeElement->LinkEndChild(AgeContent);
		CStringA appPath = Util::Convert::UnicodeToGBK(Util::Dir::GetAppDir());
        string seperator = "\\";
        string fullPath = string(appPath.GetBuffer(0)) + seperator + szFileName;
        myDocument->SaveFile(fullPath.c_str());//保存到文件
    }
    catch (string&)
    {
        return false;
    }
    return true;
}

bool ReadXmlFile(string& szFileName)
{//读取Xml文件，并遍历
    try
    {
		CStringA appPath = Util::Convert::UnicodeToGBK(Util::Dir::GetAppDir());
        string seperator = "\\";
        string fullPath = appPath.GetBuffer(0) +seperator+szFileName;
        //创建一个XML的文档对象。
        TiXmlDocument *myDocument = new TiXmlDocument(fullPath.c_str());
        myDocument->LoadFile();
        //获得根元素，即Persons。
        TiXmlElement *RootElement = myDocument->RootElement();
       // 输出根元素名称，即输出Persons。
        cout << RootElement->Value() << endl;
        //获得第一个Person节点。
        TiXmlElement *FirstPerson = RootElement->FirstChildElement();
        //获得第一个Person的name节点和age节点和ID属性。
        TiXmlElement *NameElement = FirstPerson->FirstChildElement();
        TiXmlElement *AgeElement = NameElement->NextSiblingElement();
        TiXmlAttribute *IDAttribute = FirstPerson->FirstAttribute();
        //输出第一个Person的name内容，即周星星；age内容，即；ID属性，即。
        cout << NameElement->FirstChild()->Value() << endl;
        cout << AgeElement->FirstChild()->Value() << endl;
        cout << IDAttribute->Value()<< endl;
    }
    catch (string& e)
    {
        return false;
    }
    return true;
}
int main()
{
	string fileName = GetXMLPath();
	LeakDiagParser parser;
	parser.Load(fileName);
	cout<<parser.TotalLeak()/1024<<"k"<<endl;
}