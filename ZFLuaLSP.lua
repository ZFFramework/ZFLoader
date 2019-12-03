-- register class:
--     ---@class YourBase
--     YourBase = _ZFP_ZFLuaLSP_Class([YourParent])
-- constructor:
--     function YourBase:_ZFP_ZFLuaLSP_ctor([params])
--     end
--     ---@param params SomeType
--     ---@return SomeType
--     function YourBase([params])
--         return YourBase._ZFP_ZFLuaLSP_new([params])
--     end
-- method:
--     ---@param params SomeType
--     ---@return SomeType
--     function YourBase:yourMethod([params])
--     end
local _class = {}
function _ZFP_ZFLuaLSP_Class(base)
    local class_type = {}

    class_type.__type = 'class'
    class_type._ZFP_ZFLuaLSP_ctor = false

    local vtbl = {}
    _class[class_type] = vtbl
    setmetatable(class_type,{__newindex = vtbl, __index = vtbl})

    if base then
        setmetatable(vtbl, {
                __index = function(t,k)
                    local ret = _class[base][k]
                    vtbl[k] = ret
                    return ret
                end,
            })
    end

    class_type.__base = base
    class_type._ZFP_ZFLuaLSP_new = function(...)
        local obj = {}
        obj.__base = class_type
        obj.__type = 'object'
        do
            local create
            create = function(c, ...)
                if c.__base then
                    create(c.__base, ...)
                end
                if c._ZFP_ZFLuaLSP_ctor then
                    c._ZFP_ZFLuaLSP_ctor(obj, ...)
                end
            end
            create(class_type,...)
        end
        setmetatable(obj,{ __index = _class[class_type] })
        return obj
    end

    class_type.super = function(self, f, ...)
        assert(self and self.__type == 'object', string.format('self must be a object when call super(self, %s, ...)', tostring(f)))

        local originBase = self.__base
        local s = originBase
        local base = s.__base
        while base and s[f] == base[f] do
            s = base
            base = base.__base
        end

        assert(base and base[f], string.format('base class or function cannot be found when call .super(self, %s, ...)', tostring(f)))
        while base.__base and base[f] == base.__base[f] do
            base = base.__base
        end

        if base.__base then
            self.__base = base
        end

        local result = base[f](self, ...)
        if base.__base then
            self.__base = originBase
        end
        return result
    end

    return class_type
end


------------------------------------------------------------
--- test

_Base = _ZFP_ZFLuaLSP_Class()
function _Base:_ZFP_ZFLuaLSP_ctor()
    print('base ctor')
end
---@return _Base
function Base()
    return _Base._ZFP_ZFLuaLSP_new()
end
function _Base:func()
    print('base func')
end


_Child1 = _ZFP_ZFLuaLSP_Class(_Base)
function _Child1:_ZFP_ZFLuaLSP_ctor()
    print('child1 ctor')
end
---@return _Child1
function Child1()
    return _Child1._ZFP_ZFLuaLSP_new()
end
function _Child1:test1()
    print('child1 test1')
end
function _Child1:func()
    self:super('func')
    print('child1 func')
end


_NS_Child2 = _ZFP_ZFLuaLSP_Class(_Base)
function _NS_Child2:_ZFP_ZFLuaLSP_ctor()
    print('child2 ctor')
end
---@return _NS_Child2
function NS.Child2()
    return _NS_Child2._ZFP_ZFLuaLSP_new()
end
---@param p0 _Base
function _NS_Child2:test2(p0)
    print('child2 test2')
end

NS = {}


local c1 = Child1()
c1:test1()
c1:func()

local c2 = NS.Child2()
c2:test2()
c2:func()

