//
// Created by erik on 29.05.25.
//
// ReSharper disable CppDeprecatedEntity
#include <webkit/webkit-web-process-extension.h>
#include <jsc/jsc.h>

static JSCValue* my_native_function(JSCContext* context, JSCValue* thisObject, gpointer user_data) {
    // Your C++ logic here
    return jsc_value_new_string(context, "Hello from C++!");
}

static void page_created_callback(WebKitWebProcessExtension* extension, WebKitWebPage* page, gpointer user_data) {
    g_print ("Page %d created for %s\n",
                 webkit_web_page_get_id (page),
                 webkit_web_page_get_uri (page));

    JSCContext* js_context = webkit_frame_get_js_context(webkit_web_page_get_main_frame(page));
    JSCValue* global = jsc_context_get_global_object(js_context);

    JSCValue* func = jsc_value_new_function(
        js_context,
        nullptr,
        G_CALLBACK(my_native_function),
        nullptr,
        nullptr,
        G_TYPE_STRING,
        0);
    jsc_value_object_set_property(global, "myNativeFunction", func);
}

extern "C" G_MODULE_EXPORT void webkit_web_process_extension_initialize(WebKitWebProcessExtension* extension) {
    g_signal_connect(extension, "page-created", G_CALLBACK(page_created_callback), nullptr);
}