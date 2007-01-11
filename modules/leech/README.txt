LEECH MODULE

Leech and its associated modules allow you to aggregate news from other
sites and import them as Drupal nodes on your own site.

REQUIREMENTS
The modules required for turning incoming RSS/ATOM feeds into nodes, consist of:

    * leech.module
    * node_template.module

The PHP CURL module must also be installed on your server's version of PHP. If
you are not sure if CURL is installed on your server, following the INSTALL
directions below will help you determine this. For more information about CURL,
see http://us2.php.net/curl/. For help installing CURL, consult your web host,
operating system documentation, or your favorite search engine.

An optional leech_yahoo_terms.module is available. See the REMARKS section
for details.

INSTALL
    * Enable all the required modules mentioned above.
    * Check the admin/settings/leech page to make sure that there is no warning
      message about the CURL library not being installed. If you see no message, CURL
      is installed on your server and you are good to go.
    * Create the template for your feed items. Go to node/add/story and add a
      story with a title like "template story" as the title and add some placeholder
      text (like "template node") in the body. make sure you set the publishing
      options to not published.  Then, once you submit that node, stay on the node,
      and you will see there is a new tab that appears next to the view ad edit tabs
      which says "template". Click on template, and then scroll down and save the
      template.  You do not need to enter anything in the textareas.
    * Go to admin/settings/content-types/page and enable the page content type
      for leech under "Default leech news options" by selecting the story template
      that you just made and select the other options in "Default leech news options"
      fieldset to your liking.

REMARKS
You can optionally enable leech_yahoo_terms.module which will use the
Yahoo Terms API to add keywords on every article aggregated.  You will need a
Yahoo ID to enter as an API key, which is free.  See module's settings page for
more information.
* There may be some additional settings under admin/settings/leech or
  you might want to look at for your purposes.
* You do not have to use "story" or "page" you can use other node types like CCK
  if you wish.
* Feeds get parsed at cron time. For automatically "leeching" feed content into
  your system, you need to configure cron. See http://drupal.org/cron.
