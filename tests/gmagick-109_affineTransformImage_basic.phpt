--TEST--
Test Gmagick, affineTransformImage
--SKIPIF--
<?php
$imageMagickRequiredVersion=0x675;
require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php


function affineTransformImage() {
    $gmagick = new \Gmagick("magick:logo");
    $draw = new \GmagickDraw();

    $angle = 40 ;

    $affineRotate = array(
        "sx" => cos($angle), "sy" => cos($angle), 
        "rx" => sin($angle), "ry" => -sin($angle), 
        "tx" => 0, "ty" => 0,
    );

    $draw->affine($affineRotate);

    $gmagick->affineTransformImage($draw);

    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

affineTransformImage() ;
echo "Ok";
?>
--EXPECTF--
Ok