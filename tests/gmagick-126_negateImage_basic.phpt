--TEST--
Test Gmagick, negateImage
--SKIPIF--
<?php
$imageMagickRequiredVersion=0x675;
require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php

$grayOnly = 0;
$channel = Gmagick::CHANNEL_DEFAULT;

function negateImage($grayOnly, $channel) {
    $gmagick = new \Gmagick("magick:logo");
    $gmagick->negateImage($grayOnly, $channel);
    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

negateImage($grayOnly, $channel) ;
echo "Ok";
?>
--EXPECTF--
Ok