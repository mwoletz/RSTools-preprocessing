#include "distcorrection.hpp"
#include "utils/rsstring.h"
#include "batch/util/rsunix.hpp"

using namespace rstools::batch::util;

namespace rstools {
namespace batch {
namespace plugins {
namespace distcorrection {
namespace tool {
    
void Distcorrection::_parseParams(int argc, char * argv[])
{   
    this->executionSuccessful = true;
}
    
void Distcorrection::_init()
{
    rsArgument *input = this->getTask()->getArgument("input");
    rsArgument *output = this->getTask()->getArgument("output");
    rsArgument *vdm = this->getTask()->getArgument("vdm");    

    if ( input == NULL ) {
        fprintf(stderr, "An input needs to be specified!\n");
        this->executionSuccessful = false;
    }
    
    if ( output == NULL ) {
        fprintf(stderr, "An output needs to be specified!\n");
        this->executionSuccessful = false;
    }

    if ( vdm == NULL ) {
        fprintf(stderr, "A voxe-displacement map needs to be specified!\n");
        this->executionSuccessful = false;
    }
}

void Distcorrection::destroy()
{}

bool Distcorrection::isEverythingFine()
{
    return this->executionSuccessful;
}

rstools::batch::plugins::distcorrection::task::Distcorrection* Distcorrection::getDistcorrectionTask()
{
    return (rstools::batch::plugins::distcorrection::task::Distcorrection*)this->getTask();
}

void Distcorrection::_run()
{
    this->executionSuccessful = rsExecuteUnixCommand(this->getDistcorrectionTask()->getCmd());
}

rsUIInterface* Distcorrection::createUI()
{    
    rsUIOption *o;
    rsUIInterface* interface = rsUINewInterface();
    interface->description   = rsString("Distortion Correction (FSL's fugue)");
    
    o = rsUINewOption();
    o->name                = rsString("input");
    o->shorthand           = 'i';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("The path to the dataset which is to be unwarped.");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("output");
    o->shorthand           = 'o';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("The path of the resulting unwarped dataset.");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("vdm");
    o->shorthand           = 'v';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("The path to the voxel-displacement map. Please make sure it has the same orientation as the input image.");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    o = rsUINewOption();
    o->name                = rsString("mean");
    o->shorthand           = 'm';
    o->type                = G_OPTION_ARG_FILENAME;
    o->cli_description     = rsString("If supplied, the mean of the unwarped 4D volume is computed and saved at the given path.");
    o->cli_arg_description = rsString("<volume>");
    rsUIAddOption(interface, o);
    
    return interface;
}

void Distcorrection::printCallString(FILE *stream)
{
    int argc;
    char **argv = getCallString(&argc);

    fprintf(stream, "Tool:\n %s\n\nParams:\n", getTask()->getName());
    for ( int i=1; i<argc; i++ ) {
        fprintf(stream, "  %s\n", argv[i]);
    }
    
    fprintf(stream, "\n");
    
    fprintf(stream, "Cmd:\n%s\n", getDistcorrectionTask()->getCmd());
    fprintf(stream, "\n");
}

}}}}} // namespace rstools::batch::plugins::distcorrection::tool