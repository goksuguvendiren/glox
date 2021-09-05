//
// Created by Göksu Güvendiren on 9/4/21.
//

#pragma once

#include <map>

namespace glox::stmt
{

class env_variable
{
public:
    env_variable(value_type type, const std::any& val) : type(type), value(val) {}

private:
    value_type type;
    std::any value;
};

class environnment
{
public:
    void add(const std::string& var_name, const std::any& value, value_type var_type)
    {
        variables.insert(std::make_pair<std::string, env_variable>(var_name.c_str(), env_variable{var_type, value}));
    }
private:
    std::map<std::string, env_variable> variables;
};
}