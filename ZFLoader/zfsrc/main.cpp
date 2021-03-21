#include "ZFCore.h"
#include "ZFUIKit.h"
#include "ZFUIWidget.h"
#include "ZFLua.h"

ZFMAIN_ENTRY()
{
    ZFCoreArray<zfstring> extResList;
    extResList.add(ZFFilePathForModule());
    extResList.add(ZFFilePathForStorageShared());

    zfLogTrimT() << "external res:" << extResList;
    for(zfindex i = 0; i < extResList.count(); ++i)
    {
        ZFFileResAdditionalPathAdd(extResList[i]);
    }

    ZFLuaExecute(ZFInputForResFile("zf.lua"));
    ZFLuaGC();
}

