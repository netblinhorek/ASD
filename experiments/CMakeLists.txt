create_executable_project(TableExperiments)
set_target_properties(TableExperiments PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

if(MSVC)
    # /std:c++17 применяется всегда
    target_compile_options(TableExperiments PRIVATE /std:c++17)
    
    # Оптимизации /O2 /Oi /Ot применяются ТОЛЬКО для конфигураций Release и RelWithDebInfo
    # В режиме Debug они игнорируются, и конфликт с /RTC1 исчезает
    target_compile_options(TableExperiments PRIVATE 
        $<$<CONFIG:Release,RelWithDebInfo>:/O2 /Oi /Ot>
    )
else()
    target_compile_options(TableExperiments PRIVATE -std=c++17)
    # Для GCC / Clang включаем -O3 только в Release
    target_compile_options(TableExperiments PRIVATE 
        $<$<CONFIG:Release,RelWithDebInfo>:-O3>
    )
endif()