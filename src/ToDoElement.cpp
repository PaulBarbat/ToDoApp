#include "ToDoElement.h"

size_t ToDoElement::s_ID = 1;
std::unordered_map<uint16_t, std::weak_ptr<ToDoElement>> ToDoElement::s_Element_Map;

ToDoElement::ToDoElement(bool isDone,const std::string& description): m_ID(ToDoList::getID()), m_isDone(isDone), m_description(description){}

ToDoElement::ToDoElement(size_t id, bool isDone,const std::string& description): m_ID(id), m_isDone(isDone), m_description(description){
     if(ToDoList::s_ID <= id) ToDoList::s_ID = id+1; 
}//to make sure we update the static ID to be the next id possible

bool ToDoElement::getIsDone() const{ return m_isDone;}

const std::string& ToDoElement::getDescription() const{ return m_description;}

void ToDoElement::switchIsDone(){ m_isDone=!m_isDone;}

void ToDoElement::setDescription(const std::string& description){ 
    if(!description.empty() && description != m_description)
        m_description=description;
}

bool ToDoElement::addSubElement(ToDoElement&& element){
    if(element.getDescription().empty())
        return false;
    std::shared_ptr<ToDoElement> sharedElement = std::make_shared<ToDoElement>(std::move(element));
    m_sublist.emplace_back(sharedElement);
    
    ToDoElement::s_Element_Map[sharedElement->getID()] = sharedElement;

    return true;
}

const std::vector<std::shared_ptr<ToDoElement>>& ToDoElement::getSubElements() const{
    if(!m_sublist.empty())
        return m_sublist;
    return nullptr;
}

bool ToDoElement::hasSubList() const{
    return (m_sublist&& (!m_sublist.empty()));
}

void ToDoElement::printElement(size_t offset) const{
    std::cout<<std::string(offset, '-')<<std::to_string(m_ID)+" [" +(m_isDone ? "X" : " ")+"] - "+m_description;
    if(!m_sublist.empty())
        for(const auto& element : m_sublist)
        {
            element->printElement(offset+4);
        }
}

json ToDoElement::toJson() const{
    json j;
    j["ID"] = m_ID;
    j["isDone"] = m_isDone;
    j["description"] = m_description;

    if(m_sublist && !m_sublist.empty()){
        j["sublist"] = json::array();
        for(const auto& element : m_sublist) 
            j["sublist"].push_back(element->toJson());
    }

    return j;
}

ToDoElement ToDoElement::fromJson(const json& j){
    ToDoElement element(j.value("ID",0), j.value("isDone", false), j.value("description","unknown"));
    if( j.contains("sublist") && j["sublist"].is_array()){
        for(const auto& item : j["sublist"])
            element.addSubElement(std::move(ToDoElement::fromJson(item)));
    }
    return element;
}