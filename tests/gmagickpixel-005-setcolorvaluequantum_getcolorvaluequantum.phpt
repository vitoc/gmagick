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
try {
    $gp->setColorValueQuantum(123456, 1);
    echo "GmagickPixelException was not thrown".PHP_EOL;
} catch (GmagickPixelException $gpe) {
    //This is the expected exception
    echo $gpe->getMessage();
}
?>
--EXPECTF--
0
1
Unknown color type: 123456
