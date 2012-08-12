--TEST--
Test bezier
--SKIPIF--
<?php
/* $Id: gmagickdraw-005-bezier.phpt 280206 2009-05-09 18:22:48Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$filename = dirname(__FILE__) . '/test_constructor.jpg';
$gm = new GMagick();
$gd = new GMagickDraw();
$gm->read("magick:rose");
$gd->bezier( array(
                    array( "x" => 3 , "y" => 8 ),
                    array( "x" => 13, "y" => 16 ),
                    array( "x" => 20, "y" => 25 ),
                    array( "x" => 25, "y" => 23 ),
                    array( "x" => 33, "y" => 23 ),
                    array( "x" => 33, "y" => 3 ),
                 ) );
$gm->drawImage($gd);
$gm->write($filename);
unlink($filename);
echo "ok";
?>
--EXPECT--
ok