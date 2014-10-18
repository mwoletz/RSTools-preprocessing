#include "realignment.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace realignment {
namespace task {
   
Realignment::Realignment(const char* code, const char* name) : RSTask(code, name)
{}

char* Realignment::getCmd() {
    
    rsArgument *input = this->getArgument("input");
    rsArgument *output = this->getArgument("output");
    rsArgument *stages = this->getArgument("stages");
    
    const char *fslPath = this->getJob()->getArgument("fslPath")->value;
    const char *stagesCmd = (stages == NULL)
                         ? "4"
                         : stages->value;
    
    return rsStringConcat(
        fslPath, "/mcflirt",
        " -in ", input->value, 
        " -out ", output->value,
        " -stages ", stagesCmd,
        " -mats",
        " -plots",
        " -meanvol",
        NULL
    );
}

}}}}} // namespace rstools::batch::plugins::realignment::task
