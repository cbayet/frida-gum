/*
 * Copyright (C) 2015 Ole André Vadla Ravnås <oleavr@nowsecure.com>
 *
 * Licence: wxWindows Library Licence, Version 3.1
 */

#include "gumjscriptbundle.h"

void
gum_script_bundle_load (const GumScriptSource * sources,
                        JSContextRef context)
{
  JSObjectRef global;
  const GumScriptSource * cur;

  global = JSContextGetGlobalObject (context);

  for (cur = sources; cur->name != NULL; cur++)
  {
    JSStringRef source, url;
    gchar * str;
    JSValueRef result, exception;

    str = g_strjoinv (NULL, (gchar **) cur->chunks);
    source = JSStringCreateWithUTF8CString (str);
    g_free (str);

    str = g_strconcat ("file:///", cur->name, NULL);
    url = JSStringCreateWithUTF8CString (str);
    g_free (str);

    result = JSEvaluateScript (context, source, global, url, 1, &exception);
    g_assert (result != NULL);
    g_assert (exception == NULL);

    JSStringRelease (url);
    JSStringRelease (source);
  }
}
