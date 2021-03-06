def legacy_shared_libs(name, freertos_config_headers, **kwargs):
    """
    Create a library containing all legacy shared libs

    name - The name for the library
    freertos_config_headers - Headers for the freertos config, must contain at least
                              `FreeRTOSConfig.h`
    """
    native.cc_library(
        name = name,
        srcs = [
            "//firmware/boards/shared/legacy_freertos:sources",
            "//firmware/boards/shared/legacy_stm32lib:sources",
            "//firmware/boards/shared/legacy_cdcacm:sources",
            "//firmware/boards/shared/legacy_usb:sources",
        ],
        hdrs = [
            "//firmware/boards/shared/legacy_freertos:headers",
            "//firmware/boards/shared/legacy_stm32lib:headers",
            "//firmware/boards/shared/legacy_cdcacm:headers",
            "//firmware/boards/shared/legacy_usb:headers",
            freertos_config_headers,
        ],
        copts = [
            # We don't want to mark warnings as errors for 3rd party code
            "-Wno-error",
            # We manually add include paths here, because if added in `includes`, it
            # appears that they are relative to the current directory, not absolute
            # paths from the project root (which is what we need).
            # This is in-line with the recommendations in the bazel documentation as of
            # 2020-03-18:
            # https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary.includes
            "-isystem firmware/boards/shared/legacy_freertos/include",
            "-isystem firmware/boards/shared/legacy_stm32lib/include",
            "-isystem firmware/boards/shared/legacy_cdcacm/include",
            "-isystem firmware/boards/shared/legacy_usb/include",
        ],
        defines = [
            "STM32LIB_USE_FREERTOS",
        ],
        restricted_to = ["//cc_toolchain:stm32f4"],
        # this is _very_ important. if we don't do this, bazel will not link in the
        # interrupt handling code, which *will not* cause an error, and *will* cause
        # interrupts to stop working
        alwayslink = True,
        **kwargs
    )
