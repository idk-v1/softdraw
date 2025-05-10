#ifdef __cplusplus
extern "C" {
#endif

#pragma once
#include <stdint.h>
#include <stdbool.h>

#include "../image/image.h"
#include "../timer/timer.h"
#include "../util.h"

#define enumBit 1 << 

typedef uint64_t sft_flags;
enum
{
    sft_flag_closed     = enumBit 0,

    sft_flag_hidden     = enumBit 1,
    sft_flag_noresize   = enumBit 2,
    sft_flag_borderless = enumBit 3,

    sft_flag_maximized  = enumBit 4,
    sft_flag_minimized  = enumBit 5,
    sft_flag_fullscreen = sft_flag_borderless | sft_flag_maximized,

    sft_flag_topmost    = enumBit 6,
    sft_flag_passthru   = enumBit 7,
    sft_flag_syshide    = enumBit 8,

    sft_flag_darkmode   = enumBit 9,

    sft_flag_default = 0,
};

typedef struct sft_window
{
    /**
    * \brief OS window handle
    */
    void* handle;

    /**
    * \brief Window title
    */
    char* title;

    /**
    * \brief Internal framebuffer
    */
    sft_image* frameBuf;

    /**
    * \brief Window customization options
    */
    sft_flags flags;

    /**
    * \brief Window position
    */
    int32_t left;
    /**
    * \brief Window position
    */
    int32_t top;
    /**
    * \brief Window size
    */
    uint32_t width;
    /**
    * \brief Window size
    */
    uint32_t height;

    /**
    * \brief Limit of frames displayed per second
    */
    uint32_t fpsLimit;
    /**
    * \brief Internal last tick count for frame timing
    */
    uint64_t _lastFrame;

    /**
    * \brief A pointer to use in window event callbacks
    */
    void* userData;

    /**
    * \brief Function pointer to custom event callback
    */
    void (*onClose)(struct sft_window* window);
    /**
    * \brief Function pointer to custom event callback
    */
    void (*onMove)(struct sft_window* window, int32_t left, int32_t top);
    /**
    * \brief Function pointer to custom event callback
    */
    void (*onResize)(struct sft_window* window, uint32_t width, uint32_t height);
} sft_window;

/**
* \brief Sets window customization option after window creation
* \param window The window to apply settings to
* \param enable The settings to enable
* \param disable The settings to disable
*/
void sft_window_setFlag(sft_window* window, sft_flags enable, sft_flags disable);


/**
* \brief Sets the window size
* \param window The window to set size of
* \param width The new width of the window
* \param height The new height of the window
*/
void sft_window_setSize(sft_window* window, uint64_t width, uint64_t height);

/**
* \brief Internal function to set the window size
* \param window The window to set size of
* \param width The new width of the window
* \param height The new height of the window
*/
void _sft_window_setSize(sft_window* window, uint64_t width, uint64_t height);

/**
* \brief Sets the window position
* \param window The window to set position of
* \param left The new x position of the window
* \param top The new y position of the window
*/
void sft_window_setPos(sft_window* window, uint64_t left, uint64_t top);

/**
* \brief Internal function to set the window position
* \param window The window to set position of
* \param left The new x position of the window
* \param top The new y position of the window
*/
void _sft_window_setPos(sft_window* window, uint64_t left, uint64_t top);


/**
* \brief Sets the window to show above all others
* \param window The window to set topmost
* \param value If the window should be topmost
*/
void sft_window_setTopmost(sft_window * window, bool value);

/**
* \brief Internal function to set the window to show above all others
* \param window The window to set topmost
* \param value If the window should be topmost
*/
void _sft_window_setTopmost(sft_window* window, bool value);


/**
* \brief Focuses window
* \param window The window to set focus
* \param value If the window should be topmost
*/
void sft_window_focus(sft_window* window);

/**
* \brief Internal function to focus window
* \param window The window to set focus
* \param value If the window should be topmost
*/
void _sft_window_focus(sft_window* window);


/**
* \brief Sets the window to be visible or hidden
* \param window The window to show
* \param value If the window should be shown
*/
void sft_window_setVisible(sft_window* window, bool value);

/**
* \brief Internal function to set the window to be visible or hidden
* \param window The window to show
* \param value If the window should be shown
*/
void _sft_window_setVisible(sft_window* window, bool value);


/**
* \brief Creates a window and returns a pointer to it
* \param title Title of window
* \param width Width of window
* \param height Height of window
* \param left Leftmost position of window
* \param top Topmost position of window
* \param flags Options for customizing window
*/
sft_window* sft_window_open(const char* title, uint32_t width, uint32_t height, int32_t left, int32_t top, sft_flags flags);
/**
* \brief Internal function to create a window
* \param window A pointer to a window struct to modify
* \param title Title of window
* \param width Width of window
* \param height Height of window
* \param left Leftmost position of window
* \param top Topmost position of window
* \param flags Options for customizing window
*/
bool _sft_window_open(sft_window* window, const char* title, uint32_t width, uint32_t height, int32_t left, int32_t top, sft_flags flags);

/**
* \brief Gets if the window is focused
* \param window The window to check if focused
*/
bool sft_window_hasFocus(const sft_window* window);

/**
* \brief Internal function to get if the window is focused
* \param window The window to check if focused
*/
bool _sft_window_hasFocus(const sft_window* window);

/**
* \brief Gets event messages and returns if the window should be closed
* \param window The window to be updated
*/
bool sft_window_update(sft_window* window);
/**
* \brief Internal function to get event messages
* \param window The window to be updated
*/
void _sft_window_update(sft_window* window);

/**
* \brief Draws the internal framebuffer to the window
* \param window The window to display
*/
void sft_window_display(sft_window* window);
/**
* \brief Internal function to draw the framebuffer to the window
* \param window the window to display
*/
void _sft_window_display(sft_window* window);

/**
* \brief Changes the window title
* \param window the window of the title to change
* \param title the string of the new title
*/
void sft_window_setTitle(sft_window* window, const char* title);

/**
* \brief Internal function to change the window title
* \param window the window of the title to change
*/
void _sft_window_setTitle(sft_window* window);

/**
* \brief Frees window memory and closes the window
* \param window The window to close
*/
void sft_window_close(sft_window* window);
/**
* \brief Internal function to close the window
* \param window The window to close
*/
void _sft_window_close(sft_window* window);

/**
* \brief Default callback to window.onClose is NULL
* \param window The window that was closed
*/
void sft_window_defOnClose(sft_window* window);
/**
* \brief Default callback to window.onResize is NULL
* \param window The window that was resized
* \param width The new width of the window
* \param height The new height of the window
*/
void sft_window_defOnResize(sft_window* window, uint32_t width, uint32_t height);
/**
* \brief Default callback to window.onMove is NULL
* \param window The window that was moved
* \param left The new leftmost position of the window
* \param top The new topmost position of the window
*/
void sft_window_defOnMove(sft_window* window, int32_t left, int32_t top);

/**
* \brief Setting up globals and OS specific functions
*/
void sft_window_init();

/**
* \brief Cleaning up globals and OS specific functions
*/
void sft_window_shutdown();

/**
* \brief Copies pixels from a source image to a destination window
* \param dest Destination window to draw to
* \param src Source image to get pixels from
* \param srcX Leftmost position to get pixels from source
* \param srcY Topmost position to get pixels from source
* \param srcW Width of copied image
* \param srcW Height of copied image
* \param destX Leftmost position to copy to on destination image
* \param destY Topmost position to copy to on destination image
*/
void sft_window_drawImage(sft_window* dest, const sft_image* src,
    int32_t srcX, int32_t srcY, uint32_t srcW, uint32_t srcH,
    int32_t destX, int32_t destY);

/**
* \brief Fills pixels in rectangle with a color
* \param dest Destination window to draw to
* \param x Leftmost position of rectangle
* \param y Topmost positionof rectangle
* \param w Width of rectangle
* \param h Height of rectangle
* \param color Color to fill rectangle with
*/
void sft_window_drawRect(sft_window* dest,
    int32_t x, int32_t y, uint32_t w, uint32_t h, sft_color color);

/**
* \brief Outlines pixels in rectangle with a color
* \param dest Destination window to draw to
* \param x Leftmost position of rectangle
* \param y Topmost positionof rectangle
* \param w Width of rectangle
* \param h Height of rectangle
* \param color Color to outline rectangle with
*/
void sft_window_outlineRect(sft_window* dest,
    int32_t x, int32_t y, uint32_t w, uint32_t h, sft_color color);

/**
* \brief Fills the entire window with a specified color
* \param window Target image to be filled
* \param color Color to fill window with
*/
void sft_window_fill(sft_window* window, sft_color color);

/**
* \brief Draws a string to a window
* \param window The window to draw to
* \param text The string to draw
* \param x The leftmost position
* \param y the topmost position
* \param fontSize The font size
* \param color The color of the text
*/
void sft_window_drawText(sft_window* window, const char* text,
    int32_t x, int32_t y, uint32_t fontSize, sft_color color);

/**
* \brief Draws a string to an image
* \param window The window to draw to
* \param x The leftmost position
* \param y the topmost position
* \param fontSize The font size
* \param color The color of the text
* \param fmt formatted string
*/
void sft_window_drawTextF(sft_window* window, int32_t x, int32_t y,
    uint32_t fontSize, sft_color color, const char* fmt, ...);

/**
* \brief Mostly for internal use, but could be useful.
Draws a character to a window
* \param window The window to draw to
* \param ch The character to draw
* \param x The leftmost position
* \param y the topmost position
* \param fontSize The font size
* \param color The color of the text
*/
void sft_window_drawChar(sft_window* window, char ch,
    int32_t x, int32_t y, uint32_t fontSize, sft_color color);

/**
* \brief Returns the primary monitor width
*/
uint32_t sft_screenWidth();

/**
* \brief Returns the primary monitor height
*/
uint32_t sft_screenHeight();

/**
* \brief Captures the entire screen
* \param image [out] Returns a screenshot
*
* Uses a parameter rather than returning an image, because of reusing existing memory.
* This is probably only needed for screen recording, not a single screenshot.
* This was also tested on a 2012 laptop, but it was significantly faster
*/
void sft_screenshot(sft_image* image);

#ifdef __cplusplus
}
#endif