#include "ToDoList.h"
#include <iostream>
#include <fstream>
#include <stdexcept>


ToDoList::ToDoList(const std::string& path){
    std::ifstream file(path);
    if(!file.is_open()){
        throw std::runtime_error("Failed to open file: " + path);
    }

    json j;
    file >> j;

    *this = ToDoList::fromJson(j);
}

std::shared_ptr<ToDoList::ToDoElement> ToDoList::getElement(size_t ID){
    auto it = ToDoElement::s_Element_Map.find(ID);
    if(it!= ToDoElement::s_Element_Map.end())
        return it->second.lock();
    return nullptr;
}


bool ToDoList::addElement(ToDoElement&& element){
    if(element.getDescription().empty())
        return false;
    m_elements.push_back(std::make_shared<ToDoElement>(std::move(element)));
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

json ToDoList::toJson() const{
    json j = json::array();
    for(const auto& element : m_elements) {
        j.push_back(element->toJson());
    }
    return j;
}

ToDoList ToDoList::fromJson(const json& j){
    ToDoList list;
    for(const auto& item : j)
        list.addElement(std::move(ToDoElement::fromJson(item)));
    return list;
}