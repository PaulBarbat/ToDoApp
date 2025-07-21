#pragma once
#include <vector>
#include <string>
#include <optional>
#include <memory>

class ToDoList{
public:
    class ToDoElement{
        private:
            size_t m_ID;
            bool m_isDone;
            std::string m_description;
            std::optional<std::shared_ptr<ToDoList>> m_sublist;
        public:
            ToDoElement() = delete;
            ToDoElement(bool isDone,const std::string& description);
            bool getIsDone() const;
            std::string getDescription() const;
            void setIsDone(bool value);
            void setDescription(const std::string& description);
            bool addSubElement(const ToDoElement& element);
            std::shared_ptr<ToDoList> getSubElements() const;
            bool hasSubList() const;
            const std::string& toString() const;
    };

    ToDoList();
    ToDoList(const std::string& path);
    std::shared_ptr<ToDoElement> getElement(size_t index);
    bool addElement(const ToDoElement& element);
    void printList(const std::string& offset) const;
    bool isEmpty() const;

    static inline size_t getID() {return s_ID++;}

private:
    static size_t s_ID;

    size_t m_ID;
    std::vector<std::shared_ptr<ToDoElement>> m_elements;
};
