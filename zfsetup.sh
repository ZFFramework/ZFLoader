WORK_DIR=$(cd "$(dirname "$0")"; pwd)
ZF_ROOT_PATH=$WORK_DIR/../ZFFramework

sh "$ZF_ROOT_PATH/tools/common/timestamp_check.sh" "$WORK_DIR/_tmp" _zfsetup_time_ 86400
if test "$?" = "0" ; then
    exit 0
fi

if ! test -e "$ZF_ROOT_PATH/tools"; then
    rm -rf "$ZF_ROOT_PATH" >/dev/null 2>&1
    git clone "https://github.com/ZFFramework/ZFFramework.git" "$ZF_ROOT_PATH"
    if test ! "$?" = "0" ; then exit 1 ; fi
fi

sh "$ZF_ROOT_PATH/tools/common/zfsh_recursive.sh" "$ZF_ROOT_PATH" "zfautoscript_zf3rd_setup*.zfsh"
if test ! "$?" = "0" ; then exit 1 ; fi
sh "$ZF_ROOT_PATH/tools/common/zfsh_recursive.sh" "$ZF_ROOT_PATH" "zfautoscript_zfmodule.zfsh"
if test ! "$?" = "0" ; then exit 1 ; fi

ABS_ZF_ROOT_PATH=$(cd -- "$ZF_ROOT_PATH" && pwd)
ABS_WORK_DIR=$(cd -- "$WORK_DIR" && pwd)
if ! test "$ABS_ZF_ROOT_PATH" = "$ABS_WORK_DIR" ; then
    sh "$ZF_ROOT_PATH/tools/common/zfsh_recursive.sh" "$WORK_DIR" "zfautoscript_zf3rd_setup*.zfsh"
    if test ! "$?" = "0" ; then exit 1 ; fi
    sh "$ZF_ROOT_PATH/tools/common/zfsh_recursive.sh" "$WORK_DIR" "zfautoscript_zfmodule.zfsh"
    if test ! "$?" = "0" ; then exit 1 ; fi
fi

sh "$ZF_ROOT_PATH/tools/common/timestamp_save.sh" "$WORK_DIR/_tmp" _zfsetup_time_

