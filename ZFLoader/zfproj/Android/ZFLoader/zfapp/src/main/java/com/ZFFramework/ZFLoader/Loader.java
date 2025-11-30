package com.ZFFramework.ZFLoader;

import android.app.Activity;
import android.os.Bundle;
import android.view.Window;

import com.ZFFramework.ZF_impl.ZFMainEntry;
import com.ZFFramework.ZFLoader.BuildConfig;

public class Loader extends Activity {
    static {
        System.loadLibrary("ZFLoader");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        super.onCreate(savedInstanceState);
        if (BuildConfig.DEBUG) {
            ZFMainEntry.debugMode(true);
        }
        ZFMainEntry.mainEntryFromLoader(this);
    }
}

