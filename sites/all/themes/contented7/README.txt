// $Id: README.txt,v 1.3.2.8 2008/09/10 17:38:25 hswong3i Exp $

ABOUT CONTENTED7
----------------------

This is a re-implementation of the Contented7 theme by Tom Rowan. This is a
tableless, multi-column, fluid width layout. Parts of the design are ported
from the K2 theme.

Official Contented7 project page:
  http://www.contenteddesigns.org/templates/Contented7/index.html

Drupal Contented7 project page:
  http://drupal.org/project/contented7/
  http://pantarei.com.hk/projects/contented7/

Sponsored by:
  http://pantarei.com.hk/


HOWTO SET THEME AS FIXED WIDTH LAYOUT?
----------------------

This theme is fluid width layout by default, which is different from
original design. In order to display as fixed width layout (e.g. 800x600
or 1024x768), please follow this procedure:

  1. Copy custom.example.css as custom.css.
  2. Change the custom.css as what you like.

The custom.css will always override the default style.css setting, and
will not be covered during version upgrade.


HOW THE MISSION HACK FUNCTION?
----------------------

By default, mission statement is protected by filter_xss_admin() so no
PHP script is allowed. On the other hand, all tags that can be used inside
an HTML body is allowed.

This theme provide a fancy hack so PHP script will able to execute if
mission statement starting with "<?php", or else will preform as default
style.

One example usage is combine with adsense module so only display a
skyscraper (120x600) at top page; another example is combine with banner
module so you will have a benner rotation as mission statement; or even
just execute a simple PHP code snippet as welcome message when user login.


ABOUT RTL SUPPORT
----------------------

This theme is RTL supported, and fully tested with Acid2 compatible
browsers, e.g. FireFox3, Opera9.2 and Safari3. However, other browser
such as FireFox2 and Internet Explorer 6/7 may looks buggy.

As the implementation is validate with XHTML and CSS2 coding standard,
I am not going to provide browser-specific hack, for both LTR and RTL.

For more information about Acid2:
  http://en.wikipedia.org/wiki/Acid2

To test your browser with Acid2:
  http://www.webstandards.org/files/acid2/test.html


LIST OF MAINTAINERS
----------------------

PROJECT OWNER
M: Edison Wong <hswong3i@gmail.com>
S: maintained
W: http://edin.no-ip.com/
