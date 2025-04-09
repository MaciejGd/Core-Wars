#pragma once


class IOperatorTest {
public:
    virtual void RunTests() = 0;

protected:
    int modified_cell = -1;
};