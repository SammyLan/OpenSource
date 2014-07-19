#include "StdAfx.h"
#include "LeakDiagParser.h"
#include <tinyxml\tinyxml.h>
#include <tinyxml\tinystr.h>

LeakDiagParser::LeakDiagParser()
	:total_leak_(0)
{
}
LeakDiagParser::~LeakDiagParser(void)
{
}

bool LeakDiagParser::Load(string const & strXML)
{
	TiXmlDocument doc;
	bool bRet = doc.LoadFile(strXML.c_str());
	if(!bRet)
	{
		return false;		
	}
	do
	{
		TiXmlElement * pRoot = doc.RootElement();
		TiXmlNode * pLeaks = pRoot->FirstChild("LEAKS");
		if(pLeaks == NULL)
			break;
		TiXmlElement * pStack = (TiXmlElement*)  pLeaks->FirstChild("STACK");
		while(pStack)
		{
			stackList_.push_back(ReadStack(pStack));
			pStack = (TiXmlElement*)  pLeaks->IterateChildren("STACK",pStack);
		}

		
	}while(0);

	return bRet;
}

shared_ptr<LeakDiagParser::StackInfo> LeakDiagParser::ReadStack(TiXmlElement * pStack )
{
	shared_ptr<StackInfo> pInfo( new StackInfo());
	string val = pStack->Attribute("numallocs",&pInfo->numallocs_);
	val = pStack->Attribute("size",&pInfo->size_);
	val = pStack->Attribute("totalsize",&pInfo->totalsize_);
	total_leak_ += pInfo->totalsize_;
	
	TiXmlElement * pFrame = (TiXmlElement*)  pStack->FirstChild("FRAME");
	while(pFrame)
	{
		pInfo->frames_.push_back(ReadFrame(pFrame));
		pFrame = (TiXmlElement*)  pStack->IterateChildren("FRAME",pFrame);
	}

	return pInfo;
}

shared_ptr<LeakDiagParser::FrameInfo> LeakDiagParser::ReadFrame(TiXmlElement * pFrame)
{
	shared_ptr<FrameInfo> pInfo( new FrameInfo);
	pInfo->dll_ = pFrame->Attribute("dll",(int*)NULL);
	pInfo->function_ = pFrame->Attribute("function",(int*)NULL);	
	pInfo->filename_ = pFrame->Attribute("filename",(int*)NULL);
	pFrame->Attribute("line",&pInfo->line_);
	pFrame->Attribute("offset",&pInfo->offset_);
	return pInfo;
}

int LeakDiagParser::TotalLeak()
{
	return total_leak_;
}