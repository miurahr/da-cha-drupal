<?php
// $Id: block.tpl.php,v 1.3.4.3 2008/04/24 07:38:49 hswong3i Exp $
?>
<div id="block-<?php print $block->module .'-'. $block->delta ?>" class="block block-<?php print $block->module ?>">
  <?php if ($block->subject): ?><h2><?php print $block->subject ?></h2><?php endif; ?>
  <div class="content"><?php print $block->content ?></div>
</div>
