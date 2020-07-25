## toggle-fullscreen

Library for making any window borderless fullscreen.

Responsible for:

- Finding target window by title
- Remove title bar and border

Important notes:

- Windows: target window must have the same or lower privilege level than overlay window
- X11: library relies on EWHM, more specifically `_NET_ACTIVE_WINDOW`, `_NET_WM_STATE_FULLSCREEN`, `_NET_WM_NAME`

Supported backends:

- Windows (7 - 10)
- Linux (X11)
