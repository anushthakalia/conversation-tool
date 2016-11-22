#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;

int main()
{
    
    ifstream object1;              //declaring an object for reading the text file
    string filename="conversation.txt";
	object1.open(filename.c_str());//opening the txt file
    if (!object1.is_open()){
		cout<<"error";
    }
    char letter;
	int char_count=0;// counts number of characters in txt file
	vector<string> vec; 
    string word="";
    char prev_letter='a';
	while (object1.get(letter)) {
		letter=tolower(letter);
		if(prev_letter==' ' && letter==' '){
			continue;
         }
		if(letter==' ' && char_count!=0  ){
	    if(word=="umm"||word=="mm"||word=="Ahh"||word=="hmm"){

	    }
	    else{
		vec.push_back(word);
        word="";
        }
		}
		else{
			if(letter=='!'||letter==','||letter=='.'||letter==':'||letter==';'||letter=='"'||letter=='?'){
				continue;
			}
			word=word+letter;
		}
		//if (letter==' '|| letter=='\n'|| letter=='.'|| letter==','||letter==':'||letter=='"'||letter=='') {
		//	string word1=string(word);
		//}
		prev_letter=letter;
		char_count++;

	}

	for(int i=0;i<vec.size();i++){

		cout<<vec[i]<<endl;
	}

}