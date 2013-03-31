/*test the singleton pattern*/
#include <iostream>

using namespace std;

class A
{
public:	
	static A* GetInstance();
	void Print();	
	~A();
private:
	static A *a;
	A();
	int ia;
};
A* A::a = NULL;
A::A()
{
	A::ia = 1;
	cout<<"construct"<<endl;
}
A::~A()
{
	cout<<"destruct"<<endl;
}
void A::Print()
{
	cout<<ia<<" get object"<<endl;
}
A* A::GetInstance()
{
	if(a == NULL)
		a = new A();
	return a;
}

class B
{
public:
	B()
	{
		b = 21;
	}
	void Print()
	{
		cout<<b<<endl;
	}
private:
	int b; 
};

int main()
{
	B *pb = new B();
	pb->Print();
	delete pb;
	pb->Print();
	
	A *pa = A::GetInstance();
	pa->Print();
	delete pa;
	pa->Print();//调用不出错，很奇怪
	
	return 0;
}