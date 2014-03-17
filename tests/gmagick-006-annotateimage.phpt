--TEST--
Test annotate image
--SKIPIF--
<?php
/* $Id: gmagick-006-annotateimage.phpt 333024 2014-03-17 05:37:54Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new GMagick();
$gd = new GMagickDraw();
$gm->read("magick:rose");

$fonts = $gm->queryFonts();

if (!empty($fonts))
    $gd->setFont($fonts[0]);

$gm->annotateImage($gd, 5, 15, 0, 'Test Text');
echo "ok";
?>
--EXPECT--
ok
