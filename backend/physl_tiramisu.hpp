//  Copyright (c) 2019-2020 Christopher Taylor
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#ifndef __PHYSL_TIRAMISU__
#define __PHYSL_TIRAMISU__

#include <string>
#include <vector>
#include <memory>
#include <sstream>

#include <tiramisu/tiramisu.h>

#include "physl_isl.hpp"

namespace physl { namespace tiramisu {

using namespace tiramisu;

class PhyslFunction : public ::tiramisu::function, ::tiramisu::generator {

    public:

    PhyslFunction() : function("physl_codegen"), generator() {
    }

    PhyslFunction(std::string & name) : function(name), generator() {
    }

    void lift_dist_computations() {
        lift_dist_comps();
    }

    void generate_code(std::vector< ::tiramisu::buffer* > & bufs, std::string &physlstr) {

        set_arguments(bufs);
        lift_dist_computations();
        gen_time_space_domain();
        gen_isl_ast();

        const auto comp = this->get_computation_by_name(this->get_name());

        if(comp.size() > 0) {
            for(const auto& c : comp) {
                auto e = c->get_expr();

                std::string str{};
                physl::codegen::generate_physl(
                    this->get_isl_ctx(),
                    this->get_isl_ast(),
                    e,
                    str,
                    physlstr
                );

                physlstr += str;
            }
        }
        else {

            std::string strout = 
            physl::codegen::generate_physl(
                this->get_isl_ctx(),
                this->get_isl_ast()
            );

            physlstr.assign(strout);
        }
    }
};

int codegen(std::vector< ::tiramisu::buffer > &arguments, std::string & physlstr);

} /* end namespace tiramisu */ } // end namespace physl

static inline std::string codegen_physl(std::vector< tiramisu::buffer > &arguments) {
    std::string output{};
    physl::tiramisu::codegen(arguments, output);
    return output;
}

#endif
