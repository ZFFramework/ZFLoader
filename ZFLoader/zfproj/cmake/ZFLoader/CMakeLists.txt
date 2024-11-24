cmake_minimum_required(VERSION 3.4.1)
project(ZFLoader)
set(ZF_ROOT_PATH "${PROJECT_SOURCE_DIR}/../../../../../ZFFramework")
include("${ZF_ROOT_PATH}/tools/spec/cmake/util.cmake")
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

include("${PROJECT_SOURCE_DIR}/zfprojConfig.cmake" OPTIONAL)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/../../../../_tmp/cmake/ZFLoader/app")

execute_process(COMMAND sh "${ZF_ROOT_PATH}/tools/release/release_cmake.sh" 1)

file(GLOB_RECURSE ZF_SRC_FILES RELATIVE "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/../../../zfsrc/*.c"
    "${PROJECT_SOURCE_DIR}/../../../zfsrc/*.cpp"
    "${PROJECT_SOURCE_DIR}/../../../zfsrc_ext/*.c"
    "${PROJECT_SOURCE_DIR}/../../../zfsrc_ext/*.cpp"
    )
if(COMMAND zfprojConfigBefore_ZFLoader)
    zfprojConfigBefore_ZFLoader(ZFLoader ZF_SRC_FILES)
endif()
add_executable(ZFLoader ${ZF_SRC_FILES})
zfprojStripFILE(ZFLoader)
set_target_properties(ZFLoader PROPERTIES LINKER_LANGUAGE CXX)
if(COMMAND zfprojConfigAfter_ZFLoader)
    zfprojConfigAfter_ZFLoader(ZFLoader)
endif()

target_include_directories(ZFLoader PRIVATE "${PROJECT_SOURCE_DIR}/../../../zfsrc")

function(ZFAddLib ZF_LIB_NAME_)
    target_include_directories(ZFLoader PRIVATE "${ZF_ROOT_PATH}/_release/cmake/all/include")

    target_link_directories(ZFLoader PUBLIC "${ZF_ROOT_PATH}/_release/cmake/module/${ZF_LIB_NAME_}/lib/")
    target_link_libraries(ZFLoader PUBLIC ${ZF_LIB_NAME_})

    if(WIN32)
        execute_process(COMMAND "${ZF_ROOT_PATH}\\tools\\common\\copy_check.bat" "${ZF_ROOT_PATH}\\_release\\cmake\\module\\${ZF_LIB_NAME_}\\lib\\" "${CMAKE_INSTALL_PREFIX}\\.")
        execute_process(COMMAND "${ZF_ROOT_PATH}\\tools\\util\\copy_res.bat" "${ZF_ROOT_PATH}\\_release\\cmake\\module\\${ZF_LIB_NAME_}\\zfres\\" "${PROJECT_BINARY_DIR}\\zfres")
    else()
        execute_process(COMMAND sh "${ZF_ROOT_PATH}/tools/common/copy_check.sh" "${ZF_ROOT_PATH}/_release/cmake/module/${ZF_LIB_NAME_}/lib/" "${CMAKE_INSTALL_PREFIX}/.")
        execute_process(COMMAND sh "${ZF_ROOT_PATH}/tools/util/copy_res.sh" "${ZF_ROOT_PATH}/_release/cmake/module/${ZF_LIB_NAME_}/zfres/" "${PROJECT_BINARY_DIR}/zfres")
    endif()
endfunction(ZFAddLib)

ZFAddLib(ZFCore)
ZFAddLib(ZFAlgorithm)
ZFAddLib(ZFUtility)
ZFAddLib(ZFUIKit)
ZFAddLib(ZFUIWidget)
ZFAddLib(ZFUIExt)
ZFAddLib(ZFLua)
ZFAddLib(ZFUIWebKit)
ZFAddLib(ZFNet)
ZFAddLib(ZF_impl)
ZFAddLib(ZFCore_impl)
ZFAddLib(ZFAlgorithm_impl)
ZFAddLib(ZFUIKit_impl)
ZFAddLib(ZFLua_impl)
ZFAddLib(ZFUIWebKit_impl)
ZFAddLib(ZFNet_impl)

if(APPLE)
    set_target_properties(ZFLoader PROPERTIES INSTALL_RPATH "@loader_path")
elseif(WIN32)
else()
    set_target_properties(ZFLoader PROPERTIES INSTALL_RPATH "\\\$ORIGIN;$ORIGIN")
endif()

install(TARGETS ZFLoader EXPORT ZFLoader
    LIBRARY DESTINATION "${PROJECT_BINARY_DIR}"
    ARCHIVE DESTINATION "${PROJECT_BINARY_DIR}"
    RUNTIME DESTINATION "${PROJECT_BINARY_DIR}"
    )

