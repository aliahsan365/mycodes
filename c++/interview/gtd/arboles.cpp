#include <vector>
#include <stdexcept>
#include <iostream>

int countInternalNodes (const std::vector<int>& tree)
{
	return 1; // impelmentar funcion


}

#ifndef RunTests
int main()
{
    std::vector<int> tree;
    
    tree.push_back(1);
    tree.push_back(3);
    tree.push_back(1);
    tree.push_back(-1);
    tree.push_back(3);
    

    //tree.push_back(-1);


    std::cout << countInternalNodes(tree);
}
#endif
