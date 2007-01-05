<?php
function form_colorpicker($title, $name, $value, $description = NULL, $required = FALSE) {
	static $colorpickerjs = NULL;
	
	if(is_null($colorpickerjs)){
		$colorpickerjs = _add_colorpickerjs($name);
	}

	$output = '<input type="text" name="edit['. $name .']" id="edit-'. $name .'" value="'. $value .'" size=15 style="font-size: 12px">';
	$output = '
<!-- start colorpicker -->	

<table border="0px" cellspacing="0px" cellpadding="4" width="240">
 <tr>
  <td style="background:buttonface" valign=center><div style="background-color: '. $value .'; padding: 1; height: 21px; width: 50px"><div id="ColorPrepickerView_'. $name .'" style="height: 100%; width: 100%"></div></div></td>
  <td style="background:buttonface" valign=center>'.$output.'</td>
  <td style="background:buttonface" width=100%></td>
 </tr>
</table>
<table border="0" cellspacing="1px" cellpadding="0px" width="240" bgcolor="#000000" style="cursor: hand;">
<tr>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#003300"  onClick="pickerSet(\'003300\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#006600"  onClick="pickerSet(\'006600\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#009900"  onClick="pickerSet(\'009900\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#00CC00"  onClick="pickerSet(\'00CC00\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#00FF00"  onClick="pickerSet(\'00FF00\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#330000"  onClick="pickerSet(\'330000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#333300"  onClick="pickerSet(\'333300\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#336600"  onClick="pickerSet(\'336600\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#339900"  onClick="pickerSet(\'339900\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#33CC00"  onClick="pickerSet(\'33CC00\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#33FF00"  onClick="pickerSet(\'33FF00\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#660000"  onClick="pickerSet(\'660000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#663300"  onClick="pickerSet(\'663300\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#666600"  onClick="pickerSet(\'666600\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#669900"  onClick="pickerSet(\'669900\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#66CC00"  onClick="pickerSet(\'66CC00\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#66FF00"  onClick="pickerSet(\'66FF00\',\''. $name .'\')" height="10px" width="10px"></td>
</tr>
<tr>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#333333"  onClick="pickerSet(\'333333\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#000033"  onClick="pickerSet(\'000033\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#003333"  onClick="pickerSet(\'003333\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#006633"  onClick="pickerSet(\'006633\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#009933"  onClick="pickerSet(\'009933\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#00CC33"  onClick="pickerSet(\'00CC33\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#00FF33"  onClick="pickerSet(\'00FF33\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#330033"  onClick="pickerSet(\'330033\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#333333"  onClick="pickerSet(\'333333\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#336633"  onClick="pickerSet(\'336633\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#339933"  onClick="pickerSet(\'339933\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#33CC33"  onClick="pickerSet(\'33CC33\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#33FF33"  onClick="pickerSet(\'33FF33\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#660033"  onClick="pickerSet(\'660033\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#663333"  onClick="pickerSet(\'663333\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#666633"  onClick="pickerSet(\'666633\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#669933"  onClick="pickerSet(\'669933\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#66CC33"  onClick="pickerSet(\'66CC33\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#66FF33"  onClick="pickerSet(\'66FF33\',\''. $name .'\')" height="10px" width="10px"></td>
</tr>
<tr>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#666666"  onClick="pickerSet(\'666666\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#000066"  onClick="pickerSet(\'000066\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#003366"  onClick="pickerSet(\'003366\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#006666"  onClick="pickerSet(\'006666\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#009966"  onClick="pickerSet(\'009966\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#00CC66"  onClick="pickerSet(\'00CC66\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#00FF66"  onClick="pickerSet(\'00FF66\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#330066"  onClick="pickerSet(\'330066\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#333366"  onClick="pickerSet(\'333366\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#336666"  onClick="pickerSet(\'336666\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#339966"  onClick="pickerSet(\'339966\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#33CC66"  onClick="pickerSet(\'33CC66\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#33FF66"  onClick="pickerSet(\'33FF66\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#660066"  onClick="pickerSet(\'660066\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#663366"  onClick="pickerSet(\'663366\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#666666"  onClick="pickerSet(\'666666\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#669966"  onClick="pickerSet(\'669966\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#66CC66"  onClick="pickerSet(\'66CC66\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#66FF66"  onClick="pickerSet(\'66FF66\',\''. $name .'\')" height="10px" width="10px"></td>
</tr>
<tr>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#999999"  onClick="pickerSet(\'999999\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#000099"  onClick="pickerSet(\'000099\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#003399"  onClick="pickerSet(\'003399\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#006699"  onClick="pickerSet(\'006699\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#009999"  onClick="pickerSet(\'009999\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#00CC99"  onClick="pickerSet(\'00CC99\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#00FF99"  onClick="pickerSet(\'00FF99\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#330099"  onClick="pickerSet(\'330099\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#333399"  onClick="pickerSet(\'333399\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#336699"  onClick="pickerSet(\'336699\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#339999"  onClick="pickerSet(\'339999\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#33CC99"  onClick="pickerSet(\'33CC99\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#33FF99"  onClick="pickerSet(\'33FF99\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#660099"  onClick="pickerSet(\'660099\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#663399"  onClick="pickerSet(\'663399\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#666699"  onClick="pickerSet(\'666699\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#669999"  onClick="pickerSet(\'669999\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#66CC99"  onClick="pickerSet(\'66CC99\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#66FF99"  onClick="pickerSet(\'66FF99\',\''. $name .'\')" height="10px" width="10px"></td>
</tr>
<tr>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CCCCCC"  onClick="pickerSet(\'CCCCCC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#0000CC"  onClick="pickerSet(\'0000CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#0033CC"  onClick="pickerSet(\'0033CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#0066CC"  onClick="pickerSet(\'0066CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#0099CC"  onClick="pickerSet(\'0099CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#00CCCC"  onClick="pickerSet(\'00CCCC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#00FFCC"  onClick="pickerSet(\'00FFCC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#3300CC"  onClick="pickerSet(\'3300CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#3333CC"  onClick="pickerSet(\'3333CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#3366CC"  onClick="pickerSet(\'3366CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#3399CC"  onClick="pickerSet(\'3399CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#33CCCC"  onClick="pickerSet(\'33CCCC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#33FFCC"  onClick="pickerSet(\'33FFCC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#6600CC"  onClick="pickerSet(\'6600CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#6633CC"  onClick="pickerSet(\'6633CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#6666CC"  onClick="pickerSet(\'6666CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#6699CC"  onClick="pickerSet(\'6699CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#66CCCC"  onClick="pickerSet(\'66CCCC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#66FFCC"  onClick="pickerSet(\'66FFCC\',\''. $name .'\')" height="10px" width="10px"></td>
</tr>
<tr>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FFFFFF"  onClick="pickerSet(\'FFFFFF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#0000FF"  onClick="pickerSet(\'0000FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#0033FF"  onClick="pickerSet(\'0033FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#0066FF"  onClick="pickerSet(\'0066FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#0099FF"  onClick="pickerSet(\'0099FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#00CCFF"  onClick="pickerSet(\'00CCFF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#00FFFF"  onClick="pickerSet(\'00FFFF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#3300FF"  onClick="pickerSet(\'3300FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#3333FF"  onClick="pickerSet(\'3333FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#3366FF"  onClick="pickerSet(\'3366FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#3399FF"  onClick="pickerSet(\'3399FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#33CCFF"  onClick="pickerSet(\'33CCFF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#33FFFF"  onClick="pickerSet(\'33FFFF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#6600FF"  onClick="pickerSet(\'6600FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#6633FF"  onClick="pickerSet(\'6633FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#6666FF"  onClick="pickerSet(\'6666FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#6699FF"  onClick="pickerSet(\'6699FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#66CCFF"  onClick="pickerSet(\'66CCFF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#66FFFF"  onClick="pickerSet(\'66FFFF\',\''. $name .'\')" height="10px" width="10px"></td>
</tr>
<tr>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF0000"  onClick="pickerSet(\'FF0000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#990000"  onClick="pickerSet(\'990000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#993300"  onClick="pickerSet(\'993300\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#996600"  onClick="pickerSet(\'996600\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#999900"  onClick="pickerSet(\'999900\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#99CC00"  onClick="pickerSet(\'99CC00\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#99FF00"  onClick="pickerSet(\'99FF00\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC0000"  onClick="pickerSet(\'CC0000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC3300"  onClick="pickerSet(\'CC3300\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC6600"  onClick="pickerSet(\'CC6600\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC9900"  onClick="pickerSet(\'CC9900\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CCCC00"  onClick="pickerSet(\'CCCC00\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CCFF00"  onClick="pickerSet(\'CCFF00\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF0000"  onClick="pickerSet(\'FF0000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF3300"  onClick="pickerSet(\'FF3300\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF6600"  onClick="pickerSet(\'FF6600\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF9900"  onClick="pickerSet(\'FF9900\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FFCC00"  onClick="pickerSet(\'FFCC00\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FFFF00"  onClick="pickerSet(\'FFFF00\',\''. $name .'\')" height="10px" width="10px"></td>
</tr>
<tr>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#00FF00"  onClick="pickerSet(\'00FF00\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#990033"  onClick="pickerSet(\'990033\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#993333"  onClick="pickerSet(\'993333\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#996633"  onClick="pickerSet(\'996633\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#999933"  onClick="pickerSet(\'999933\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#99CC33"  onClick="pickerSet(\'99CC33\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#99FF33"  onClick="pickerSet(\'99FF33\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC0033"  onClick="pickerSet(\'CC0033\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC3333"  onClick="pickerSet(\'CC3333\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC6633"  onClick="pickerSet(\'CC6633\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC9933"  onClick="pickerSet(\'CC9933\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CCCC33"  onClick="pickerSet(\'CCCC33\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CCFF33"  onClick="pickerSet(\'CCFF33\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF0033"  onClick="pickerSet(\'FF0033\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF3333"  onClick="pickerSet(\'FF3333\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF6633"  onClick="pickerSet(\'FF6633\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF9933"  onClick="pickerSet(\'FF9933\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FFCC33"  onClick="pickerSet(\'FFCC33\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FFFF33"  onClick="pickerSet(\'FFFF33\',\''. $name .'\')" height="10px" width="10px"></td>
</tr>
<tr>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#0000FF"  onClick="pickerSet(\'0000FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#990066"  onClick="pickerSet(\'990066\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#993366"  onClick="pickerSet(\'993366\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#996666"  onClick="pickerSet(\'996666\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#999966"  onClick="pickerSet(\'999966\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#99CC66"  onClick="pickerSet(\'99CC66\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#99FF66"  onClick="pickerSet(\'99FF66\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC0066"  onClick="pickerSet(\'CC0066\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC3366"  onClick="pickerSet(\'CC3366\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC6666"  onClick="pickerSet(\'CC6666\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC9966"  onClick="pickerSet(\'CC9966\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CCCC66"  onClick="pickerSet(\'CCCC66\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CCFF66"  onClick="pickerSet(\'CCFF66\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF0066"  onClick="pickerSet(\'FF0066\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF3366"  onClick="pickerSet(\'FF3366\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF6666"  onClick="pickerSet(\'FF6666\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF9966"  onClick="pickerSet(\'FF9966\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FFCC66"  onClick="pickerSet(\'FFCC66\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FFFF66"  onClick="pickerSet(\'FFFF66\',\''. $name .'\')" height="10px" width="10px"></td>
</tr>
<tr>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FFFF00"  onClick="pickerSet(\'FFFF00\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#990099"  onClick="pickerSet(\'990099\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#993399"  onClick="pickerSet(\'993399\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#996699"  onClick="pickerSet(\'996699\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#999999"  onClick="pickerSet(\'999999\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#99CC99"  onClick="pickerSet(\'99CC99\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#99FF99"  onClick="pickerSet(\'99FF99\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC0099"  onClick="pickerSet(\'CC0099\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC3399"  onClick="pickerSet(\'CC3399\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC6699"  onClick="pickerSet(\'CC6699\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC9999"  onClick="pickerSet(\'CC9999\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CCCC99"  onClick="pickerSet(\'CCCC99\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CCFF99"  onClick="pickerSet(\'CCFF99\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF0099"  onClick="pickerSet(\'FF0099\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF3399"  onClick="pickerSet(\'FF3399\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF6699"  onClick="pickerSet(\'FF6699\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF9999"  onClick="pickerSet(\'FF9999\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FFCC99"  onClick="pickerSet(\'FFCC99\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FFFF99"  onClick="pickerSet(\'FFFF99\',\''. $name .'\')" height="10px" width="10px"></td>
</tr>
<tr>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#00FFFF"  onClick="pickerSet(\'00FFFF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#9900CC"  onClick="pickerSet(\'9900CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#9933CC"  onClick="pickerSet(\'9933CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#9966CC"  onClick="pickerSet(\'9966CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#9999CC"  onClick="pickerSet(\'9999CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#99CCCC"  onClick="pickerSet(\'99CCCC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#99FFCC"  onClick="pickerSet(\'99FFCC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC00CC"  onClick="pickerSet(\'CC00CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC33CC"  onClick="pickerSet(\'CC33CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC66CC"  onClick="pickerSet(\'CC66CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC99CC"  onClick="pickerSet(\'CC99CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CCCCCC"  onClick="pickerSet(\'CCCCCC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CCFFCC"  onClick="pickerSet(\'CCFFCC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF00CC"  onClick="pickerSet(\'FF00CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF33CC"  onClick="pickerSet(\'FF33CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF66CC"  onClick="pickerSet(\'FF66CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF99CC"  onClick="pickerSet(\'FF99CC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FFCCCC"  onClick="pickerSet(\'FFCCCC\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FFFFCC"  onClick="pickerSet(\'FFFFCC\',\''. $name .'\')" height="10px" width="10px"></td>
</tr>
<tr>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF00FF"  onClick="pickerSet(\'FF00FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#000000"  onClick="pickerSet(\'000000\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#9900FF"  onClick="pickerSet(\'9900FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#9933FF"  onClick="pickerSet(\'9933FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#9966FF"  onClick="pickerSet(\'9966FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#9999FF"  onClick="pickerSet(\'9999FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#99CCFF"  onClick="pickerSet(\'99CCFF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#99FFFF"  onClick="pickerSet(\'99FFFF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC00FF"  onClick="pickerSet(\'CC00FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC33FF"  onClick="pickerSet(\'CC33FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC66FF"  onClick="pickerSet(\'CC66FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CC99FF"  onClick="pickerSet(\'CC99FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CCCCFF"  onClick="pickerSet(\'CCCCFF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#CCFFFF"  onClick="pickerSet(\'CCFFFF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF00FF"  onClick="pickerSet(\'FF00FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF33FF"  onClick="pickerSet(\'FF33FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF66FF"  onClick="pickerSet(\'FF66FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FF99FF"  onClick="pickerSet(\'FF99FF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FFCCFF"  onClick="pickerSet(\'FFCCFF\',\''. $name .'\')" height="10px" width="10px"></td>
<td bgcolor="#FFFFFF"  onClick="pickerSet(\'FFFFFF\',\''. $name .'\')" height="10px" width="10px"></td>
</tr>
</table>
<!-- end colorpicker -->	
';

  return theme('form_element', 
  				$title, 
  				$output, 
  				$description, 
  				'edit-'. $name, 
  				$required, 
  				_form_get_error($name));
}

function _add_colorpickerjs(){
	$js = '
<!-- colorpicker javascript -->	
<script type="text/javascript">

function pickerView(color, pickerid) {                  // preview color
  document.getElementById("ColorPrepickerView_" + pickerid).style.backgroundColor = "#" + color;
  document.getElementById("edit-" + pickerid).value = "#" + color;
}

function pickerSet(string, pickerid) {                   // select color
  var color = pickerValidateColor(string);
  if (color == null) { alert("Invalid color code: " + string); }        // invalid color
  else {                                                                // valid color
    pickerView(color, pickerid);                          // show selected color
  }
}

function pickerValidateColor(string) {                // return valid color code
  string = string || "";
  string = string + "";
  string = string.toUpperCase();
  var chars = "0123456789ABCDEF";
  var out   = "";

  for (var i=0; i<string.length; i++) {             // remove invalid color chars
    var schar = string.charAt(i);
    if (chars.indexOf(schar) != -1) { out += schar; }
  }

  if (out.length != 6) { return null; }            // check length
  return out;
}

	</script>
';
	drupal_set_html_head($js);
	return $js;
}
?>
