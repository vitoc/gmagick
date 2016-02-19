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
$gp->setColorValueQuantum(123456,1);
?>
--EXPECTF--
0
1

Fatal error: Uncaught GmagickPixelException: Unknown color type: 123456 in %s/tests/gmagickpixel-005-setcolorvaluequantum_getcolorvaluequantum.php:6
Stack trace:
#0 %s/tests/gmagickpixel-005-setcolorvaluequantum_getcolorvaluequantum.php(6): GmagickPixel->setcolorvaluequantum(123456, 1)
#1 {main}
  thrown in %s/tests/gmagickpixel-005-setcolorvaluequantum_getcolorvaluequantum.php on line 6