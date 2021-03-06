#ifndef rstools_rsbatch_plugin_bfcorrection_task_bfcorrection_h
#define rstools_rsbatch_plugin_bfcorrection_task_bfcorrection_h

#include <iostream>
#include "batch/util/rsunixtask.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace bfcorrection {
namespace task {
    
class BFCorrection : public RSUnixTask {

public: 
    BFCorrection(const char* code, const char* name);
    
    char* getCmd(bool asExecuted);
};

}}}}} // namespace rstools::batch::plugins::bfcorrection::task

#endif
