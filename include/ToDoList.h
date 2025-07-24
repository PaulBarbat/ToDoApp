#pragma once
#include "ToDoElement.h"

class ToDoList{
public:

    ToDoList();
    ToDoList(const std::string& path);
    std::shared_ptr<ToDoElement> getElement(size_t ID);
    bool addElement(ToDoElement&& element);
    void printList(const std::string& offset) const;
    bool isEmpty() const;

    json toJson() const;
    static ToDoList fromJson(const json& j);

private:

    std::vector<std::shared_ptr<ToDoElement>> m_elements;
};
