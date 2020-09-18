#######################################################################
#                              Constants                              #
#######################################################################

# the weird espace charecters at the front change the color to red when
# printed in a terminal, the espace charecter at the end clears and resets
# back to the original color. More info can be found here:
# https://stackoverflow.com/questions/287871/print-in-terminal-with-colors
AUTOGEN_FAILURE_MSG = """\033[91m====================================================\033[0m
\033[91m                CFG AUTOGEN FAILURE
\u001b[34;1m Reason: {}
\033[91m====================================================\033[0m"""

# the working directory is set to the current folder in CMakeLists
PATH_TO_YAML = "./software/parameter/config/"
PATH_TO_AUTOGEN_CFG = "./software/parameter/autogenerated/cfg/"
PATH_TO_AUTOGEN_CPP = "./software/parameter/"
PATH_TO_AUTOGEN_NODE = "./software/dynamic_reconfigure_manager/"
DYNAMIC_PARMETERS_HEADER = "dynamic_parameters.h"
DYNAMIC_PARMETERS_CPP = "dynamic_parameters.cpp"

#######################################################################
#                              Parameter                              #
#######################################################################

PARAMETER_PUBLIC_ENTRY = """const std::shared_ptr<const Parameter<{type}>> {immutable_accessor_name} () const
           {{
               return std::const_pointer_cast<const Parameter<{type}>>({param_variable_name});
           }}

           const std::shared_ptr<Parameter<{type}>> {mutable_accessor_name} ()
           {{
               return {param_variable_name};
           }}
        """

PARAMETER_PRIVATE_ENTRY = "std::shared_ptr<Parameter<{type}>> {param_variable_name};"

PARAMETER_CONSTRUCTOR_ENTRY = """{param_variable_name} = std::make_shared<Parameter<{type}>>(\"{param_name}\", {quote}{value}{quote});"""

IMMUTABLE_PARAMETER_LIST_PARAMETER_ENTRY = (
    "std::const_pointer_cast<const Parameter<{type}>>({param_variable_name})"
)

PARAMETER_COMMAND_LINE_BOOL_SWITCH_ENTRY = 'desc.add_options()("{param_name}", boost::program_options::bool_switch(&args.{param_name}), "{param_desc}");\n'

PARAMETER_COMMAND_LINE_ENTRY = 'desc.add_options()("{param_name}", boost::program_options::value<{param_type}>(&args.{param_name}), "{param_desc}");\n'

COMMAND_LINE_ARG_ENTRY = "{param_type} {param_name} = {quote}{default_value}{quote};\n"

LOAD_COMMAND_LINE_ARG_INTO_CONFIG = (
    "this->mutable{param_name}()->setValue(args.{param_name});\n"
)


#######################################################################
#                               Config                                #
#######################################################################

CONFIG_PUBLIC_ENTRY = """const std::shared_ptr<const {config_name}> {immutable_accessor_name} () const
           {{
               return std::const_pointer_cast<const {config_name}>({config_variable_name});
           }}

           const std::shared_ptr<{config_name}> {mutable_accessor_name} ()
           {{
               return {config_variable_name};
           }}
        """

CONFIG_CONSTRUCTOR_ENTRY = (
    "{config_variable_name} = std::make_shared<{config_name}>();\n"
)

CONFIG_PRIVATE_ENTRY = "std::shared_ptr<{config_name}> {config_variable_name};"

IMMUTABLE_PARAMETER_LIST_CONFIG_ENTRY = (
    "std::const_pointer_cast<const {config_name}>({config_variable_name})"
)

CONFIG_CLASS = """class {config_name} : public Config
{{
   public:
    {config_name}()
    {{
        {constructor_entries}
        mutable_internal_param_list = {{{mutable_parameter_list_entries}}};
        immutable_internal_param_list = {{{immutable_parameter_list_entries}}};
    }}
    {public_entries}

    const std::string name() const
    {{
        return "{config_name}";
    }}

    void loadFromCommandLineArguments(int argc, char **argv) {{

        struct commandLineArgs {{
            bool help = false;
            {command_line_arg_struct_contents}
        }};

        commandLineArgs args;
        boost::program_options::options_description desc{{"Options"}};

        desc.add_options()("help,h", boost::program_options::bool_switch(&args.help),
                       "Help screen");

        {parse_command_line_args_function_contents}

        boost::program_options::variables_map vm;
        boost::program_options::store(parse_command_line(argc, argv, desc), vm);
        boost::program_options::notify(vm);

        {load_command_line_args_into_config_contents}

        if (args.help)
        {{
            std::cout << desc << std::endl;
        }}

    }}

    const MutableParameterList& getMutableParameterList()
    {{
        return mutable_internal_param_list;
    }}

    const ParameterList& getParameterList() const
    {{
        return immutable_internal_param_list;
    }}

   private:
        MutableParameterList mutable_internal_param_list;
        ParameterList immutable_internal_param_list;
        {private_entries}
}};
"""

AUTOGEN_WARNING = """
/**
 *  !! WARNING !!
 *
 *  THIS FILE IS AUTOGENERATED, ANY CHANGES MADE WILL BE LOST
 *
 *  !! WARNING !!
 */
"""

H_HEADER = """{}
#pragma once
#include <iostream>
#include <boost/program_options.hpp>
#include \"software/parameter/config.h\"
""".format(
    AUTOGEN_WARNING
)
