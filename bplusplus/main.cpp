#include "cplusplus.h"
#include <iostream>

int main() {
	Bplusplus bt;
	bt.Insert(23,23);
	bt.Insert(22,22);
	bt.Insert(21,21);
	bt.Insert(245,245);
	bt.Insert(232,232);
	bt.Insert(234,234);
	bt.Insert(32,32);
	bt.Insert(54,54);
	bt.Insert(28,28);
	bt.Insert(56,56);
	bt.Show();
	bt.Delete(28);
	bt.Delete(54);
	bt.Delete(234);
	bt.Delete(232);
	bt.Show();
}