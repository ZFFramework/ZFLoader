/**
 * @file ZFLuaLSP.h
 * @brief util to export a lua file for LSP
 */

#ifndef _ZFI_ZFLuaLSP_h_
#define _ZFI_ZFLuaLSP_h_

#include "ZFLua.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief util to export a lua file for LSP (Language Server Protocol)
 *
 * include the generated lua file for LSP plugins,
 * then your LSP plugin should be able to perform semantic completion\n
 * recommended LSP is EmmyLua
 * @code
 *   https://github.com/EmmyLua/EmmyLua-LanguageServer
 * @endcode
 */
ZFMETHOD_FUNC_DECLARE_1(void, ZFLuaLSPGenFile,
                        ZFMP_IN(const ZFOutput &, output))

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFLuaLSP_h_

