#include "ZFCore.h"
#include "ZFUIKit.h"
#include "ZFUIWidget.h"
#include "ZFLua.h"

ZFMAIN_ENTRY()
{
    ZFCoreArray<ZFPathInfo> extResList;
    extResList.add(ZFPathInfo(ZFPathType_file(), ZFPathForModule()));
    extResList.add(ZFPathInfo(ZFPathType_file(), ZFPathForStorageShared()));

    zfLogTrimT() << "external res:" << extResList;
    for(zfindex i = 0; i < extResList.count(); ++i)
    {
        ZFResExtPathAdd(extResList[i]);
    }

    ZFLuaExecute(ZFInputForRes("zf.lua"));
    ZFLuaGC();
}

