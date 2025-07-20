#include "ZFCore.h"
#include "ZFUIKit.h"
#include "ZFUIWidget.h"
#include "ZFLua.h"

static void _ZFLoaderEntry(void) {
    ZFCoreArray<ZFPathInfo> extResList;
    extResList.add(ZFPathInfo(ZFPathType_file(), ZFPathForModule()));
    extResList.add(ZFPathInfo(ZFPathType_file(), ZFPathForStorageShared()));

    ZFPathInfo custom;
    if(ZFPathInfoFromStringT(custom, ZFState::instance()->get("ZFCustomResExt"))) {
        extResList.add(custom);
    }

    ZFLogTrim() << "external res: " << extResList;
    for(zfindex i = 0; i < extResList.count(); ++i) {
        ZFResExtPathAdd(extResList[i]);
    }

    zfobj<ZFUIWindow> w;
    ZFUIOnScreenKeyboardAutoResizeStart(w);
    w->show();
    w->layoutParam()->c_margin(20);

    zfobj<ZFUITextView> text;
    w->child(text)->c_sizeWrap();
    text->singleLine(zffalse);
    zfstring hint = "put a \"zf.lua\" to one of these paths and run again:\n";
    for(zfindex i = 0; i < ZFResExtPathList().count(); ++i) {
        hint += "\n";
        ZFPathInfoToStringT(hint, ZFResExtPathList()[i]);
    }
    text->text(hint);

    zfautoT<ZFUIText> input;
    if(ZFProtocolIsAvailable("ZFUITextEdit")) {
        input = zfobj<ZFUITextEditWidget>()
            ->c_placeholderProp("text", zfobj<v_zfstring>("custom path info ext"))
            ;
    }
    else {
        input = zfobj<ZFUITextView>()
            ->c_text("http:http://localhost")
            ;
    }
    zfobj<ZFUIButtonBasic> btn;

    w
        ->child(zfobj<ZFUILinearLayout>()
            ->c_orientation(ZFUIOrientation::e_Top)

            ->child(zfobj<ZFUITextView>()
                ->c_text("or, input custom path info:")
                ->c_textAlign(ZFUIAlign::e_Left)
            )->c_widthFill()

            ->child(zfobj<ZFUILinearLayout>()
                ->c_orientation(ZFUIOrientation::e_Left)

                ->child(input
                )->c_weight(1)->c_widthFill()

                ->child(btn
                    ->c_labelProp("text", zfobj<v_zfstring>("OK"))
                    ->c_viewSizeMin(ZFUISizeCreate(60, 48))
                )
            )->c_widthFill()
        )->c_widthFill()->c_alignBottom()
        ;

    ZFLISTENER_1(onClick
            , zfautoT<ZFUIText>, input
            ) {
        zfstring key = "ZFCustomResExt";
        zfstring text = input->text();
        if(text) {
            ZFState::instance()->set(key, text);
            ZFUIHintShow(zfstr("restart to take effect"));
        }
        else {
            ZFState::instance()->remove(key);
            ZFUIHintShow("res ext cleared");
        }
    } ZFLISTENER_END()
    btn->onClick(onClick);

    ZFInput src = ZFInputForRes("zf.lua");
    if(src) {
        ZFLogTrim("redirect to %s", src.callbackId());
        ZFLuaExecute(src);
        ZFLuaGC();
    }
}

ZFMAIN_ENTRY() {
    ZFLISTENER_0(loadFinish) {
        _ZFLoaderEntry();
    } ZFLISTENER_END()
    ZFState::instance()->load(loadFinish);
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

