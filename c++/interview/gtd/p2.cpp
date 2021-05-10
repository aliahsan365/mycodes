#include <vector>
#include <stdexcept>
#include <iostream>

int countInternalNodes (const std::vector<int>& tree)
{

    int n_nodes = tree.size();
    std::vector<bool> i_node(n_nodes,false);
    for (int i = 0; i < n_nodes; ++i) {
    	int son = i;
    	int padre = tree[son];
    	bool padre_root = padre == -1;
    	if (padre_root) {
    		if (n_nodes > 1) {
    			i_node[son] = true;
    		}
    	}
    	else {
    		i_node[padre] = true;
    	}
    }

    int internal_nodes = 0;
    for (int i = 0; i < n_nodes; ++i) 
    {
    	if (i_node[i]) {
    		++internal_nodes;
    	}
    } 


    return internal_nodes;

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