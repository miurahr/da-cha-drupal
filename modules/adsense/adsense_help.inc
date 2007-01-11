<?php

function adsense_help_text($formats = '') {

return t('
<h2>Overview</h2>
<p>This module provides web site admins the factility to display Google AdSense ads on their web site, thus earning revenue.</p>

<h2>Prerequisites</h2>
<p>You must have a Google AdSense account before using this module. If you do not have an account, then please consider using  <a href="http://baheyeldin.com/click/476/1">the module\'s author referral link</a>, which provides us with a referral fee from Google, with absolutely no cost to you. This page also contains various useful links and resources on Adsense, and how to optimize your site for it.</p>

<h2>Supported Formats</h2>
<p>The following ad formats are supported:</p>'
. $formats .
'<h2>Configuration</h2>
<p>To use this module, you need to do the following first:</p>
<ul>
<li>Go to administer -> modules and enable the profile module.</li>
<li>Go to administer -> settings -> profile and create a new profile field of type "single line textfield". Name this field something like "Google Adsense Client ID", and form name "profile_google_adsense_client_id". This is a required configuration parameter. At a minimum you should enter this field for user 1.
<p>Note that the new profile field must be setup as: "Private field, content only available to privileged users". All other values are either insecure or will not work, so do not use any of them.</p>
<p>If you want to use revenue sharing and force users to enter a value when they signup, then check the following settings:</p>
<ul>
<li>The user must enter a value.</li>
<li>Visible in user registration form.</li>
</ul>
<p>Also, you should enter a descriptive explanation for the Google Adsense Client ID, so users know what to enter in this field.</p></li>
<li>Go to "my account" -> edit, then click on the category that you defined the Google Adsense Client ID under, and then enter your Google ID, which is something like "pub-9999999999999", and click Submit.</li>
</ul>

<h2>Displaying AdSense Ads</h2>
<p>There are several ways to display ads, summarized as follows:</p>
<p>Ads can be displayed in pre-defined blocks, in custom blocks, in content or in any phptemplate based theme.</p>

<h3>Using Blocks</h3>
<p>The easiest way to get started with this module is to use one or more of the pre-defined blocks.</p>
<p>Visit the '. l(t('blocks'), 'admin/block') .' configuration page, and click on the <strong>configure</strong> link of one of the adsense blocks. You have to select a format, a group, and a channel.</p>
<p>Enable the block, and specify a region it would be displayed in.</p>

<h3>Using Custom PHP code</h3>
<p>To display ads, you call a function <code>adsense_display</code> and supply it with the following arguments.</p>
<ul>
<li>Format: This is a string of two numbers with an "x" in between. It can be any valid combination from the list provided above. If not specified, then 160x600 is assumed.</li>
<li>Group: This is the group that denotes the type (text or image) and color of the ad. This can be 1, 2 or 3. If not specified, then 1 is assumed.</li>
<li>Channel: This is the Custom Channel for the ad, as configured in AdSense. This is an optional parameter and if not specified, then 1 is assumed. If you did not configure any channels, then leave this parameter out.</li>
</ul>

<p>You can also To display ads in blocks, add a new block, make its type "PHP", and enclose it in php tags.</p>
<pre><code>
print adsense_display("120x600", 1, 2);
</code></pre>
<p>If you want to make sure that you do not get errors if adsense module is accidentally disabled or deleted, then use the longer form:</p>
<pre><code>
if (module_exist("adsense"))
{
 print adsense_display("120x600", 2, 4);
}
</code></pre>

<h3>Using Themes</h3>
<p>You must use a phptemplate based theme to display ads from within the theme. This requires some familiarity with PHP. Edit the appropriate <strong>.tpl.php</strong> file in your theme directory, and add:</p>
<pre><code>
print adsense_display("468x60");
</code></pre>
<p>Make sure you enclose it in php tags.</p>
<p>You could also use the longer format that protects you against deleting or disabling the module:<pre><code>
if (module_exist("adsense"))
{
 print adsense_display("120x600", 2, 4);
}
</code></pre>

<h3>Using Tags</h3>
<p>The tags feature allows placement of ads in any place in the content. Please note that content here means any part that is passed through Drupal\'s filter system. Text in the slogan, mission, and footer is normally not filtered the same was as text in nodes, so you cannot put tags in those places.</p>
<p>To enable the tags feature, you have to enable the "AdSense tag" filter in the input format you are using (e.g. Full HTML or Filtered HTML) from Administer >> Input Formats. Then you have to insert the appropriate tag anywhere in your node where you like the ad to appear.</p>
<p>Note that filters sometimes may have conflicts, and changing the order can make adsense work in some cases.</p>
<p>The tag syntax comes in these variants:</p>
<dt>1. [adsense:<em>format:group:channel</em>]</dt>
<p>Where:</p>
<ul>
 <li>format: one of the supported ad formats (e.g. 468x60)</li>
 <li>group: a number corresponding to the ad group this ad belongs to, determines colors</li>
 <li>channel: a number corresponding to the ad channel</li>
</ul>
<p>All fields are required, unlike when using the adsense_display() function above.</p>
<p>Example:</p>
<pre>[adsense:468x60:1:2]</pre>
<p>Display a 468x60 banner with the colors defined in group 1, and with channel ID 2</p>

<dt>2. [adsense:block:<em>block_id</em>]</dt>
<p>Where:</p>
<ul>
 <li>block_id: The block ID of a custom block with input format of PHP with a call to the adsense_display() function.</li>
</ul>
<p>This allows more finegrained visibility control via the block mechanism. The block does not need to be enabled, and therefore will be hidden from the sidebars and other regions. The title of the block will not be displayed.</p>
<p>All fields are required.</p>

<p>Example:</p>
<pre>[adsense:block:7]</pre>
<p>Display the ad code of the block with ID 7.</p>
</ul>

<dt>3. [adsense:flexiblock:<em>location</em>]</dt>
<p>This is provided for backward compatibility, but will be deprecated in a future release. Use the normal block filter instead.</p>
<p>Where:</p>
<ul>
 <li>location: a number corresponding to a location in flexiblock that contains only one block with the call to the adsense_display() function.  This allows visibility control via the block mechanism. flexiblock must be installed and configured. The title of the flexiblock will not be displayed.</li>
</ul>
<p>All fields are required.</p>

<p>Example:</p>
<pre>[adsense:flexiblock:2]</pre>
<p>Display the contents of the flexiblock in location 2</p>


<h2>Revenue Sharing</h2>
<p>For revenue sharing, each author gets an predefined share of ad revenue from clicks occuring on nodes they authored.</p>
<p>In order for the user to be credited they must have a Google AdSense account before getting ad revenue. As a site admin, please advertise <a href="http://baheyeldin.com/click/476/1">the module\'s author referral link</a>, which provides us with a referral fee from Google, with absolutely no cost to you. This page also contains various useful links and resources on Adsense, and how to optimize your site for it.</p>
<p>Each user must enter their Google Adsense Client ID in the profile field you defined above.</p>

<h2>Adsense Clicks</h2>
<p>Adsense clicks are now tracked, and the IP address and timestamp recorded for each click. This should help with fraud detection. There are three reports under administer -> logs: the default one shows click details, the by date shows the number of clicks per day by day, and the top pages shows the top pages of a site that get clicks, the total number of clicks it got, and the last click date/time.</p>
<p>Note that there are some potential limitations with click tracking, such as:</p>
<ul>
<li>The javascript code does not work in Firefox, and perhaps Opera. Patches to make it work on Firefox are appreciated.</li>
<li>Google throws out what it sees as invalid clicks.</li>
<li>There is a lag of 15 to 20 minutes before Google records the click.</li>
<li>When using AdLinks. The click on the link is recorded but any subsequent click on links is not recorded (since it is not actually on your site anymore).
</li>

<h2>Notes</h2>
<p>
The site administrator will not see ads displayed as long as they are logged in.
This is by design, in order not to skew the page views, and not to accidentally
click on ads (against Google\'s policy). Log out to see the ads.</p>
<p>
You can use the advanced options to disable ads and configure a placeholder when
you are developing or theming to know where the ads will appear.</p>
<p>
If ads are not displayed, that could be caused by several things:</p>
<ul>
<li>You are logged in as the site administrator. Log off to see the ads.</li>
<li>Your site is still new and Google did not index it yet.</li>
<li>The maximum possible ad units to display have already been displayed. Your
 page does not have enough content to display more than one or two units.</li>

<li>Check the page source for comments like this <!--adsense: ???-->. These tell
 more what is going on, and if you know PHP you can trace those in the module\'s
 source code.</li>
</ul>');
}
