--TEST--
cloneimage test
--SKIPIF--
<?php
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$image = new Gmagick('magick:rose');
$cloned = $image->cloneimage();
echo "ok";
?>
--EXPECTF--
ok
