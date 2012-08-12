--TEST--
Test affine
--SKIPIF--
<?php
/* $Id: gmagickdraw-025-affine.phpt 280206 2010-08-07 12:46:00Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
    $gDraw = new GmagickDraw();
    $affineArray = array("sx" => 1, "rx" => 0, "ry" => 0, "sy" =>1, "tx" => 0, "ty" => 0);
    $gDraw->affine($affineArray);
    echo "ok";
?>
--EXPECT--
ok
