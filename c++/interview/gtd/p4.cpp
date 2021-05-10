#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>

class Resource
{
public:
    Resource(int id)
    {
        this->id = id;
    }

    void performTask(std::string task)
    {
        tasks.push_back(task);
    }

    size_t countTasks() const
    {
        return tasks.size();
    }

    std::string getTask(int index) const
    {
        return tasks.at(index);
    }

private:
    std::vector<std::string> tasks;
    int id;
};

class Runner
{
public:
    Resource* acquireResource(int id)
    {
        std::unordered_map<int, Resource*>::iterator search = resources.find(id);
        if (search == resources.end())
        {
            Resource* resource = new Resource(id);
            std::pair<int, Resource*> keyValue(id, resource);
            resources.insert(keyValue);
            return resource;
        }
        else
        {
            return search->second;
        }
    }

    void releaseResource(int id)
    {
        resources.erase(id);
    }

private:
    std::unordered_map<int, Resource*> resources;
};

#ifndef RunTests
void printResource(const Resource& resource)
{
    for (size_t i = 0; i < resource.countTasks(); i++)
    {
        if (i != 0)
        {
            std::cout << ", ";
        }

        std::cout << resource.getTask(i);
    }
    std::cout << '\n';
}

int main()
{
    Runner d;

    d.acquireResource(1)->performTask("Task11");
    d.acquireResource(2)->performTask("Task21");
    printResource(*d.acquireResource(2));
    d.releaseResource(2);

    d.acquireResource(1)->performTask("Task12");
    printResource(*d.acquireResource(1));
    d.releaseResource(1);
}
#endif