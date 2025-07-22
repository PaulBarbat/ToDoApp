#include "ToDoList.h"

using ToDoElement = ToDoList::ToDoElement;

ToDoElement::ToDoElement(bool isDone,const std::string& description): m_ID(ToDoList::getID()), m_isDone(isDone), m_description(description){}

ToDoElement::ToDoElement(size_t id, bool isDone,const std::string& description): m_ID(id), m_isDone(isDone), m_description(description){
     if(ToDoList::s_ID <= id) ToDoList::s_ID = id+1; 
}//to make sure we update the static ID to be the next id possible

bool ToDoElement::getIsDone() const{ return m_isDone;}

const std::string& ToDoElement::getDescription() const{ return m_description;}

void ToDoElement::setIsDone(bool value){ m_isDone=value;}

void ToDoElement::setDescription(const std::string& description){ 
    if(!description.empty() && description != m_description)
        m_description=description;
}

bool ToDoElement::addSubElement(ToDoElement&& element){
    if(element.getDescription().empty())
        return false;
    if(!m_sublist)
        m_sublist = std::make_shared<ToDoList>();
    return m_sublist->addElement(std::move(element));
}

std::shared_ptr<ToDoList> ToDoElement::getSubElements() const{
    if(m_sublist)
        return m_sublist;
    return nullptr;
}

bool ToDoElement::hasSubList() const{
    return (m_sublist&& (!m_sublist->isEmpty()));
}

std::string ToDoElement::toString() const{
    return std::to_string(m_ID)+" [" +(m_isDone ? "X" : " ")+"] - "+m_description;
}

json ToDoElement::toJson() const{
    json j;
    j["ID"] = m_ID;
    j["isDone"] = m_isDone;
    j["description"] = m_description;

    if(m_sublist && !m_sublist->isEmpty())
        j["sublist"] = m_sublist->toJson();

    return j;
}

ToDoElement ToDoElement::fromJson(const json& j){
    ToDoElement element(j.value("ID",0), j.value("isDone", false), j.value("description","unknown"));
    if( j.contains("sublist") && j["sublist"].is_array()){
        element.m_sublist = std::make_shared<ToDoList>(ToDoList::fromJson(j["sublist"]));
    }
    return element;
}