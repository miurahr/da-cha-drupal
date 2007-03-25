<?php if ($page == 0): ?>
    <h2><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
<?php endif; ?>
  <?php print $content ?>
  <?php print $submitted ?>
  </div>
<?php if ($links): ?>
  <?php print $links ?>
<?php endif; ?>

