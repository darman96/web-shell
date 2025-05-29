//
// Created by erik on 29.05.25.
//

#pragma once

#include <gtkmm-4.0/gtkmm.h>
#include <webkit/webkit.h>

#include "WidgetSpecification.h"

namespace WebShell {

    class WidgetWindow {

    public:
        explicit WidgetWindow(const WidgetSpecifications& specifications);
        ~WidgetWindow();

        void show() const;

        Gtk::Window* getGtkWindow() const { return m_window; }

    private:
        void initializeWindow(const WidgetSpecifications& specifications);
        void initializeWebView();

    private:
        Gtk::Window* m_window;
        Gtk::Widget* m_webViewWidget;
        WebKitWebView* m_webView;

    };

} // WebShell
