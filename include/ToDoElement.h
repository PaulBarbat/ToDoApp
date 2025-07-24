#pragma once
#include <vector>
#include <string>
#include <optional>
#include <memory>
#include <unordered_map>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ToDoElement{
private:
    size_t m_ID;
    bool m_isDone;
    std::string m_description;
    std::vector<std::shared_ptr<ToDoElement>> m_sublist;

    static std::unordered_map<size_t, std::weak_ptr<ToDoElement>> s_Element_Map;
    static size_t s_ID;
public:
    ToDoElement() = delete;
    ToDoElement(bool isDone,const std::string& description);
    ToDoElement(size_t id, bool isDone,const std::string& description);
    bool getIsDone() const;
    const std::string& getDescription() const;
    const std::vector<std::shared_ptr<ToDoElement>>& getSubElements() const;
    void switchIsDone();
    void setDescription(const std::string& description);
    bool addSubElement(ToDoElement&& element);
    bool hasSubList() const;
    void printElement(size_t offset) const;//no const ref return because the string is temporary

    json toJson() const;
    static ToDoElement fromJson(const json& j);
    static inline size_t getID() {return s_ID++;}
};