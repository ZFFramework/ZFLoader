package com.ZFFramework.Android.ZFLoader;

import android.app.Activity;
import android.os.Bundle;
import android.view.Window;

import com.ZFFramework.Android.ZF_impl.ZFMainEntry;

public class Loader extends Activity {
    static {
        System.loadLibrary("ZFLoader");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        super.onCreate(savedInstanceState);
        if(BuildConfig.DEBUG) {
            ZFMainEntry.debugMode(true);
        }
        ZFMainEntry.mainEntryFromLoader(this);
    }
}

