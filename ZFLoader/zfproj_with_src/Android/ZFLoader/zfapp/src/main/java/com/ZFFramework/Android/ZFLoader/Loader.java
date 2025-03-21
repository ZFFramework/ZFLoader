package com.ZFFramework.Android.ZFLoader;

import com.ZFFramework.Android.ZF_impl.ZFLoader;

public class Loader extends ZFLoader {

    static {
        System.loadLibrary("ZFLoader");
    }

}

