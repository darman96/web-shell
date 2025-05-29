//
// Created by erik on 29.05.25.
//

#pragma once

namespace WebShell
{
    enum class WidgetLayer
    {
        Top,
        Bottom,
        Overlay
    };

    enum class WidgetAnchor : uint8_t
    {
        None   = 0,
        Top    = 1 << 0,
        Bottom = 1 << 1,
        Left   = 1 << 2,
        Right  = 1 << 3,
    };

    // Enable bitmask operations for WidgetAnchor
    inline WidgetAnchor operator|(WidgetAnchor a, WidgetAnchor b) {
        return static_cast<WidgetAnchor>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
    }
    inline WidgetAnchor operator&(WidgetAnchor a, WidgetAnchor b) {
        return static_cast<WidgetAnchor>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
    }
    inline WidgetAnchor& operator|=(WidgetAnchor& a, WidgetAnchor b) {
        a = a | b;
        return a;
    }

    struct WidgetSize
    {
        uint width;
        uint height;
    };

    struct WidgetMargins
    {
        uint left;
        uint right;
        uint top;
        uint bottom;
    };

    struct WidgetSpecifications
    {
        std::string title;
        WidgetLayer layer = WidgetLayer::Overlay;
        WidgetAnchor anchor = WidgetAnchor::None;
        WidgetSize size;
        WidgetMargins margins = {0, 0, 0, 0};
    };
}

