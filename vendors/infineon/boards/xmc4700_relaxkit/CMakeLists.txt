# Set variables.
set(xmc4700_dir "${AFR_VENDORS_DIR}/infineon/boards/xmc4700_relaxkit")
set(xmc4700_ports_dir "${xmc4700_dir}/ports")
set(xmclib_dir "${AFR_VENDORS_DIR}/infineon/XMCLib/2.2.0")
set(trustx_dir "${AFR_VENDORS_DIR}/infineon/secure_elements/optiga_trust_x")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(AFR_IS_TESTING)
    set(xmc4700_aws_dir "${xmc4700_dir}/aws_tests")
else()
    set(xmc4700_aws_dir "${xmc4700_dir}/aws_demos")
endif()

#Tool chain specific check
if(NOT ${AFR_TOOLCHAIN} STREQUAL "arm-gcc")
   if(NOT AFR_METADATA_MODE)
       message( FATAL_ERROR "The toolchain is not supported." )
   endif()
endif()

# -------------------------------------------------------------------------------------------------
# Amazon FreeRTOS Console metadata
# -------------------------------------------------------------------------------------------------

afr_set_board_metadata(ID "Infineon-XMC4700-Relax-Kit")
afr_set_board_metadata(DISPLAY_NAME "XMC4700 Relax Kit")
afr_set_board_metadata(DESCRIPTION "Development kit for ARM Cortex-M4 based XMC4700 MCU")
afr_set_board_metadata(VENDOR_NAME "Infineon")
afr_set_board_metadata(FAMILY_NAME "XMC4x00")
afr_set_board_metadata(CODE_SIGNER "null")
afr_set_board_metadata(DATA_RAM_MEMORY "352KB")
afr_set_board_metadata(PROGRAM_MEMORY "2MB")
afr_set_board_metadata(SUPPORTED_IDE "DAVE")
afr_set_board_metadata(RECOMMENDED_IDE "DAVE")
afr_set_board_metadata(IDE_DAVE_NAME "DAVE")
afr_set_board_metadata(IDE_DAVE_COMPILER "GCC")
afr_set_board_metadata(KEY_IMPORT_PROVISIONING "FALSE")
afr_set_board_metadata(IS_ACTIVE "TRUE")
afr_set_board_metadata(IDE_DAVE_PROJECT_LOCATION "${AFR_ROOT_DIR}/projects/infineon/xmc4700_relaxkit/dave4/aws_demos")
afr_set_board_metadata(AWS_DEMOS_CONFIG_FILES_LOCATION "${AFR_ROOT_DIR}/vendors/infineon/boards/xmc4700_relaxkit/aws_demos/config_files")

# -------------------------------------------------------------------------------------------------
# Compiler settings
# -------------------------------------------------------------------------------------------------
afr_mcu_port(compiler)


#Set defined symbols for compiler and assembler
set( defined_symbols
     XMC4700_F144x2048
     XMC_ETH_PHY_KSZ8081RNB
     USE_CMDLIB_WITH_RTOS
     MBEDTLS_ECDSA_SIGN_ALT
     MBEDTLS_ECDSA_VERIFY_ALT
     MBEDTLS_ECDH_COMPUTE_SHARED_ALT
     MBEDTLS_ECDH_GEN_PUBLIC_ALT
     PAL_OS_HAS_EVENT_INIT
)

# Compiler defined symbols.
target_compile_definitions(
    AFR::compiler::mcu_port
    INTERFACE
    ${defined_symbols}
)

#Set Compiler Debug options
set( compiler_debug_options "-g" "-gdwarf-2")

#Set compiler warnings level
set( compiler_warnings "-Wall" )

#Set compiler optimization level
set( compiler_optimization_options "-Os" "-fomit-frame-pointer" "-ffunction-sections" "-fdata-sections" "-ffreestanding" "-fno-builtin" "-fno-common")

#Set ARM GCC options
set( compiler_arm_options "-mfloat-abi=hard" "-mcpu=cortex-m4" "-mfpu=fpv4-sp-d16" "-mthumb")

#Set other compiler options and flags
set( compiler_misc_options
     "-std=c99"
     "-c"
     "-fmessage-length=0"
)

#All compiler options
set( compiler_flags
     ${compiler_debug_options}
     ${compiler_warnings}
     ${compiler_optimization_options}
     ${compiler_arm_options}
     ${compiler_misc_options}
     "-pipe" )
target_compile_options(
    AFR::compiler::mcu_port
    INTERFACE
        $<$<COMPILE_LANGUAGE:C>:${compiler_flags}>
)


#All assembler options
set( assembler_flags
     "-x"
     "assembler-with-cpp"
     ${compiler_debug_options}
     ${compiler_warnings}
     ${compiler_optimization_options}
     ${compiler_arm_options}
     ${compiler_misc_options}
)
target_compile_options(
    AFR::compiler::mcu_port
    INTERFACE
        $<$<COMPILE_LANGUAGE:ASM>:${assembler_flags}>
)


#Linker script path
set( linker_script "${xmc4700_dir}/XMC4700x2048.ld" )

#All linker options
set( linker_flags
     "-T" ${linker_script}
     "-nostartfiles"
     "-Xlinker"
     "--gc-sections"
     "-specs=nano.specs"
     "-specs=nosys.specs"
     "-Wl,-Map,aws_demos.map"
     ${compiler_arm_options}
     ${compiler_debug_options}
)

target_link_options(
    AFR::compiler::mcu_port
    INTERFACE
        ${linker_flags}
)

#Linker libraries
set(linker_libs
    "m"
)
target_link_libraries(
    AFR::compiler::mcu_port
    INTERFACE
        ${linker_libs}
)

# -------------------------------------------------------------------------------------------------
# Kernel and Amazon FreeRTOS portable layers
# -------------------------------------------------------------------------------------------------

# Kernel
afr_mcu_port(kernel)

#Driver source files
afr_glob_src(driver_src DIRECTORY "${xmclib_dir}/drivers/src")
afr_glob_src(cmsis_driver_src DIRECTORY "${xmclib_dir}/CMSIS/Driver/Source")

#Trust X source files
afr_glob_src(trustx_src DIRECTORY "${trustx_dir}/optiga" RECURSE)
afr_glob_src(trustx_utils_src DIRECTORY "${trustx_dir}/examples" RECURSE)
afr_glob_src(trustx_pal_src DIRECTORY "${trustx_dir}/pal/xmc_freertos" RECURSE)

#Source files specific to compiler
set(compiler_src
    "${AFR_KERNEL_DIR}/portable/GCC/ARM_CM4F/port.c"
    "${AFR_KERNEL_DIR}/portable/GCC/ARM_CM4F/portmacro.h"
    "${xmclib_dir}/CMSIS/Infineon/XMC4700_series/Source/system_XMC4700.c"
    "${xmclib_dir}/CMSIS/Infineon/XMC4700_series/Source/GCC/startup_XMC4700.S"
)

target_sources(
    AFR::kernel::mcu_port
    INTERFACE
       "${AFR_KERNEL_DIR}/portable/MemMang/heap_4.c"
        ${compiler_src}
        ${driver_src}
        ${cmsis_driver_src}
	${trustx_src}
	${trustx_utils_src}
	${trustx_pal_src}
)

#Include directories specific to compiler
set(compiler_includes
    "${AFR_KERNEL_DIR}/portable/GCC/ARM_CM4F"
)
set( board_includes
     "${xmclib_dir}/CMSIS/Include"
     "${xmclib_dir}/drivers/inc"
     "${xmclib_dir}/CMSIS/Infineon/XMC4700_series/Include"
     "${xmclib_dir}/CMSIS/Driver/Include"
     "${xmc4700_aws_dir}/application_code/infineon_code"
     "${trustx_dir}/examples/ecdsa_utils"
     "${trustx_dir}/examples/authenticate_chip"
     "${trustx_dir}/optiga/include"
     "${trustx_dir}/pal/xmc_freertos"
     "${AFR_VENDORS_DIR}/infineon/secure_elements/pkcs11"
)
set(kernel_includes
    ${board_includes}
    ${compiler_includes}
    "${AFR_KERNEL_DIR}/include"
    "$<IF:${AFR_IS_TESTING},${AFR_TESTS_DIR},${AFR_DEMOS_DIR}>/include"
    "${AFR_3RDPARTY_DIR}/mbedtls/include"
    "${xmc4700_aws_dir}/config_files"
)

target_include_directories(
    AFR::kernel::mcu_port
    INTERFACE $<$<NOT:$<COMPILE_LANGUAGE:ASM>>:${kernel_includes}>
)

#Posix
afr_mcu_port(posix)

target_sources(
    AFR::posix::mcu_port
    INTERFACE "${xmc4700_ports_dir}/posix/FreeRTOS_POSIX_portable.h"
)

target_include_directories(
    AFR::posix::mcu_port
    INTERFACE "${xmc4700_ports_dir}/posix"
)

target_link_libraries(
    AFR::posix::mcu_port
    INTERFACE AFR::freertos_plus_posix
)

# PKCS11
afr_mcu_port(pkcs11_implementation)
target_sources(
    AFR::pkcs11_implementation::mcu_port
    INTERFACE
        "${AFR_VENDORS_DIR}/infineon/secure_elements/pkcs11/iot_pkcs11_trustx.c"
)

# FreeRTOS Plus TCP
afr_mcu_port(freertos_plus_tcp)
target_sources(
    AFR::freertos_plus_tcp::mcu_port
    INTERFACE
        "${AFR_MODULES_FREERTOS_PLUS_DIR}/standard/freertos_plus_tcp/source/portable/BufferManagement/BufferAllocation_1.c"
        "${AFR_MODULES_FREERTOS_PLUS_DIR}/standard/freertos_plus_tcp/source/portable/NetworkInterface/XMC4/NetworkInterface.c"
)
target_include_directories(
    AFR::freertos_plus_tcp::mcu_port
    INTERFACE
        "${AFR_MODULES_FREERTOS_PLUS_DIR}/standard/freertos_plus_tcp/source/portable/Compiler/GCC"
)

# Secure sockets
afr_mcu_port(secure_sockets)
target_link_libraries(
    AFR::secure_sockets::mcu_port
    INTERFACE AFR::secure_sockets_freertos_plus_tcp
)

# -------------------------------------------------------------------------------------------------
# Amazon FreeRTOS demos and tests
# -------------------------------------------------------------------------------------------------
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

if(AFR_IS_TESTING)
    set(exe_target aws_tests)
else()
    set(exe_target aws_demos)
endif()


afr_glob_src(board_src DIRECTORY "${xmc4700_aws_dir}/application_code/infineon_code")
afr_glob_src(newlib DIRECTORY "${xmclib_dir}/Newlib")
afr_glob_src(config_src DIRECTORY "${xmc4700_aws_dir}/config_files")

# Do not add demos or tests if they're turned off.
if(AFR_ENABLE_DEMOS OR AFR_ENABLE_TESTS)
    add_executable(
        ${exe_target}
        ${board_src}
        ${config_src}
        ${newlib}
        ${linker_script}
        "${xmc4700_aws_dir}/application_code/main.c"
    )

    target_link_libraries(
        ${exe_target}
        PRIVATE
            AFR::freertos_plus_tcp
            AFR::dev_mode_key_provisioning
            AFR::utils
    )

    if(AFR_METADATA_MODE)
        return()
    endif()

    find_program(gcc_objectcopy arm-none-eabi-objcopy)
    find_program(gcc_size arm-none-eabi-size)

    if(NOT gcc_objectcopy )
        message(FATAL_ERROR "Cannot find arm-none-eabi-objcopy.")
    endif()

    set(output_file "$<TARGET_FILE_DIR:${exe_target}>/${exe_target}.hex")

    add_custom_command(
        TARGET ${exe_target} POST_BUILD
        COMMAND "${gcc_objectcopy}" -O ihex "$<TARGET_FILE:${exe_target}>" "${output_file}"
        COMMAND "${gcc_size}" "$<TARGET_FILE:${exe_target}>"
    )

    add_custom_command(
        TARGET ${exe_target} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy "${output_file}" "${CMAKE_BINARY_DIR}"
    )
endif()
