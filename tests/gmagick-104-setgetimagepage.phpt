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
$result = $image->getImagePage();
if (($result['width'] === 10) && ($result['height'] === 10) 
    && ($result['x'] === 10) && ($result['y'] === 10)) {
    echo "ok";
}
?>
--EXPECTF--
ok