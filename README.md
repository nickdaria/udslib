# udslib
Memory-safe C framework for building UDS sessions, lookup tables, and security access across any communication protocol - namely ISO-TP.

While UDS is typically used in a CAN/LIN bus environment with ISO-TP, this abstraction allows the same diagnostic procedures to be implemented with other protocols like TCP/IP + BLE without rewriting diagnostic code.

> [!IMPORTANT] 
This library solely focuses on implementation of the UDS protocol. As UDS is often implemented alongside ISO-TP, this library was designed to integrate seamlessly with [isotplib](https://github.com/nickdaria/isotplib).

# 🚀 Features
- UDS session management
- Security access level support with granular permissions
- Easily build function and variable lookup tables
- Pure C, platform agnostic w/ C++/Arduino compatibility
- No dynamic code allocation required
- Tight scope, no bloat


# ⚡️ Advanced Features
- Multiple concurrent sessions
- Peek at multi-packet data before full transfer completion
- Optional user-defined dynamic memory allocation

# ✏️ Usage
- See `examples/` for functioning code examples (command line & microcontroller)
- See [Implementation](https://github.com/nickdaria/udslib/wiki/Implementation) for generic implementation directions
