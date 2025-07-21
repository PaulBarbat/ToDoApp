#include "ToDoList.h"

using ToDoElement = ToDoList::ToDoElement;

ToDoElement::ToDoElement(bool isDone,const std::string& description): m_ID(ToDoList::getID()), m_isDone(isDone), m_description(description){}

bool ToDoElement::getIsDone() const{ return m_isDone;}

std::string ToDoElement::getDescription() const{ return m_description;}

void ToDoElement::setIsDone(bool value){ m_isDone=value;}

void ToDoElement::setDescription(const std::string& description){ 
    if(!description.empty())
        m_description=description;
}

bool ToDoElement::addSubElement(const ToDoElement& element){
    if(element.getDescription().empty())
        return false;
    if(!m_sublist.has_value())
        m_sublist = std::make_shared<ToDoList>();
    return (*m_sublist)->addElement(element);
}

std::shared_ptr<ToDoList> ToDoElement::getSubElements() const{
    if(m_sublist.has_value())
        return *m_sublist;
    return nullptr;
}

bool ToDoElement::hasSubList() const{
    return (m_sublist.has_value()&& (!(*m_sublist)->isEmpty()));
}

const std::string& ToDoElement::toString() const{
    return std::to_string(m_ID)+" [" +(m_isDone ? "X" : "")+"] - "+m_description;
}
