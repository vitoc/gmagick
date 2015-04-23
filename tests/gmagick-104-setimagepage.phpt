--TEST--
setImagePage test
--SKIPIF--
<?php
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$image = new Gmagick('magick:rose');
$image->setImagePage(10,10,10,10);
echo "ok";
?>
--EXPECTF--
ok
