#include "ZFCore.h"
#include "ZFUIKit.h"
#include "ZFUIWidget.h"
#include "ZFLua.h"

ZFMAIN_ENTRY(params)
{
    zfstring extRes = zfstringWithFormat("%s", ZFFilePathForStorageShared());
    zfLogTrimT() << "external res:" << extRes;
    ZFFileResAdditionalPathAdd(extRes);

    ZFLuaExecute(ZFInputForResFile("zf.lua"));
    ZFLuaGC();
    return 0;
}

