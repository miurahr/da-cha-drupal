<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language ?>" xml:lang="<?php print $language ?>">

  <head>
    <title><?php print $head_title ?></title>
    <meta http-equiv="content-type" content="text/html; charset=iso-8859-1" />
    <meta name="description" content="Your description goes here" />
    <meta name="keywords" content="your,keywords,come,here" />
    <?php print $head ?>
    <?php print theme('stylesheet_import', base_path() . path_to_theme() . '/css/style_screen.css', 'screen');?>
    <?php print theme('stylesheet_import', base_path() . path_to_theme() . '/css/style_print.css', 'print');?>
<?php print theme('stylesheet_import', base_path() . path_to_theme() . '/css/style_override.css', 'all');?>
<?php print $styles ?>
  </head>

  <body<?php print theme("onload_attribute");?>>
    <div class="page-container-<?php echo $layoutcode ?>">

      <!-- HEADER -->
      <!-- Flag navigations -->
      <div class="navflag-container">
	<div class="navflag">

	</div>
      </div>
      
      <!-- Navigation Level 1-->
      <div class="nav1-container">
	<div class="nav1">
	  <?php if (is_array($secondary_links)) : ?>
	  <ul>
	    <?php foreach ($secondary_links as $link): ?>
	    <li><?php print $link?></li>
	    <?php endforeach; ?>
	  </ul>
	  <?php endif; ?>
	</div>
      </div>

      <!-- Sitename -->
      <div class="site-name">
	<?php if ($site_name) { ?><p class="title"><a href="<?php print $base_path ?>"><?php print $site_name ?></a></p><?php } ?>
      </div>
      <!-- Site slogan -->
      <div class="site-slogan-container">
	<div class="site-slogan">
	  <p class="text"><?php if ($site_slogan) { print($site_slogan); } // you could try class='title' or class='subtitle' for bigger text?>
	  </p>
      	  

	</div>
      </div>
      <!-- Header banner -->
      <div><img class="img-header" src="<?php print base_path() . path_to_theme() ?>/img/header.gif" alt=""/></div>

      <!-- Navigation Level 2-->
      <div class="nav2">
	<?php if (is_array($primary_links)) : ?>
	<ul>
	  <?php foreach ($primary_links as $link): ?>
	  <li> <?php print $link?> </li>
	  <?php endforeach; ?>
	</ul>
	<?php endif; ?>
      </div>

      <!-- Buffer after header -->
      <div class="buffer"></div>

      <!-- Left block-->
      <?php if ($sidebar_left != ""): ?>
      <div class="mainnav">
	<?php print $sidebar_left ?>
      </div>
      <?php endif; ?>
      
      <!-- CONTENT -->
      <div class="content<?php echo $layoutcode ?>">

	<?php if ($mission) { ?><div id="mission"><h3><?php print $mission ?></h3></div><?php } ?>
	<!-- Page title -->
	<?php print $breadcrumb ?>
	<?php if ($title != ""): ?>
	<div class="content<?php echo $layoutcode ?>-pagetitle"><?php print ($title) ?></div>
	<?php endif; ?>
	<?php if ($tabs) { ?>
	<?php print ($tabs) ?>
	<?php ; } ?>
	<?php if ($help) { ?>
	<div class="content<?php echo $layoutcode ?>-container line-box">
	  <div class="content<?php echo $layoutcode ?>-container-1col">
	    <div class="content-txtbox-shade bg-green02 txt-green10">
	      <?php print ($help) ?>
	    </div>
	  </div>
	</div>
	<?php } ?>
	<?php if ($messages) { ?>
	<div class="content<?php echo $layoutcode ?>-container line-box">
	  <div class="content<?php echo $layoutcode ?>-container-1col">
	    <div class="content-txtbox-shade bg-yellow04">
	      <?php print ($messages) ?>
	    </div>
	  </div>
	</div>
	<?php } ?>
	
	<!-- Content -->
	<div class="content<?php echo $layoutcode ?>-container">
	  <?php print($content) ?>
	</div>
      </div>
      

      <!-- SIDEBAR -->
      <?php if ($sidebar_right != ""): ?>
      <div class="sidebar">
	<?php print $sidebar_right ?>
      </div>
      <?php endif; ?>

      

      <!-- FOOTER -->
      <div class="footer">
	<?php if ($footer_message != ""): ?>
	<p><?php print $footer_message ?></p>
	<?php endif; ?>
	<p>Based on a design by G. Wolfgang | <a href="http://validator.w3.org/check?uri=referer" title="Validate code as W3C XHTML 1.1 Strict Compliant">W3C XHTML 1.0</a> | <a href="http://jigsaw.w3.org/css-validator/" title="Validate Style Sheet as W3C CSS 2.0 Compliant">W3C CSS 2.0</a></p>
      </div>
    </div>
    <?php print $closure ?>
  </body>
</html>
