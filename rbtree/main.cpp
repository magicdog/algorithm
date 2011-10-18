#include "rbtree.cpp"

int main()
{
    RbTree<int> rbtree;
    rbtree.Insert(43);
    rbtree.Insert(45);
    rbtree.Insert(23);
    rbtree.Insert(65);
    rbtree.Insert(33);
    rbtree.Insert(11);
    rbtree.ShowNode(rbtree.Search(11));
    rbtree.ShowNode(rbtree.Successor(rbtree.Search(33)));
    rbtree.Delete(11);
    rbtree.Delete(33);
    rbtree.Show();
    return 0;
}
