--TEST--
Gmagick::readImageBlob
--SKIPIF--
<?php
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$image = new Gmagick('magick:rose');
$image->setImageFormat('png');
$imageBlob = $image->getImageBlob();

$imageReload = new Gmagick();
$imageReload->readImageBlob($imageBlob);
printf(
    "Dimensions are %d x %d\n",
    $imageReload->getImageWidth(),
    $imageReload->getImageHeight()
);
echo "ok";

?>
--EXPECTF--
Dimensions are 70 x 46
ok