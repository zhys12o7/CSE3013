#include "string.h"
#include <cstring>
#include <iostream>
using namespace std;
Str::Str(int leng)
{
	if(leng<0) //if length is <0 print error message
	{
		cout<<"Array bound error!"<<endl;
		len=0; //return len
	}
	else
	{
		str=new char[leng]; //make array 
		len=leng;//make len size of string
	}
}

Str::Str(char *neyong)
{
	if(neyong==NULL)//if neyong is null print error message
	{
		cout<<"error"<<endl;
		len=0;//return len
	}
	else
	{
		str=new char[len]; //make array 		
		strcpy(str,neyong); //copy neyong to str
		len=strlen(neyong);//return len
	}
}

Str::~Str()
{
    delete[] str; //소멸자
}

int Str::length(void)
{
	return len; //return length size
}

char *Str::contents(void)
{
    return str;//return the contents of string
}

int Str::compare(class Str& a)
{
	return strcmp(str, a.contents());//compare with str and a
}

int Str::compare(char *a)
{
	return strcmp(str, a); //compare with str and a
}

void Str::operator=(char *a)
{
	delete[] str; //delete the original string

	if(a!=NULL)
	{
		len=strlen(a); //return new len
		str=new char[len]; //make a new string
		strcpy(str,a); //copy a to str 
	}
	else
	{
		cout<<"error"<<endl;//print error message
		len=0;//return len
	}
}

void Str::operator=(class Str& a)
{
	delete[] str; //delete the original string
	len=a.length();//return len
	str=new char[len];//make s new string
	strcpy(str,a.contents());//copy s.contents() to str
}

