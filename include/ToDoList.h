#pragma once
#include <vector>
#include <string>
#include <optional>

class ToDoList{
public:
    class ToDoElement{
        private:
            bool m_isDone;
            std::string m_Description;
            [[maybe_unused]] std::optional<ToDoList> m_sublist;
        public:
            ToDoElement() = delete;
            ToDoElement(bool isDone,const std::string& description);
            bool getIsDone() const;
            std::string getDescription() const;
            void setIsDone(bool value);
            void setDescription(const std::string& description);
            bool addSubElement(const ToDoElement& element);
            ToDoList getSubElements() const;
    };
    
    ToDoList(const std::string& path);
    ToDoElement getElement(int index);
    bool addElement(const ToDoElement& element);
    void printList();

private:
    std::vector<ToDoElement> m_elements;
};