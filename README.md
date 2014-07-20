XPLC (Cross-Platform Lightweight Components)
============================================

Web Site: http://xplc.sourceforge.net/
Maintainer: Pierre Phaneuf <pp@ludusdesign.com>

Introduction
------------

XPLC (cross-platform lightweight components) is a component system
that provide extensibility and reusability both inside and between
applications, being portable across platforms and languages, easy to
use and having the lowest possible overhead.

Stability/Usability
-------------------

XPLC is quickly becoming usable, but it's API is still in a state of
flux. A project that would like to use XPLC would thus have to either
require a precise version or link it statically. They should also be
prepared to follow changes in the API as they change from one version
of XPLC to the other.

That said, using XPLC should now be possible, provided that you are
subscribed to the mailing list and know what you are doing.

Documentation
-------------

The documentation for XPLC is available online:

		   http://xplc.sourceforge.net/doc/

Thanks
------

I would like to thank Net Integration Technologies, my employers, for
allowing me to work on XPLC a day a week and generally being a cool
place to work at.

License
-------

All files included in this package are covered by the Lesser General
Public License, unless noted otherwise. Refer to the 'LICENSE' file
for terms and conditions.

Releases
--------

XPLC uses a numbering scheme for releases similar to what the Linux
kernel uses. In short, a release number is composed of three parts,
the major, minor and patchlevel numbers (like this: 3.4.31).

The minor number has a special signification depending on whether it
is even or odd. If it is even, it means that this is a stable release,
suitable for use in a production environment. If it is odd, it means
that this is a development release, intended for people willing to
test XPLC, report bugs and/or work on its development.

Installation
------------

See the 'INSTALL' file.

Patches
-------

Patches should preferably be submitted to the patch tracking system on
our SourceForge project page (http://sourceforge.net/projects/xplc/),
but could also be send via e-mail to the maintainer.

                          *** IMPORTANT ***
				   
Before preparing a patch, you should make sure that 'make tests'
passes all tests. Those tests are made to be as easy to use as
possible, so please use them. Using the "--enable-fatal-warnings"
option of the "configure" script is also recommended.

The simpler way to prepare a patch requires CVS and Internet
access. Just issue the following command in the root XPLC project
directory:

$ cvs diff -u > mypatch.diff

You can also send a patch that is limited to a few files in the
following way:

$ cvs diff -u [FILES] > mypatch.diff

If you do not have CVS and/or Internet access, you should do the
following:

 - rename the XPLC source directory to something like 'xplc-modified'
 - unpack the fresh XPLC sources
 - run the following command:

$ diff -ruN xplc-X.Y.Z xplc-modified > mypatch.diff

You can then submit the mypatch.diff file for inclusion in XPLC!

