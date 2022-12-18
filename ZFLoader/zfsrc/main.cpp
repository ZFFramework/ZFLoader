#include "ZFCore.h"
#include "ZFUIKit.h"
#include "ZFUIWidget.h"
#include "ZFLua.h"

ZFMAIN_ENTRY()
{
    ZFCoreArray<ZFPathInfo> extResList;
    extResList.add(ZFPathInfo(ZFPathType_file(), ZFFilePathForModule()));
    extResList.add(ZFPathInfo(ZFPathType_file(), ZFFilePathForStorageShared()));

    zfLogTrimT() << "external res:" << extResList;
    for(zfindex i = 0; i < extResList.count(); ++i)
    {
        ZFFileResExtPathAdd(extResList[i]);
    }

    ZFLuaExecute(ZFInputForRes("zf.lua"));
    ZFLuaGC();
}

