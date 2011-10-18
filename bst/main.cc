#include "bst.cc"

int main()
{
    BinarySearchTree<int> bst;
   
    bst.Insert(44);
    bst.Insert(23);
    bst.Insert(22);
    bst.Insert(54);
    bst.Insert(65);
    bst.Insert(34);
    bst.Insert(224);
    bst.Insert(98);
    bst.InorderTraversal();
    //bst.Delete(54);
    // bst.Delete(224);
    bst.InorderTraversal();
    std::cout << bst.FindMin() << std::endl;
    std::cout << bst.Predecessor(98) << std::endl;
    std::cout << bst.Successor(34) << std::endl;
    std::cout << bst.FindMax() << std::endl;
   // bst.Search(22);
    
    return 0;
}
