local text = ZFUITextView()
ZFUIWindowShow(text, ZFUISizeParamWrapWrap())
text:textSingleLine(zffalse)
text:text('put a "zf.lua" to this path and run again:\n\n' .. ZFFilePathForStorageShared())

