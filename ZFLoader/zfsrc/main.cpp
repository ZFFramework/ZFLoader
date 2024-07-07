#include "ZFCore.h"
#include "ZFUIKit.h"
#include "ZFUIWidget.h"
#include "ZFLua.h"

ZFMAIN_ENTRY() {
    ZFCoreArray<ZFPathInfo> extResList;
    extResList.add(ZFPathInfo(ZFPathType_file(), ZFPathForModule()));
    extResList.add(ZFPathInfo(ZFPathType_file(), ZFPathForStorageShared()));

    zfLogTrim() << "external res: " << extResList;
    for(zfindex i = 0; i < extResList.count(); ++i) {
        ZFResExtPathAdd(extResList[i]);
    }

    ZFLuaExecute(ZFInputForRes("zf.lua"));
    ZFLuaGC();
}

ZFMAIN_PARAM_DISPATCH(LuaRunner) {
    if(ZFApp::appParams().isEmpty() || ZFRegExpFind(ZFApp::appParams()[0], ".*\\.lua$") == ZFIndexRangeZero()) {
        return;
    }
    zfargs.eventFiltered(zftrue);

    const ZFCoreArray<zfstring> &appParams = ZFApp::appParams();
    ZFPathInfo pathInfo;
    if(!ZFPathInfoFromStringT(pathInfo, appParams[0])) {
        pathInfo.pathType = ZFPathType_file();
        pathInfo.pathData = appParams[0];
    }
    ZFCoreArray<zfauto> luaParams;
    for(zfindex i = 1; i < appParams.count(); ++i) {
        luaParams.add(zfobj<v_zfstring>(appParams[i]));
    }
    ZFLuaExecuteDetail(ZFInputForPathInfo(pathInfo), luaParams);
}

