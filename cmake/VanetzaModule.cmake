macro(vanetza_module NAME)
    set(_sources ${ARGN})
    set_property(GLOBAL APPEND PROPERTY VANETZA_MODULES ${NAME})
    add_library(${NAME} SHARED ${_sources})
    add_library(${NAME}_static STATIC ${_sources})
    set_property(TARGET ${NAME} PROPERTY OUTPUT_NAME vanetza_${NAME})
    set_property(TARGET ${NAME}_static PROPERTY OUTPUT_NAME vanetza_${NAME})
    set_property(TARGET ${NAME} ${NAME}_static PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR})
endmacro()

macro(vanetza_module_dependencies NAME)
    set(_deps ${ARGN})
    foreach(_dep ${_deps})
        target_link_libraries(${NAME} ${_dep})
        target_link_libraries(${NAME}_static ${_dep})
    endforeach()
endmacro()

macro(vanetza_intermodule_dependencies NAME)
    set(_modules ${ARGN})
    foreach(_module ${_modules})
        target_link_libraries(${NAME} ${_module})
        target_link_libraries(${NAME}_static ${_module}_static)
    endforeach()
endmacro()

macro(vanetza_module_property NAME)
    set_property(TARGET ${NAME} ${NAME}_static APPEND PROPERTY ${PROPERTY} ${ARGN})
endmacro()

macro(target_link_vanetza TARGET)
    set(_modules ${ARGN})
    foreach(_module ${_modules})
        target_link_libraries(${TARGET} ${_module}_static)
    endforeach()
endmacro()

macro(vanetza_export_modules)
    get_property(_modules GLOBAL PROPERTY VANETZA_MODULES)
    set(_targets "")
    foreach(_module ${_modules})
        list(APPEND _targets ${_module} ${_module}_static)
    endforeach()
    export(TARGETS ${_targets} NAMESPACE Vanetza:: FILE vanetza-targets.cmake)
endmacro()
