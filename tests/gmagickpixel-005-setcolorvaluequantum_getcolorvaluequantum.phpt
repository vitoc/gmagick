--TEST--
Test setColorValueQuantum and getColorValueQuantum methods
--SKIPIF--
<?php
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gp = new GMagickPixel();
echo $gp->getColorValueQuantum(Gmagick::COLOR_BLACK). "\n";
$gp->setColorValueQuantum(Gmagick::COLOR_BLACK,1);
echo $gp->getColorValueQuantum(Gmagick::COLOR_BLACK). "\n";
?>
--EXPECTF--
0
1