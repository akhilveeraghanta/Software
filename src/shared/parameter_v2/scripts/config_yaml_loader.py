import os
import sys

import networkx
import yaml
from colorama import Fore, init
import jsonschema

<<<<<<< HEAD
=======
from typing import List

YamlPathList = List[str]

>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
from dynamic_parameter_schema import (
    INCLUDE_DEF_SCHEMA,
    PARAM_DEF_SCHEMA,
    SUPPORTED_TYPES,
<<<<<<< HEAD
=======
    INCLUDE_KEY,
    PARAMETER_KEY,
>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
)

#######################################################################
#                         Config Yaml Loader                          #
#######################################################################


class ConfigYamlLoader(object):
    @staticmethod
<<<<<<< HEAD
    def get_config_metadata(yaml_paths: list):
        """Loads the yamls in the root config directory and verifies that the
        requested configuration is valid. Then returns config_metadata dict
        with a specified format capturing all the requested params and configs.
=======
    def get_config_metadata(yaml_paths: YamlPathList) -> dict:
        """Loads the yamls in the YamlPathList (a list of absolute paths to yamls)
        and verifies that the requested configuration is valid. Then returns
        config_metadata dict with a specified format capturing all the requested
        params and configs.
>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6

        Example config directory:
        .
        └── config
            ├── ai
            │   ├── ai.yaml
            │   ├── passing
            │   │   └── passing.yaml
            │   └── plays
            │       ├── plays.yaml
            │       ├── defense.yaml
            │       └── offense.yaml
            ├── sensor_fusion
            │   └── sensor_fusion.yaml
            └── tbots_config.yaml

        A valid config directory maintains the following properties:

<<<<<<< HEAD
=======
        - All yaml file names are unique
>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
        - All yamls are properly formed (i.e proper syntax, YAML Version 1.2)
        - All parameter definitions abide by the dynamic parameter schema
        - All include statements do NOT cause cycles in configs

<<<<<<< HEAD
=======
        :raises ConfigYamlMalformed: when the yaml is malformed
        :raises ConfigSchemaViolation: When the shema is violated
        :raises ConfigYamlCycleDetected: When a cycle is detected in the incldues

>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
        :param yaml_paths: the path to all the config yamls
        :type yaml_paths: list of str

        :returns config_metadata: the config name followed by a list of
            included configs and a list of defined parameters.
        {
            "ai.yaml": {
                "includes": ["passing.yaml", "plays.yaml"],
                "parameters" :
                [{
                    "int": {
                        "name": "example_int", "value": 10, "min": 0, "max": 20
                    },
                    ...
                }]
            },

            "plays.yaml": {
                "includes": ["defense.yaml", "offense.yaml"],
                ...
            }
            ...
        }

        :rtype: dict

        """
        # load yaml into config_metadata
        config_metadata = ConfigYamlLoader.__load_yaml_into_dict(yaml_paths)

<<<<<<< HEAD
        # validate schema
=======
        # validate correct format with schema
>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
        ConfigYamlLoader.__validate_config_metadata(config_metadata)

        # detect cycles
        ConfigYamlLoader.__detect_cycles_in_config_metadata(config_metadata)

        # valid config ready to be generated
        return config_metadata

    @staticmethod
<<<<<<< HEAD
    def __load_yaml_into_dict(yaml_paths: list):
=======
    def __load_yaml_into_dict(yaml_paths: YamlPathList) -> dict:
>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
        """Loads the yamls into an dictionary. Any errors while in the yaml
        syntax will raise to the main thread. We also adjust how the dictionary
        is stored for easier access later.

<<<<<<< HEAD
        :raises: ConfigYamlMalformed
=======
        :raises ConfigYamlMalformed: when the yaml is malformed
>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
        :param yaml_paths: the path to all the config yamls
        :type yaml_paths: list of str
        :returns: config_medata dict representing the data to generate
        :rtype: dict

        """
        raw_config_metadata = {}

        for filename in yaml_paths:
            with open(filename, "r") as param_yaml:

                try:
                    # extract config name from filename
                    _, tail = os.path.split(filename)

                    # safe load yaml into dictionary
                    raw_config_metadata[tail] = list(yaml.safe_load_all(param_yaml))

                    if len(raw_config_metadata[tail]) == 1:

                        # include only in file
                        if isinstance(raw_config_metadata[tail][0], dict):
                            raw_config_metadata[tail] = {
<<<<<<< HEAD
                                "include": raw_config_metadata[tail][0]["include"]
=======
                                INCLUDE_KEY: raw_config_metadata[tail][0][INCLUDE_KEY]
>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
                            }

                        # parameter definitions only in file
                        if isinstance(raw_config_metadata[tail][0], list):
                            raw_config_metadata[tail] = {
<<<<<<< HEAD
                                "parameters": raw_config_metadata[tail][0]
=======
                                PARAMETER_KEY: raw_config_metadata[tail][0]
>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
                            }

                    elif len(raw_config_metadata[tail]) == 2:

                        # include and param definition in file
                        raw_config_metadata[tail] = {
<<<<<<< HEAD
                            "include": raw_config_metadata[tail][0]["include"],
                            "parameters": raw_config_metadata[tail][1],
                        }

=======
                            INCLUDE_KEY: raw_config_metadata[tail][0][INCLUDE_KEY],
                            PARAMETER_KEY: raw_config_metadata[tail][1],
                        }

                    else:
                        raise ConfigYamlMalformed(
                            "More than two yaml documents in {}".format(tail)
                        )

>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
                except yaml.YAMLError as ymle:
                    raise ConfigYamlMalformed(
                        "Check malformed {} \n {}".format(tail, ymle)
                    ) from None

        return raw_config_metadata

    @staticmethod
    def __validate_config_metadata(config_metadata: dict):
        """Validates the config_metadata that was loaded against the
        dynamic_parameter_schemas and then checks for duplicate includes
        and duplicate parameters in the same config.

<<<<<<< HEAD
        :raises: ConfigYamlMalformed
        :raises: ConfigSchemaViolation
=======
        :raises ConfigYamlMalformed: When the yaml is malformed
        :raises ConfigSchemaViolation: When the shema is violated
>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
        :param config_metadata: Metadata describing params and config includes
        :type config_metadata: dict

        """

        for config_file, metadata in config_metadata.items():

<<<<<<< HEAD
            if "include" in metadata:

                # check schema
                try:
                    jsonschema.validate(metadata["include"], INCLUDE_DEF_SCHEMA)
=======
            if INCLUDE_KEY in metadata:

                # validate correct format with schema
                try:
                    jsonschema.validate(metadata[INCLUDE_KEY], INCLUDE_DEF_SCHEMA)
>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
                except jsonschema.exceptions.ValidationError as jsval:
                    raise ConfigYamlSchemaViolation(
                        "Schema violation in {}: {}".format(config_file, jsval)
                    ) from None

                # check duplicates
<<<<<<< HEAD
                if len(metadata["include"]) > len(set(metadata["include"])):
=======
                if len(metadata[INCLUDE_KEY]) > len(set(metadata[INCLUDE_KEY])):
>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
                    raise ConfigYamlMalformed(
                        "Duplicate include detected in {}".format(config_file)
                    )

                # check that included yaml is defined elsewhere
<<<<<<< HEAD
                for included_yaml in metadata["include"]:
=======
                for included_yaml in metadata[INCLUDE_KEY]:
>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
                    if included_yaml not in config_metadata.keys():
                        raise ConfigYamlMalformed(
                            "definition could not be found for {} in {}".format(
                                included_yaml, config_file
                            )
                        )

<<<<<<< HEAD
            if "parameters" in metadata:

                # check schema
                try:
                    jsonschema.validate(metadata["parameters"], PARAM_DEF_SCHEMA)
=======
            if PARAMETER_KEY in metadata:

                # validate correct format with schema
                try:
                    jsonschema.validate(metadata[PARAMETER_KEY], PARAM_DEF_SCHEMA)
>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
                except jsonschema.exceptions.ValidationError as jsval:
                    raise ConfigYamlSchemaViolation(
                        "Schema violation in {}: {}".format(config_file, jsval)
                    ) from None

                # Get all parameter names as a list, the parameter type comes
                # first and the name follows in the dictionary. If the schema
                # check above succeeded, its safe to assume the "name" key
                # exists in the parameter dictionary
                param_names = [
                    list(param_entry.values())[0]["name"]
<<<<<<< HEAD
                    for param_entry in metadata["parameters"]
=======
                    for param_entry in metadata[PARAMETER_KEY]
>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
                ]

                # check duplicates
                if len(param_names) > len(set(param_names)):
                    raise ConfigYamlMalformed(
                        "Duplicate parameter detected in {}".format(config_file)
                    )

                # This is an ugly artifact of how the yaml is defined and loaded
                # We are extracting all the requested types to check that
                # they are all supported. This is the one thing the schema
                # can't validate that we would like to check
                requested_types = [
                    key[0]
<<<<<<< HEAD
                    for key in [list(entry.keys()) for entry in metadata["parameters"]]
=======
                    for key in [list(entry.keys()) for entry in metadata[PARAMETER_KEY]]
>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
                ]

                # check if type requested is supported
                for requested_type in requested_types:
                    if requested_type not in SUPPORTED_TYPES:
                        raise ConfigYamlMalformed(
                            "{} type unsupported in {}".format(
                                requested_type, config_file
                            )
                        )

    @staticmethod
    def __detect_cycles_in_config_metadata(config_metadata: dict):
        """Creates a DiGraph from all the included configs and checks if there
        are cycles. Raises to the main thread if a cycle is detected

<<<<<<< HEAD
        :raises: ConfigYamlCycleDetected
=======
        :raises ConfigYamlCycleDetected: When a cycle is detected in the incldues
>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
        :param config_metadata: Metadata describing params and config includes
        :type config_metadata: dict

        """
        edges = []

        for config, metadata in config_metadata.items():
<<<<<<< HEAD
            if "include" in metadata:
                for included_config in metadata["include"]:
=======
            if INCLUDE_KEY in metadata:
                for included_config in metadata[INCLUDE_KEY]:
>>>>>>> 5d2c96b782680af6fd4f43f057cdf1be939b46e6
                    edges.append((config, included_config))

        G = networkx.DiGraph(edges)

        for cycle in networkx.simple_cycles(G):
            raise ConfigYamlCycleDetected(
                "Cycle detected in the include statements: "
                + " -> ".join(cycle + [cycle[0]])
            )


#######################################################################
#                             Exceptions                              #
#######################################################################


class ConfigYamlException(Exception):
    """We use custom exceptions to facilitate terminating the genrule
    using the ConfigYamlLoader class and to print the log in red and yellow,
    making it more visible in the build log clutter.

    :param message: The exception msg to print in red
    :type message: str

    """

    def __init__(self, message):
        init()  # init Fore
        super().__init__(
            Fore.LIGHTRED_EX
            + "Parameter generation error: "
            + Fore.YELLOW
            + message
            + Fore.RESET
        )


class ConfigYamlCycleDetected(ConfigYamlException):
    """Indicates when there is a cycle in the included configs
    """


class ConfigYamlMalformed(ConfigYamlException):
    """Indicates when the yaml has a typo or doesn't follow proper syntax
    """


class ConfigYamlSchemaViolation(ConfigYamlException):
    """Indicates when the yaml schema has been violated
    """
