# hostlog nss module

Want to know what domains your processes are looking up this will mostly do that.

## Installation

Use the makefile to build the module: `make all`

Put the libnss_hostlog.so library next to your other nss modules in wherever your linux distro stores them.

Edit `/etc/nsswitch.conf` and add `hostlog` to the `hosts` line as the first entry. It must be the first entry
