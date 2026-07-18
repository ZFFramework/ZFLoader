package com.ZFFramework.ZFLoader;

import android.app.Application;

public class ZFApplication extends Application {
    static {
        System.loadLibrary("ZFLoader");
    }
}
