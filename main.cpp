#include "ToDoList.h"

void saveJsonToFile(const std::string& path, const json& j)
{
    std::ostream file(path);
    if(!file.is_open()){
        throw std::runtime_error("Failed to open file for writing: "+path);
    }

    file << j.dump(4);
}

void main()
{
    ToDoList list {"resources/list.json"};
    list.printList();
    cin.get();
}