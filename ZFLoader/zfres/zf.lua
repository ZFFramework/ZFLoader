local text = ZFUITextView()
ZFUIWindowShow(text, ZFUISizeParamWrapWrap())
text:textSingleLine(zffalse)

local hint = 'put a "zf.lua" to one of these paths and run again:\n'
local count = zfl_luaValue(ZFFileResExtPathList():count())
for i=0,count-1 do
    hint = hint .. '\n' .. ZFFileResExtPathList():get(i)
end
text:text(hint)

