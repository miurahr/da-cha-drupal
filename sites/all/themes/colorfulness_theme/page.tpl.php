<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>">
<!-- Theme Design by niGraphic.com -->
<head>
  <title><?php print $head_title ?></title>
  <?php print $head ?>
  <?php print $styles ?>	
  <?php print $scripts ?>
  <script type="text/javascript"><?php /* Needed to avoid Flash of Unstyle Content in IE */ ?> </script>
  </head>
<body>
<div id="pagewidth">
	<div id="header">
		<div id="HeaderWidth">
		<div id="HeaderWrapper" class="clearfix">
			<div id="HeaderTwocols" class="clearfix">
				<div id="HeaderMenu">
					<?php if (isset($primary_links)) { ?><?php print theme('links', $primary_links, array('class' =>'linksTop', 'id' => 'navlist')) ?><?php } ?> </div>
			</div>
			<div id="HeaderSearch">
				<?php print $search_box ?></div>
		</div>
		<div id="logo">
			<?php if ($site_name) { ?><h1 class='site-name'><a href="<?php print $base_path ?>" title="<?php print $site_name ?>"><?php print $site_name ?></a></h1><?php } ?>
			<?php if ($site_slogan) { ?><div class='site-slogan'><?php print $site_slogan ?></div><?php } ?></div>
		</div>
	</div>
	<div id="wrapper" class="clearfix">
		<div id="twocols<?php if (!$left) {print "NoLeft";}?>" class="clearfix">
			<div id="maincol">
				<?php print $breadcrumb ?>
				<h1 class="title"><?php print $title ?></h1>
				<div class="tabs"><?php print $tabs ?></div>
				<?php print $help ?>
				<?php print $messages ?>
				<?php print $content; ?>
				<?php print $feed_icons; ?>
			</div>
				
		<?php if ($right) { ?>
			<div id="rightcol">
				<?php print $right ?>
			</div>
		<?php } ?>
		</div>
		
	<?php if ($left) { ?>
		<div id="leftcol">
      		<?php print $left ?>
    	</div>
	<?php } ?>
	</div>
	<div id="footer">
		<?php print $footer_message ?> 
		<br/><a href="http://www.nigraphic.com" title="Web Design & Photography"> Design by niGraphic</a></div>
</div>
<?php print $closure ?>
</body>
</html>
