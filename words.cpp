#include<iostream>

#include "tinyxml2.h"
#include "tinyxml2.cpp"

using namespace std;
using namespace tinyxml2;

int main(int argc, char const *argv[])
{
	
	XMLDocument xmlDoc;
	XMLError eResult=xmlDoc.LoadFile("words.xml");
	XMLNode *pRoot=xmlDoc.FirstChild();
	
	
	for(XMLElement* e=pRoot->FirstChildElement("entry");e!=NULL;e=e->NextSiblingElement("entry")){
		XMLElement* tokened=e->FirstChildElement("token");
		const char* word = tokened->GetText();
		 printf( "%s\n ", word); 
		 string tag=e->Attribute("tags");
		 cout<<tag<<endl;
	}
	
	

	return XML_SUCCESS;
    }