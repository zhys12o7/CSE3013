#include "string.h" //header file
#include <iostream>  //header file

using namespace std;
int main()
{
	Str a("I'm a girl"); //class type a
	cout<<a.contents(); //print a's contents
	a="I'm a boy\n"; //change a
	cout<<a.contents(); //print a's contents again it should be changed
	cout<<a.compare("I'm a a")<<endl; //compare a with "I'm a a"
	return 0; //end
}
