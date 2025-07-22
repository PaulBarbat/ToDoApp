#pragma once
#include <vector>
#include <string>
#include <optional>
#include <memory>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ToDoList{
public:
    class ToDoElement{
        private:
            size_t m_ID;
            bool m_isDone;
            std::string m_description;
            std::shared_ptr<ToDoList> m_sublist;
        public:
            ToDoElement() = delete;
            ToDoElement(bool isDone,const std::string& description);
            ToDoElement(size_t id, bool isDone,const std::string& description);
            bool getIsDone() const;
            const std::string& getDescription() const;
            void setIsDone(bool value);
            void setDescription(const std::string& description);
            bool addSubElement(ToDoElement&& element);
            std::shared_ptr<ToDoList> getSubElements() const;
            bool hasSubList() const;
            std::string toString() const;//no const ref return because the string is temporary

            json toJson() const;
            static ToDoElement fromJson(const json& j);
    };

    ToDoList();
    ToDoList(const std::string& path);
    std::shared_ptr<ToDoElement> getElement(size_t index);
    bool addElement(ToDoElement&& element);
    void printList(const std::string& offset) const;
    bool isEmpty() const;

    json toJson() const;
    static ToDoList fromJson(const json& j);

    static inline size_t getID() {return s_ID++;}

private:
    static size_t s_ID;

    size_t m_ID;
    std::vector<std::shared_ptr<ToDoElement>> m_elements;
};
