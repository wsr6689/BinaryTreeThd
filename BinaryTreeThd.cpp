#include "BinaryTreeThd.h"


void test()
{
	int a1[10] = {1,2,3,'#','#',4,'#','#',5,6};
	int a2[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8}; 
	BinaryTreeThd<int> b(a2,15,'#');
	//b.InOrderThreading();
	//b.InOrderThd();
	b.PrevOrderThreading();
	b.PrevOrderThd();
	//b.PostOrderThreading();
}
int main()
{
	test();
	return 0;
}