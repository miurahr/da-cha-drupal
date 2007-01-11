<?php 
  //  Content region needs different wrapper divs
if ($block->region =='content') { ?>
<div class="content<?php echo $layoutcode ?>-container line-box">
  <div class="content<?php echo $layoutcode ?>-container-1col">
    <p class="content-title-shade-size3 bg-blue03 txt-white"><?php print $box->subject?></p>
    <div class="content-txtbox-shade">
     <?php print ($block->content) ?>
   </div>
  </div>
</div>
<?php }
// Test to see if the main menu is being output.  If so,
// use a special class to format it properly

elseif ($block->module == 'user' and $block->delta == '1') { ?>

  <p class="sidebar-title-noshade bg-blue07">
    <?php print "$block->subject"; ?></p>
      <div class="sidebar-txtbox-noshade bg-blue02 mainmenu">  
  <ul>
    <?php print $block->content; ?>
  </ul>
</div>

<?php } else 

	  // normal sidebar
      { 
      $colours = array("red","yellow","green","blue");
      $colour=$colours[$block_id % 4];
      // a bit of a fudge, but it will do for now.
      ?>
<p class="sidebar-title-noshade bg-<?php print $colour ?>07">
  <?php print "$block->subject"; ?></p>
<div class="sidebar-txtbox-noshade bg-<?php print $colour ?>03">
  <?php print $block->content; ?>
</div>	


<?php } ; ?>
