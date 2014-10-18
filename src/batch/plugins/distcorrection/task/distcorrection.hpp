#ifndef rstools_rsbatch_plugin_distcorrection_task_distcorrection_h
#define rstools_rsbatch_plugin_distcorrection_task_distcorrection_h

#include <iostream>
#include "batch/util/rstask.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace distcorrection {
namespace task {
    
class Distcorrection : public RSTask {

public: 
    Distcorrection(const char* code, const char* name);
    
    char* getCmd();
};

}}}}} // namespace rstools::batch::plugins::distcorrection::task

#endif