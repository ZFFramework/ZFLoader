local text = ZFUITextView()
ZFUIWindowShow(text, ZFUISizeParamWrapWrap())
text:textSingleLine(zffalse)
text:text('put a "zf.lua" to one of these paths and run again:\n'
    .. '\n' .. ZFFilePathForModule()
    .. '\n' .. ZFFilePathForStorageShared()
    )

