# hostlog nss module

A NSS module that will log to syslog every address that a process asks to resolve using NSS.

This means that as long as the software uses the following libc functions, it should log:

* [getaddrinfo](https://linux.die.net/man/3/getaddrinfo)
* [gethostbyname?](https://linux.die.net/man/3/gethostbyname)

## Why this was written

The genesis for this came from tracking down why we received a [GuardDuty](https://aws.amazon.com/guardduty/) alert that an EC2 instance had tried to resolve a domain connected to a known malicious actor.

We had a couple of problems running this down:

1. AWS Magic DNS logs aren't available to customers.
2. Even if they were, we had no idea what of the 1000+ processes on that instance made the request!

We got a hunch from a smart sysadmin that maybe `sshd` was responsible.  When we looked in `/var/log/auth.log` on the system, indeed, the IP address that resolved to the domain listed in the guardduty alert was found as attempting to brute force SSH into that system.  The `UseDNS` configuration option in `/etc/ssh/sshd.conf` was set to `yes`.

![Mission Accomplished](https://i.imgur.com/E5slr5K.jpg "Mission Accomplished")

We got lucky this time.

In our mind, greater visibility into which PID was making what DNS queries would be valuable information to have in your SIEM.  That's where this module comes in.

## Important Limitations

Because this tool works with NSS, tools that do *not* use the variety of system calls that NSS supports for name resollution will not be logged.

Examples include, but are by no means limited to:

* `host`
* `dig`
* `nslookup` (do people still use this?)

## Installation

Use the makefile to build the module: `make all`

Put the libnss_hostlog.so library next to your other nss modules in wherever your linux distro stores them.

Symlink appropriately for NSS: `ln -nfs libnss_hostlog.so libnss_hostlog.so.2`

Edit `/etc/nsswitch.conf` and add `hostlog` to the `hosts:` line as the first entry. It must be the first entry.

As you can see in the code, it logs at [LOG_INFO](http://man7.org/linux/man-pages/man3/syslog.3.html) level (see "Values for facility).  Be sure your local syslog configuration doesn't filter that priority level out.  While you're there, ensure that your syslog configuration also includes the PID.  Kali Linux doesn't by default, Fedora does, YMMV.

## Future Work

* Pull out the full path to the executable via `/proc/$PID/exe`
* Customizable syslog message?
