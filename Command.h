#pragma once
class Command{
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};