//
// Created by Göksu Güvendiren on 8/19/21.
//

#pragma once

#include <string>

namespace glox
{
class code_generator
{
public:
    struct type_definition
    {
        std::string type_name;
        std::vector<std::string> parameters;
    };

    static void generate_ast(const std::string& output_folder,
                             std::vector<type_definition>& expressions);

};
}