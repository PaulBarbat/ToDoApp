#include "ToDoList.h"

void main()
{
    ToDoList list {"resources/list.json"};
    list.printList();
    cin.get();
}