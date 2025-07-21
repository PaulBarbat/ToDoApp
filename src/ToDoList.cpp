#include "ToDoList.h"
#include <iostream>

size_t ToDoList::s_ID = 1;

ToDoList::ToDoList(const std::string& path){
//json reading here
}

std::shared_ptr<ToDoList::ToDoElement> ToDoList::getElement(size_t index){
    if(index >=0 && index < m_elements.size())
        return m_elements.at(index);
    return nullptr;
}

bool ToDoList::addElement(const ToDoElement& element){
    if(element.getDescription().empty())
        return false;
    m_elements.push_back(std::make_shared<ToDoElement>(element));
    return true;
}

void ToDoList::printList(const std::string& offset) const{
    for(const auto& element : m_elements)
    {
        std::cout<< offset<< element->toString()<< std::endl;
        if(element->hasSubList())
            element->getSubElements()->printList(offset+"----");
    }
}

bool ToDoList::isEmpty() const{ return m_elements.empty();}