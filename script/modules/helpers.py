"""Manage configuration for board

This module provide function to help setup configuration 
for board during build process. List of avalible functions:

load_content_file() -- Return whole file content
read_template_variable_cmd() -- Read from command line input variable
concate_template_with_variables() -- Return content config came from conacted content template and variables
concate_template_with_variable() -- Return content config came from conacted content template and variable
save_file() -- Save content to file
modify_main_config_file() -- Modify main config file
validate_configuration() -- Check const value for specific name. 0 - configuration didn't set, 1 - configuration already set
"""
__all__ = [
    "load_content_file",
    "read_template_variable_cmd",
    "concate_template_with_variables",
    "concate_template_with_variable",
    "save_file",
    "modify_main_config_file",
    "validate_configuration"
]

import re


def load_content_file(path):
    """ Return whole file content

    Keywords arguments:
    path -- path to file
    """

    file_content = ""

    with open(path) as file:
        file_content = file.read()
    
    return file_content

def read_template_variable_cmd(message, default = ""):
    """ Read from command line input variable

    Keywords arguments:
    message -- Messange display for prompt in cmd
    default -- Default value if user set empty (default empty string default="")
    """

    value = input(message)

    if (value == ""):
        return default
    else:
        return value

def concate_template_with_variables(content, variables, pre = "<<!", post = ">>"):
    """ Return content config came from conacted content template and variables

    Keywords arguments:
    content -- content of template config
    variables -- list of variables: ((var_name,  var_value), (var2_name, var2_value))
    pre -- prefix default: <<!
    post -- postfix default >>
    """

    for variable in variables:
        content = concate_template_with_variable(content, variable, pre, post)

    return content

def concate_template_with_variable(content, variable, pre = "<<!", post = ">>"):
    """ Return content config came from conacted content template and variable

    Keywords arguments:
    content -- content of template config
    variables -- list of variable data: (var_name,  var_value)
    pre -- prefix default: <<!
    post -- postfix default >>
    """

    var_to_replace = pre + variable[0] + post
    content = content.replace(var_to_replace, variable[1])

    return content

def save_file(path, content):
    """ Save content to file

    Keywords arguments:
    path -- path to file
    content -- content of file
    """

    file = open(path, "w")
    file.write(content)
    file.close()

def modify_main_config_file(path, variable_name, file_name, const_name):
    """ Modify main config file

    Keywords arguments:
    path -- path to file
    variable_name -- name of variable to replace
    file_name -- config file name to include
    const_name -- const variable name
    """

    file_content = load_content_file(path)
    content_include = '#include "' + file_name + '"'
    file_content = concate_template_with_variable(file_content, (variable_name, content_include), '/*<<!', '>>*/')
    file_content = change_const_value(file_content, const_name, "true")

    save_file(path, file_content)

def change_const_value(content, const_name, value):
    """ Change value for specific const variable

    Keywords arguments:
    content -- content of config
    const_name -- name of const variable
    value -- value to set
    """

    reg = re.compile('#define ' + const_name + ' (true|false)', re.MULTILINE)

    content_to_return = reg.sub('#define ' + const_name + ' ' + value, content)
    
    return content_to_return

def validate_configuration(path, const_name):
    """ Check const value for specific name. 0 - configuration didn't set, 1 - configuration already set

    Keywords arguments:\r\n
    path -  path to main config file
    const_name -name of const variable check for value
    """

    file_content = load_content_file(path)
    regx = r'(#define ' + const_name + ' (true|false))'
    match = re.search(regx, file_content, re.MULTILINE)
    
    if match is not None:
        if match.group(2) == 'true':
            return 1

    return 0