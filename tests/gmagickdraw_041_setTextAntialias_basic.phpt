--TEST--
Test GmagickDraw, popDefs
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$backgroundColor = 'rgb(225, 225, 225)';
$strokeColor = 'rgb(0, 0, 0)';
$fillColor = 'DodgerBlue2';

function popDefs($strokeColor, $fillColor, $backgroundColor) {

    $draw = new \GmagickDraw();

    $draw->setStrokeColor($strokeColor);
    $draw->setFillColor($fillColor);
    $draw->setstrokeOpacity(1);
    $draw->setStrokeWidth(2);
    $draw->setFontSize(72);
    $draw->pushDefs();
    $draw->setStrokeColor('white');
    $draw->rectangle(50, 50, 200, 200);
    $draw->popDefs();

    $draw->rectangle(300, 50, 450, 200);

    $gmagick = new \Gmagick();
    $gmagick->newImage(500, 500, $backgroundColor);
    $gmagick->setImageFormat("png");
    $gmagick->drawImage($draw);

    $bytes = $gmagick->getImageBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

popDefs($strokeColor, $fillColor, $backgroundColor) ;
echo "Ok";
?>
--EXPECTF--
Ok