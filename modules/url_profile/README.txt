URL PROFILE MODULE

URL profile collects URLs with a common host string and retrieves information
for Alexa and Technorati about these hosts.

URL profile is to be used in combination with a feed aggregator. When the
aggregator subscribes to a feed with articles from different sources (for
example the Planet Drupal feed), URL profile finds out which sources those
articles are coming from (in this example http://www.buytaert.net,
http://www.planet-soc.com ... ) and provides navigation by those sources. In
addition to that, page thumbnails and blog rankings are pulled from Alexa and
Technorati (API keys necessary).

REQUIREMENTS

Leech module - Currently, the Leech module is the only aggregator that
implements an interface to URL profile.

The PHP CURL module must be installed on your server's version of PHP. If
you are not sure if CURL is installed on your server, following the INSTALL
directions below will help you determine this. For more information about CURL,
see http://us2.php.net/curl/. For help installing CURL, consult your web host,
operating system documentation, or your favorite search engine.

The modules url_profile_alexa and url_profile_technorati are optional (but
really cool). Note that you need API keys for alexa and technorati API in order
to use them.

URL profiles are calculated at cron time. Don't forget to set cron accordingly.
Setting URL profile to 25 profiles per cron run (settings page) and cron to run
every 15 minutes (your server) is usually a good rule of thumb.

INSTALL
    * Unpack tarball in your modules directory
    * Go to admin/modules and activate at least url_profile, optionally
      url_profile_alexa and url_profile_technorati
    * Configure the activated modules on the settings page according your
      preferences.

The module is sponsored by Development Seed, the World Bank in coordination with
Pierre Wielezynski and the World Resources Institute.