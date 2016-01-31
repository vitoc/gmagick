--TEST--
Test PHP writing to php://memory 
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$gmagick = new Gmagick("magick:logo");
$gmagick->setFormat("png");

$fp = fopen("php://memory", 'r+');
$gmagick->writeImageFile($fp);
rewind($fp);
$memoryBlob = stream_get_contents($fp);
fclose($fp);

//This test depends on getImageBlob working correctly.
$imageBlob = $gmagick->getImageBlob();

//Read the images from the data blobs.
$imageReopened = new Gmagick();
$imageReopened->readImageBlob($imageBlob);
$memoryReopened = new Gmagick();
$memoryReopened->readImageBlob($memoryBlob);

//Compare to see if they are identical.
$result = $imageReopened->compareImages($memoryReopened, \Gmagick::METRIC_MEANABSOLUTEERROR);

if ($result[1] == 0) {
    echo "Reopened images are identical.";
}
else {
    echo "Error, reopened images have changed.";
    var_dump($result);
}

?>
--EXPECTF--
Reopened images are identical.
