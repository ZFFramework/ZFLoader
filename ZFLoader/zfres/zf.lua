local text = ZFUITextView()
ZFUIWindowShow(text, ZFUISizeParamWrapWrap())
text:textSingleLineSet(zffalse)
text:textSet('put a "zf.lua" to this path and run again:\n\n' .. ZFFilePathForStorageShared())

