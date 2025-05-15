#include "ZFCore.h"
#include "ZFUIKit.h"
#include "ZFUIWidget.h"
#include "ZFLua.h"

ZFMAIN_ENTRY() {
    ZFCoreArray<ZFPathInfo> extResList;
    extResList.add(ZFPathInfo(ZFPathType_file(), ZFPathForModule()));
    extResList.add(ZFPathInfo(ZFPathType_file(), ZFPathForStorageShared()));

    ZFLogTrim() << "external res: " << extResList;
    for(zfindex i = 0; i < extResList.count(); ++i) {
        ZFResExtPathAdd(extResList[i]);
    }

    ZFInput src = ZFInputForRes("zf.lua");
    if(src) {
        ZFLogTrim("redirect to %s", src.callbackId());
        ZFLuaExecute(src);
        ZFLuaGC();
        return;
    }

    zfobj<ZFUIWindow> w;
    w->show();
    zfobj<ZFUITextView> text;
    w->child(text)->c_sizeWrap();
    text->singleLine(zffalse);
    zfstring hint = "put a \"zf.lua\" to one of these paths and run again:\n";
    for(zfindex i = 0; i < ZFResExtPathList().count(); ++i) {
        hint += "\n";
        ZFPathInfoToStringT(hint, ZFResExtPathList()[i]);
    }
    text->text(hint);
}

ZFMAIN_PARAM_DISPATCH(LuaRunner) {
    if(ZFApp::appParams().isEmpty() || ZFRegExpFind(ZFApp::appParams()[0], ".*\\.lua$") == ZFIndexRangeMax()) {
        return;
    }
    zfargs.eventFiltered(zftrue);

    const ZFCoreArray<zfstring> &appParams = ZFApp::appParams();
    ZFPathInfo pathInfo;
    if(!ZFPathInfoFromStringT(pathInfo, appParams[0])) {
        pathInfo.pathType(ZFPathType_file());
        pathInfo.pathData(appParams[0]);
    }
    ZFCoreArray<zfauto> luaParams;
    for(zfindex i = 1; i < appParams.count(); ++i) {
        luaParams.add(zfobj<v_zfstring>(appParams[i]));
    }
    ZFLuaExecuteDetail(ZFInputForPathInfo(pathInfo), luaParams);
}

