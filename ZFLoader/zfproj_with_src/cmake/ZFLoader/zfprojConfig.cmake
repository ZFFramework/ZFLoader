
include("${ZF_ROOT_PATH}/ZF/ZF_impl/zfproj/cmake/ZF_impl/zfprojConfig.cmake")

function(zfprojConfigBefore_ZFLoader projName srcfiles)
    if(COMMAND zfprojConfigBefore_ZF_impl)
        zfprojConfigBefore_ZF_impl(${projName} ${srcfiles})
    endif()
endfunction(zfprojConfigBefore_ZFLoader)

function(zfprojConfigAfter_ZFLoader projName)
    if(COMMAND zfprojConfigAfter_ZF_impl)
        zfprojConfigAfter_ZF_impl(${projName})
    endif()
endfunction(zfprojConfigAfter_ZFLoader)

