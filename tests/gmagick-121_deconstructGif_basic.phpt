--TEST--
Test Tutorial, deconstructGif
--SKIPIF--
<?php

require_once(dirname(__FILE__) . '/skipif.inc');

checkClassMethods("GmagickDraw", array('circle', 'translate'));

?>
--FILE--
<?php

$deconstruct = 1;

function makeSimpleGif($deconstruct) {
    $aniGif = new \Gmagick();
    $aniGif->setFormat("gif");

    $circleRadius = 20;
    $imageFrames = 6;
    $imageSize = 200;

    $background = new \Gmagick();
    $background->newImage($imageSize, $imageSize, "gray");

    $blackWhite = new \Gmagick();
    $blackWhite->newImage($imageSize, $imageSize, "white");

    $backgroundPalette = clone $background;
    $backgroundPalette->quantizeImage(240, \Gmagick::COLORSPACE_RGB, 8, false, false);

    $blackWhitePalette = clone $blackWhite;
    $blackWhitePalette->quantizeImage(16, \Gmagick::COLORSPACE_RGB, 8, false, false);

    $backgroundPalette->addimage($blackWhitePalette);

    for($count=0 ; $count<$imageFrames ; $count++) {
        echo "Frame: ".$count."\n";
        $drawing = new \GmagickDraw();
        $drawing->setFillColor('white');
        $drawing->setStrokeColor('rgba(64, 64, 64, 0.8)');
        $strokeWidth = 4;
        $drawing->setStrokeWidth($strokeWidth);
        
        $distanceToMove = $imageSize + (($circleRadius + $strokeWidth) * 2);
        $offset = ($distanceToMove * $count / ($imageFrames -1)) - ($circleRadius + $strokeWidth);
        $drawing->translate(
             $offset,
             ($imageSize / 2) + ($imageSize / 3 * cos(20 * $count / $imageFrames))
        );
        $drawing->circle(0, 0, $circleRadius, 0);

        $frame = clone $background;
        $frame->drawimage($drawing);
        $frame->clutimage($backgroundPalette);
        $frame->setImageDelay(10);
        $aniGif->addImage($frame);
    }

    if ($deconstruct == true) {
        $aniGif = $aniGif->deconstructImages();
    }

    $bytes = $aniGif->getImagesBlob();
    if (strlen($bytes) <= 0) { echo "Failed to generate image.";} 
}

makeSimpleGif($deconstruct) ;
echo "Ok";
?>
--EXPECTF--
Frame: 0
Frame: 1
Frame: 2
Frame: 3
Frame: 4
Frame: 5
Ok