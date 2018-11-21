/* ====================================================================== *
 * Copyright (c) 2010-2018 ZFFramework
 * Github repo: https://github.com/ZFFramework/ZFFramework
 * Home page: http://ZFFramework.com
 * Blog: http://zsaber.com
 * Contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/LICENSE
 * ====================================================================== */
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

