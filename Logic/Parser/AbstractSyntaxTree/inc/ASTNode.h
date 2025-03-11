#pragma once

// evaluation of node
// should store value (can we use generic programming for this purpose???)/variadic?

template<typename T>
class ASTNode {
public:
    ASTNode(T value): m_val(value) {};
    virtual void Eval() = 0;
private:
    T m_val;
};