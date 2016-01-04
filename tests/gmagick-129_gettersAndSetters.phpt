--TEST--
Test static methods
--SKIPIF--
<?php require_once(dirname(__FILE__) . '/skipif.inc'); ?>
--FILE--
<?php

$gmagick = new \Gmagick("magick:logo");





$gmagick->getImageGravity();
$gmagick->getImageVirtualPixelMethod();
$gmagick->getImageBackgroundColor();
$gmagick->getImageBluePrimary();
$gmagick->getImageBorderColor();
$gmagick->getImagesBlob();
$gmagick->getImageColorspace();
$gmagick->getImageCompose();
$gmagick->getImageDelay();
$gmagick->getImageDepth();
$gmagick->getImageCompression();
$gmagick->getImageDispose();
$gmagick->getImageExtrema();
$gmagick->getImageFilename();
$gmagick->getImageFormat();
$gmagick->getImageGamma();
$gmagick->getImageGreenPrimary();
$gmagick->getImageIndex();
$gmagick->getImageInterlaceScheme();
$gmagick->getImageIterations();
$gmagick->getImageMatteColor();
$gmagick->getImagePage();
$gmagick->getImageRedPrimary();
$gmagick->getImageRenderingIntent();
$gmagick->getImageResolution();
$gmagick->getImageScene();
$gmagick->getImageBoundingbox(0.1);
$gmagick->getImageFuzz();
$gmagick->getImageSavedType();

$gmagick->getImageType();
$gmagick->getImageUnits();
$gmagick->getImageWhitepoint();

$gmagick->getSamplingfactors();
$gmagick->getSize();
$gmagick->getImageGeometry();
$gmagick->setImageAttribute("comment", "this is a comment");
$gmagick->setImageColormapColor(0, 'red');
$gmagick->setImageGravity(\GMAGICK::GRAVITY_SOUTHWEST);
$gmagick->setImageMatteColor('pink');
$gmagick->setDepth(16);
$gmagick->setImageFuzz(0.1 * \GMAGICK::QUANTUM);
$gmagick->setImageOption("jpeg", "preserve-settings", "true");
$gmagick->setImageSavedType(\GMAGICK::IMGTYPE_TRUECOLOR);
$gmagick->setResolutionUnits(\GMAGICK::RESOLUTION_PIXELSPERCENTIMETER);
$gmagick->setImageIndex(0);
$gmagick->setInterlaceScheme(\GMAGICK::INTERLACE_PLANE);
$gmagick->setImageCompression(\GMAGICK::COMPRESSION_NO);
$gmagick->setImageFormat("BMP");

$gmagick->setResourceLimit(\GMAGICK::RESOURCETYPE_MEMORY, 16*1024*1024);
$gmagick->getImageAttribute("comment");
$gmagick->getImageChannelExtrema(\GMAGICK::CHANNEL_RED);
$gmagick->getImageChannelMean(\GMAGICK::CHANNEL_RED);
$gmagick->getImageColormapColor(0);
$gmagick->getImageChannelDepth(\GMAGICK::CHANNEL_RED);
$gmagick->getResourceLimit(\GMAGICK::RESOURCETYPE_MEMORY);

// Don't know how to call this successfully.
// $gmagick->get ImageProfile("ICC");


echo 'ok';

?>
--EXPECT--
ok