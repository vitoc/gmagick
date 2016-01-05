--TEST--
Test GmagickDraw, circle
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$backgroundColor = 'rgb(225, 225, 225)';
$strokeColor = 'rgb(0, 0, 0)';
$fillColor = 'DodgerBlue2';
$originX = 250;
$originY = 250;
$endX = 400;
$endY = 400;

function circle($strokeColor, $fillColor, $backgroundColor, $originX, $originY, $endX, $endY) {

    //Create a GmagickDraw object to draw into.
    $draw = new \GmagickDraw();

    $strokeColor = new \GmagickPixel($strokeColor);
    $fillColor = new \GmagickPixel($fillColor);

    $draw->setStrokeOpacity(1);
    $draw->setStrokeColor($strokeColor);
    $draw->setFillColor($fillColor);

    $draw->setStrokeWidth(2);
    $draw->setFontSize(72);

    $draw->circle($originX, $originY, $endX, $endY);

    $imagick = new \Gmagick();
    $imagick->newImage(500, 500, $backgroundColor);
    $imagick->setImageFormat("png");
    $imagick->drawImage($draw);

    $bytes = $imagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

circle($strokeColor, $fillColor, $backgroundColor, $originX, $originY, $endX, $endY) ;
echo "Ok";
?>
--EXPECTF--
Ok