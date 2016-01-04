--TEST--
Test Tutorial, edgeExtend
--SKIPIF--
<?php
$imageMagickRequiredVersion=0x675;
require_once(dirname(__FILE__) . '/skipif.inc');
?>
--FILE--
<?php

$virtualPixelType = 5;

function edgeExtend($virtualPixelType) {
    $gmagick = new \Gmagick("magick:logo");
    $gmagick->setImageVirtualPixelMethod($virtualPixelType);

    $gmagick->scaleimage(400, 300, true);

    $gmagick->setimagebackgroundcolor('pink');
   
    $desiredWidth = 600;
    $originalWidth = $gmagick->getImageWidth();

    //Make the image be the desired width.
    $gmagick->sampleimage($desiredWidth, $gmagick->getImageHeight());

    //Now scale, rotate, translate (aka affine project) it
    //to be how you want
    $points = array(//The x scaling factor is 0.5 when the desired width is double
        //the source width
        ($originalWidth / $desiredWidth), 0, //Don't scale vertically
        0, 1, //Offset the image so that it's in the centre
        ($desiredWidth - $originalWidth) / 2, 0);

    $amplitude = 5;
    $length = 20;
    $gmagick->waveImage($amplitude, $length);

    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 

//Fyi it may be easier to think of the affine transform by 
//how it works for a rotation:
//$affineRotate = array(
//    "sx" => cos($angle),
//    "sy" => cos($angle),
//    "rx" => sin($angle),
//    "ry" => -sin($angle),
//    "tx" => 0,
//    "ty" => 0,
//);
}

edgeExtend($virtualPixelType) ;
echo "Ok";
?>
--EXPECTF--
Ok