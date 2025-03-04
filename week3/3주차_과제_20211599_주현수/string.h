#ifndef __STR__
#define __STR__

class Str //class name
{
	private:
		char *str; //string 
		int len; //string's length
	public:
		Str(int leng); //leng means string's length
		Str(char *neyong); //neyong means string's contents
		~Str();//소멸자
		int length(void);//return string's length
		char *contents(void);//return string's contents
		int compare(class Str&a);//compare with a
		int compare(char *a);//compare with a
		void operator=(char *a);//string 값을 대입한다
		void operator=(class Str&a);//string 값을 대입한다
};
#endif

