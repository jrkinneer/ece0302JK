// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

// TODO: Implement the constructor here
XMLParser::XMLParser()
{
	valid = false;
	elementNameBag = new Bag<string>;
	parseStack = new Stack<string>;
}  // end default constructor

// TODO: Implement the destructor here
XMLParser::~XMLParser()
{
	clear();
	delete elementNameBag;
	delete parseStack;
	elementNameBag = nullptr;
	parseStack = nullptr;
}  // end destructor

// TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	TokenStruct temp;
	string tag, content;
	std::vector<char> illegalChar = {'!','\"','#','#','$','%','&','\'','(',')','*','+',',','/',';','<','=','>','?','@','[','\\',']','^','`','{','|','{','~'};
	//holds the values of the characters that are not 
	//allowed to show up in XML parsed strings
	std::vector<char> illegalStart = {' ', '-', '.', ',','1','2','3','4','5','6','7','8','9'};

	//first we check to see that the input string is a valid 
	//input beginning with "<" and ending with ">"
	/*if (inputString[0] != '<' || inputString[inputString.length()-1] != '>'){
		clear();
		return false;
	}*/ //if these conditions are not met, the internal data structures are cleared
	//and a false value is returned
	
	//otherwise
	int i = 0;
	while (i < inputString.length()){
		//this loop will allow us to grab the tag name
		//and the content of the input string
		
		int index; //tracks location in input string

		if (inputString[i] == '<'){
			tag = "";
			for (int j = i+1; inputString[j] != '>' ;j++){
				index = j + 1;
				if (inputString[j] == '<'){
					return false;
				}//checks for nested delimiters, and if one is found false is returned
				
				//otherwise we add the contents of input string to tag
				//so we can later determine what type of tag it is
				tag += inputString[j];

			}//loops through the text between the delimiters

			//now that tag holds the values of all text between 
			//the delimiters we can check for what type of tag it is

			if (tag[0] == '/'){//checks if end tag
				//first we check to see if the value stored in tag
				//begins with the unallowed starting chars
				for (int k = 0; k < illegalStart.size(); k++){
					if (tag[1] == illegalStart[k]){
						std::cout<<"fail end tag start"<<std::endl;
						clear();
						return false;
					}
				}
				//if we make it past that check then
				//we have to check if the contents of the tag
				//are acceptable
				for (int i = 1; i < tag.length(); i++){
					for (int j = 0 ; j < illegalChar.size(); j++){
						if (tag[i] == illegalChar[j]){
							std::cout<<"fail end tag illegal"<<std::endl;
							clear();
							return false;
						}
					}
				}
				//if both the beginning and internal content checks pass then
				tag = tagNameCreator(tag);
				temp.tokenString = tag;
				temp.tokenType = END_TAG;
				tokenizedInputVector.push_back(temp); 
			}//end check end tag

			else if(tag[tag.length() - 1] == '/'){
				//checks if empty tag
				//here we can use very similar loops and conditionals as we
				//did in the end tag if statement
				for (int k = 0; k < illegalStart.size(); k++){
					if (tag[0] == illegalStart[k]){
						std::cout<<"fail empty start"<<std::endl;
						clear();
						return false;
					}
				}
				
				for (int i = 0; (i < (tag.length() - 1)) && tag[i] != ' '; i++){
					//here we change the comparison part of the loop because an empty tag 
					//goes until either the first white space (tag[i] != ' ') or the
					//the last / delimiter which would be at tag.length() - 1
					for (int j = 0 ; j < illegalChar.size(); j++){
						if (tag[i] == illegalChar[j]){
							std::cout<<"fail empty illegal"<<std::endl;
							clear();
							return false;
						}
					}
				}
				tag = tagNameCreator(tag);
				temp.tokenString = tag;
				temp.tokenType = EMPTY_TAG;
				tokenizedInputVector.push_back(temp);
			}//end of empty tag

			else if(tag[0] == '?' && tag[tag.length() - 1] == '?'){
				//checks if declaration
				for (int k = 0; k < illegalStart.size(); k++){
					if (tag[1] == illegalStart[k]){
						std::cout<<"fail dec start"<<std::endl;
						clear();
						return false;
					}
				}
				//if we make it past that check then
				//we have to check if the contents of the tag
				//are acceptable
				for (int i = 1; (i < tag.length() - 2) && tag[i] != ' '; i++){
					for (int j = 0 ; j < illegalChar.size(); j++){
						if (tag[i] == illegalChar[j]){
							std::cout<<"fail dec illagla"<<std::endl;
							clear();
							return false;
						}
					}
				}
				tag = tagNameCreator(tag);
				temp.tokenString = tag;
				temp.tokenType = DECLARATION;
				tokenizedInputVector.push_back(temp);
			}//end declaration
			else{
				//checks start tag
				for (int k = 0; k < illegalStart.size(); k++){
					if (tag[0] == illegalStart[k]){
						std::cout<<"fail start start"<<std::endl;
						clear();
						return false;
					}
				}
				for (int i = 0; (i < (tag.length() - 1)) && tag[i] != ' '; i++){
					
					for (int j = 0 ; j < illegalChar.size(); j++){
						if (tag[i] == illegalChar[j]){
							clear();
							return false;
						}
					}
				}
				tag = tagNameCreator(tag);
				temp.tokenString = tag;
				temp.tokenType = START_TAG;
				tokenizedInputVector.push_back(temp);
			}//end start tag

			//increment index
			index++;
		} //end if inputString[i] = '<' a.k.a. tags
		else{
			//here we will get the content, so anything
			//not contained within a < > delimiter set
			content = "";
			for (int j=i; inputString[j] != '<' && index<inputString.length(); j++){
				content += inputString[j];
				index = j + 1;
			} //this loop goes through and collects the content, stopping
			//when either another tag is found or all the input is checked
			//so if those conditions are satisified then the current char
			//from the input is added to the content string
			//and the index is updated

			//now we have to check to make sure we haven't just added
			//a bunch of blank spaces to the content string
			int spaces = 0;
			for (int k = 0; k < content.length(); k++){
				if (content[k] == ' '){
					spaces++;
				}
			}
			if (spaces != content.length()){
				//this logic is just saying that if space and content.length()
				//differ in value that means that there is at 
				//least one character of actual value in the string
				//and the member variables can be updated
				temp.tokenString = content;
				temp.tokenType = CONTENT;
				tokenizedInputVector.push_back(temp);
			}
		} //end content
		i = index;
	}//end loop
	return true;
}  // end function

// TODO: Implement a helper function to delete attributes from a START_TAG
// or EMPTY_TAG string (you can change this...)
string XMLParser::tagNameCreator(const string tag){
	//finds the tag name based on the whole tag found in 
	//tokenizeInputString
	string tName;
	
	//here we check to see what type of tag we are 
	//working with and move from there
	if (tag[0] == '?'){//declaration
		for (int i = 0; tag[i]!='?'; i++){
			tName+=tag[i];
		} //here we loop through input tag until the final
		//? is found to get the right name
	}
	else if(tag[tag.length()-1]=='/'){//empty
		for (int i = 0; tag[i] != ' ' && tag[i] != '/'; i++){
			tName += tag[i];
		} //adds characters until a space or / signaling the end tag
	}
	else if(tag[0] == '/'){//end tag
		for (int i = 1; i<tag.length(); i++){
			tName += tag[i];
		}
	}
	else{
		for (int i = 0; tag[i] != ' ' && i < tag.length(); i++){
			tName += tag[i];
		}
	}
	return tName;
}

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput()
{
	//first we check to see if the tokenized input vector
	//is empty and if its not then we go through each node 
	//and add the contents at that location to the elementNameBag
	//and the parseStack accordingly
	if (tokenizedInputVector.size() == 0){
		
		return false;
	}
	for (int i = 0; i < tokenizedInputVector.size(); i++){
		//here we go through all the tags with a conditional
		//for each tag type
		if (tokenizedInputVector[i].tokenType == START_TAG)
		{
			elementNameBag->add(tokenizedInputVector[i].tokenString);
			parseStack->push(tokenizedInputVector[i].tokenString);
		}
		else if (tokenizedInputVector[i].tokenType == END_TAG)
		{
			if (parseStack->peek()!=tokenizedInputVector[i].tokenString){
				
				return false;
			}
			parseStack->pop();
		}
		else if (tokenizedInputVector[i].tokenType == DECLARATION)
		{
			elementNameBag->add(tokenizedInputVector[i].tokenString);
		}
		else if (tokenizedInputVector[i].tokenType == CONTENT && parseStack->isEmpty())
		{
			
			return false;
		}
	}//end loop
	if (!parseStack->isEmpty()){
		
		return false;
	}
	valid = true;
	return true;
}//end function

// TODO: Implement the clear method here
void XMLParser::clear()
{
	//clear the individual data structures
	parseStack->clear();
	elementNameBag->clear();
	tokenizedInputVector.clear();
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const
{
	
	//using the contains member function to determine
	//if the input string is in the elementNameBag
	if (elementNameBag->contains(inputString)){
		return true;
	}
	return false;
}

// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const
{
	//check validity again
	if (!valid){
		throw logic_error("ERROR. Invalid XML.");
	}

	return elementNameBag->getFrequencyOf(inputString);
}
