#pragma once
#include<string>
#include<vector>
#include<list>
#include <tinyxml\tinyxml.h>

using namespace std;

class LeakDiagParser
{
	struct FrameInfo
	{
		string dll_;
		string function_;		
		string filename_;
		int line_;
		int offset_;
	};
	struct StackInfo
	{
		int numallocs_;
		int size_;
		int totalsize_;
		vector<shared_ptr<FrameInfo> > frames_;
	};
public:
	LeakDiagParser();	
	~LeakDiagParser(void);
	bool Load(string const & strXML);
	int TotalLeak();
protected:
	shared_ptr<LeakDiagParser::StackInfo> ReadStack(TiXmlElement * pStack );
	shared_ptr<LeakDiagParser::FrameInfo> ReadFrame(TiXmlElement * pFrame);
private:
	vector<shared_ptr<StackInfo> > stackList_;
	int total_leak_;
};

