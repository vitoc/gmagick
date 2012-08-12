--TEST--
thresholdImage test
--SKIPIF--
<?php
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$image = new Gmagick('magick:rose');
$image->thresholdImage(2);
echo "ok";
?>
--EXPECTF--
ok
