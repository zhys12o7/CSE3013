#ifndef __LINKEDLIST__
#define __LINKEDLIST__

#include <iostream>
using namespace std;

//LinkedList Node의 템플릿 선언
template <class T>
class Node{
	public:
		T data;//데이터를 저장할 변수
		Node *link;//노드구조체 이용, 다음 노드의 주소를 저장할 포인터
		Node(T element){
			data=element;
			link=0;
		}
};
//LinkedList Class의 템플릿 선언
template<class T>
class LinkedList{
	protected:
		//첫번째 노드의 주소를 저장할 포인터
		Node<T> *first; //처음을 가리키는 포인터
		T current_size; //리스트의 크기
	public:
		//생성자, 초기화 
		LinkedList(){
			first = 0;
			current_size = 0;
		};

		//노드 개수를 리턴
		int GetSize(){
			return current_size;
		};

		//맨 앞에 원소를 삽입, LinkedList와 Stack 둘다 같다
		void Insert(T element);
		
		//맨 뒤의 원소를 삭제, 제일 나중에 들어온 원소 삭제  - LinkedList
		virtual bool Delete(T &element);

		//리스트 출력
		void Print();
};


//새 노드를 맨 앞에 붙이고 값을 넣음
template <class T> 
void  LinkedList<T>::Insert(T element){
	//노드 생성
	Node<T> *newnode = new Node<T>(element);

	//새 노드가 첫번째 노드를 가리킴
	//newnode는 포인터이기 때문에 -> 를 사용해 함수, 변수를 불러옴 newnode.link와 뜻은 같다
	newnode -> link = first;
	first = newnode;
	current_size++;//리스트 크기 증량
}

//마지막 노드의 값을 리턴하면서 메모리에서 할당 해제
template <class T>
bool LinkedList<T>::Delete(T &element){

	if (first == 0) //삭제할 노드가 없으면 false를 리턴
		return false;
	
	Node<T> *current = first;
	Node<T> *previous = 0;
	
	//마지막 노드까지 찾아가는 반복문
	while(1){
		if (current->link == 0){  //마지막 노드를 찾는것
			if (previous)//맨 처음 리스트를 삭제하는 것이 아닐 때
				previous -> link = current -> link;
			else
				first = first -> link; //맨 처음 리스트를 삭제하는 것일 때
			break;
		}
		previous = current;//previous포인터를 다음 칸으로 설정
		current = current -> link;//current포인터를 다음칸으로 설정
	}
	element = current -> data;
	delete current;//삭제할 노드
	current_size--;//리스트의 사이즈 감소시키기

	return true;
}

//리스트를 출력하는 Print 함수
template <class T>
void LinkedList<T>::Print(){
	Node<T> *i;
	int index = 1;

	if (current_size != 0){
		for( i = first; i != NULL; i=i->link){
			if (index == current_size){
				cout << "[" << index << "|";
				cout << i -> data <<"]";
			}
			
			else {
				cout << "[" << index << "|";
				cout << i -> data << "]->";
				index++;
			}
		}
		cout << endl;
	}

}


#endif
